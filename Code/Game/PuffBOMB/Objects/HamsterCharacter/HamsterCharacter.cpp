// - ------------------------------------------------------------------------------------------ - //
// HamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/NewParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "HamsterCharacter.h"
#include <Impulse/Impulse.h>
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Action( cImpulse* const _Vs ) {
	Component[ 0 ].SetAnimation( 1 );
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
