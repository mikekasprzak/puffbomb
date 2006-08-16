// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include "DynamicObjectComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// In the case of a component without a parent, if checks should be placed to stop messanging //
cDynamicObject::cDynamicObject( ) :
	Parent( 0 )
{	
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicObject::cDynamicObject( class cDynamicObject* _Parent ) :
	Parent( _Parent )
{	
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Step() {
	// Step the nodes //
	Body.Step();

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update all Springs //
		Body.StepSprings();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Draw() {
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
