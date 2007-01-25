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
#include "Player/PlayerInfo.h"
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
	cAnimator BombGraphic;
	
	// Engine State //
	int State;

public:
	// Victory related variables //
	bool LevelComplete;
	int CharacterAtEndZone;

	bool HitBoundery;


	cAnimator ArrowAnimator;
	std::vector < cAnimator > PlayerAnimators;
	std::vector < cAnimator > PointsOfInterestAnimators;

	bool IsHelp;
	
	Vector3D HelpTexVertex[ 4 ];
	Vector2D HelpTexUV[ 4 ];
	unsigned int HelpTexIndices[ 4 ];
	cTexture HelpTex;	
		
public:
	void TurnBasedPlay();

public:
	cGolfGameEngine( const std::string& FileName, const std::vector< cPlayerInfo >& _Players = std::vector< cPlayerInfo >(4), int _StartPlayer = 0 );
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
