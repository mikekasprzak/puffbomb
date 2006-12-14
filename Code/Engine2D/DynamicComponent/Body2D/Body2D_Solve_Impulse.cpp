// - ------------------------------------------------------------------------------------------ - //
#include <DynamicComponent/Body2D/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Impulse/Impulse.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
bool cBody2D::Solve( cImpulse& _Vs ) {
	// Convert our pose parts in to something local //
	std::vector< cSphere >& Sphere = Pose->Sphere;

	// Test Bounding Rectangles //
//	if ( BoundingRect != _Vs.BoundingRect )
//		return;

	bool Changed = false;

	// For all spheres //
	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		// Calculate the force applied by the impulse //
		Vector2D Force = _Vs.GetForce( Nodes.Pos( Sphere[ idx ].Index ) ) * Nodes.InvMass( Sphere[ idx ].Index );
		// If the force is worth caring about //
		if ( !Force.IsZero() ) {
			// If a sensor, note the touch of an impulse, but don't act on it //
			if ( Sphere[ idx ].Flags.Sensor() ) {
				SphereFlags[ idx ].SetImpulse();
				continue;
			}
			
			Nodes.AddForce( Sphere[ idx ].Index, Force );
			// Grow the bounding rectangle //
			GrowBoundingRectBySphere( idx );
			// Wake up and set flags //
			//WakeUp();
			SphereFlags[ idx ].SetImpulse();
			
			Changed = true;
		}
	}
	
	CalcBoundingRect();
	
	return Changed;
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::ApplyImpulse( const cImpulse& _Vs ) {
	std::vector< cSphere >& Sphere = Pose->Sphere;

	// For all spheres //
	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		// Calculate the force applied by the impulse //
		Vector2D Force = _Vs.GetForce( Nodes.Pos( Sphere[ idx ].Index ) ) * Nodes.InvMass( Sphere[ idx ].Index );
		// If the force is worth caring about //
		if ( !Force.IsZero() ) {
			// If a sensor, note the touch of an impulse, but don't act on it //
			if ( Sphere[ idx ].Flags.Sensor() ) {
				SphereFlags[ idx ].SetImpulse();
				continue;
			}
			
			Nodes.AddForce( Sphere[ idx ].Index, Force );
			// Grow the bounding rectangle //
			GrowBoundingRectBySphere( idx );
			// Wake up and set flags //
			//WakeUp();
			SphereFlags[ idx ].SetImpulse();
		}
	}
	
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
