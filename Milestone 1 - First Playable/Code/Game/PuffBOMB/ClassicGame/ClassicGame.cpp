// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGame.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cClassicGame::cClassicGame( const std::string& FileName ) {
	// Creating Engine //
	Log( LOG_HIGHEST_LEVEL, "Creating Engine..." );
	Engine = new cClassicGameEngine( FileName );
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //
cClassicGame::~cClassicGame() {
	delete Engine;
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGame::Draw() {
	Engine->Draw();
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGame::Step() {
	Engine->Step();
}
// - ------------------------------------------------------------------------------------------ - //
