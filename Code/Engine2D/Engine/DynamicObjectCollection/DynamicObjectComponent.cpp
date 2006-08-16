// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include "DynamicObjectComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// In the case of a component without a parent, if checks should be placed to stop messanging //
cDynamicObjectComponent::cDynamicObjectComponent( ) :
	Parent( 0 )
{	
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicObjectComponent::cDynamicObjectComponent( class cDynamicObject* _Parent ) :
	Parent( _Parent )
{	
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Step() {
	// Step the nodes //
	Body.Step();

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update all Springs //
		Body.StepSprings();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Draw() {
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
