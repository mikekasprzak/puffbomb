// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Impulse.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::Solve( cImpulse& _Vs ) {
	// Test Bounding Rectangles //
//	if ( BoundingRect != _Vs.BoundingRect )
//		return;

	// For all spheres //
	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		// Calculate the force applied by the impulse //
		Vector2D Force = _Vs.GetForce( Nodes.Pos( Sphere[ idx ].Index ) ) * Nodes.InvMass( Sphere[ idx ].Index );
		// If the force is worth caring about //
		if ( !Force.IsZero() ) {
			// If a sensor, note the touch of an impulse, but don't act on it //
			if ( Sphere[ idx ].Sensor ) {
				Sphere[ idx ].Flags.SetImpulse();
				continue;
			}
			
			Nodes.AddForce( Sphere[ idx ].Index, Force );
			// Grow the bounding rectangle //
			GrowBoundingRectBySphere( idx );
			// Wake up and set flags //
			//WakeUp();
			Sphere[ idx ].Flags.SetImpulse();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
