// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Engine/DynamicObjectCollection/DynamicObject.h>
#include <Physics/Impulse.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Solve( cImpulse& _Vs ) {
	// If I'm more than simply active //
	if ( !State.OnlyActive() ) {
		// If I'm ignoring impulses, bail//
		if ( State.IgnoreImpulses() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !State.Active() ) {
			return;
		}
	}
	
	// Solve the collision //
	Body.Solve( _Vs ); 
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
