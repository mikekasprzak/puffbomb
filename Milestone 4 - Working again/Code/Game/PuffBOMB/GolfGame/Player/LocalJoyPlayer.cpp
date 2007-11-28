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
	// Cursor Control //
	if ( MyJoy().Button[ PAD_R ] ) {
		BombPos += MyJoy().Stick1 * Real( 15 );
	}
	else {
		BombPos += MyJoy().Stick1 * Real( 5 );
	}
	
	BombPos += MyJoy().DPad.KeyRepeat() * Real(1);
	

	// Constrain outside center //
	if ( BombPos.Magnitude() < Real( 128 ) ) {
		BombPos += (Real(128) - BombPos.Magnitude()) * BombPos.Normal();
	}
		
	// Constrain inside circle //
	if ( BombPos.Magnitude() > Real( 512 - 32 ) ) {
		BombPos += (Real(512 - 32) - BombPos.Magnitude()) * BombPos.Normal();
	}
	
	// Fire //
	if ( MyJoy().Button[ PAD_A ].Pressed() ) {
		return true;
	}
	
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
