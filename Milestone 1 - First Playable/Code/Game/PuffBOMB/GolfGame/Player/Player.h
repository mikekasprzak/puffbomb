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
	bool Finished;
	
	bool Spawned;
	
	Vector2D BombPos;
	
	Vector2D MyLastDropPos;
	
	int InsignificantMotion;
	
	// Statistics //
	// int NumberOfShotsTaken;
	// something to represent the last position of the player, just in case he goes out of bounds //
	// Total Time taken over all turns (hahaha... stupid statistic) //
	
public:
	cPlayer( Engine2D::cDynamicCollection* _MyObject );
	virtual ~cPlayer();
	
public:
	virtual bool Control() = 0;

	inline const Vector2D GetCenter() const {
/*		if( MyObject->Component.size() > 1 )  // should change this so that its to the current player frame //
		{
			return MyObject->Component[ 1 ].Body.BoundingRect.Center();
		}
	*/
		return MyObject->Component[ 0 ].Body.BoundingRect.Center();
	}

	inline const Rect2D GetRect() const {
		return MyObject->Component[ 0 ].Body.BoundingRect.ToRect();
	}

	inline void AccumulateMotion() {
		if ( MyObject->IsActive() ) {
			if ( MyObject->Component[ 0 ].Body.Nodes.Motion < Real( 0.5 ) ) {
				InsignificantMotion++;
			}
			else {
				InsignificantMotion = 0;
			}
		}
		else {
			InsignificantMotion++;
		}
	}
	
	inline void AddScore( const int _Value ) {
		Score += _Value;
		if ( Score < 0 ) {
			Score = 0;
		}
	}
	
	inline void AddStroke() {
		Stroke++;
		if ( Stroke > 10 ) {
			Stroke = 10;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Player_Player_H__ // 
// - ------------------------------------------------------------------------------------------ - //
