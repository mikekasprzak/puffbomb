// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Engine/DynamicComponent.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Solve( cDynamicComponent& _Vs ) {
	// If either object is more than simply active //
	if ( !State.OnlyActive() || !_Vs.State.OnlyActive() ) {
		// If either of us are ignoring our family, and we are part of the same family, bail //
		if ( State.IgnoreFamily() || _Vs.State.IgnoreFamily() ) {
			if ( Parent == _Vs.Parent ) {
				return;
			}
		}
		
		// If either of us are ignoring objects, bail //
		if ( State.IgnoreObjects() || _Vs.State.IgnoreObjects() ) {
			return;
		}

		// If either of us are inactive objects, bail //
		if ( !State.Active() || !_Vs.State.Active() ) {
			return;
		}
	}
	
	// Solve the collision //
	Body.Solve( _Vs.Body ); 
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
