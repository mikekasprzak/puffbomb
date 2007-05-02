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
private:
	class cClassicGameEngine* Engine;

public:
	// Position of the cursor //
	Vector2D Pos;
	
	// Parts for the Stick Accelerator //
	int Accelerator;
	Real SpeedScalar;
	
	// Currently Selected Bomb //
	int Selection;
	
	// Maximum number of bombs you can place in this level //
	int BombLimit;

	// Vector of bomb information to be added //
	std::vector< cBombInfo > Bomb;
	cAnimator BombGraphic;
	cAnimator BombTimer;
	cAnimator BombTab;

public:
	cClassicCursor();
	~cClassicCursor();
		
public:
	void Step();
	void Draw();

public:	
	// Check if a Bomb can be placed at a position //
	bool CanPlaceBombHere( const Vector2D& _Pos, const int Index = -1 ) const;
	inline bool CanPlaceBombHere( const int Index = -1 ) const {
		return CanPlaceBombHere( Pos, Index );
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
