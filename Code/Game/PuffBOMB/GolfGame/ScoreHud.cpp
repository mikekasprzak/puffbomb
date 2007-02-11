// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
#include "ScoreHud.h"
// - ------------------------------------------------------------------------------------------ - //
#include "GolfGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
cScoreHud::cScoreHud( ) :
	Engine( dynamic_cast<cGolfGameEngine*>(Engine2D::cEngine2D::Current) ),
	Hud( "2D/Hud/Tournament/TournamentHud.form" )
{

}
// - ------------------------------------------------------------------------------------------ - //
cScoreHud::~cScoreHud() {
	
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
void cScoreHud::Step() {

	
	// Step the animations of the hud //	
	Hud.Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cScoreHud::Draw() {
	Hud.Draw();
}
// - ------------------------------------------------------------------------------------------ - //
