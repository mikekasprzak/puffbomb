// - ------------------------------------------------------------------------------------------ - //
// Player //
// - ------------------------------------------------------------------------------------------ - //
#include "Player.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cPlayer::cPlayer( Engine2D::cDynamicCollection* _MyObject ) :
	MyObject( _MyObject ),
	Score( 0 ),
	Stroke( 0 ),
	Finished( false )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
cPlayer::~cPlayer() {
	
}
// - ------------------------------------------------------------------------------------------ - //
