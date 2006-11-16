// - ------------------------------------------------------------------------------------------ - //
// ClassicGameEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __ClassicGame_PuffBOMB_ClassicGameEngine_H__
#define __ClassicGame_PuffBOMB_ClassicGameEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>

#include "Player/Player.h"
// - ------------------------------------------------------------------------------------------ - //
class cClassicGameEngine : public Engine2D::cEngine2D { 
public:
	// Custom Camera used to create a HUD //
	cCamera *HudCamera;

public:

//	void TurnBasedPlay();

public:
	cClassicGameEngine();
	~cClassicGameEngine();
	
public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // ClassicGame // 
// - ------------------------------------------------------------------------------------------ - //
