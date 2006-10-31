// - ------------------------------------------------------------------------------------------ - //
// StaticObjectInstanceInfo //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_StaticObjectInstanceInfo_H__
#define __Engine2D_StaticObjectInstanceInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectInstanceInfo {
public:
	std::string FileName;
	Vector2D Pos;
	int Arg;

public:
	cStaticObjectInstanceInfo() :
		FileName( "" ),
		Pos( Vector2D::Zero ),
		Arg( 0 )
	{
		
	}
	cStaticObjectInstanceInfo( const std::string _FileName, const Vector2D _Pos, const int _Arg = 0 ) :
		FileName( _FileName ),
		Pos( _Pos ),
		Arg( _Arg )
	{
		
	}

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_StaticObjectInstanceInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
