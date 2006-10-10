// - ------------------------------------------------------------------------------------------ - //
// PolyObject_Solve //
// - ------------------------------------------------------------------------------------------ - //

#include "PolyObject.h"

#include "SphereObject.h"
#include "StaticObject.h"

// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::Solve( cPolyObject& Vs ) {
	// If Asleep, Bail //
	
	// Test Bounding Rectangles //
	if ( BoundingRect != Vs.BoundingRect )
		return;
		
	// *** Wake Up the other object *** //


	{
		for ( size_t idx = 0; idx < size(); idx++ ) {
			// Against Triangles //
			{
				int TriangleCount = Vs.Triangle.size();
				for ( int idx2 = 0; idx2 < TriangleCount; idx2++ ) {
					Vector2D Point = Pos( idx );
					
					Vector2D RayCorner1 = Vs.Pos( Vs.Triangle[ idx2 ].IndexB ) - Point;
					Vector2D RayCorner2 = Vs.Pos( Vs.Triangle[ idx2 ].IndexC ) - Point;
					
					Real DistanceA = Vs.Triangle[ idx2 ].NormalA * RayCorner1;
					Real DistanceB = Vs.Triangle[ idx2 ].NormalB * RayCorner1;
					Real DistanceC = Vs.Triangle[ idx2 ].NormalC * RayCorner2;
					
					// If Inside //
					if ( DistanceA >= Real::Zero )
						if ( DistanceB >= Real::Zero )
							if ( DistanceC >= Real::Zero ) {
								// Take shortest //
								Vector2D Normal = Vs.Triangle[ idx2 ].NormalA;
								Real NewDistance = DistanceA;
								int PointIndex1 = Vs.Triangle[ idx2 ].IndexA;
								int PointIndex2 = Vs.Triangle[ idx2 ].IndexB;
								
								if ( DistanceB < NewDistance ) {
									Normal = Vs.Triangle[ idx2 ].NormalB;
									NewDistance = DistanceB;
									PointIndex1 = Vs.Triangle[ idx2 ].IndexB;
									PointIndex2 = Vs.Triangle[ idx2 ].IndexC;
								}
								if ( DistanceC < NewDistance ) {
									Normal = Vs.Triangle[ idx2 ].NormalC;
									NewDistance = DistanceC;
									PointIndex1 = Vs.Triangle[ idx2 ].IndexC;
									PointIndex2 = Vs.Triangle[ idx2 ].IndexA;
								}


								// Calculate Balance //
								Vector2D SurfaceRay = Vs.Pos( PointIndex2 ) - Vs.Pos( PointIndex1 );
								Vector2D SurfaceRayNormalized = SurfaceRay;
								Real SurfaceRayLength = SurfaceRayNormalized.NormalizeRet();
								
								Vector2D ToPointRay = Pos( idx ) - Vs.Pos( PointIndex1 );
								
								Real C1;
								if ( !SurfaceRayLength.IsZero() )
									C1 = (SurfaceRayNormalized * ToPointRay) / SurfaceRayLength;
								else
									C1 = 1.0f;
									
								Real C2 = 1.0f - C1;

								// Move Points //								
								Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );

								Vs.Pos( PointIndex1 ) -= Normal * (NewDistance) * C2;
								Vs.Pos( PointIndex2 ) -= Normal * (NewDistance) * C1;
								
								continue;
							}		
				}
			}
			
			// Against Quads //
			{
				for ( size_t idx2 = 0; idx2 < Vs.Quad.size(); idx2++ ) {
					Vector2D Point = Pos( idx );
					
					Vector2D RayCorner1 = Vs.Pos( Vs.Quad[ idx2 ].IndexB ) - Point;
					Vector2D RayCorner2 = Vs.Pos( Vs.Quad[ idx2 ].IndexD ) - Point;
					
					Real DistanceA = Vs.Quad[ idx2 ].NormalA * RayCorner1;
					Real DistanceB = Vs.Quad[ idx2 ].NormalB * RayCorner1;
					Real DistanceC = Vs.Quad[ idx2 ].NormalC * RayCorner2;
					Real DistanceD = Vs.Quad[ idx2 ].NormalD * RayCorner2;
					
					// If Inside //
					if ( DistanceA >= Real::Zero )
						if ( DistanceB >= Real::Zero )
							if ( DistanceC >= Real::Zero )
								if ( DistanceD >= Real::Zero ) {
									// Take shortest //
									Vector2D Normal = Vs.Quad[ idx2 ].NormalA;
									Real NewDistance = DistanceA;
									int PointIndex1 = Vs.Quad[ idx2 ].IndexA;
									int PointIndex2 = Vs.Quad[ idx2 ].IndexB;
									
									if ( DistanceB < NewDistance ) {
										Normal = Vs.Quad[ idx2 ].NormalB;
										NewDistance = DistanceB;
										PointIndex1 = Vs.Quad[ idx2 ].IndexB;
										PointIndex2 = Vs.Quad[ idx2 ].IndexC;
									}
									if ( DistanceC < NewDistance ) {
										Normal = Vs.Quad[ idx2 ].NormalC;
										NewDistance = DistanceC;
										PointIndex1 = Vs.Quad[ idx2 ].IndexC;
										PointIndex2 = Vs.Quad[ idx2 ].IndexD;
									}
									if ( DistanceD < NewDistance ) {
										Normal = Vs.Quad[ idx2 ].NormalD;
										NewDistance = DistanceD;
										PointIndex1 = Vs.Quad[ idx2 ].IndexD;
										PointIndex2 = Vs.Quad[ idx2 ].IndexA;
									}


									// Calculate Balance //
									Vector2D SurfaceRay = Vs.Pos( PointIndex2 ) - Vs.Pos( PointIndex1 );
									Vector2D SurfaceRayNormalized = SurfaceRay;
									Real SurfaceRayLength = SurfaceRayNormalized.NormalizeRet();
									
									Vector2D ToPointRay = Pos( idx ) - Vs.Pos( PointIndex1 );
									
									Real C1;
									if ( !SurfaceRayLength.IsZero() )
										C1 = (SurfaceRayNormalized * ToPointRay) / SurfaceRayLength;
									else
										C1 = 1.0f;
										
									Real C2 = 1.0f - C1;
	
									// Move Points //								
//									Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );
//	
//									Vs.Pos( PointIndex1 ) -= Normal * (NewDistance) * C2;
//									Vs.Pos( PointIndex2 ) -= Normal * (NewDistance) * C1;
																									
									Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );

									Vs.Pos( PointIndex1 ) -= Normal * (NewDistance) * Real( 0.5 );
									Vs.Pos( PointIndex2 ) -= Normal * (NewDistance) * Real( 0.5 );
									
									continue;
								}
				}
			}
		}
	}	


	{
		// Collision Quad Vs Me! //
		for ( size_t idx = 0; idx < Quad.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Vs.size(); idx2++ ) {
				Vector2D Point = Vs.Pos( idx2 );
				
				Vector2D RayCorner1 = Pos( Quad[ idx ].IndexB ) - Point;
				Vector2D RayCorner2 = Pos( Quad[ idx ].IndexD ) - Point;
				
				Real DistanceA = Quad[ idx ].NormalA * RayCorner1;
				Real DistanceB = Quad[ idx ].NormalB * RayCorner1;
				Real DistanceC = Quad[ idx ].NormalC * RayCorner2;
				Real DistanceD = Quad[ idx ].NormalD * RayCorner2;
				
				// If Inside //
				if ( DistanceA >= Real::Zero )
					if ( DistanceB >= Real::Zero )
						if ( DistanceC >= Real::Zero )
							if ( DistanceD >= Real::Zero ) {
								// Take shortest //
								Vector2D Normal = Quad[ idx ].NormalA;
								Real NewDistance = DistanceA;
								int PointIndex1 = Quad[ idx ].IndexA;
								int PointIndex2 = Quad[ idx ].IndexB;
								
								if ( DistanceB < NewDistance ) {
									Normal = Quad[ idx ].NormalB;
									NewDistance = DistanceB;
									PointIndex1 = Quad[ idx ].IndexB;
									PointIndex2 = Quad[ idx ].IndexC;
								}
								if ( DistanceC < NewDistance ) {
									Normal = Quad[ idx ].NormalC;
									NewDistance = DistanceC;
									PointIndex1 = Quad[ idx ].IndexC;
									PointIndex2 = Quad[ idx ].IndexD;
								}
								if ( DistanceD < NewDistance ) {
									Normal = Quad[ idx ].NormalD;
									NewDistance = DistanceD;
									PointIndex1 = Quad[ idx ].IndexD;
									PointIndex2 = Quad[ idx ].IndexA;
								}

								// Calculate Balance //
								Vector2D SurfaceRay = Pos( PointIndex2 ) - Pos( PointIndex1 );
								Vector2D SurfaceRayNormalized = SurfaceRay;
								Real SurfaceRayLength = SurfaceRayNormalized.NormalizeRet();
								
								Vector2D ToPointRay = Vs.Pos( idx ) - Pos( PointIndex1 );
								
								Real C1;
								if ( !SurfaceRayLength.IsZero() )
									C1 = (SurfaceRayNormalized * ToPointRay) / SurfaceRayLength;
								else
									C1 = 1.0f;
									
								Real C2 = 1.0f - C1;

								// Move Points //								
								Vs.Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );

								Pos( PointIndex1 ) -= Normal * (NewDistance) * C2;
								Pos( PointIndex2 ) -= Normal * (NewDistance) * C1;

								
//								Vs.Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );
//								
//								Pos( PointIndex1 ) -= Normal * (NewDistance) * Real( 0.5 );
//								Pos( PointIndex2 ) -= Normal * (NewDistance) * Real( 0.5 );
								
								continue;
							}
			}
		}

		// Collision Tri Vs Me! //
		for ( size_t idx = 0; idx < Triangle.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Vs.size(); idx2++ ) {
				Vector2D Point = Vs.Pos( idx2 );
				
				Vector2D RayCorner1 = Pos( Triangle[ idx ].IndexB ) - Point;
				Vector2D RayCorner2 = Pos( Triangle[ idx ].IndexC ) - Point;
				
				Real DistanceA = Triangle[ idx ].NormalA * RayCorner1;
				Real DistanceB = Triangle[ idx ].NormalB * RayCorner1;
				Real DistanceC = Triangle[ idx ].NormalC * RayCorner2;
				
				// If Inside //
				if ( DistanceA >= Real::Zero )
					if ( DistanceB >= Real::Zero )
						if ( DistanceC >= Real::Zero ) {
							// Take shortest //
							Vector2D Normal = Triangle[ idx ].NormalA;
							Real NewDistance = DistanceA;
							int PointIndex1 = Triangle[ idx ].IndexA;
							int PointIndex2 = Triangle[ idx ].IndexB;
							
							if ( DistanceB < NewDistance ) {
								Normal = Triangle[ idx ].NormalB;
								NewDistance = DistanceB;
								PointIndex1 = Triangle[ idx ].IndexB;
								PointIndex2 = Triangle[ idx ].IndexC;
							}
							if ( DistanceC < NewDistance ) {
								Normal = Triangle[ idx ].NormalC;
								NewDistance = DistanceC;
								PointIndex1 = Triangle[ idx ].IndexC;
								PointIndex2 = Triangle[ idx ].IndexA;
							}

							// Calculate Balance //
							Vector2D SurfaceRay = Pos( PointIndex2 ) - Pos( PointIndex1 );
							Vector2D SurfaceRayNormalized = SurfaceRay;
							Real SurfaceRayLength = SurfaceRayNormalized.NormalizeRet();
							
							Vector2D ToPointRay = Vs.Pos( idx ) - Pos( PointIndex1 );
							
							Real C1;
							if ( !SurfaceRayLength.IsZero() )
								C1 = (SurfaceRayNormalized * ToPointRay) / SurfaceRayLength;
							else
								C1 = 1.0f;
								
							Real C2 = 1.0f - C1;

							// Move Points //								
							Vs.Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );

							Pos( PointIndex1 ) -= Normal * (NewDistance) * C2;
							Pos( PointIndex2 ) -= Normal * (NewDistance) * C1;							

//							Vs.Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );
//							
//							Pos( PointIndex1 ) -= Normal * (NewDistance) * Real( 0.5 );
//							Pos( PointIndex2 ) -= Normal * (NewDistance) * Real( 0.5 );
							
							continue;
						}
			}
		}
	}	


	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
	CalcNormals();	
	Vs.CalcBoundingRect();
	Vs.CalcNormals();
}
// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::Solve( cSphereObject& Vs ) {
	// If Asleep, Bail //
	
	// Test Bounding Rectangles //
	if ( BoundingRect != Vs.BoundingRect )
		return;
		
	// *** Wake Up the other object *** //
	
	
