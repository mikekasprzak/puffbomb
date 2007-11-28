// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <DynamicComponent/DynamicComponent.h>
#include <StaticObject/StaticObjectInstance.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Solve( cStaticObjectInstance& _Vs ) {
	// If I'm more than simply active //
	if ( !Flags.OnlyActive() ) {
		// If I'm ignoring scenery, bail//
		if ( Flags.IgnoreScenery() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !Flags.Active() ) {
			return;
		}
	}
	
	// Generate an edge list from the Used list found inside the Instance //
	std::vector< int > EdgeIndex;
	for ( size_t idx = 0; idx < _Vs.UsedEdge.size(); idx++ ) {
		if ( _Vs.UsedEdge[ idx ] ) {
			EdgeIndex.push_back( idx );
		}
	}	
	
	// Solve the collision //
	Body.Solve( _Vs.Object->Body, _Vs.Pos, EdgeIndex ); 
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
