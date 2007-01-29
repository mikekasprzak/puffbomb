// - ------------------------------------------------------------------------------------------ - //
// PassiveObjectInstanceInfo //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_PassiveObjectInstanceInfo_H__
#define __Engine2D_PassiveObjectInstanceInfo_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cPassiveObjectInstanceInfo {
public:
	int Id;
	Vector2D Pos;
	int Arg;
	
public:
	cPassiveObjectInstanceInfo() :
		Id( 0 ),
		Pos( Vector2D::Zero ),
		Arg( 0 )
	{
		
	}
	cPassiveObjectInstanceInfo( const int _Id, const Vector2D _Pos, const int _Arg = 0 ) :
		Id( _Id ),
		Pos( _Pos ),
		Arg( _Arg )
	{
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_PassiveObjectInstanceInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
