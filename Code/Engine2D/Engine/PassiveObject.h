// - ------------------------------------------------------------------------------------------ - //
// PassiveObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_PassiveObject_H__
#define __Engine2D_Engine_PassiveObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cPassiveObject {
public:
	Vector2D Pos;
	
	int Id;
	int Argument;
	
	//cAnimator Animator;

public:
	// Bounding rectangle //
	cPhysics::BoundingRectType BoundingRect;
	// Draw it //
	void DrawBoundingRect( const bool Selected = false ) const;

public:	
	void Draw() const;
	void DebugDraw() const;
	
	virtual void Work();

public:
	// Messanging //
	void Action( class cDynamicComponent& _Vs );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_PassiveObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
