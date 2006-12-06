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
	void AddBombs();

public:
	// Victory related variables //
	bool LevelComplete;
	int CharactersAtEndZones;
	
	void FrameStart();
	void FrameEnd();
	
public:
	cClassicGameEngine( const std::string& FileName );
	virtual ~cClassicGameEngine();
	
public:
	void Step();
	void Draw();
	
public:
	// - -------------------------------------------------------------------------------------- - //
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicCollection* const Sender );
	virtual int Message( int Msg, Engine2D::cPassiveObject* const Sender );	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // ClassicGame // 
// - ------------------------------------------------------------------------------------------ - //
