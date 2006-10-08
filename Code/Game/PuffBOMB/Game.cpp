// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cGame::cGame()
{
	// Creating Engine //
	Log( LOG_HIGHEST_LEVEL, "Creating Engine..." );
	Engine = new Engine2D::cEngine2D();
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //
cGame::~cGame()
{
	delete Engine;
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Draw()
{
	Engine->Draw();
	
	Engine->HudDraw();
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Step()
{
	Engine->Step();
	
}
// - ------------------------------------------------------------------------------------------ - //
