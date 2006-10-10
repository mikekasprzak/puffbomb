// - ------------------------------------------------------------------------------------------ - //
#include "Physics.h"
// - ------------------------------------------------------------------------------------------ - //
Real cPhysics::Friction = Real::One;
Real cPhysics::AirFriction;
Real cPhysics::SurfaceFriction;
Real cPhysics::ObjectFriction;
Vector2D cPhysics::Force = Vector2D::Zero;
int cPhysics::OperationFlags = 0;
// - ------------------------------------------------------------------------------------------ - //
cPhysics::cPhysics() {
	Friction = Real::One;
	Force = Vector2D( 0.0f, -0.1f );
	AirFriction = 0.999f;
	SurfaceFriction = 0.94;//0.795f;
	ObjectFriction = 0.8f;
	
	// A log message to know what just happened //
	Log( LOG_HIGHEST_LEVEL, 
		"Physics entity created.\n" <<
		"- Global friction: " << Friction << "\n" <<
		"- Global force (gravity): " << Force.x << ", " << Force.y );
}
// - ------------------------------------------------------------------------------------------ - //