//	// Test Sphere's //
//	{
//		int SphereCount = Sphere.size();
//		for ( size_t idx = 0; idx < SphereCount; idx++ ) {
//			int VsSphereCount = Vs.Sphere.size();
//			for ( size_t idx2 = 0; idx2 < VsSphereCount; idx2++ ) {
//				// Optimized Verlet with Square Root Approximation //
//				Vector2D Ray = Vs.Pos( Vs.Sphere[ idx2 ].Index ) - Pos( Sphere[ idx ].Index );
//				
//				Real RadiusSum = Sphere[ idx ].Radius + Vs.Sphere[ idx2 ].Radius;
//				Real RadiusSumSquared = RadiusSum * RadiusSum;
//				
//				// Bail if not touching //
//				if ( RadiusSumSquared < Ray.MagnitudeSquared() )
//					continue;
//				
//				// Hmm.. Division //
//				Ray *= (RadiusSumSquared) / ( (Ray * Ray) + (RadiusSumSquared) ) - Real( 0.5 );
//				
//				Pos( Sphere[ idx ].Index ) -= Ray;
//				Vs.Pos( Vs.Sphere[ idx2 ].Index ) += Ray;
//			}
//		};
//	}

	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
	CalcNormals();	
	Vs.CalcBoundingRect();	
}
// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::Solve( cStaticObject& Vs ) {
	// If Asleep, Bail //
	
	// Test Bounding Rectangles //
	if ( BoundingRect != Vs.BoundingRect )
		return;

	// Find overlap Region //		
	RectType OverlapRect = BoundingRect - Vs.BoundingRect;

	// Find all spheres //
	std::vector< int > NodeIndex;							// Store this Vector in thread/worker //
	//std::vector< RectType > SphereRect;
	for ( size_t idx = 0; idx < size(); idx++ ) {
		// Make a rectangle for the sphere //
//		RectType Rect = RectType::Pair(
//			Pos( idx ),
//			Pos( idx )
//			);
		// Test the sphere against the region //
		//if ( OverlapRect == Rect )
		{
			NodeIndex.push_back( idx );
			//SphereRect.push_back( Rect );
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
		if ( OverlapRect == Vs.Edge[idx].BoundingRect ) {
			EdgeIndex.push_back( idx );
		}
	}
	
	
	// Do tests //
	for ( size_t idx = 0; idx < NodeIndex.size(); idx++ ) {
		// Store the Point //
		Vector2D& Point = Pos( NodeIndex[idx] );

//		// Versus Edges //
//		for ( size_t idx2 = 0; idx2 < EdgeIndex.size(); idx2++ ) {
//			// Rectangles throw away test (overkill?) //
//			//if ( Vs.Edge[ EdgeIndex[idx2] ].BoundingRect == SphereRect[idx] )
//			{
//				Vector2D PointOnEdge = Vs.Edge[ EdgeIndex[idx2] ].ClosestPoint( Vs, Point );
//				
//				Vector2D ToPoint = PointOnEdge - Point;
//				
//				// If touching the edge //
//				//if ( ToPoint.MagnitudeSquared() < NodeIndex[idx] )
//				{
//					Real Push = Sphere[ NodeIndex[idx] ].Radius - ToPoint.Magnitude();
//					
//					// Solve //
//					Point += (Push * Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal());// * Real::Half;
//
//					// Set Flags //
//					Sphere[ NodeIndex[idx] ].Flags |= cSphere::flScenery | cSphere::flPolygon;
//					
//					// Friction "A - A dot B * B" //
////					Old( Sphere[ NodeIndex[idx] ].Index ) +=
////						(Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * Velocity( Sphere[ NodeIndex[idx] ].Index )) *
////						Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent();
//
//					// Friction "A - Sign(A dot B) * B * PushLength //
////					Old( Sphere[ NodeIndex[idx] ].Index ) +=
////						(Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() * Velocity( Sphere[ NodeIndex[idx] ].Index )).Normal() *
////						Vs.Edge[ EdgeIndex[idx2] ].SurfaceNormal().Tangent() *
////						Push;
//
//					// Friction Hack//
//					SetFriction( NodeIndex[idx], Vs.Friction );
//					
//					// Mark this object as solved, so not to do polygon testing on (Optimization) //
//				}
//			}
//		}

		// Versus Polygons //
		{
			bool Inside = false;
			
			// See if sphere is inside any polygon //
			for ( size_t idx2 = 0; idx2 < PolyIndex.size(); idx2++ ) {
				// Rectangles throw away test //
				//if ( Vs.Polygon[ PolyIndex[idx2] ].BoundingRect == SphereRect[idx] )
				{
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
					//if ( Velocity( NodeIndex[idx] ) * Vs.Edge[ EdgeIndex[idx2] ].Normal <= Real::Zero )
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
						//if ( Velocity( NodeIndex[idx] ) * Vs.Edge[idx2].Normal <= Real::Zero )
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
					//Push += (Push.Normal() * NodeIndex[idx] ].Radius);
					Point += Push;

					// Set Flags //
					//Sphere[ NodeIndex[idx] ].Flags |= cSphere::flScenery | cSphere::flPolygon | cSphere::flInside;
					
					// Friction "A - A dot B * B" //
//					Old( Sphere[ NodeIndex[idx] ].Index ) +=
//						(Push.Normal().Tangent() * Velocity( Sphere[ NodeIndex[idx] ].Index )) *
//						Push.Normal().Tangent();

					// Friction "A - Sign(A dot B) * B * PushLength //
//					Old( Sphere[ NodeIndex[idx] ].Index ) +=
//						(Push.Normal().Tangent() * Velocity( Sphere[ NodeIndex[idx] ].Index )).Normal() *
//						Push.Normal().Tangent() *
//						Push.Magnitude();

					// Friction Hack //
					SetFriction( NodeIndex[idx], Vs.Friction );
				}
				else {
					Log( 10, "ERROR!!!! NO EXIT POINT FOUND!!!!! *********" );
				}
			}
		}

	}





/*
	// Test Spheres against //
	{
		for ( size_t idx = 0; idx < size(); idx++ ) {
//			// Against Axis Aligned Bounding Boxes //
//			{
//				int BoxCount = Vs.Box.size();
//				for ( int idx2 = 0; idx2 < BoxCount; idx2++ ) {
//					// Get the closest point to the Rectangle //
//					Rect2D Rect( Vs.Pos( Vs.Box[ idx2 ].IndexA ), Vs.Pos( Vs.Box[ idx2 ].IndexB ) );
//					Vector2D Point = Rect.ClosestPoint( Pos( Sphere[ idx ].Index ) );
//					
//					// If the same as the point passed, it's a closest side alignment //
//					if ( (Point.x == Pos( Sphere[ idx ].Index ).x) && (Point.y == Pos( Sphere[ idx ].Index ).y) ) {
//						// Calculate Best X side //
//						Real X;
//						if ( (Point.x - Rect.x) < (Rect.x + Rect.w - Point.x) ) {
//							X = (Point.x - Rect.x) - Sphere[ idx ].Radius;
//						}
//						else {
//							X = (Rect.x + Rect.w - Point.x) + Sphere[ idx ].Radius;
//						}
//						
//						// Calculate Best Y Side //
//						Real Y;
//						if ( (Point.y - Rect.y) < (Rect.y + Rect.h - Point.y) ) {
//							Y = (Point.y - Rect.y) - Sphere[ idx ].Radius;
//						}
//						else {
//							Y = (Rect.y + Rect.h - Point.y) + Sphere[ idx ].Radius;
//						}
//						
//						// Take whatever side is shorter //
//						if ( X < Y ) {
//							Pos( Sphere[ idx ].Index ).x += X * Real( 0.5 );
//						}
//						else {
//							Pos( Sphere[ idx ].Index ).y += Y * Real( 0.5 );
//						}
//					}
//					// If different, then it's a normal closest point push //
//					else {
//						Vector2D Ray = Point - Pos( Sphere[ idx ].Index );
//
//						Real RadiusSum = Sphere[ idx ].Radius;
//						Real RadiusSumSquared = RadiusSum * RadiusSum;
//				
//						// Bail if not touching //
//						if ( RadiusSumSquared < Ray.MagnitudeSquared() )
//							continue;
//
//						Real RayLength = Ray.Magnitude();
//						Real Difference = (RadiusSum - RayLength) / RayLength;						
//						Vector2D Value = Ray * Difference * Real( 0.5 );
//
//						Pos( idx ) -= Value;
//					}
//				}
//			}
			
			// Against Triangles //
			{
				int TriangleCount = Vs.Triangle.size();
				for ( int idx2 = 0; idx2 < TriangleCount; idx2++ ) {
					Vector2D Point = Pos( idx );
					
					Vector2D RayCorner1 = Vs.Pos( Vs.Triangle[ idx2 ].IndexB ) - Point;
					Vector2D RayCorner2 = Vs.Pos( Vs.Triangle[ idx2 ].IndexC ) - Point;
					
					Real DistanceA = Vs.Triangle[ idx2 ].NormalA * RayCorner1;
					Real DistanceB = Vs.Triangle[ idx2 ].NormalB * RayCorner1;
					Real DistanceC = Vs.Triangle[ idx2 ].NormalC * RayCorner2;
					
					// If Inside //
					if ( DistanceA >= Real::Zero )
						if ( DistanceB >= Real::Zero )
							if ( DistanceC >= Real::Zero ) {
								// Take shortest //
								Vector2D Normal = Vs.Triangle[ idx2 ].NormalA;
								Real NewDistance = DistanceA;
								
								if ( DistanceB < NewDistance ) {
									Normal = Vs.Triangle[ idx2 ].NormalB;
									NewDistance = DistanceB;
								}
								if ( DistanceC < NewDistance ) {
									Normal = Vs.Triangle[ idx2 ].NormalC;
									NewDistance = DistanceC;
								}
								
								Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );	
								SetFriction( idx, Vs.Friction );
								
								continue;
							}		
				}
			}
			
			// Against Quads //
			{
				for ( size_t idx2 = 0; idx2 < Vs.Quad.size(); idx2++ ) {
					Vector2D Point = Pos( idx );
					
					Vector2D RayCorner1 = Vs.Pos( Vs.Quad[ idx2 ].IndexB ) - Point;
					Vector2D RayCorner2 = Vs.Pos( Vs.Quad[ idx2 ].IndexD ) - Point;
					
					Real DistanceA = Vs.Quad[ idx2 ].NormalA * RayCorner1;
					Real DistanceB = Vs.Quad[ idx2 ].NormalB * RayCorner1;
					Real DistanceC = Vs.Quad[ idx2 ].NormalC * RayCorner2;
					Real DistanceD = Vs.Quad[ idx2 ].NormalD * RayCorner2;
					
					// If Inside //
					if ( DistanceA >= Real::Zero )
						if ( DistanceB >= Real::Zero )
							if ( DistanceC >= Real::Zero )
								if ( DistanceD >= Real::Zero ) {
									// Take shortest //
									Vector2D Normal = Vs.Quad[ idx2 ].NormalA;
									Real NewDistance = DistanceA;
									
									if ( DistanceB < NewDistance ) {
										Normal = Vs.Quad[ idx2 ].NormalB;
										NewDistance = DistanceB;
									}
									if ( DistanceC < NewDistance ) {
										Normal = Vs.Quad[ idx2 ].NormalC;
										NewDistance = DistanceC;
									}
									if ( DistanceD < NewDistance ) {
										Normal = Vs.Quad[ idx2 ].NormalD;
										NewDistance = DistanceD;
									}
									
									Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );
									SetFriction( idx, Vs.Friction );
									
									continue;
								}
				}
			}
			
			// Against Polygons ? //
			
			// Against Spheres ? //
		};
	}

	{
		// Collision Quad Vs Me! //
		for ( size_t idx = 0; idx < Quad.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Vs.size(); idx2++ ) {
				Vector2D Point = Vs.Pos( idx2 );
				
				Vector2D RayCorner1 = Pos( Quad[ idx ].IndexB ) - Point;
				Vector2D RayCorner2 = Pos( Quad[ idx ].IndexD ) - Point;
				
				Real DistanceA = Quad[ idx ].NormalA * RayCorner1;
				Real DistanceB = Quad[ idx ].NormalB * RayCorner1;
				Real DistanceC = Quad[ idx ].NormalC * RayCorner2;
				Real DistanceD = Quad[ idx ].NormalD * RayCorner2;
				
				// If Inside //
				if ( DistanceA >= Real::Zero )
					if ( DistanceB >= Real::Zero )
						if ( DistanceC >= Real::Zero )
							if ( DistanceD >= Real::Zero ) {
								// Take shortest //
								Vector2D Normal = Quad[ idx ].NormalA;
								Real NewDistance = DistanceA;
								int PointIndex1 = Quad[ idx ].IndexA;
								int PointIndex2 = Quad[ idx ].IndexB;
								
								if ( DistanceB < NewDistance ) {
									Normal = Quad[ idx ].NormalB;
									NewDistance = DistanceB;
									PointIndex1 = Quad[ idx ].IndexB;
									PointIndex2 = Quad[ idx ].IndexC;
								}
								if ( DistanceC < NewDistance ) {
									Normal = Quad[ idx ].NormalC;
									NewDistance = DistanceC;
									PointIndex1 = Quad[ idx ].IndexC;
									PointIndex2 = Quad[ idx ].IndexD;
								}
								if ( DistanceD < NewDistance ) {
									Normal = Quad[ idx ].NormalD;
									NewDistance = DistanceD;
									PointIndex1 = Quad[ idx ].IndexD;
									PointIndex2 = Quad[ idx ].IndexA;
								}


//								// Calculate Balance //
//								Vector2D SurfaceRay = Pos( PointIndex2 ) - Pos( PointIndex1 );
//								Vector2D SurfaceRayNormalized = SurfaceRay;
//								Real SurfaceRayLength = SurfaceRayNormalized.NormalizeRet();
//								
//								Vector2D ToPointRay = Vs.Pos( idx ) - Pos( PointIndex1 );
//								
//								Real C1;
//								if ( !SurfaceRayLength.IsZero() )
//									C1 = (SurfaceRayNormalized * ToPointRay) / SurfaceRayLength;
//								else
//									C1 = 1.0f;
//									
//								Real C2 = 1.0f - C1;
//								
//								Vector2D Delta = SurfaceRay;
//								Real Lambda = (Normal * NewDistance) * Delta;
//								Lambda /= ( (C1 * C1) + (C2 * C2)) * (Delta * Delta);
//
//								// Move Points //								
//								Pos( PointIndex1 ) -= (C2 * Lambda) * Delta * 2;//Normal * (NewDistance) * C2;
//								Pos( PointIndex2 ) -= (C1 * Lambda) * Delta * 2;//Normal * (NewDistance) * C1;
								
								// Static, so no pushing //
								//Vs.Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );
								
								Pos( PointIndex1 ) -= Normal * (NewDistance) * Real( 0.5 );
								Pos( PointIndex2 ) -= Normal * (NewDistance) * Real( 0.5 );
								
								continue;
							}
			}
		}

		// Collision Tri Vs Me! //
		for ( size_t idx = 0; idx < Triangle.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Vs.size(); idx2++ ) {
				Vector2D Point = Vs.Pos( idx2 );
				
				Vector2D RayCorner1 = Pos( Triangle[ idx ].IndexB ) - Point;
				Vector2D RayCorner2 = Pos( Triangle[ idx ].IndexC ) - Point;
				
				Real DistanceA = Triangle[ idx ].NormalA * RayCorner1;
				Real DistanceB = Triangle[ idx ].NormalB * RayCorner1;
				Real DistanceC = Triangle[ idx ].NormalC * RayCorner2;
				
				// If Inside //
				if ( DistanceA >= Real::Zero )
					if ( DistanceB >= Real::Zero )
						if ( DistanceC >= Real::Zero ) {
							// Take shortest //
							Vector2D Normal = Triangle[ idx ].NormalA;
							Real NewDistance = DistanceA;
							int PointIndex1 = Triangle[ idx ].IndexA;
							int PointIndex2 = Triangle[ idx ].IndexB;
							
							if ( DistanceB < NewDistance ) {
								Normal = Triangle[ idx ].NormalB;
								NewDistance = DistanceB;
								PointIndex1 = Triangle[ idx ].IndexB;
								PointIndex2 = Triangle[ idx ].IndexC;
							}
							if ( DistanceC < NewDistance ) {
								Normal = Triangle[ idx ].NormalC;
								NewDistance = DistanceC;
								PointIndex1 = Triangle[ idx ].IndexC;
								PointIndex2 = Triangle[ idx ].IndexA;
							}


//							// Calculate Balance //
//							Vector2D SurfaceRay = Pos( PointIndex2 ) - Pos( PointIndex1 );
//							Vector2D SurfaceRayNormalized = SurfaceRay;
//							Real SurfaceRayLength = SurfaceRayNormalized.NormalizeRet();
//							
//							Vector2D ToPointRay = Vs.Pos( idx ) - Pos( PointIndex1 );
//							
//							Real C1;
//							if ( !SurfaceRayLength.IsZero() )
//								C1 = (SurfaceRayNormalized * ToPointRay) / SurfaceRayLength;
//							else
//								C1 = 1.0f;
//								
//							Real C2 = 1.0f - C1;
//
//							// Move Points //								
//							Pos( PointIndex1 ) -= Normal * (NewDistance) * C2;
//							Pos( PointIndex2 ) -= Normal * (NewDistance) * C1;
							
							// Static, so no pushing //
							//Vs.Pos( idx ) += Normal * (NewDistance) * Real( 0.5 );
							
							Pos( PointIndex1 ) -= Normal * (NewDistance) * Real( 0.5 );
							Pos( PointIndex2 ) -= Normal * (NewDistance) * Real( 0.5 );
							
							continue;
						}
			}
		}
	}
*/		
			
	// Recalculate Bounding Rectangles //
	CalcBoundingRect();
	CalcNormals();
}
// - ------------------------------------------------------------------------------------------ - //
