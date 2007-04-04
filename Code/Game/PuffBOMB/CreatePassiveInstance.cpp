// - ------------------------------------------------------------------------------------------ - //
// CreatePassiveInstance //
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include "CreatePassiveInstance.h"

#include <Objects/Distortion/Distortion.h>
#include <Objects/BasicBomb/BasicBomb.h>
#include <Objects/GolfDrop/GolfDrop.h>
#include <Objects/Pickup/Pickup.h>
#include <Objects/RainGenerator/RainGenerator.h>
#include <Objects/DripGenerator/DripGenerator.h>
#include <Objects/ExitVortex/ExitVortex.h>
// - ------------------------------------------------------------------------------------------ - //
Engine2D::cPassiveObject* CreatePassiveInstance( const unsigned int Id, const Vector2D& Pos, const int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			cExitVortex* MyVortex = new cExitVortex( Pos );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 1, MyVortex );
			}
			return MyVortex;
			break;
		}

		case 2: {
			return new cBasicBomb( Pos, Argument );
			break;
		}

		case 3: {
			Engine2D::cPassiveObject* MyObj = new Engine2D::cPassiveObject( Pos, Argument );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 3, MyObj );
			}
			return MyObj;
			break;
		}

		case 5: {
			cGolfDrop* MyStart = new cGolfDrop( Pos );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 5, MyStart );
			}
			return MyStart;
			break;
		}
		case 6: {
			cGolfDrop* MyDrop = new cGolfDrop( Pos );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 6, MyDrop );
			}
			return MyDrop;
			break;
		}

		// Point of interest //
		case 7: {
			Engine2D::cPassiveObject* MyObj = new Engine2D::cPassiveObject( "EndArrow.anim", Pos );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 7, MyObj );
			}
			return MyObj;
			break;
		}
		case 9: {
			cDistortion* MyDistortion = new cDistortion( Pos );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 1, MyDistortion );
			}
			return MyDistortion;
			break;
		}

		case 10: {
			return new cPickup( "Cherry.anim", Pos, Id - 10 );
			break;
		}
		case 11: {
			return new cPickup( "Cherry2.anim", Pos, Id - 10 );
			break;
		}
		case 12: {
			return new cPickup( "Cherry3.anim", Pos, Id - 10 );
			break;
		}
		case 13: {
			return new cPickup( "Cherry4.anim", Pos, Id - 10 );
			break;
		}
		case 14: {
			return new cPickup( "Cherry5.anim", Pos, Id - 10 );
			break;
		}

		case 15 ... 19: {
			return new cPickup( "Cherry.anim", Pos, Id - 10 );
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
		case 33: {
			cDripGenerator* MyDrip = new cDripGenerator( Pos, Argument );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 1, MyDrip );
			}
			return MyDrip;

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
