// - ------------------------------------------------------------------------------------------ - //
// Physics //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Physics_H__
#define __Engine2D_Physics_Physics_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>

#include <Geometry/Real.h>
#include <Geometry/Vector.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cPhysics {
public:
	static cPhysics* Current;
public:	
	// Default components for physics //
	Real Friction;
	Vector2D Force;

	// Contact friction values //
	Real AirFriction;
	Real SurfaceFriction;
	Real ObjectFriction;

	// Spare internal variable set by collision code to return additional info about a collision //
	int OperationFlags;
	// Number of times to run the physics relaxation loop (springs and collision, not node steps) //
	int RelaxationSteps;
public:
	// Common Rectangle type for bounding boxes //
	typedef RadiusRect2D BoundingRectType;	

public:
	cPhysics();

public:
	// Claim the controlling Physics property //
	inline void SetActive() {
		Current = this;
	}

	// Normal functions for changing the state of gravity //	
	void NormalGravity();
	void ZeroGravity();
	
public:
	// Write the current status of physics to the log //
	void Dump();

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Physics_H__ //
// - ------------------------------------------------------------------------------------------ - //
