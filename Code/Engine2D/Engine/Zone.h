// - ------------------------------------------------------------------------------------------ - //
// Zone //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_Zone_H__
#define __Engine2D_Engine_Zone_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cZone {
public:
	// Bounding rectangle, the only thing a Zone has going for it, beyond actions //
	cPhysics::BoundingRectType BoundingRect;
	
	int Id;
	int Argument;

public:
	cZone( const Vector2D Pos1, const Vector2D Pos2 ) :
		BoundingRect( cPhysics::BoundingRectType::Pair( Pos1, Pos2 ) ),
		Id( 0 ),
		Argument( 0 )
	{
	}

public:
	void Action( class cDynamicObject& _Vs );
	bool InitZone( );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_Zone_H__ //
// - ------------------------------------------------------------------------------------------ - //
