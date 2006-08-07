// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include "DynamicObject.h"

#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Step() {
	// Step all the nodes //
	for ( size_t idx = 0; idx < Component.size(); idx++ ) {
		Component[ idx ].Body.Step();
	}

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update nodes via NodeLink springs //
		for ( size_t idx = 0; idx < NodeLink.size(); idx++ ) {
			NodeLink[ idx ].Step( Component );
		}
		
		// Update all Springs //
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			Component[ idx ].Body.StepSprings();
		}
	}		
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Work() {
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Draw() {
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
