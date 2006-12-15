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
	
	std::vector< Engine2D::cDynamicCollection* > CameraTracking;
	std::vector< Engine2D::cPassiveObject* > AlwaysActivePassives;

public:
	void AddBombs();

public:
	// Victory related variables //
	bool LevelComplete;
	int CharactersAtEndZones;
	
	void FrameStart();
	void FrameEnd();

public:
	int Score;
	inline void AddScore( const int _Score ) {
		Score += _Score;
		if ( Score < 0 ) {
			Score = 0;
		}
	}
	
public:
	cClassicGameEngine( const std::string& FileName );
	virtual ~cClassicGameEngine();
	
public:
	void Step();
	void Draw();
	
public:
	// - -------------------------------------------------------------------------------------- - //
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicCollection* Sender );
	virtual int Message( int Msg, Engine2D::cPassiveObject* Sender );	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // ClassicGame // 
// - ------------------------------------------------------------------------------------------ - //
