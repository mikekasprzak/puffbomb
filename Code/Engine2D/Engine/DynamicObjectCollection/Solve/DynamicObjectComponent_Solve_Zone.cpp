// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Engine/DynamicObject/DynamicObjectComponent.h>
#include <Engine/Zone.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Solve( cZone& _Vs ) {
	// If I'm more than simply active //
	if ( !State.OnlyActive() ) {
		// If I'm ignoring zones, bail//
		if ( State.IgnoreZones() ) {
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

	// Send message //
	_Vs.Action( *this );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
