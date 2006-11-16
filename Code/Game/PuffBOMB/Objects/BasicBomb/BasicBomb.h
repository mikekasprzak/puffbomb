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
	// ??? //

public:
	cBasicBomb( const Vector2D& _Pos ) :
		cPassiveObject( _Pos )
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
