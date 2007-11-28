// - ------------------------------------------------------------------------------------------ - //
// GolfDrop //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_GolfDrop_H__
#define __PuffBOMB_Objects_GolfDrop_H__
// - ------------------------------------------------------------------------------------------ - //
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cGolfDrop: public Engine2D::cPassiveObject {
public:

public:
	cGolfDrop( const Vector2D& _Pos ) :
		cPassiveObject( _Pos )
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
#endif // __PuffBOMB_Objects_GolfDrop_H__ //
// - ------------------------------------------------------------------------------------------ - //
