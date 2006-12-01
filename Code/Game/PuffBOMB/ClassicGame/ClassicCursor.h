// - ------------------------------------------------------------------------------------------ - //
// ClassicCursor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __ClassicGame_PuffBOMB_ClassicCursor_H__
#define __ClassicGame_PuffBOMB_ClassicCursor_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include "BombInfo.h"
// - ------------------------------------------------------------------------------------------ - //
class cClassicCursor { 
public:
	// Position of the cursor //
	Vector2D Pos;
	
	int Selection;

	// Vector of bomb information to be added //
	std::vector< cBombInfo > Bomb;

public:
	cClassicCursor();
	~cClassicCursor();
	
public:
	void Step();
	void Draw();

public:	
	inline bool CanPlaceBombHere() const {
		return CanPlaceBombHere( Pos );
	}
	
	bool CanPlaceBombHere( const Vector2D& _Pos ) const;
	
	
	inline int WhatBombIsHere() const {
		return WhatBombIsHere( Pos );
	}

	int WhatBombIsHere( const Vector2D& _Pos ) const;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __ClassicGame_PuffBOMB_ClassicCursor_H__ // 
// - ------------------------------------------------------------------------------------------ - //
