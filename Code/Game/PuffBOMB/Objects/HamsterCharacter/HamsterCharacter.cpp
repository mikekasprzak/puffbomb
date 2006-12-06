// - ------------------------------------------------------------------------------------------ - //
// HamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/NewParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "HamsterCharacter.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cHamsterCharacter::Message( int Msg, Engine2D::cPassiveObject* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			Log( 10, "Teenage mundane samurai rodents!" );
			break;
		}
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
int cHamsterCharacter::Message( int Msg, Engine2D::cDynamicCollection* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			Log( 10, "Cowabunga!" );
			break;
		}
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Message( const Engine2D::cImpulse& Sender ) {
	Component[ 0 ].SetAnimation( 1 );
}
// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Message( const Engine2D::cZone& Sender ) {
	switch ( Sender.Id ) {
		// Win Zonev!! //
		case 9: {
			Engine2D::cEngine2D::Current->Message( 2, this );
			
			break;
		}		
	};
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool cHamsterCharacter::Work() {
//	if ( Component[ 0 ].Body.CollisionFlags.Scenery() )
//		Component[ 0 ].SetAnimation( 0 );
//	else
//		Component[ 0 ].SetAnimation( 1 );
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
