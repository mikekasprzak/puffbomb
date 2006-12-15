// - ------------------------------------------------------------------------------------------ - //
// Coin //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
//#include <Particle2D/SolidParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Coin.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cCoin::Message( int Msg, Engine2D::cDynamicComponent* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			//Log( 10, "Teenage mundane samurai rodents!" );
			//Engine2D::cEngine2D::Current->Message( 10 + Variant, this );
			break;
		}
		// Who am I? //
		case 2: {
			if ( !Collected ) {
				Collected = true;
				return 10 + Variant;
			}
			break;
		}
	};
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
bool cCoin::Work() {
	if ( Collected ) {
		return false;
	}
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
