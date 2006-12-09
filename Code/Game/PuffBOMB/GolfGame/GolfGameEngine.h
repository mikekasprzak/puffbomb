// - ------------------------------------------------------------------------------------------ - //
// GolfGameEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GolfGame_PuffBOMB_GolfGameEngine_H__
#define __GolfGame_PuffBOMB_GolfGameEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>

#include "Player/Player.h"
// - ------------------------------------------------------------------------------------------ - //
class cGolfGameEngine : public Engine2D::cEngine2D { 
public:
	// Custom Camera used to create a HUD //
	cCamera *HudCamera;

public:
	// Start point //
	Engine2D::cPassiveObject* StartPoint;
	
	// Our players //
	std::vector< cPlayer* > Player;
	
	// Our current player //
	size_t CurrentPlayer;
	// Engine State //
	int State;
	

	void TurnBasedPlay();
//	void RealTimePlay();

public:
	cGolfGameEngine();
	~cGolfGameEngine();
	
public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // GolfGame // 
// - ------------------------------------------------------------------------------------------ - //
