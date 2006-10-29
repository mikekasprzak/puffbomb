// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <DynamicComponent/DynamicComponent.h>
#include <StaticObject/StaticObjectInstance.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Solve( cStaticObjectInstance& _Vs ) {
	// If I'm more than simply active //
	if ( !State.OnlyActive() ) {
		// If I'm ignoring scenery, bail//
		if ( State.IgnoreScenery() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !State.Active() ) {
			return;
		}
	}
	
	// Solve the collision //
	Body.Solve( _Vs.Object->Body, _Vs.Pos ); 
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
