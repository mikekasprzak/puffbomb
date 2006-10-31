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
	Vector2D Pos;
	std::string FileName;
	int Arg;

public:
	cStaticObjectInstanceInfo() :
		Pos( Vector2D::Zero ),
		FileName( "" ),
		Arg( 0 )
	{
		
	}
	cStaticObjectInstanceInfo( const Vector2D _Pos, const std::string _FileName, const int _Arg = 0 ) :
		Pos( Vector2D::Zero ),
		FileName( "" ),
		Arg( 0 )
	{
		
	}

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_StaticObjectInstanceInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
