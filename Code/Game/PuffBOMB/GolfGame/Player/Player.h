// - ------------------------------------------------------------------------------------------ - //
// Player //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_Player_Player_H__
#define __Game_PuffBOMB_Player_Player_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include <DynamicCollection/DynamicCollection.h>
// - ------------------------------------------------------------------------------------------ - //
class cPlayer { 
public:
	Engine2D::cDynamicCollection* MyObject;

public:
	// Elements of a Player //
	int Score;
	int Stroke;
	Vector2D BombPos;
	
	// Statistics //
	// int NumberOfShotsTaken;
	// something to represent the last position of the player, just in case he goes out of bounds //
	// Total Time taken over all turns (hahaha... stupid statistic) //
	
public:
	cPlayer( Engine2D::cDynamicCollection* _MyObject );
	virtual ~cPlayer();
	
public:
	virtual bool Control() = 0;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Player_Player_H__ // 
// - ------------------------------------------------------------------------------------------ - //
