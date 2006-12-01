// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <DynamicCollection/DynamicCollection.h>

#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicCollection::Step() {
	// Step all the nodes //
	for ( size_t idx = 0; idx < Component.size(); idx++ ) {
		Component[ idx ].Body.Nodes.WakeUp();
		Component[ idx ].Body.Step();
	}

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update nodes via NodeLink springs only (no anchors) //
		for ( size_t idx = 0; idx < NodeLink.size(); idx++ ) {
			NodeLink[ idx ].Step( Component );
		}
		
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
void cDynamicCollection::StepLinkage() {
	// Update nodes via Anchors //
	for ( size_t idx = 0; idx < NodeAnchor.size(); idx++ ) {
		NodeAnchor[ idx ].Step( Component );
	}

	// Update nodes via NodeLink springs //
	for ( size_t idx = 0; idx < NodeLink.size(); idx++ ) {
		NodeLink[ idx ].Step( Component );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicCollection::Draw() {
	// For all components, draw them //
	for ( size_t idx = 0; idx < Component.size(); idx++ ) {
		Component[ idx ].Draw();
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicCollection::Work() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicCollection::UpdateAnchors() {
	for ( size_t idx = 0; idx < NodeAnchor.size(); idx++ ) {
		cNodeAnchor& MyAnchor = NodeAnchor[ idx ];
		MyAnchor.Pos = Component[ MyAnchor.Object ].Body.Nodes.Pos( MyAnchor.Index );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
