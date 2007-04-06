// - ------------------------------------------------------------------------------------------ - //
// Pickup //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
//#include <Particle2D/SolidParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Pickup.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cPickup::Message( int Msg, Engine2D::cDynamicComponent* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			//Log( 10, "Teenage mundane samurai rodents!" );
			//Engine2D::cEngine2D::Current->Message( 10 + Variant, this );
			break;
		};
		// Who am I? //
		case 2: {
			if ( !Collected ) {
				return 10 + Variant;
			}
			break;
		};
		// Collect it //
		case 3: {
			Collected = true;
			
			// Display appropriate particle pickup //
			switch ( Variant ) {
				case 0: {
					FXLibrary::Pickup( Pos, 50 );
					break;
				}
				case 1: {
					FXLibrary::Pickup( Pos, 100 );
					break;
				}
				case 2: {
					FXLibrary::Pickup( Pos, 150 );
					break;
				}
				case 3: {
					FXLibrary::Pickup( Pos, 250 );
					break;
				}
				case 4: {
					FXLibrary::Pickup( Pos, 500 );
					break;
				}
			};
			
			break;
		};
	};
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
bool cPickup::Work() {
	if ( Collected ) {
		SetInactive();
		return false;
	}
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
