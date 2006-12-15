// - ------------------------------------------------------------------------------------------ - //
// GolfCoin //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_GolfCoin_H__
#define __PuffBOMB_Objects_GolfCoin_H__
// - ------------------------------------------------------------------------------------------ - //
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cGolfCoin: public Engine2D::cPassiveObject {
public:
	int Variant;
	bool Collected;
public:
	cGolfCoin( const Vector2D& _Pos, int _Variant = 0 ) :
		cPassiveObject( _Pos ),
		Variant( _Variant ),
		Collected( false )
	{
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 64, 64 ), _Pos + Vector2D( 64, 64 ) );
	}

public:	
	virtual bool Work();

public:
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicComponent* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_GolfCoin_H__ //
// - ------------------------------------------------------------------------------------------ - //