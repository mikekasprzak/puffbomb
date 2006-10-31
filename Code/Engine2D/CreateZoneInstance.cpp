// - ------------------------------------------------------------------------------------------ - //
// CreateZoneInstance //
// - ------------------------------------------------------------------------------------------ - //
#include "CreateZoneInstance.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cZone* CreateZoneInstance( const unsigned int Id, const Rect2D& Rect, const int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			//return new cZone( "2D/Hamster/Hamster.coll", Pos );
			break;
		}
		
		default: {
			// No object with Id requested found, so return a null  //
			return 0;
			break;
		}
	}
	
	// In case the function accidentially doesn't return anything //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //