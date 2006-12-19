// - ------------------------------------------------------------------------------------------ - //
// ClassicCursor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __ClassicGame_PuffBOMB_ClassicCursor_H__
#define __ClassicGame_PuffBOMB_ClassicCursor_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Animation/Animator.h>
#include "BombInfo.h"
// - ------------------------------------------------------------------------------------------ - //
class cClassicCursor { 
public:
	// Position of the cursor //
	Vector2D Pos;
	
	// Currently Selected Bomb //
	int Selection;
	
	// Boolean describing what edit mode you're in (Position or Time) //
	bool TimeMode;

	// Vector of bomb information to be added //
	std::vector< cBombInfo > Bomb;
	cAnimator BombGraphic;

public:
	cClassicCursor();
	~cClassicCursor();
	
public:
	void Step();
	void Draw();

public:	
	// Check if a Bomb can be placed at a position //
	bool CanPlaceBombHere( const Vector2D& _Pos ) const;
	inline bool CanPlaceBombHere() const {
		return CanPlaceBombHere( Pos );
	}
	
	// Determine what bomb can be found at a position //
	int WhatBombIsHere( const Vector2D& _Pos ) const;
	inline int WhatBombIsHere() const {
		return WhatBombIsHere( Pos );
	}

	// Make sure a bomb isn't inside another bomb //
	void PushMeOutOfOtherBombs( const int _Selection );
	inline void PushMeOutOfOtherBombs() {
		PushMeOutOfOtherBombs( Selection );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __ClassicGame_PuffBOMB_ClassicCursor_H__ // 
// - ------------------------------------------------------------------------------------------ - //
