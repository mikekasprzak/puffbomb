// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include "Physics.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cPhysics* cPhysics::Current;
// - ------------------------------------------------------------------------------------------ - //
cPhysics::cPhysics() {
	Current = this;
	
	Friction = Real::One;
	Force = Vector2D( 0.0f, -0.1f );
	AirFriction = 0.999f;
	SurfaceFriction = 0.94;//0.795f;
	ObjectFriction = 0.8f;
	
	// Clear the Flags //
	OperationFlags = 0;
	
	// The number of times to do the relaxation loop //
	RelaxationSteps = 2;

	// A log message to know what just happened //
	Dump();	
}
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::Dump() {
	Log( LOG_HIGHEST_LEVEL, 
		"Physics entity created.\n" <<
		"- Global friction: " << Friction << "\n" <<
		"- Global force (gravity): " << Force.x << ", " << Force.y );	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
