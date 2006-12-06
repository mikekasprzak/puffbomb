// - ------------------------------------------------------------------------------------------ - //
// CreatePassiveInstance //
// - ------------------------------------------------------------------------------------------ - //
#include "CreatePassiveInstance.h"

#include <Objects/Distortion/Distortion.h>
#include <Objects/BasicBomb/BasicBomb.h>
#include <Objects/GolfStart/GolfStart.h>
// - ------------------------------------------------------------------------------------------ - //
Engine2D::cPassiveObject* CreatePassiveInstance( const unsigned int Id, const Vector2D& Pos, const int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			return new cDistortion( Pos );
			break;
		}

		case 2: {
			return new cBasicBomb( Pos, Argument );
			break;
		}

		case 5: {
			return new cGolfStart( Pos );
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
