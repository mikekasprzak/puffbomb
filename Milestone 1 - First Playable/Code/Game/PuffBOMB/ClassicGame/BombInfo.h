// - ------------------------------------------------------------------------------------------ - //
// BombInfo //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __ClassicGame_PuffBOMB_BombInfo_H__
#define __ClassicGame_PuffBOMB_BombInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cBombInfo { 
public:
	// Position of the Bomb //
	Vector2D Pos;

	// Fuse Length //
	int Time;

	// True if actually placed //
	bool Placed;
public:
	cBombInfo( const Vector2D& _Pos = Vector2D::Zero ) :
		Pos( _Pos ),
		Time( 10 ),
		Placed( true )
	{
	}
	
	~cBombInfo() {
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __ClassicGame_PuffBOMB_BombInfo_H__ // 
// - ------------------------------------------------------------------------------------------ - //
