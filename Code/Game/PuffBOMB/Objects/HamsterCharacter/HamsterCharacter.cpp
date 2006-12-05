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

#include <Framework/MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Action( Engine2D::cPassiveObject* const _Vs ) {
	//Log( 10, "Teenage mundane samurai rodents!" );
}
// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Action( Engine2D::cDynamicCollection* const _Vs ) {
	//Log( 10, "Cowabunga!" );
}
// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Action( const Engine2D::cImpulse& _Vs ) {
	Component[ 0 ].SetAnimation( 1 );
}
// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Action( const Engine2D::cZone& _Vs ) {
	switch ( _Vs.Id ) {
		// Win Zonev!! //
		case 9: {
			
			cMessageEntity::Current->BreakLoop = true;
			break;
		}		
	};
}
// - ------------------------------------------------------------------------------------------ - //
bool cHamsterCharacter::Work() {
//	if ( Component[ 0 ].Body.CollisionFlags.Scenery() )
//		Component[ 0 ].SetAnimation( 0 );
//	else
//		Component[ 0 ].SetAnimation( 1 );
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
