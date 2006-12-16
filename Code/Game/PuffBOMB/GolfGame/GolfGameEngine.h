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
		
		
		
	// Drop points (in case of ... pits) //
	std::vector< Engine2D::cPassiveObject* > DropPoint;
		
	const Vector2D FindNearestDrop( const Engine2D::cDynamicCollection& Obj ) {
		Vector2D Pos = Obj.Component[ 0 ].Body.BoundingRect.Center();
		Real BestDistance = (Pos - StartPoint->Pos).MagnitudeSquared();
		Vector2D BestDrop = StartPoint->Pos;
		
		for ( size_t idx = 0; idx < DropPoint.size(); idx++ ) {
			Real Distance = (Pos - DropPoint[ idx ]->Pos).MagnitudeSquared();
			if ( Distance < BestDistance ) {
				BestDistance = Distance;
				BestDrop = DropPoint[ idx ]->Pos;
			}
		}
		
		return BestDrop;
	}
	
	
	// Our current player //
	size_t CurrentPlayer;
	
	// Engine State //
	int State;

public:
	int CharacterAtEndZone;
	bool HitBoundery;
	
	cAnimator PlayerAnimator;
	cAnimator EndingAnimator;
	
public:
	void TurnBasedPlay();

public:
	cGolfGameEngine();
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
