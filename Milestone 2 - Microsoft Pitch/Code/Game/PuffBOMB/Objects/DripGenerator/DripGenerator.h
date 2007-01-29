// - ------------------------------------------------------------------------------------------ - //
// DripGenerator //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_DripGenerator_H__
#define __PuffBOMB_Objects_DripGenerator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cDripGenerator: public Engine2D::cPassiveObject {
public:
	// How often to create Drip, lower the more frequent //
	int DripFreq;

	// How dense to make the Drip //
	int DripDensity;
	
	int LastTime;

public:
	cDripGenerator( const Vector2D& _Pos, int _DripFreq = 80 ) :
		cPassiveObject( _Pos ),
		DripFreq( _DripFreq ),
		DripDensity( 20 ),
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
#endif // __PuffBOMB_Objects_DripGenerator_H__ //
// - ------------------------------------------------------------------------------------------ - //
