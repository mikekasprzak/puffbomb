// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include "DynamicObjectComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
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
