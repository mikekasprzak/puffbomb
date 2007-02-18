// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include "DynamicComponentAnimator.h"
#include "ComponentAnimationSet/ComponentAnimationSetPool.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cDynamicComponentAnimator::cDynamicComponentAnimator( )
{
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicComponentAnimator::cDynamicComponentAnimator( cComponentAnimationSet* _AnimationSet ) :
	AnimationSet( _AnimationSet ),
	CurrentAnimation( 0 ),
	CurrentFrame( 0 ),
	CurrentFrameTime( Real::Zero ),
	PlayBackRate( Real::One )
{
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponentAnimator::Step() {
	// Make sure we actually have an associated animation set //
	if ( AnimationSet ) {
		// Step our current frame time forward by our rate of playback //
		CurrentFrameTime += PlayBackRate;
		
		// If our current frame time breaks the hold length of the current frame //
		if ( CurrentFrameTime >= Real( AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Time ) ) {
			// Step to the next frame //
			CurrentFrame++;
			
			// If our frame hits the end //
			if ( CurrentFrame >= (int)AnimationSet->Animation[ CurrentAnimation ].Frame.size() ) {
				// Set frame to the loop point //
				CurrentFrame = AnimationSet->Animation[ CurrentAnimation ].LoopPoint;
				
				// Set looped flag //
				AnimationFlags.SetLooped();
			}

			// Update the Pose //
//			Body.Pose = &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];
			
			// Offset the Current Frame Time by the hold of the previous, to correctly accumulate //
			CurrentFrameTime -= Real( AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Time );
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
cBody2DPose* cDynamicComponentAnimator::GetPose() {
	return &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];

}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponentAnimator::SetAnimation( const int AnimationNumber, const Real& _PlayBackRate ) {
	// Set the animation as requested //
	if ( AnimationNumber < (int)AnimationSet->Animation.size() )
		CurrentAnimation = AnimationNumber;
	else {
		Log( 10, "Error!  Animation " << AnimationNumber << " Requested, but doesn't exist!" );
	}
	
	// Set internal animator variables //
	PlayBackRate = _PlayBackRate;
	CurrentFrame = 0;
	CurrentFrameTime = Real::Zero;
	
	// Clear Flags //
	AnimationFlags.Clear();
	
	// Set Pose //
//	Body.Pose = &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponentAnimator::SetArcingAnimation( const int AnimationNumber ) {
	// Set the animation as requested //
	if ( AnimationNumber < (int)AnimationSet->Animation.size() )
		CurrentAnimation = AnimationNumber;
	else {
		Log( 10, "Error!  Arcing Animation " << AnimationNumber << " Requested, but doesn't exist!" );
	}
	
	// Set internal animator variables //
	PlayBackRate = Real::Zero;
	CurrentFrame = 0;
	CurrentFrameTime = Real::Zero;
	
	// Clear Flags //
	AnimationFlags.Clear();
	
	// Set Pose //
//	Body.Pose = &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];	
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponentAnimator::SetArc( const Real& Arc ) {
	CurrentFrame = (int)( Arc * Real( AnimationSet->Animation[ CurrentAnimation ].Frame.size() ) );

	// If too big //
	if ( CurrentFrame >= (int)AnimationSet->Animation[ CurrentAnimation ].Frame.size() ) {
		// Clip to the end //
		CurrentFrame = AnimationSet->Animation[ CurrentAnimation ].Frame.size() - 1;
	}
	// If too small //
	else if ( CurrentFrame < 0 ) {
		CurrentFrame = 0;
	}

	// Set Pose //
//	Body.Pose = &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponentAnimator::Draw( cBody2D _Body, const int RenderPass ) {
	// Make sure we actually have an associated animation set //
	if ( AnimationSet ) {
		AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Draw( _Body, RenderPass );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
