// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <DynamicComponent/DynamicComponent.h>
#include <DynamicCollection/DynamicCollection.h>
#include <Impulse/Impulse.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Solve( cImpulse& _Vs ) {
	// If I'm more than simply active //
	if ( !Flags.OnlyActive() ) {
		// If I'm ignoring impulses, bail//
		if ( Flags.IgnoreImpulses() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !Flags.Active() ) {
			return;
		}
	}
	
	// Solve the collision //
	if ( Body.Solve( _Vs ) ) {
		// Take action based on the impulse //
		Parent->Message( _Vs );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
