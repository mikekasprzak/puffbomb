// - ------------------------------------------------------------------------------------------ - //
// Pickup //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_Pickup_H__
#define __PuffBOMB_Objects_Pickup_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <PassiveObject/PassiveObject.h>
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
class cPickup: public Engine2D::cPassiveObject {
public:
	int Variant;
	bool Collected;
public:
	cPickup( const std::string& AnimationName, const Vector2D& _Pos, int _Variant = 0 ) :
		cPassiveObject( AnimationName, _Pos ),
		Variant( _Variant ),
		Collected( false )
	{
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 64, 64 ), _Pos + Vector2D( 64, 64 ) );
			
		//Animator.Set( &AnimationPool.Load( AnimationName ), 0 );
	}

public:	
	virtual bool Work();

public:
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicComponent* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_Pickup_H__ //
// - ------------------------------------------------------------------------------------------ - //
