// - ------------------------------------------------------------------------------------------ - //
// CreatePassiveInstance //
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include "CreatePassiveInstance.h"

#include <Objects/Distortion/Distortion.h>
#include <Objects/BasicBomb/BasicBomb.h>
#include <Objects/GolfStart/GolfStart.h>
#include <Objects/RainGenerator/RainGenerator.h>
// - ------------------------------------------------------------------------------------------ - //
Engine2D::cPassiveObject* CreatePassiveInstance( const unsigned int Id, const Vector2D& Pos, const int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			cDistortion* MyDistortion = new cDistortion( Pos );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 1, MyDistortion );
			}
			return MyDistortion;
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

		case 32: {
			cRainGenerator* MyRain = new cRainGenerator( Pos, Argument );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 1, MyRain );
			}
			return MyRain;
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
