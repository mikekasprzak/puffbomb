// - ------------------------------------------------------------------------------------------ - //
#include "ClockHud.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cClockHud::cClockHud() :
	Hud( "2D/Hud/Classic/ClassicHud.form" )
{
}
// - ------------------------------------------------------------------------------------------ - //
cClockHud::~cClockHud() {
	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClockHud::Step() {
	Hud.Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cClockHud::Draw() {
	Hud.Draw();
}
// - ------------------------------------------------------------------------------------------ - //
