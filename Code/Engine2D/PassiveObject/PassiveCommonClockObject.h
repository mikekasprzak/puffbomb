// - ------------------------------------------------------------------------------------------ - //
// PassiveCommonClockObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_PassiveCommonClockObject_H__
#define __Engine2D_Engine_PassiveCommonClockObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include "PassiveObject.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cPassiveCommonClockObject: public cPassiveObject {
public:
	static Real CommonClock;
	
public:
	cPassiveCommonClockObject() :
		cPassiveObject()
	{
	}
	
	cPassiveCommonClockObject( const Vector2D& _Pos, int _Argument = 0 ) :
		cPassiveObject( _Pos, _Argument )
	{
	}

	cPassiveCommonClockObject( const std::string& AnimationName, const Vector2D& _Pos, int _Argument = 0 ) :
		cPassiveObject( AnimationName, _Pos, _Argument )
	{
	}
	
	virtual ~cPassiveCommonClockObject()
	{
	}
	
public:
	inline static void SetClock( const Real& Clock ) {
		CommonClock = Clock;
	}
	
	inline static void ResetClock() {
		SetClock( Real::Zero );
	}
	
	inline static void StepClock() {
		CommonClock += Real( 0.001 );
		if ( CommonClock >= Real::One )
			CommonClock = Real::Zero;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_PassiveCommonClockObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
