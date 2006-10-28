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
cDynamicComponent::cDynamicComponent( const cDynamicCollection* const _Parent, const std::string& ComponentFile ) :
	Parent( _Parent ),
	AnimationSet( ComponentAnimationSetPool.Load( ComponentFile ) ),
	Body( AnimationSet->BodyPose[ 0 ] )
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
void cDynamicComponent::Draw() {
	// Make sure we actually have an associated animation set //
	if ( AnimationSet ) {
		AnimationSet->Animation[ 0 ].Frame[ 0 ].Draw( Body );
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
