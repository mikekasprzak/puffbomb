// - ------------------------------------------------------------------------------------------ - //
// Sphere //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Constraints_Constraint_Sphere_H__
#define __Engine2D_Physics_Constraints_Constraint_Sphere_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Physics/Body2D/CollisionFlags.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cSphere {
public:
	Real Radius;
	cCollisionFlags Flags;

	// Indices at the end for consistency //
	size_t Index;

public:
	inline cSphere() {
	}
	
	inline cSphere( size_t _Index ) :
		Radius( Real::One ),
		Index( _Index )
	{
	}

	inline const Real Area() {
		return Real::Pi * Radius * Radius;
	}
	
	inline const Real RadiusSquared() {
		return Radius * Radius;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Constraints_Constraint_Sphere_H__ //
// - ------------------------------------------------------------------------------------------ - //
