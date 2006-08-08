// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Engine/DynamicObject.h>

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
		StepNodeLinks();
		
		// Update all Springs //
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			Component[ idx ].Body.StepSprings();
		}

		// Solve collisions between components //
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			for ( size_t idx2 = idx+1; idx2 < Component.size(); idx2++ ) {
				Component[ idx ].Solve( Component[ idx2 ] );
			}
		}
	}		
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::StepNodeLinks() {
	// Update nodes via NodeLink springs //
	for ( size_t idx = 0; idx < NodeLink.size(); idx++ ) {
		NodeLink[ idx ].Step( Component );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Work() {
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Draw() {
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
