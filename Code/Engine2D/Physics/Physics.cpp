// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include "Physics.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cPhysics* cPhysics::Current;
// - ------------------------------------------------------------------------------------------ - //
// The settings found here should somehow become game specific. Else it could break old games. //
// - ------------------------------------------------------------------------------------------ - //
cPhysics::cPhysics() :
	Friction( Real::One ),
	AirFriction( 0.999f ),
	SurfaceFriction( 0.94 ), //( 0.795 ),
	ObjectFriction( 0.8f ),
	OperationFlags( 0 ),
	RelaxationSteps( 1 )
{
	// Use normal gravity //
	NormalGravity();
	
	// A log message to know what just happened //
	Dump();	
}
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::NormalGravity() {
	Force = Vector2D( 0.0f, -0.11f );
}
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::ZeroGravity() {
	Force = Vector2D::Zero;
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
