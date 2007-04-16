// - ------------------------------------------------------------------------------------------ - //
// FXLibrary //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_FXLibrary_H__
#define __Rendo_FXLibrary_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Animation/Animation.h>
// - ------------------------------------------------------------------------------------------ - //
class FXLibrary
{
public:
	static cAnimation* Number[ 10 ];
	// - -------------------------------------------------------------------------------------- - //
	
public:
	// - -------------------------------------------------------------------------------------- - //
	FXLibrary()
	{
		
	}
	
	static void InitAnims();
	
	static void Bomb( const Vector2D& Pos );
	static void Pickup( const Vector2D& Pos, const int Points = 0 );
	static void CrazyTest( const Vector2D& Pos );
	static void CrazyPuffTest( const Vector2D& Pos );
	static void Rain( const Vector2D& Pos, const int Density = 20 );
	static void Drip( const Vector2D& Pos, const int Density = 8 );
	static void OutlineTest( const Vector2D& Pos );
	
	static void EnterVortex( const Vector2D& Pos, const int Points = 0 );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_FXLibrary_H__ //
// - ------------------------------------------------------------------------------------------ - //
