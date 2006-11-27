// - ------------------------------------------------------------------------------------------ - //
// PassiveObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_PassiveObject_H__
#define __Engine2D_Engine_PassiveObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Physics/Physics.h>

#include <Animation/Animator.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cPassiveObject {
public:
	Vector2D Pos;
	
	int Argument;
	
	cAnimator Animator;

public:
	// Bounding rectangle //
	cPhysics::BoundingRectType BoundingRect;
	// Draw it //
	void DrawBoundingRect( const bool Selected = false ) const;

public:
	cPassiveObject() :
		Argument( 0 )
	{
	}
	
	cPassiveObject( const Vector2D& _Pos, int _Argument = 0 ) :
		Pos( _Pos ),
		Argument( _Argument )
	{
	}
	
	virtual ~cPassiveObject()
	{
		
	}

public:	
	void Draw() const;
	void DebugDraw() const;
	
	virtual void Work();

public:
	// Messanging //
	virtual void Action( class cDynamicComponent& _Vs );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_PassiveObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
