// - ------------------------------------------------------------------------------------------ - //
// GameEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_GameEngine_H__
#define __Game_PuffBOMB_GameEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
class cGameEngine : public Engine2D::cEngine2D { 
public:
	// Custom Camera used to create a HUD //
	cCamera *HudCamera;

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