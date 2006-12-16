// - ------------------------------------------------------------------------------------------ - //
// GolfGameEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GolfGame_PuffBOMB_GolfGameEngine_H__
#define __GolfGame_PuffBOMB_GolfGameEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
#include <Animation/Animator.h>

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
	
	// Our notable things to point out //
	std::vector< Engine2D::cPassiveObject* > PointsOfInterest;
		
		
		
	// Drop points (in case of pits or other hungry things) //
	std::vector< Engine2D::cPassiveObject* > DropPoint;
	const Vector2D FindNearestDrop( const Engine2D::cDynamicCollection& Obj );
	
	
	// Our current player //
	size_t CurrentPlayer;
	
	// Engine State //
	int State;

public:
	// Victory related variables //
	bool LevelComplete;
	int CharacterAtEndZone;

	bool HitBoundery;
	
	cAnimator PlayerAnimator;
	cAnimator EndingAnimator;
	
public:
	void TurnBasedPlay();

public:
	cGolfGameEngine( const std::string& FileName );
	~cGolfGameEngine();
	
public:
	void Step();
	void Draw();

	virtual int Message( int Msg, Engine2D::cDynamicCollection* Sender );
	virtual int Message( int Msg, Engine2D::cPassiveObject* Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // GolfGame // 
// - ------------------------------------------------------------------------------------------ - //
