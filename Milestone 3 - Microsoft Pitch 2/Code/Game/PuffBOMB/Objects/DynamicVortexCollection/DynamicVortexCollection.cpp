// - ------------------------------------------------------------------------------------------ - //
// DynamicVortexCollection //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
//#include <Particle2D/SolidParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "DynamicVortexCollection.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cDynamicVortexCollection::Message( int Msg, Engine2D::cPassiveObject* const Sender ) {
	switch ( Msg ) {
		// Who Are You? //
		case 2: {
			// Check who is asking //
			switch( int SubMsg = Sender->Message( 2, (Engine2D::cDynamicComponent*)this ) ) {
				// Exit Vortex //
				case 20: {
					// I am a normal object that is to be pulled in to a vortex //
					return 21;
					break;
				};
			};
			return 0;
			break;
		}
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
