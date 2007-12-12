// - ------------------------------------------------------------------------------------------ - //
// ExitVortex //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_ExitVortex_H__
#define __Engine2D_Engine_ExitVortex_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
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
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 4, 4 ), _Pos + Vector2D( 4, 4 ) );
	}

public:
	virtual void StepAnimation();
	virtual bool Work();
	virtual void Draw();

public:
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicComponent* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_ExitVortex_H__ //
// - ------------------------------------------------------------------------------------------ - //
