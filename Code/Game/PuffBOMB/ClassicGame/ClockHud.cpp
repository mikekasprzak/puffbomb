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
	FlickerClock( 0 ),
	BestClock( 0 )
{
	
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
	FlickerClock = 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClockHud::StartActiveFlicker() {
	FrameClockActive = false;
	FlickerClock = 0;
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
