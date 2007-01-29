// - ------------------------------------------------------------------------------------------ - //
// Zone //
// - ------------------------------------------------------------------------------------------ - //
#include "Zone.h"
#include <Phiz/SphereObject.h>

//#include <Game.h>
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cZone::Action( const cSphereObject& Vs ) {
	switch ( Id ) {
		// Camera Boundary //
		case 1: {
			
		}

		// Level Boundary //
		case 2: {
			
		}
		
		// ??? //
		case 3: {
			if ( Vs.Sphere.size() ) {
				// Uhh //	
			}
		}
	};
}
// - ------------------------------------------------------------------------------------------ - //
bool cZone::InitZone( ) {
	switch ( Id ) {
		// Camera Boundary //
		case 1: {
/*			cGame::Current->Camera->CameraBounds = BoundingRect.ToPairRect();

			Log( 10, "New Camera Bounds: (" <<
				cGame::Current->Camera->CameraBounds.P1().x << ", " <<
				cGame::Current->Camera->CameraBounds.P1().y << ") -> (" <<
				cGame::Current->Camera->CameraBounds.P2().x << ", " <<
				cGame::Current->Camera->CameraBounds.P2().y << ")" );*/  // Removed because of game dependency //
		}

		// Level Boundary //
		case 2: {
			//cGame::Current->Camera->LevelBounds = BoundingRect;			
		}
		
		default: {
			return false;
		}
	};
	
	// Remove self //
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
