// - ------------------------------------------------------------------------------------------ - //
// RainGenerator //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_RainGenerator_H__
#define __PuffBOMB_Objects_RainGenerator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cRainGenerator: public Engine2D::cPassiveObject {
public:
	// How often to create rain, lower the more frequent //
	int RainFreq;

	// How dense to make the Rain //
	int RainDensity;
	
	int LastTime;

public:
	cRainGenerator( const Vector2D& _Pos, int _RainFreq = 80 ) :
		cPassiveObject( _Pos ),
		RainFreq( _RainFreq ),
		RainDensity( 20 ),
		LastTime( 0 )
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
#endif // __PuffBOMB_Objects_RainGenerator_H__ //
// - ------------------------------------------------------------------------------------------ - //
