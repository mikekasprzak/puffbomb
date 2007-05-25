// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
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
	// Since I forget how to do array init lists (asuming they were even possible) //
	for ( int idx = 0; idx < 4; idx ++ ) {
		Score[ idx ] = 0;
		InterpolatingScore[ idx ] = 0;
		Stroke[ idx ] = 0;
	}

}
// - ------------------------------------------------------------------------------------------ - //
cScoreHud::~cScoreHud() {
	
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cScoreHud::SetScore( const int _Player, const int _Score ) {
	// Assert on invalid player //
	
	// Flag something special when this changes //
	if ( _Score != Score[ _Player ] ) {
		
	}
	
	Score[ _Player ] = _Score;
}
// - ------------------------------------------------------------------------------------------ - //
void cScoreHud::StartScore( const int _Player, const int _Score ) {
	// Assert on invalid player //

	
	Score[ _Player ] = _Score;
	InterpolatingScore[ _Player ] = _Score;
}
// - ------------------------------------------------------------------------------------------ - //
void cScoreHud::SetStroke( const int _Player, const int _Stroke ) {
	// Assert on invalid player //
	
	// Flag something special when this changes //
	if ( _Stroke != Stroke[ _Player ] ) {
		
	}
	
	Stroke[ _Player ] = _Stroke;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cScoreHud::Step() {
	// Scoreboards //
	for ( int idx = 0; idx < 4; idx++ ) {
		std::stringstream st;
		st << InterpolatingScore[ idx ];
		Hud.Group( 13 - idx, 2 ).TextLabel()->Text = st.str();
	}
	// Strokes //
	for ( int idx = 0; idx < 4; idx++ ) {
		std::stringstream st;
		st << Stroke[ idx ];
		Hud.Group( 13 - idx, 3 ).TextLabel()->Text = st.str();
	}
	
	// Step the Interpolating Score //
	for ( int idx = 0; idx < 4; idx++ ) {
		if ( InterpolatingScore[ idx ] != Score[ idx ] ) {
			if ( InterpolatingScore[ idx ] > Score[ idx ] ) { 
				InterpolatingScore[ idx ] -= 2;
			}
			if ( InterpolatingScore[ idx ] < Score[ idx ] ) {
				InterpolatingScore[ idx ] += 2;
			}
		}
	}
	
	// Step the animations of the hud //	
	Hud.Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cScoreHud::Draw() {
	Hud.Draw();
}
// - ------------------------------------------------------------------------------------------ - //
