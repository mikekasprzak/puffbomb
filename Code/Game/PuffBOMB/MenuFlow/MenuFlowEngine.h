// - ------------------------------------------------------------------------------------------ - //
// MenuFlowEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __MenuFlow_PuffBOMB_MenuFlowEngine_H__
#define __MenuFlow_PuffBOMB_MenuFlowEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
#include <Animation/Animator.h>
// - ------------------------------------------------------------------------------------------ - //
#include "MenuManager.h"
// - ------------------------------------------------------------------------------------------ - //
class cMenuFlowEngine : public Engine2D::cEngine2D { 
public:
	// Custom Camera used to create a HUD //
	cCamera *HudCamera;

public:
	cMenuManager MenuManager;

	// Start point //
	Engine2D::cPassiveObject* StartPoint;
	
	// Engine State //
	int State;

public:
	cMenuFlowEngine( const std::string& FileName );
	~cMenuFlowEngine();
	
public:
	void Step();
	void Draw();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // MenuFlow // 
// - ------------------------------------------------------------------------------------------ - //
