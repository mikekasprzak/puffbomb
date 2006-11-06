// - ------------------------------------------------------------------------------------------ - //
// DynamicObjectInstanceInfo //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_DynamicObjectInstanceInfo_H__
#define __Engine2D_DynamicObjectInstanceInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObjectInstanceInfo {
public:
	class cComponent {
		std::vector< Vector2D > NodePos;
	};

public:
	int Id;
	Vector2D Pos;
	int Arg;

	std::vector< cComponent > Component;
	
public:
	cDynamicObjectInstanceInfo() :
		Id( 0 ),
		Pos( Vector2D::Zero ),
		Arg( 0 )
	{
		
	}
	cDynamicObjectInstanceInfo( const int _Id, const Vector2D _Pos, const int _Arg = 0 ) :
		Id( _Id ),
		Pos( _Pos ),
		Arg( _Arg )
	{
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_DynamicObjectInstanceInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
