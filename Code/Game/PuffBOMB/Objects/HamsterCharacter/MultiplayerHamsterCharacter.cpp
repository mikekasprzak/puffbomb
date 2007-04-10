// - ------------------------------------------------------------------------------------------ - //
// MultiplayerHamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
// - ------------------------------------------------------------------------------------------ - //
#include "MultiplayerHamsterCharacter.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cMultiplayerHamsterCharacter::Message( int Msg, Engine2D::cPassiveObject* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			// Check who it is //
			switch( int SubMsg = Sender->Message( 2, (Engine2D::cDynamicComponent*)this ) ) {
				// Exit Vortex //
				case 20: {
					// Disappear //
					SetInactive();
					
					// Increment victory scoring //
					Engine2D::cEngine2D::Current->Message( 2, this );
					
					// Create some sort of disappearing effect //
					FXLibrary::EnterVortex( Component[ 0 ].Body.BoundingRect.Center(), 1 );
						
					// Nothing more to do here, end! //
					return 0;
					break;
				};
			};
			
			break;
		}
		// Who Are You? //
		case 2: {
			// Check who is asking //
			switch( int SubMsg = Sender->Message( 2, (Engine2D::cDynamicComponent*)this ) ) {
				// Exit Vortex //
				case 20: {
					// I am self sufficent //
					return 23;
					break;
				};
			};
			break;
		}
	};
	
	return cHamsterCharacter::Message( Msg, Sender );
}
// - ------------------------------------------------------------------------------------------ - //
