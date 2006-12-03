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
	Parent->Action( &_Vs );
	_Vs.Action( this );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
