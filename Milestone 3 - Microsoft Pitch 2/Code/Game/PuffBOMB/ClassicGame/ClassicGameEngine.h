// - ------------------------------------------------------------------------------------------ - //
// ClassicGameEngine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __ClassicGame_PuffBOMB_ClassicGameEngine_H__
#define __ClassicGame_PuffBOMB_ClassicGameEngine_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>

#include <Graphics/Texture.h>
#include <Animation/Animator.h>

#include "ClockHud.h"
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

	// Our notable things to point out //
	std::vector< Engine2D::cPassiveObject* > PointsOfInterest;

	cClockHud ClockHud;

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
	cAnimator ArrowAnimator;
	std::vector < cAnimator > PointsOfInterestAnimators;
		
	bool IsHelp;
	
	Vector3D HelpTexVertex[ 4 ];
	Vector2D HelpTexUV[ 4 ];
	unsigned int HelpTexIndices[ 4 ];
	cTexture HelpTex;
	
	Vector3D MiniMapTexVertex[ 4 ];
	Vector2D MiniMapTexUV[ 4 ];
	unsigned int MiniMapTexIndices[ 4 ];
	cTexture MiniMapTex;
	
	std::string MiniMapName;
	Real MiniMapXRatio;
	Real MiniMapYRatio;
	Real MiniMapRatio;
	Vector2D MiniMapCenterShift;
	
public:
	void MiniMapInit();
		
	void Step();
	void Draw();
	
	virtual void PhysicsStart();
	virtual void PhysicsEnd();
	
public:
	// - -------------------------------------------------------------------------------------- - //
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicCollection* Sender );
	virtual int Message( int Msg, Engine2D::cPassiveObject* Sender );	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // ClassicGame // 
// - ------------------------------------------------------------------------------------------ - //
