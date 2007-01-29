// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <DynamicComponent/DynamicComponent.h>
#include <DynamicCollection/DynamicCollection.h>
#include <Zone/Zone.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Solve( cZone& _Vs ) {
	// If I'm more than simply active //
	if ( !Flags.OnlyActive() ) {
		// If I'm ignoring zones, bail//
		if ( Flags.IgnoreZones() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !Flags.Active() ) {
			return;
		}
	}
	
	// Test Bounding Rectangles //
	if ( Body.BoundingRect != _Vs.BoundingRect )
		return;

	// Send message //
	Parent->Message( _Vs );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
