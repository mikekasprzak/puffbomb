// - ------------------------------------------------------------------------------------------ - //
// ExitVortex //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_ExitVortex_H__
#define __Engine2D_Engine_ExitVortex_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <PassiveObject/PassiveCommonClockObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cExitVortex: public Engine2D::cPassiveCommonClockObject {
public:
	cAnimator Face;

public:
	cExitVortex( const Vector2D& _Pos ) :
		cPassiveCommonClockObject( "LargeVortex.anim", _Pos ),
		Face( "VortexEyes.anim" )
	{
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 32, 32 ), _Pos + Vector2D( 32, 32 ) );
	}

public:
	virtual void StepAnimation();
	virtual bool Work();
	virtual void Draw();

public:
	// Messanging //
	//virtual int Message( int Msg, cDynamicComponent* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_ExitVortex_H__ //
// - ------------------------------------------------------------------------------------------ - //
