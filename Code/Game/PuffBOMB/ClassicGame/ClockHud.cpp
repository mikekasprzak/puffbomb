// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include "ClockHud.h"
// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
cClockHud::cClockHud( ) :
	Engine( dynamic_cast<cClassicGameEngine*>(Engine2D::cEngine2D::Current) ),
	Hud( "2D/Hud/Classic/ClassicHud.form" ),
	FrameClock( 0 ),
	FrameClockActive( true ),
	FlickerClock( Global::FrameRate >> 1 ),
	BestClock( 0 )
{
	SetBombs( 4 );
}
// - ------------------------------------------------------------------------------------------ - //
cClockHud::~cClockHud() {
	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClockHud::StartActionMode() {
	FrameClockActive = true;
	FrameClock = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cClockHud::StartEditMode() {
	// Start with : off //
	FlickerClock = Global::FrameRate >> 1;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClockHud::StartActiveFlicker() {
	FrameClockActive = false;
	FlickerClock = 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClockHud::SetBombs( const int _Count ) {
	// Set bomb numbers //
	MaxBombCount = _Count;
	BombCount = MaxBombCount;
	
	// Show all sockets for visible bombs //
	for ( size_t idx = 0; idx < MaxBombCount; idx++ ) {
		Hud.GroupVisible( 10 + idx, true );
	}

	// Hide all sockets of invisible bombs //
	for ( size_t idx = MaxBombCount; idx < 5; idx++ ) {
		Hud.GroupVisible( 10 + idx, false );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClockHud::AddBomb() {
	int OldBombCount = BombCount;
	
	// Add a bomb //
	BombCount++;
	
	// Clip BombCount to Max //
	if ( BombCount > MaxBombCount )
		BombCount = MaxBombCount;
	
	// If the bomb adding operation was successful //
	if ( OldBombCount != BombCount ) {
		// Trigger a bomb addition animation //
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cClockHud::RemoveBomb() {
	int OldBombCount = BombCount;
	
	// Add a bomb //
	BombCount--;
	
	// Clip BombCount to Max //
	if ( BombCount < 0 )
		BombCount = 0;
	
	// If the bomb adding operation was successful //
	if ( OldBombCount != BombCount ) {
		// Trigger a bomb removal animation //
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cClockHud::Step() {
	// Action Mode //
	if ( Engine->GameActive ) {
		// Step forward the frame clock //
		if ( FrameClockActive ) {
			FrameClock++;
			// Cap at 99:59 or 99:99 respectfully //
			if ( FrameClock > ((100 * Global::FrameRate) - 1) ) {
				FrameClock = ((100 * Global::FrameRate) - 1);
					
				// Enable flickering //
				StartActiveFlicker();
			}
		}
		
		// Calculate time digits //
		int Frames = FrameClock % Global::FrameRate;
		int Seconds = FrameClock / Global::FrameRate;

		Hud.Group( 2, 4 ).AniLabel()->Animator.SetFrame( Frames % 10 );
		Hud.Group( 2, 3 ).AniLabel()->Animator.SetFrame( Frames / 10 );
		Hud.Group( 2, 1 ).AniLabel()->Animator.SetFrame( Seconds % 10 );
		Hud.Group( 2, 0 ).AniLabel()->Animator.SetFrame( Seconds / 10 );
		
		// Flash Numbers on inactivity //
		if ( !FrameClockActive ) {
			Hud.GroupVisible( 2, ((FlickerClock / (Global::FrameRate >> 1) ) & 1) == 0 );
		}

		// Show Clock Colon //
		Hud.GroupVisible( 2, 2, true );
		
	}
	// Edit Mode //
	else {		
		// Flash Clock Colon //
		Hud.GroupVisible( 2, 2, ((FlickerClock / (Global::FrameRate >> 1) ) & 1) == 0 );
			
		Hud.Group( 2, 0 ).AniLabel()->Animator.SetFrame( 0 );
		Hud.Group( 2, 1 ).AniLabel()->Animator.SetFrame( 0 );
		Hud.Group( 2, 3 ).AniLabel()->Animator.SetFrame( 0 );
		Hud.Group( 2, 4 ).AniLabel()->Animator.SetFrame( 0 );
	}

	// Step forward the Flicker clock //
	FlickerClock++;

	
	// Step the animations of the hud //	
	Hud.Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cClockHud::Draw() {
	Hud.Draw();
}
// - ------------------------------------------------------------------------------------------ - //
