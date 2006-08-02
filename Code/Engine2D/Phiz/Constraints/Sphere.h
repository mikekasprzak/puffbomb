// - ------------------------------------------------------------------------------------------ - //
// Sphere //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_Constraint_Sphere_H__
#define __Phiz_Constraint_Sphere_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Physics/CollisionFlags.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cSphere {
public:
	Real Radius;
	cCollisionFlags Flags;

	// Flags of interesting information set by the physics engine, for figuring stuff out //
//	int Flags;


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

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_Constraint_Sphere_H__ //
// - ------------------------------------------------------------------------------------------ - //
