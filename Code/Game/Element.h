// - ------------------------------------------------------------------------------------------ - //
// Element //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_Element_H__
#define __Game_Element_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cElement {
public:
	Vector2D Pos;
	
	int Id;
	int Argument;
	
public:
	cElement( const Real _x, const Real _y ) :
		Pos( _x, _y ),
		Id( 0 ),
		Argument( 0 )
	{
	}
	cElement( const Vector2D _Pos ) :
		Pos( _Pos ),
		Id( 0 ),
		Argument( 0 )
	{
	}
	
	//void Action( const class cSphereObject& Vs );
	//void Action( const class cPolyObject& Vs );
	
	bool InitElement( );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_Element_H__ //
// - ------------------------------------------------------------------------------------------ - //