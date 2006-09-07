// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/StaticBody2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::Solve( cStaticBody2D& _Vs, const Vector2D& _Offset ) {
	// Convert our pose parts in to something local //
	std::vector< cSphere >& Sphere = Pose->Sphere;

	// Test Bounding Rectangles //
	if ( (BoundingRect - _Offset) != _Vs.BoundingRect )
		return;

	// Find overlap Region //		
	cPhysics::BoundingRectType OverlapRect = (BoundingRect - _Offset) - _Vs.BoundingRect;

	// Find all spheres //
	std::vector< int > SphereIndex;							// Store this Vector in thread/worker //
	std::vector< cPhysics::BoundingRectType > SphereRect;
	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		// Make a rectangle for the sphere //
		cPhysics::BoundingRectType Rect = cPhysics::BoundingRectType::Pair(
			Nodes.Pos( Sphere[ idx ].Index ) - _Offset - Sphere[ idx ].Radius,
			Nodes.Pos( Sphere[ idx ].Index ) - _Offset + Sphere[ idx ].Radius
			);
		// Test the sphere against the region //
		if ( OverlapRect == Rect ) {
			SphereIndex.push_back( idx );
			SphereRect.push_back( Rect );
		}
	}
	
	// Find all polygons //
	std::vector< int > PolyIndex;							// Store this Vector in thread/worker //
	for ( size_t idx = 0; idx < _Vs.Polygon.size(); idx++ ) {
		if ( OverlapRect == _Vs.Polygon[idx].BoundingRect ) {
			PolyIndex.push_back( idx );
		}
	}
	// Find all edges //
	std::vector< int > EdgeIndex;							// Store this Vector in thread/worker //
	for ( size_t idx = 0; idx < _Vs.Edge.size(); idx++ ) {
		//if ( OverlapRect == _Vs.Edge[idx].BoundingRect )
		{
			EdgeIndex.push_back( idx );
		}
	}
	
	
	// Do tests //
	for ( size_t idx = 0; idx < SphereIndex.size(); idx++ ) {
		// Store the Point //
		Vector2D Point = Nodes.Pos( Sphere[ SphereIndex[idx] ].Index ) - _Offset;
		Vector2D PointOld = Nodes.Old( Sphere[ SphereIndex[idx] ].Index ) - _Offset;
		Vector2D PointVelocity = Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index );

		// Versus Edges //
		for ( size_t idx2 = 0; idx2 < EdgeIndex.size(); idx2++ ) {
			// Rectangles throw away test (overkill?) //
			if ( _Vs.Edge[ EdgeIndex[idx2] ].BoundingRect == SphereRect[idx] ) {
				// Find the closest point on the edge to us //
				int ClosestFlags = 0;
				Vector2D PointOnEdge = _Vs.Edge[ EdgeIndex[idx2] ].ClosestPoint( _Vs.Nodes, Point, ClosestFlags );
				
				// If the closest point was a corner, bail, as we'd prefer to solve with edges first //
				if ( ClosestFlags & cStaticEdge::flCorner )
					continue;
				
				// Trace a vector to the closest point //
				Vector2D ToPoint = PointOnEdge - Point;
				
				// If touching the edge //
				if ( ToPoint.MagnitudeSquared() < Sphere[ SphereIndex[idx] ].RadiusSquared() ) {
					// If a sensor, note our contact, but don't solve //
					if ( Sphere[ SphereIndex[idx] ].Flags.Sensor() ) {
						SphereFlags[ SphereIndex[idx] ].SetScenery().SetPolygon().SetEdge();
						continue;
					}


					// Calculate the penetration depth of the collision //
					Real Penetration = Sphere[ SphereIndex[idx] ].Radius - ToPoint.Magnitude();

					// Solving //
					Point -= Penetration * ToPoint.Normal() * Real::Half;
					
					// Friction //
					// 0 - Perfecly Ice like friction surface //
					// 1 - Perfectly sticky surface (kills all motion) //
					Real Friction = (ToPoint.Normal().Tangent() *
						Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index )) *
						Real( 0.02 );
					
					Point -= Friction * ToPoint.Normal().Tangent();

					// Restitution //
					// 0 - Perfect dampening //
					// 1 - Perfect bounce //
					Real DistanceToSurface = ToPoint.Normal() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index );
					if ( DistanceToSurface > 0 ) {
						// Mirroring, to emulate restitution //
						PointOld += ( DistanceToSurface +
							(DistanceToSurface * Real( 0.2 ) ) ) *
							ToPoint.Normal();
					}

					// Set Flags //
					SphereFlags[ SphereIndex[idx] ].SetScenery().SetPolygon().SetEdge();
					CollisionFlags.Set( SphereFlags[ SphereIndex[idx] ] );

					
					//Real Penetration = (ToPoint * _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal());
					//Real Push = Penetration + Sphere[ SphereIndex[idx] ].Radius;
					
					//Real PowerPush = PointVelocity * _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal();

//					// Get Rotational Energy //
//					Sphere[ SphereIndex[idx] ].RotationalEnergy +=
//						//-Sphere[ SphereIndex[idx] ].RotationalEnergy +
//						( ( _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() *
//						Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) ).Normal() *
//						Push );
					
					// Solve //
					//Point += (Push * _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal());
					
//						if ( Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) * _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal() > Real::Zero ) {
							// Cancel out surface normal parellel velocity //
//							PointOld += (PowerPush - Penetration) * _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal();
							// Surface restitution //
							//PointOld += (PowerPush) * _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal();
//						}
//					}
					
					
					// Push out of Scenery //
					//Point += (Push * _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal()) * Real::Half;
					//Point -= ToPoint;// + (ToPoint.Normal() * Sphere[ SphereIndex[idx] ].Radius);// * Real::Half;


//					PointOld += (ToPoint.Normal() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) * Real(2) ) *
//						ToPoint.Normal();


//					Point += (PointVelocity.Magnitude() - 
//						Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ).Magnitude()) *
//						ToPoint.Normal().Tangent();
						
					
					
//					PointOld += ((Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) * ToPoint.Normal()) * ToPoint.Normal()) +
//								(Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) * ToPoint.Normal()) * ToPoint.Normal();
					
//					if ( !(Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ).IsZero()) ) {
//						Real PowPush;
//						if ( !(PowerPush.IsZero()) )
//							PowPush = ( Push / PowerPush ).Abs().Max( Real::One );
//						
//						Real StrengthChange;
//						if ( !(PointVelocity.MagnitudeSquared().IsZero()) )
//							StrengthChange = ( Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ).Magnitude() / PointVelocity.Magnitude() ).Max( Real::One );
//													
//						// Push back quantity of friction //
//						Point -= _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() *
//							( ( _Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * PointVelocity ) *
//							PowPush *
//							StrengthChange *
//							Real(0.99) );
//					}						

//					Point += Sphere[ SphereIndex[idx] ].RotationalEnergy *
//							(Real::One / Real( Sphere[ SphereIndex[idx] ].Radius )) *
//							_Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent();
//					
//					Sphere[ SphereIndex[idx] ].RotationalEnergy *= Real::Half;


//					Point += Sphere[ SphereIndex[idx] ].RotationalEnergy.Abs().Sqrt() * Sphere[ SphereIndex[idx] ].RotationalEnergy.Normal() *
//							(Real::One / Real( Sphere[ SphereIndex[idx] ].Radius )) *
//							_Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent();

					
					// Friction "A - A dot B * B" //
//					Nodes.Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(_Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index )) *
//						_Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent();

					// Friction "A - Sign(A dot B) * B * PushLength //
//					Nodes.Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(_Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index )).Normal() *
//						_Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() *
//						Push;

					// Friction Hack//
					//SetFriction( Sphere[ SphereIndex[idx] ].Index, _Vs.Friction );
					
					// Mark this object as solved, so not to do polygon testing on (Optimization) //
				}
			}
		}
		
		// Versus Corners of Edges //
		for ( size_t idx2 = 0; idx2 < EdgeIndex.size(); idx2++ ) {
			// Rectangles throw away test (overkill?) //
			if ( _Vs.Edge[ EdgeIndex[idx2] ].BoundingRect == SphereRect[idx] ) {
				// Get the first point (a) of an edge //
				Vector2D& VersusPoint = _Vs.Nodes.Pos( _Vs.Edge[ EdgeIndex[idx2] ].a );
				
				// Trace a vector to the point //
				Vector2D ToPoint = VersusPoint - Point;
				
				// If touching the edge //
				if ( ToPoint.MagnitudeSquared() < Sphere[ SphereIndex[idx] ].RadiusSquared() ) {
					// If a sensor, note our contact, but don't solve //
					if ( Sphere[ SphereIndex[idx] ].Flags.Sensor() ) {
						SphereFlags[ idx ].SetScenery().SetPolygon().SetCorner();
						continue;
					}

					// Calculate the penetration depth of the collision //
					Real Penetration = Sphere[ SphereIndex[idx] ].Radius - ToPoint.Magnitude();

					// Solving //
					Point -= Penetration * ToPoint.Normal() * Real::Half;
					
					// Friction //
					// 0 - Perfecly Ice like friction surface //
					// 1 - Perfectly sticky surface (kills all motion) //
					Point -= (ToPoint.Normal().Tangent() *
						Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index )) *
						ToPoint.Normal().Tangent() * Real( 0.02 );

					// Restitution //
					// 0 - Perfect dampening //
					// 1 - Perfect bounce //
					Real DistanceToSurface = ToPoint.Normal() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index );
					if ( DistanceToSurface > 0 ) {
						// Mirroring, to emulate restitution //
						PointOld += ( DistanceToSurface +
							(DistanceToSurface * Real( 0.2 ) ) ) *
							ToPoint.Normal();
					}

					// Set Flags //
					SphereFlags[ SphereIndex[idx] ].SetScenery().SetPolygon().SetCorner();
					CollisionFlags.Set( SphereFlags[ SphereIndex[idx] ] );
				}				
			}			
		}

		// Versus Polygons //
		{
			bool Inside = false;
			
			// See if sphere is inside any polygon //
			for ( size_t idx2 = 0; idx2 < PolyIndex.size(); idx2++ ) {
				// Rectangles throw away test //
				if ( _Vs.Polygon[ PolyIndex[idx2] ].BoundingRect == SphereRect[idx] ) {
					// The number of sides found, so far //
					size_t SideCount = 0;

					// An optimization.  As long as it's only 1 more, we can re use if to the end //
					Vector2D ToCorner;
					
					// Check if we're inside all sides except the last //
					for ( size_t idx3 = 0; idx3 < _Vs.Polygon[ PolyIndex[idx2] ].Index.size() - 1; idx3++ ) {
						Vector2D Segment =
							_Vs.Nodes.Pos( _Vs.Polygon[ PolyIndex[idx2] ].Index[idx3 + 1] ) -
							_Vs.Nodes.Pos( _Vs.Polygon[ PolyIndex[idx2] ].Index[idx3] );
						
						ToCorner = _Vs.Nodes.Pos( _Vs.Polygon[ PolyIndex[idx2] ].Index[idx3 + 1] ) - Point;
						
						// If Inside this side //
						if ( (-Segment.Tangent()) * ToCorner > Real::Zero )
							SideCount++;
						else
							break;
					}

					// If we bailed early, we're not inside //
					if ( SideCount != _Vs.Polygon[ PolyIndex[idx2] ].Index.size() - 1 )
						continue;
						
					// Test last side //
					Vector2D Segment =
						_Vs.Nodes.Pos( _Vs.Polygon[ PolyIndex[idx2] ].Index[0] ) -
						_Vs.Nodes.Pos( _Vs.Polygon[ PolyIndex[idx2] ].Index[SideCount] );
					
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
					//if ( Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) * _Vs.Edge[ EdgeIndex[idx2] ].Normal <= Real::Zero )
					{
						Vector2D PointOnEdge = _Vs.Edge[ EdgeIndex[idx2] ].ClosestPoint( _Vs.Nodes, Point );
						
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
					for ( size_t idx2 = 0; idx2 < _Vs.Edge.size(); idx2++ ) {
						// Motion Vector half space throw away test (Bad, as it allows perfect squishes to go through) //
						//if ( Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) * _Vs.Edge[idx2].Normal <= Real::Zero )
						{
							Vector2D PointOnEdge = _Vs.Edge[idx2].ClosestPoint( _Vs.Nodes, Point );
							
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
					// If a sensor, note our contact, but don't solve //
					if ( Sphere[ SphereIndex[idx] ].Flags.Sensor() ) {
						SphereFlags[ SphereIndex[idx] ].SetScenery().SetPolygon().SetInside();
						continue;
					}
					
					// Solve //
					Push += (Push.Normal() * Sphere[ SphereIndex[idx] ].Radius);
					Point += Push * Real::Half;
						
					// Friction //
					Point -= (Push.Normal().Tangent() *
						Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index )) *
						Push.Normal().Tangent() * Real( 0.02 );
						

					// Set Flags //
					SphereFlags[ SphereIndex[idx] ].SetScenery().SetPolygon().SetInside();
					CollisionFlags.Set( SphereFlags[ SphereIndex[idx] ] );

					// Get Rotational Energy //
//					Sphere[ SphereIndex[idx] ].RotationalEnergy +=
//						Push.Normal().Tangent() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index );
//					
//					AddForce(
//						Sphere[ SphereIndex[idx] ].Index,
//						Sphere[ SphereIndex[idx] ].RotationalEnergy * Push.Normal().Tangent()
//						);
					
					// Friction "A - A dot B * B" //
//					Nodes.Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(Push.Normal().Tangent() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index )) *
//						Push.Normal().Tangent();

					// Friction "A - Sign(A dot B) * B * PushLength //
//					Nodes.Old( Sphere[ SphereIndex[idx] ].Index ) +=
//						(Push.Normal().Tangent() * Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index )).Normal() *
//						Push.Normal().Tangent() *
//						Push.Magnitude();

					// Friction Hack //
					//SetFriction( Sphere[ SphereIndex[idx] ].Index, _Vs.Friction );
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
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
