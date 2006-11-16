// - ------------------------------------------------------------------------------------------ - //
// BasicBomb //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_BasicBomb_H__
#define __PuffBOMB_Objects_BasicBomb_H__
// - ------------------------------------------------------------------------------------------ - //
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cBasicBomb: public Engine2D::cPassiveObject {
public:
	// How many frames to wait before exploding //
	int FrameClock;

public:
	cBasicBomb( const Vector2D& _Pos, int _FrameClock = 60 ) :
		cPassiveObject( _Pos ),
		FrameClock( _FrameClock )
	{
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 32, 32 ), _Pos + Vector2D( 32, 32 ) );
	}

public:	
	virtual void Work();

public:
	// Messanging //
	//virtual void Action( class cDynamicComponent& _Vs );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_BasicBomb_H__ //
// - ------------------------------------------------------------------------------------------ - //
