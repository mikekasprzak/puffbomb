// - ------------------------------------------------------------------------------------------ - //
// LocalJoyPlayer //
// - ------------------------------------------------------------------------------------------ - //
#include "LocalJoyPlayer.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cLocalJoyPlayer::cLocalJoyPlayer( Engine2D::cDynamicCollection* _MyObject, int _MyInputDevice ) :
	cPlayer( _MyObject ),
	MyInputDevice( _MyInputDevice )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
cLocalJoyPlayer::~cLocalJoyPlayer() {
	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool cLocalJoyPlayer::Control() {
	
	if ( MyJoy().Button[ PAD_A ].Pressed() ) {
		return true;
	}
	
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
