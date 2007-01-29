// - ------------------------------------------------------------------------------------------ - //
// Distortion //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_Distortion_H__
#define __Engine2D_Engine_Distortion_H__
// - ------------------------------------------------------------------------------------------ - //
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cDistortion: public Engine2D::cPassiveObject {
public:
	// ??? //

public:
	cDistortion( const Vector2D& _Pos ) :
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
#endif // __Engine2D_Engine_Distortion_H__ //
// - ------------------------------------------------------------------------------------------ - //
