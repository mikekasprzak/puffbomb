// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <DynamicComponent/DynamicComponent.h>
#include <DynamicCollection/DynamicCollection.h>
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Solve( cPassiveObject& _Vs ) {
	// If I'm more than simply active //
	if ( !State.OnlyActive() ) {
		// If I'm ignoring passive objects, bail//
		if ( State.IgnorePassives() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !State.Active() ) {
			return;
		}
	}
	
	// Test Bounding Rectangles //
	if ( Body.BoundingRect != _Vs.BoundingRect )
		return;

	// Send messages //
	Parent->Message( 1, &_Vs );
	_Vs.Action( this );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
