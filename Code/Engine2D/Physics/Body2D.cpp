// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::Step() {
	// Clear Collision Flags //
	Collision.Clear();
	
	// Step each Node //
	Nodes.Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::StepSprings() {
	// Solve all springs in the component //
	for ( size_t idx = 0; idx < Spring.size(); idx++ ) {
		Spring[ idx ].Step( Nodes );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
