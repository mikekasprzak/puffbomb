// - ------------------------------------------------------------------------------------------ - //
// HamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
//#include <Particle2D/SolidParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "HamsterCharacter.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cHamsterCharacter::Message( int Msg, Engine2D::cPassiveObject* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			// Check who it is //
			switch( int SubMsg = Sender->Message( 2, (Engine2D::cDynamicComponent*)this ) ) {
				case 10 ... 14: {
					Sender->Message( 3, (Engine2D::cDynamicComponent*)this );
					Engine2D::cEngine2D::Current->Message( SubMsg, this );
					break;
				};
			};
			
			break;
		}
		// Who Are You? //
		case 2: {
			return 0;
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
			//Log( 10, "Cowabunga!" );
			break;
		}
		// Who Are You? //
		case 2: {
			return 0;
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
		// Win Zone!! //
		case 9: {
			Engine2D::cEngine2D::Current->Message( 2, this );
			
			break;
		}		
		// Fall out, send back to last position //
		case 4: {
			Engine2D::cEngine2D::Current->Message( 4, this );
			
			break;
		}		
		// Fall out, send back to drop point //
		case 5: {
			Engine2D::cEngine2D::Current->Message( 5, this );
			
			break;
		}		
	};
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool cHamsterCharacter::Work() {
	// If I became an Object Sensor //
	if ( Component[ 0 ].Body.Flags.ObjectSensor() ) {
		// If I have no contact with other objects //
		if ( !Component[ 0 ].Body.CollisionFlags.Object() ) {
			// I no longer need to be an Object Sensor //
			Component[ 0 ].Body.Flags.ResetObjectSensor();
		}
	}
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
