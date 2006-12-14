// - ------------------------------------------------------------------------------------------ - //
// FXLibrary //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_FXLibrary_H__
#define __Rendo_FXLibrary_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class FXLibrary
{
public:
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	FXLibrary()
	{
		
	}
	
/*	static void Explosion1( const Vector2D& Pos );
	static void Explosion2( const Vector2D& Pos );
	static void Shot1( const Vector2D& Pos );
	static void MuzzleFlash( const Vector2D& Pos, const Vector2D& Direction );
	static void Smoke1( const Vector2D& Pos );
	static void Steam( const Vector2D& Pos, const Vector2D& Direction );*/
	
	static void Bomb( const Vector2D& Pos );
	static void CrazyTest( const Vector2D& Pos );
	static void CrazyPuffTest( const Vector2D& Pos );
	static void Rain( const Vector2D& Pos, const int Density = 20 );
	static void Drip( const Vector2D& Pos, const int Density = 8 );
	static void OutlineTest( const Vector2D& Pos );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_FXLibrary_H__ //
// - ------------------------------------------------------------------------------------------ - //
