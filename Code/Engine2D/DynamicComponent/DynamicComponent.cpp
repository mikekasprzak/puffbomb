// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include <DynamicCollection/DynamicCollection.h>
#include "DynamicComponent.h"

#include "ComponentAnimationSet/ComponentAnimationSetPool.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// In the case of a component without a parent, if checks should be placed to stop messanging //
cDynamicComponent::cDynamicComponent( ) :
	Parent( 0 )
{
//	std::map< std::string, cComponentAnimationSet > Nurb;
//	AnimationSetIterator = Nurb.find("Newtar.tx");
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicComponent::cDynamicComponent( const cDynamicCollection* const _Parent, const std::string& ComponentFile, const Vector2D& Offset ) :
	Parent( _Parent ),
	AnimationSet( ComponentAnimationSetPool.Load( ComponentFile ) ),

	CurrentAnimation( 0 ),
	CurrentFrame( 0 ),
	CurrentFrameTime( Real::Zero ),
	PlayBackRate( Real::One ),

	Body( AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ], Offset )
{
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Step() {
	// Step the nodes //
	Body.Step();

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update all Springs //
		Body.StepSprings();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::StepAnimation() {
	// Make sure we actually have an associated animation set //
	if ( AnimationSet ) {
		// Step our current frame time forward by our rate of playback //
		CurrentFrameTime += PlayBackRate;
		
		// If our current frame time breaks the hold length of the current frame //
		if ( CurrentFrameTime >= Real( AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Time ) ) {
			// Step to the next frame //
			CurrentFrame++;
			
			// If our frame hits the end //
			if ( CurrentFrame >= AnimationSet->Animation[ CurrentAnimation ].Frame.size() ) {
				// Set frame to the loop point //
				CurrentFrame = AnimationSet->Animation[ CurrentAnimation ].LoopPoint;
				
				// Set animation flags //
			}

			// Update the Pose //
			Body.Pose = &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];
			
			// Offset the Current Frame Time by the hold of the previous, to correctly accumulate //
			CurrentFrameTime -= Real( AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Time );
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Draw() {
	// Make sure we actually have an associated animation set //
	if ( AnimationSet ) {
		AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Draw( Body );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::DrawBody( const bool Selected ) const {
	// Draw the debug body information //
	Body.DrawSpheres();
	Body.DrawSprings();
	Body.DrawNodes();
	
	Body.DrawBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
