// - ------------------------------------------------------------------------------------------ - //
#include <DynamicComponent/Body2D/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
bool cBody2D::Solve( cBody2D& _Vs ) {
	// Convert our pose parts in to something local //
	std::vector< cSphere >& Sphere = Pose->Sphere;
	std::vector< cSphere >& _VsSphere = _Vs.Pose->Sphere;

	// If Asleep, Bail //
//	if ( !IsAwake() )
//		if ( !_Vs.IsAwake() )
//			return;
	
	// Test Bounding Rectangles //
	if ( BoundingRect != _Vs.BoundingRect )
		return false;
		
	// *** Wake Up the other SphereObject *** //	
	
	
	bool Changed = false;
	
	// Test Sphere's //
	{
		for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < _VsSphere.size(); idx2++ ) {
				// Shorthand references to avoid typo errors //
				cSphere& MySphere = Sphere[ idx ];
				cSphere& HisSphere = _VsSphere[ idx2 ];
				
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
				if ( MySphere.Flags.Sensor() || Flags.ObjectSensor() ) {
					// And his is not //
					if ( !HisSphere.Flags.Sensor() && !_Vs.Flags.ObjectSensor() ) {
						// Note senses of an interaction with a sphere //
						SphereFlags[ idx ].SetObject().SetSphere();
						CollisionFlags.Set( SphereFlags[ idx ] );
						continue;
					}
				}

				// If his sphere is a sensor //
				if ( HisSphere.Flags.Sensor() || _Vs.Flags.ObjectSensor() ) {
					// And not mine // * Might be able to remove 'cause above test * //
					if ( !MySphere.Flags.Sensor() && !Flags.ObjectSensor() ) {
						// Note senses of an interaction with a sphere //
						_Vs.SphereFlags[ idx2 ].SetObject().SetSphere();
						_Vs.CollisionFlags.Set( _Vs.SphereFlags[ idx2 ] );
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
				SphereFlags[ idx ].SetObject().SetSphere();
				CollisionFlags.Set( SphereFlags[ idx ] );
					
				_Vs.Nodes.Pos( VsIndex ) -= HisPush;
//				_Vs.Nodes.Pos( VsIndex ) -= HisPush - (MyFriction * InvMass( Index ) * Diff);
				_Vs.SphereFlags[ idx2 ].SetObject().SetSphere();
				_Vs.CollisionFlags.Set( _Vs.SphereFlags[ idx2 ] );

				Changed = true;

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
	
	return Changed;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
