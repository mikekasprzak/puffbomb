// - ------------------------------------------------------------------------------------------ - //
// DynamicObjectInstanceInfo //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_DynamicObjectInstanceInfo_H__
#define __Engine2D_DynamicObjectInstanceInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObjectInstanceInfo {
public:
	Vector2D Pos;
	int Id;
	int Arg;
	
public:
	cDynamicObjectInstanceInfo() :
		Pos( Vector2D::Zero ),
		Id( 0 ),
		Arg( 0 )
	{
		
	}
	cDynamicObjectInstanceInfo( const Vector2D _Pos, const int _Id, const int _Arg = 0 ) :
		Pos( _Pos ),
		Id( _Id ),
		Arg( _Arg )
	{
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_DynamicObjectInstanceInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
