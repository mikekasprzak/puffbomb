// - ------------------------------------------------------------------------------------------ - //
// Zone //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Zone_H__
#define __Engine2D_Zone_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cZone {
public:
	int Id;
	int Argument;

public:
	// Bounding rectangle, the only thing a Zone has going for it, beyond actions //
	cPhysics::BoundingRectType BoundingRect;
	// Draw it //
	void DrawBoundingRect( const bool Selected = false ) const;

public:
	cZone( const Vector2D Pos1, const Vector2D Pos2 ) :
		Id( 0 ),
		Argument( 0 ),
		BoundingRect( cPhysics::BoundingRectType::Pair( Pos1, Pos2 ) )
	{
	}

	cZone( const cPhysics::BoundingRectType _BoundingRect, const int _Id, const int _Arg = 0 ) :
		Id( _Id ),
		Argument( _Arg ),
		BoundingRect( _BoundingRect )
	{
		
	}
public:
	void DebugDraw() const;
public:
	// Messanging //
	virtual void Action( class cDynamicComponent& _Vs );
	
	// Functioning (actions to take with zones on initialization) //
	// Return true to kill it after executing //
	bool InitZone( );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Zone_H__ //
// - ------------------------------------------------------------------------------------------ - //
