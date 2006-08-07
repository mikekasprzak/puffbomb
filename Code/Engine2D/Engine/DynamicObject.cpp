// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include "DynamicObject.h"

#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Step() {
	// Move all my parts //
	for ( size_t idx = 0; idx < Component.size(); idx++ ) {
		Component[ idx ].Step();
	}

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update Positions via NodeLinks //
		for ( size_t idx = 0; idx < NodeLink.size(); idx++ ) {
			
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
