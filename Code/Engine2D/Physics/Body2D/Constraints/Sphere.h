// - ------------------------------------------------------------------------------------------ - //
// Sphere //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_Constraints_Sphere_H__
#define __Engine2D_Physics_Body2D_Constraints_Sphere_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Physics/Body2D/CollisionFlags.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cSphere {
public:
	// Node Index that's my position //
	size_t Index;
	// Radius of the Sphere //
	Real Radius;

	// Flags set with information about contacts //
	cCollisionFlags Flags;	
	// True if I'm a sensor (I collect flags only, no solving) //
	bool Sensor;

public:
	inline cSphere( const size_t _Index = 0, const Real _Radius = Real::One, const bool _Sensor = false ) :
		Index( _Index ),
		Radius( _Radius ),
		Sensor( _Sensor )
	{
	}

public:
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
#endif // __Engine2D_Physics_Body2D_Constraints_Sphere_H__ //
// - ------------------------------------------------------------------------------------------ - //
