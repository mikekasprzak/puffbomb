// - ------------------------------------------------------------------------------------------ - //
#include "GolfGame.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cGolfGame::cGolfGame( const std::string& FileName, const std::vector< cPlayerInfo >& _Players, int _StartPlayer ) {
	// Creating Engine //
	Log( LOG_HIGHEST_LEVEL, "Creating Engine..." );
	Engine = new cGolfGameEngine( FileName, _Players, _StartPlayer );
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //
cGolfGame::~cGolfGame() {
	delete Engine;
}
// - ------------------------------------------------------------------------------------------ - //
void cGolfGame::Draw() {
	Engine->Draw();
}
// - ------------------------------------------------------------------------------------------ - //
void cGolfGame::Step() {
	Engine->Step();
}
// - ------------------------------------------------------------------------------------------ - //
