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
		cPassiveObject( "BlueBomb.anim", _Pos ),
		FrameClock( _FrameClock )
	{
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 32, 32 ), _Pos + Vector2D( 32, 32 ) );
	}

public:	
	virtual bool Work();

public:
	// Messanging //
	//virtual int Message( int Msg, cDynamicComponent* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_BasicBomb_H__ //
// - ------------------------------------------------------------------------------------------ - //
