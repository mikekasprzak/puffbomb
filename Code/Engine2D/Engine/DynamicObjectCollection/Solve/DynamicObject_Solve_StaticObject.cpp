// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Engine/DynamicObjectCollection/DynamicObject.h>
#include <Engine/StaticObjectCollection/StaticObject.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Solve( cStaticObject& _Vs ) {
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
	Body.Solve( _Vs.Body ); 
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
