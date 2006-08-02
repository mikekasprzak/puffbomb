// - ------------------------------------------------------------------------------------------ - //
// DenseParticle //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_DenseParticle_H__
#define __Phiz_DenseParticle_H__
// - ------------------------------------------------------------------------------------------ - //

#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <Phiz/Physics.h>

#include <Util/ClassDesigner.h>
#include <Graphics/Gfx.h>

// - ------------------------------------------------------------------------------------------ - //
class cDenseParticle {
public:
	Vector2D Home;
	Real BreakPointSquared;
	
	Vector2D Pos;
	Vector2D Old;
	
	int Color;
	
	int TileNumber;
	std::list< cDenseParticle* >::iterator MyTile;
	
	enum {
		flLockedHome = bit0
	};
	int Flags;

public:
	cDenseParticle() :
		Color( gfx::RGB( 255, 255, 255 ) ),
		Flags( 0 )
	{
	}
	
	cDenseParticle( const Vector2D& _Pos, int _Color ) :
		Home( _Pos ),
		BreakPointSquared( Real( 2 ) ),
		Pos( _Pos ),
		Old( _Pos ),
		Color( _Color ),
		Flags( flLockedHome )
	{
	}
	
	const Vector2D Velocity() const {
		return Pos - Old;
	}
	
	void Reset() {
		Pos = Home;
		Old = Home;
	}
	
	void Step() {
		if ( (Flags & flLockedHome) ) {
//			if ( (Home - Pos).MagnitudeSquared() > BreakPointSquared ) {
//				Flags &= ~flLockedHome;
//			}
//			else {
				Pos = Home;
//			}			
		}
		else {
			Vector2D Swap = Pos;
			Pos += Velocity() + Vector2D( 0, -0.002 );// + cPhysics::Force; //(( + _Force[ idx ] ) * _Friction[ idx ]);
			Old = Swap;
		}
	}	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_DenseParticle_H__ //
// - ------------------------------------------------------------------------------------------ - //
