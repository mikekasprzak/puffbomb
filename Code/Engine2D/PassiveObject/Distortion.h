// - ------------------------------------------------------------------------------------------ - //
// Distortion //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_Distortion_H__
#define __Engine2D_Engine_Distortion_H__
// - ------------------------------------------------------------------------------------------ - //
#include "PassiveObject.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDistortion: public cPassiveObject {
public:
	// ??? //

public:
	cDistortion( const Vector2D& _Pos ) :
		cPassiveObject( _Pos )
	{
		BoundingRect = cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 32, 32 ), _Pos + Vector2D( 32, 32 ) );
	}

public:	
	virtual void Work();

public:
	// Messanging //
	//virtual void Action( class cDynamicComponent& _Vs );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_Distortion_H__ //
// - ------------------------------------------------------------------------------------------ - //
