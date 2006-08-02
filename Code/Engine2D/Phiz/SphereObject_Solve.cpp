// - ------------------------------------------------------------------------------------------ - //
// SphereObject_Solve //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "SphereObject.h"
// - ------------------------------------------------------------------------------------------ - //
#include "PolyObject.h"
#include "StaticObject.h"
#include "Impulse.h"
#include <Game/Zone.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::Solve( cSphereObject& Vs ) {
	// If Asleep, Bail //
	if ( !IsAwake() )
		if ( !Vs.IsAwake() )
			return;
	
	// Test Bounding Rectangles //
	if ( BoundingRect != Vs.BoundingRect )
		return;
		
	// *** Wake Up the other SphereObject *** //	
	
	// Test Sphere's //
	{
		for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Vs.Sphere.size(); idx2++ ) {
				const int& Index = Sphere[ idx ].Index;
				const int& VsIndex = Vs.Sphere[ idx2 ].Index;

				// Sum of Radius //				
				Real RadiusSum = Sphere[ idx ].Radius + Vs.Sphere[ idx2 ].Radius;
				Real RadiusSumSquared = RadiusSum * RadiusSum;
				
				// Optimized Verlet with Square Root Approximation //
				Vector2D Ray = Vs.Pos( VsIndex ) - Pos( Index );
				
				// Bail if not touching //
				if ( RadiusSumSquared < Ray.MagnitudeSquared() )
					continue;
				
//				// Massless with square root approximation //
//				Ray *= (RadiusSumSquared) / ( (Ray * Ray) + (RadiusSumSquared) ) - Real( 0.5 );
//				
//				Pos( Index ) -= Ray;
//				Vs.Pos( VsIndex ) += Ray;

				// Mass with square root //
				Vector2D RayNormal = Ray;
				Real RayLength = RayNormal.NormalizeRet();
				
				Real Divisor = RayLength * (InvMass( Index ) + Vs.InvMass( VsIndex ));
				if ( Divisor.IsZero() )
					continue;
				Real Diff = (RayLength - RadiusSum) / Divisor;
				
				Vector2D MyPush = InvMass( Index ) * Ray * Diff;
				Vector2D HisPush = Vs.InvMass( VsIndex ) * Ray * Diff;
				
				Vector2D MyFriction = (RayNormal.Tangent() * Velocity( Index )) * RayNormal.Tangent();
				Vector2D HisFriction = (RayNormal.Tangent() * Vs.Velocity( VsIndex )) * RayNormal.Tangent();

				Pos( Index ) += MyPush;
//				Pos( Index ) += MyPush - (HisFriction * Vs.InvMass( VsIndex ) * Diff);
				Sphere[ idx ].Flags.SetObject().SetSphere();
				Flags.Set( Sphere[ idx ].Flags );
					
				Vs.Pos( VsIndex ) -= HisPush;
//				Vs.Pos( VsIndex ) -= HisPush - (MyFriction * InvMass( Index ) * Diff);
				Vs.Sphere[ idx2 ].Flags.SetObject().SetSphere();
				Vs.Flags.Set( Vs.Sphere[ idx2 ].Flags );



				// Friction "A - A dot B * B" //
//				Old( Index ) += MyFriction;
//				Vs.Old( VsIndex ) += HisFriction;

				// Friction "A - Sign(A dot B) * B * PushLength //
//				Old( Index ) +=
//					(RayNormal.Tangent() * Velocity( Index )).Normal() *
//					RayNormal.Tangent() *
//					MyPush.Magnitude();
//
//				Vs.Old( VsIndex ) +=
//					(RayNormal.Tangent() * Vs.Velocity( VsIndex )).Normal() *
//					RayNormal.Tangent() *
//					HisPush.Magnitude();
				
				// Friction Hack //
				//SetFriction( Index, cPhysics::ObjectFriction );
				//Vs.SetFriction( VsIndex, cPhysics::ObjectFriction );

				// Wake Up Hack //
				WakeUp();
				Vs.WakeUp();
			}
		};
	
		// Sensor Spheres.  See other objects //
		for ( size_t idx = 0; idx < SensorSphere.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Vs.Sphere.size(); idx2++ ) {
				// Optimized Verlet with Square Root Approximation //
				Vector2D Ray = Vs.Pos( Vs.Sphere[ idx2 ].Index ) - Pos( SensorSphere[ idx ].Index );
				
				Real RadiusSum = SensorSphere[ idx ].Radius + Vs.Sphere[ idx2 ].Radius;
				Real RadiusSumSquared = RadiusSum * RadiusSum;
				
				// Bail if not touching //
				if ( RadiusSumSquared < Ray.MagnitudeSquared() )
					continue;

				SensorSphere[ idx ].Flags.SetObject().SetSphere();
				Flags.Set( SensorSphere[ idx ].Flags );
				Vs.Sphere[ idx2 ].Flags.SetObject().SetSphere();				
				Vs.Flags.Set( Vs.Sphere[ idx2 ].Flags );
			}
		}	
	}

	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
	Vs.CalcBoundingRect();
}

// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::Solve( cPolyObject& Vs ) {
	// If Asleep, Bail //
	if ( !IsAwake() )
		if ( !Vs.IsAwake() )
			return;
	
	// Test Bounding Rectangles //
	if ( BoundingRect != Vs.BoundingRect )
		return;
		
	// *** Wake Up the other SphereObject *** //
	WakeUp();
	Vs.WakeUp();
		

	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
	Vs.CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::Solve( cStaticObject& Vs ) {
	// Test Bounding Rectangles //
	if ( BoundingRect != Vs.BoundingRect )
		return;

	// Find overlap Region //		
	RectType OverlapRect = BoundingRect - Vs.BoundingRect;

	// Find all spheres //
	std::vector< int > SphereIndex;							// Store this Vector in thread/worker //
	std::vector< RectType > SphereRect;
	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		// Make a rectangle for the sphere //
		RectType Rect = RectType::Pair(
			Pos( Sphere[ idx ].Index ) - Sphere[ idx ].Radius,
			Pos( Sphere[ idx ].Index ) + Sphere[ idx ].Radius
			);
		// Test the sphere against the region //
		if ( OverlapRect == Rect ) {
			SphereIndex.push_back( idx );
			SphereRect.push_back( Rect );
		}
	}
	
	// Find all polygons //
	std::vector< int > PolyIndex;							// Store this Vector in thread/worker //
	for ( size_t idx = 0; idx < Vs.Polygon.size(); idx++ ) {
		if ( OverlapRect == Vs.Polygon[idx].BoundingRect ) {
			PolyIndex.push_back( idx );
		}
	}
	// Find all edges //
	std::vector< int > EdgeIndex;							// Store this Vector in thread/worker //
	for ( size_t idx = 0; idx < Vs.Edge.size(); idx++ ) {
		//if ( OverlapRect == Vs.Edge[idx].BoundingRect )
		{
			EdgeIndex.push_back( idx );
		}
	}
	
	
	// Do tests //
	for ( size_t idx = 0; idx < SphereIndex.size(); idx++ ) {
		// Store the Point //
		Vector2D& Point = Pos( Sphere[ SphereIndex[idx] ].Index );
		Vector2D& PointOld = Old( Sphere[ SphereIndex[idx] ].Index );
		Vector2D PointVelocity = Velocity( Sphere[ SphereIndex[idx] ].Index );

		// Versus Edges //
		for ( size_t idx2 = 0; idx2 < EdgeIndex.size(); idx2++ ) {
			// Rectangles throw away test (overkill?) //
			if ( Vs.Edge[ EdgeIndex[idx2] ].BoundingRect == SphereRect[idx] ) {
				// Find the closest point on the edge to us //
				int ClosestFlags = 0;
				Vector2D PointOnEdge = Vs.Edge[ EdgeIndex[idx2] ].ClosestPoint( Vs, Point, ClosestFlags );
				
				// If the closest point was a corner, bail, as we'd prefer to solve with edges first //
				if ( ClosestFlags & cStaticEdge::flCorner )
					continue;
				
				// Trace a vector to the closest point //
				Vector2D ToPoint = PointOnEdge - Point;
				
				// If touching the edge //
				if ( ToPoint.MagnitudeSquared() < Sphere[ SphereIndex[idx] ].RadiusSquared() ) {
					// Calculate the penetration depth of the collision //
					Real Penetration = Sphere[ SphereIndex[idx] ].Radius - ToPoint.Magnitude();

					// Solving //
					Point -= Penetration * ToPoint.Normal() * Real::Half;
					
					// Friction //
					// 0 - Perfecly Ice like friction surface //
					// 1 - Perfectly sticky surface (kills all motion) //
					Real Friction = (ToPoint.Normal().Tangent() *
						Velocity( Sphere[ SphereIndex[idx] ].Index )) *
						Real( 0.02 );
					
					Point -= Friction * ToPoint.Normal().Tangent();

					// Restitution //
					// 0 - Perfect dampening //
					// 1 - Perfect bounce //
					Real DistanceToSurface = ToPoint.Normal() * Velocity( Sphere[ SphereIndex[idx] ].Index );
					if ( DistanceToSurface > 0 ) {
						// Mirroring, to emulate restitution //
						PointOld += ( DistanceToSurface +
							(DistanceToSurface * Real( 0.2 ) ) ) *
							ToPoint.Normal();
					}

					// Set Flags //
					Sphere[ SphereIndex[idx] ].Flags.SetScenery().SetPolygon().SetEdge();
					Flags.Set( Sphere[ SphereIndex[idx] ].Flags );

					
					//Real Penetration = (ToPoint * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal());
					//Real Push = Penetration + Sphere[ SphereIndex[idx] ].Radius;
					
					//Real PowerPush = PointVelocity * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal();

//					// Get Rotational Energy //
//					Sphere[ SphereIndex[idx] ].RotationalEnergy +=
//						//-Sphere[ SphereIndex[idx] ].RotationalEnergy +
//						( ( Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() *
//						Velocity( Sphere[ SphereIndex[idx] ].Index ) ).Normal() *
//						Push );
					
					// Solve //
					//Point += (Push * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal());
					
//						if ( Velocity( Sphere[ SphereIndex[idx] ].Index ) * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal() > Real::Zero ) {
							// Cancel out surface normal parellel velocity //
//							PointOld += (PowerPush - Penetration) * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal();
							// Surface restitution //
							//PointOld += (PowerPush) * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal();
//						}
//					}
					
					
					// Push out of Scenery //
					//Point += (Push * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal()) * Real::Half;
					//Point -= ToPoint;// + (ToPoint.Normal() * Sphere[ SphereIndex[idx] ].Radius);// * Real::Half;


//					PointOld += (ToPoint.Normal() * Velocity( Sphere[ SphereIndex[idx] ].Index ) * Real(2) ) *
//						ToPoint.Normal();


//					Point += (PointVelocity.Magnitude() - 
//						Velocity( Sphere[ SphereIndex[idx] ].Index ).Magnitude()) *
//						ToPoint.Normal().Tangent();
						
					
					
//					PointOld += ((Velocity( Sphere[ SphereIndex[idx] ].Index ) * ToPoint.Normal()) * ToPoint.Normal()) +
//								(Velocity( Sphere[ SphereIndex[idx] ].Index ) * ToPoint.Normal()) * ToPoint.Normal();
					
//					if ( !(Velocity( Sphere[ SphereIndex[idx] ].Index ).IsZero()) ) {
//						Real PowPush;
//						if ( !(PowerPush.IsZero()) )
//							PowPush = ( Push / PowerPush ).Abs().Max( Real::One );
//						
//						Real StrengthChange;
//						if ( !(PointVelocity.MagnitudeSquared().IsZero()) )
//							StrengthChange = ( Velocity( Sphere[ SphereIndex[idx] ].Index ).Magnitude() / PointVelocity.Magnitude() ).Max( Real::One );
//													
//						// Push back quantity of friction //
//						Point -= Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() *
//							( ( Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * PointVelocity ) *
//							PowPush *
//							StrengthChange *
//							Real(0.99) );
//					}						

//					Point += Sphere[ SphereIndex[idx] ].RotationalEnergy *
//							(Real::One / Real( Sphere[ SphereIndex[idx] ].Radius )) *
//							Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent();
//					
//					Sphere[ SphereIndex[idx] ].RotationalEnergy *= Real::Half;


//					Point += Sphere[ SphereIndex[idx] ].RotationalEnergy.Abs().Sqrt() * Sphere[ SphereIndex[idx] ].RotationalEnergy.Normal() *
//							(Real::One / Real( Sphere[ SphereIndex[idx] ].Radius )) *
//							Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent();

					
					// Friction "A - A dot B * B" //
//					Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * Velocity( Sphere[ SphereIndex[idx] ].Index )) *
//						Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent();

					// Friction "A - Sign(A dot B) * B * PushLength //
//					Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * Velocity( Sphere[ SphereIndex[idx] ].Index )).Normal() *
//						Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() *
//						Push;

					// Friction Hack//
					//SetFriction( Sphere[ SphereIndex[idx] ].Index, Vs.Friction );
					
					// Mark this object as solved, so not to do polygon testing on (Optimization) //
				}
			}
		}
		
		// Versus Corners of Edges //
		for ( size_t idx2 = 0; idx2 < EdgeIndex.size(); idx2++ ) {
			// Rectangles throw away test (overkill?) //
			if ( Vs.Edge[ EdgeIndex[idx2] ].BoundingRect == SphereRect[idx] ) {
				// Get the first point (a) of an edge //
				Vector2D& VersusPoint = Vs.Pos( Vs.Edge[ EdgeIndex[idx2] ].a );
				
				// Trace a vector to the point //
				Vector2D ToPoint = VersusPoint - Point;
				
				// If touching the edge //
				if ( ToPoint.MagnitudeSquared() < Sphere[ SphereIndex[idx] ].RadiusSquared() ) {
					// Calculate the penetration depth of the collision //
					Real Penetration = Sphere[ SphereIndex[idx] ].Radius - ToPoint.Magnitude();

					// Solving //
					Point -= Penetration * ToPoint.Normal() * Real::Half;
					
					// Friction //
					// 0 - Perfecly Ice like friction surface //
					// 1 - Perfectly sticky surface (kills all motion) //
					Point -= (ToPoint.Normal().Tangent() *
						Velocity( Sphere[ SphereIndex[idx] ].Index )) *
						ToPoint.Normal().Tangent() * Real( 0.02 );

					// Restitution //
					// 0 - Perfect dampening //
					// 1 - Perfect bounce //
					Real DistanceToSurface = ToPoint.Normal() * Velocity( Sphere[ SphereIndex[idx] ].Index );
					if ( DistanceToSurface > 0 ) {
						// Mirroring, to emulate restitution //
						PointOld += ( DistanceToSurface +
							(DistanceToSurface * Real( 0.2 ) ) ) *
							ToPoint.Normal();
					}

					// Set Flags //
					Sphere[ SphereIndex[idx] ].Flags.SetScenery().SetPolygon().SetCorner();
					Flags.Set( Sphere[ SphereIndex[idx] ].Flags );
				}				
			}			
		}

		// Versus Polygons //
		{
			bool Inside = false;
			
			// See if sphere is inside any polygon //
			for ( size_t idx2 = 0; idx2 < PolyIndex.size(); idx2++ ) {
				// Rectangles throw away test //
				if ( Vs.Polygon[ PolyIndex[idx2] ].BoundingRect == SphereRect[idx] ) {
					// The number of sides found, so far //
					size_t SideCount = 0;

					// An optimization.  As long as it's only 1 more, we can re use if to the end //
					Vector2D ToCorner;
					
					// Check if we're inside all sides except the last //
					for ( size_t idx3 = 0; idx3 < Vs.Polygon[ PolyIndex[idx2] ].Index.size() - 1; idx3++ ) {
						Vector2D Segment =
							Vs.Pos( Vs.Polygon[ PolyIndex[idx2] ].Index[idx3 + 1] ) -
							Vs.Pos( Vs.Polygon[ PolyIndex[idx2] ].Index[idx3] );
						
						ToCorner = Vs.Pos( Vs.Polygon[ PolyIndex[idx2] ].Index[idx3 + 1] ) - Point;
						
						// If Inside this side //
						if ( (-Segment.Tangent()) * ToCorner > Real::Zero )
							SideCount++;
						else
							break;
					}

					// If we bailed early, we're not inside //
					if ( SideCount != Vs.Polygon[ PolyIndex[idx2] ].Index.size() - 1 )
						continue;
						
					// Test last side //
					Vector2D Segment =
						Vs.Pos( Vs.Polygon[ PolyIndex[idx2] ].Index[0] ) -
						Vs.Pos( Vs.Polygon[ PolyIndex[idx2] ].Index[SideCount] );
					
					// If you are inside, great!  That's all we care about. //
					if ( (-Segment.Tangent()) * ToCorner > Real::Zero ) {
						Inside = true;
						break;
					}
				}
			}
			
			// If you are (confirmed), find the closest point on the nearest edge //
			if ( Inside ) {
				bool FoundPoint = false;
				Vector2D Push;
				Real Mag;
				
				// Search optimized edges //
				for ( size_t idx2 = 0; idx2 < EdgeIndex.size(); idx2++ ) {
					// Motion Vector half space throw away test (Bad, as it allows perfect squishes to go through) //
					//if ( Velocity( Sphere[ SphereIndex[idx] ].Index ) * Vs.Edge[ EdgeIndex[idx2] ].Normal <= Real::Zero )
					{
						Vector2D PointOnEdge = Vs.Edge[ EdgeIndex[idx2] ].ClosestPoint( Vs, Point );
						
						if ( !FoundPoint ) {
							Push = PointOnEdge - Point;
							Mag = Push.MagnitudeSquared();
							FoundPoint = true;
						}
						else {
							Vector2D ToEdge = PointOnEdge - Point;
							Real NewMag = ToEdge.MagnitudeSquared();
							
							if ( NewMag < Mag ) {
								Push = ToEdge;
								Mag = NewMag;
							}
						}
					}
				}
				
				// If none found, search all edges for nearest //
				if ( !FoundPoint ) {
					for ( size_t idx2 = 0; idx2 < Vs.Edge.size(); idx2++ ) {
						// Motion Vector half space throw away test (Bad, as it allows perfect squishes to go through) //
						//if ( Velocity( Sphere[ SphereIndex[idx] ].Index ) * Vs.Edge[idx2].Normal <= Real::Zero )
						{
							Vector2D PointOnEdge = Vs.Edge[idx2].ClosestPoint( Vs, Point );
							
							if ( !FoundPoint ) {
								Push = PointOnEdge - Point;
								Mag = Push.MagnitudeSquared();
								FoundPoint = true;
							}
							else {
								Vector2D ToEdge = PointOnEdge - Point;
								Real NewMag = ToEdge.MagnitudeSquared();
								
								if ( NewMag < Mag ) {
									Push = ToEdge;
									Mag = NewMag;
								}
							}
						}
					}
					
				}
				
				// Solve for the found edge //
				if ( FoundPoint ) {
					// Solve //
					Push += (Push.Normal() * Sphere[ SphereIndex[idx] ].Radius);
					Point += Push * Real::Half;
						
					// Friction //
					Point -= (Push.Normal().Tangent() *
						Velocity( Sphere[ SphereIndex[idx] ].Index )) *
						Push.Normal().Tangent() * Real( 0.02 );
						

					// Set Flags //
					Sphere[ SphereIndex[idx] ].Flags.SetScenery().SetPolygon().SetInside();
					Flags.Set( Sphere[ SphereIndex[idx] ].Flags );

					// Get Rotational Energy //
//					Sphere[ SphereIndex[idx] ].RotationalEnergy +=
//						Push.Normal().Tangent() * Velocity( Sphere[ SphereIndex[idx] ].Index );
//					
//					AddForce(
//						Sphere[ SphereIndex[idx] ].Index,
//						Sphere[ SphereIndex[idx] ].RotationalEnergy * Push.Normal().Tangent()
//						);
					
					// Friction "A - A dot B * B" //
//					Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(Push.Normal().Tangent() * Velocity( Sphere[ SphereIndex[idx] ].Index )) *
//						Push.Normal().Tangent();

					// Friction "A - Sign(A dot B) * B * PushLength //
//					Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(Push.Normal().Tangent() * Velocity( Sphere[ SphereIndex[idx] ].Index )).Normal() *
//						Push.Normal().Tangent() *
//						Push.Magnitude();

					// Friction Hack //
					//SetFriction( Sphere[ SphereIndex[idx] ].Index, Vs.Friction );
				}
				else {
					Log( 10, "ERROR!!!! NO EXIT POINT FOUND!!!!! *********" );
				}
			}
		}

	}

	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::Solve( cImpulse& Vs ) {
	// Test Bounding Rectangles //
//	if ( BoundingRect != Vs.BoundingRect )
//		return;


//	// Find overlap Region //		
//	RectType OverlapRect = BoundingRect - Vs.BoundingRect;
//
//	// Find all spheres //
//	std::vector< int > SphereIndex;							// Store this Vector in thread/worker //
//	std::vector< RectType > SphereRect;
//	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
//		// Make a rectangle for the sphere //
//		RectType Rect = RectType::Pair(
//			Pos( Sphere[ idx ].Index ) - Sphere[ idx ].Radius,
//			Pos( Sphere[ idx ].Index ) + Sphere[ idx ].Radius
//			);
//		// Test the sphere against the region //
//		if ( OverlapRect == Rect ) {
//			SphereIndex.push_back( idx );
//			SphereRect.push_back( Rect );
//		}
//	}

	//for ( size_t idx = 0; idx < SphereIndex.size(); idx++ ) {

	// Do tests //
	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		if ( !(Vs.GetForce( Pos( idx ) ) * InvMass( idx )).IsZero() ) {
			WakeUp();
			AddForce( idx, Vs.GetForce( Pos( idx ) ) * InvMass( idx ) );
		}
	}
	
	
	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::Solve( cZone& Vs ) {
	// Test Bounding Rectangles //
	if ( BoundingRect != Vs.BoundingRect )
		return;

	// Cheesy bounding rect version //
	Vs.Action( *this );
}
// - ------------------------------------------------------------------------------------------ - //
