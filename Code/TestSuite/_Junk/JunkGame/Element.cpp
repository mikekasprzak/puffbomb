// - ------------------------------------------------------------------------------------------ - //
// Element //
// - ------------------------------------------------------------------------------------------ - //
#include "Element.h"

//#include <Game.h> // Removed because of game dependency //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool cElement::InitElement( ) {
	switch ( Id ) {
		// Some Element //
		case 1: {

		}
		
		default: {
			return false;
		}
	};
	
	// Remove self //
	return true;
}
// - ------------------------------------------------------------------------------------------ - //