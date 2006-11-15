// - ------------------------------------------------------------------------------------------ - //
// GameEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_GameEngine_H__
#define __Game_PuffBOMB_GameEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>

#include "Player/Player.h"
// - ------------------------------------------------------------------------------------------ - //
class cGameEngine : public Engine2D::cEngine2D { 
public:
	// Custom Camera used to create a HUD //
	cCamera *HudCamera;

public:
	// Our players //
	std::vector< cPlayer* > Player;
	// Our current player //
	size_t CurrentPlayer;

	void TurnBasedPlay();
	void RealTimePlay();

public:
	cGameEngine();
	~cGameEngine();
	
public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Game // 
// - ------------------------------------------------------------------------------------------ - //
