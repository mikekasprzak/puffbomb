// - ------------------------------------------------------------------------------------------ - //
// CreatePassiveInstance //
// - ------------------------------------------------------------------------------------------ - //
#include "CreatePassiveInstance.h"

#include <Objects/Distortion/Distortion.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cPassiveObject* CreatePassiveInstance( const unsigned int Id, const Vector2D& Pos, const int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			return new cDistortion( Pos );
			break;
		}
		
		default: {
			// No object with Id requested found, so return a null object //
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
