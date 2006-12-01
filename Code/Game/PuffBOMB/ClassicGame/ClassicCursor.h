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
	
	int Selected;

	// Vector of bomb information to be added //
	std::vector< cBombInfo > Bomb;

public:
	cClassicCursor();
	~cClassicCursor();
	
public:
	void Step();
	void Draw();
	
	inline bool CanPlaceBombHere() {
		return CanPlaceBombHere( Pos );
	}
	
	bool CanPlaceBombHere( const Vector2D& _Pos );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __ClassicGame_PuffBOMB_ClassicCursor_H__ // 
// - ------------------------------------------------------------------------------------------ - //
