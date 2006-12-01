// - ------------------------------------------------------------------------------------------ - //
// ClassicGameEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __ClassicGame_PuffBOMB_ClassicGameEngine_H__
#define __ClassicGame_PuffBOMB_ClassicGameEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
#include "ClassicCursor.h"
// - ------------------------------------------------------------------------------------------ - //
class cClassicGameEngine : public Engine2D::cEngine2D { 
public:
	// Custom Camera used to create a HUD //
	cCamera *HudCamera;

public:
	bool GameActive;
	cClassicCursor Cursor;

public:
//	void TurnBasedPlay();
	void AddBombs();

public:
	cClassicGameEngine( const std::string& FileName );
	~cClassicGameEngine();
	
public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // ClassicGame // 
// - ------------------------------------------------------------------------------------------ - //
