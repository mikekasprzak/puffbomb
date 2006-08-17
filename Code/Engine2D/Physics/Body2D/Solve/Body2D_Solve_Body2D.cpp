// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::Solve( cBody2D& _Vs ) {
	// If Asleep, Bail //
//	if ( !IsAwake() )
//		if ( !_Vs.IsAwake() )
//			return;
	
	// Test Bounding Rectangles //
	if ( BoundingRect != _Vs.BoundingRect )
		return;
		
	// *** Wake Up the other SphereObject *** //	
	
	// Test Sphere's //
	{
		for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < _Vs.Sphere.size(); idx2++ ) {
				// Shorthand references to avoid typo errors //
				cSphere& MySphere = Sphere[ idx ];
				cSphere& HisSphere = _Vs.Sphere[ idx2 ];
				
				const int& Index = MySphere.Index;
				const int& VsIndex = HisSphere.Index;


				// Sum of Radius //				
				Real RadiusSum = MySphere.Radius + HisSphere.Radius;
				Real RadiusSumSquared = RadiusSum * RadiusSum;
				
				// Optimized Verlet with Square Root Approximation //
				Vector2D Ray = _Vs.Nodes.Pos( VsIndex ) - Nodes.Pos( Index );
				
				// Bail if not touching //
				if ( RadiusSumSquared < Ray.MagnitudeSquared() )
					continue;
				
				
				// If my sphere is a sensor //
				if ( MySphere.Sensor ) {
					// And his is not //
					if ( !HisSphere.Sensor ) {
						// Note senses of an interaction with a sphere //
						MySphere.Flags.SetObject().SetSphere();
						continue;
					}
				}

				// If his sphere is a sensor //
				if ( HisSphere.Sensor ) {
					// And not mine //
					if ( !MySphere.Sensor ) {
						// Note senses of an interaction with a sphere //
						HisSphere.Flags.SetObject().SetSphere();
						continue;
					}
				}
				
				
//				// Massless with square root approximation //
//				Ray *= (RadiusSumSquared) / ( (Ray * Ray) + (RadiusSumSquared) ) - Real( 0.5 );
//				
//				Nodes.Pos( Index ) -= Ray;
//				_Vs.Nodes.Pos( VsIndex ) += Ray;

				// Mass with square root //
				Vector2D RayNormal = Ray;
				Real RayLength = RayNormal.NormalizeRet();
				
				Real Divisor = RayLength * (Nodes.InvMass( Index ) + _Vs.Nodes.InvMass( VsIndex ));
				if ( Divisor.IsZero() )
					continue;
				Real Diff = (RayLength - RadiusSum) / Divisor;
				
				Vector2D MyPush = Nodes.InvMass( Index ) * Ray * Diff;
				Vector2D HisPush = _Vs.Nodes.InvMass( VsIndex ) * Ray * Diff;
				
				Vector2D MyFriction = (RayNormal.Tangent() * Nodes.Velocity( Index )) * RayNormal.Tangent();
				Vector2D HisFriction = (RayNormal.Tangent() * _Vs.Nodes.Velocity( VsIndex )) * RayNormal.Tangent();

				Nodes.Pos( Index ) += MyPush;
//				Nodes.Pos( Index ) += MyPush - (HisFriction * _Vs.InvMass( VsIndex ) * Diff);
				MySphere.Flags.SetObject().SetSphere();
				Collision.Set( MySphere.Flags );
					
				_Vs.Nodes.Pos( VsIndex ) -= HisPush;
//				_Vs.Nodes.Pos( VsIndex ) -= HisPush - (MyFriction * InvMass( Index ) * Diff);
				HisSphere.Flags.SetObject().SetSphere();
				_Vs.Collision.Set( HisSphere.Flags );



				// Friction "A - A dot B * B" //
//				Nodes.Old( Index ) += MyFriction;
//				_Vs.Nodes.Old( VsIndex ) += HisFriction;

				// Friction "A - Sign(A dot B) * B * PushLength //
//				Nodes.Old( Index ) +=
//					(RayNormal.Tangent() * Nodes.Velocity( Index )).Normal() *
//					RayNormal.Tangent() *
//					MyPush.Magnitude();
//
//				_Vs.Nodes.Old( VsIndex ) +=
//					(RayNormal.Tangent() * _Vs.Nodes.Velocity( VsIndex )).Normal() *
//					RayNormal.Tangent() *
//					HisPush.Magnitude();
				
				// Friction Hack //
				//SetFriction( Index, cPhysics::ObjectFriction );
				//_Vs.SetFriction( VsIndex, cPhysics::ObjectFriction );

				// Wake Up Hack //
//				WakeUp();
//				Vs.WakeUp();
			}
		};
	}

	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
	_Vs.CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
