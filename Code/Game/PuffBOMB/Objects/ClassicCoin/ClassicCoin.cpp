// - ------------------------------------------------------------------------------------------ - //
// ClassicCoin //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
//#include <Particle2D/SolidParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "ClassicCoin.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cClassicCoin::Message( int Msg, Engine2D::cDynamicComponent* const Sender ) {
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
			break;
		};
	};
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
bool cClassicCoin::Work() {
	if ( Collected ) {
		return false;
	}
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
