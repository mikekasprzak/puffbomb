// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <External/Triangulate3/Triangulate.h>

#include "StaticBody2D.h"
#include "../Mesh3D/Mesh3D.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cCollisionLine {
public:
	Vector2D a, b;
	Vector2D Normal;
	bool Used;
	
	cCollisionLine() :
		Used( false )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
extern int __vp[V_MAX];
int __vp[V_MAX];
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::GenerateCollision( const std::vector< cMesh3D >& Mesh ) {    
	Log( LOG_HIGHEST_LEVEL, "----- Generating Collision... -------------------------" );
	
	// Lines calculated from the collision //
	vector< cCollisionLine > CollisionLine;
	vector< std::vector< cCollisionLine > > Polygon;
	
	//CollisionLine.clear();
	//Polygon.clear();
	
	// For all polygons, get the line segments //
	for( size_t ObjectIndex = 0; ObjectIndex < Mesh.size(); ++ObjectIndex ) {
		if ( Mesh[ ObjectIndex ].NoCollision() ) {
			Log( LOG_HIGHEST_LEVEL, "Skipping Collision Generation for this Shape" ); 
			continue;
		}
		
		for ( size_t Index = 0; Index < (*Mesh[ ObjectIndex ].Indices).Size(); Index+=3 ) {
			// Test if polygon if it crosses the Z axis //
			int Sign = 0;

			const Vector3D* V1 = &((*Mesh[ ObjectIndex ].Vertex)[ ((*Mesh[ ObjectIndex ].Indices)[ Index ]) + 0 ]);
			const Vector3D* V2 = &((*Mesh[ ObjectIndex ].Vertex)[ ((*Mesh[ ObjectIndex ].Indices)[ Index ]) + 1 ]);
			const Vector3D* V3 = &((*Mesh[ ObjectIndex ].Vertex)[ ((*Mesh[ ObjectIndex ].Indices)[ Index ]) + 2 ]);
			
			const Vector3D* Positive = V1;
			const Vector3D* Negative = V1;

			
			if ( V1->z < Real::Zero ) {
				Negative = V1;
				Sign--;
			}
			else {
				Positive = V1;
				Sign++;
			}

			if ( V2->z < Real::Zero ) {
				Negative = V2;
				Sign--;
			}
			else {
				Positive = V2;
				Sign++;
			}

			if ( V3->z < Real::Zero ) {
				Negative = V3;
				Sign--;
			}
			else {
				Positive = V3;
				Sign++;
			}


			// If if did //
			if ( abs( Sign ) != 3 ) {
				// Add a new Collision Line //
				CollisionLine.push_back( cCollisionLine() );
				
				// Get the approximate normal (zero z and perhaps normalize) //
				CollisionLine.back().Normal = (*Mesh[ ObjectIndex ].VertexNormal[ ((*Mesh[ ObjectIndex ].Indices)[ Index ]) + 0 ]).ToVector2D();
				//CollisionLine.back().Normal = Vector2D( Model[0].Model->VertexNormal[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Normal.a ].x,Model[0].Model->VertexNormal[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Normal.a ].z ); 
					
				// Determine which two lines are the crossing lines //
				const Vector3D* Point;
				
				if ( Sign == 1 ) {
					Point = Negative;
				}
				else {
					Point = Positive;
				}

				const Vector3D* PointA = V1;
				const Vector3D* PointB = V2;
				
				if ( PointA == Point ) {
					PointA = V2;
					PointB = V3;
				}
				else if ( PointB == Point ) {
					PointB = V3;
				}
				
				// Get points on each line segment to make new 2D line //
				Vector3D OriginNormal( Real::Zero, Real::Zero, Real::One );
				
				Vector3D RayA = *PointA - *Point;
				Real DistanceA = -(OriginNormal * *Point) / (OriginNormal * RayA);
				CollisionLine.back().a = (*Point + ( DistanceA * RayA )).ToVector2D();
				
				Vector3D RayB = *PointB - *Point;
				Real DistanceB = -(OriginNormal * *Point) / (OriginNormal * RayB);
				CollisionLine.back().b = (*Point + ( DistanceB * RayB )).ToVector2D();
			}
		}				
	}

	
	
	Log( 10, "Redundant... " << CollisionLine.size() << " lines total" );

	// Remove redundant entries (ones nearly equal on both ends) //
	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
		if ( CollisionLine[ idx ].a == CollisionLine[ idx ].b ) {
			//Log( 10, "Error!!  CollisionLine " << idx << " is itself!" );
			CollisionLine.erase( CollisionLine.begin() + idx );
			if ( idx != 0 )
				idx--;
		}
	}
	
	Log( 10, "Optimized down to " << CollisionLine.size() << " lines" );


	// Rearrange the A/B order based on the normal //
	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
		Vector2D Ray = CollisionLine[ idx ].b - CollisionLine[ idx ].a;
		
		if ( Ray.Tangent() * CollisionLine[ idx ].Normal >= Real::Zero ) {
			Vector2D Temp = CollisionLine[ idx ].a;
			CollisionLine[ idx ].a = CollisionLine[ idx ].b;
			CollisionLine[ idx ].b = Temp;
		}
	}
	
	// Re-Normalize //
	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
		CollisionLine[ idx ].Normal = (CollisionLine[ idx ].a - CollisionLine[ idx ].b).Tangent().Normal();
	}

	Log( 10, "Optimizing... " << CollisionLine.size() << " lines total" );

	// Optimize lines //	
	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
		for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
			// Similar Position //
			if ( CollisionLine[ idx ].b == CollisionLine[ idx2 ].a ) {
				// Similar Normal //
				if ( CollisionLine[ idx ].Normal == CollisionLine[ idx2 ].Normal ) {
					CollisionLine[ idx ].b = CollisionLine[ idx2 ].b;
					CollisionLine.erase( CollisionLine.begin() + idx2 );
					idx2--;
				}
			}
			// Similar Position //
			else if ( CollisionLine[ idx ].a == CollisionLine[ idx2 ].b ) {
				// Similar Normal //
				if ( CollisionLine[ idx ].Normal == CollisionLine[ idx2 ].Normal ) {
					CollisionLine[ idx ].a = CollisionLine[ idx2 ].a;
					CollisionLine.erase( CollisionLine.begin() + idx2 );
					idx2--;
				}
			}
		}
	}
	
	Log( 10, "Optimized down to " << CollisionLine.size() << " lines" );

	Log( 10, "" );

	Log( 10, "Searching for Polygons..." );
	
	// Generate Polygons //
	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {		
		// If found an unused line, create a new polygon //
		if ( !CollisionLine[ idx ].Used ) {
			//Log( 10, "Object " << StaticObject.size() << " (Polygon " << idx << ")..." );

			CollisionLine[ idx ].Used = true;
			Polygon.push_back( vector< cCollisionLine >() );
			Polygon.back().push_back( CollisionLine[ idx ] );
				
			// Search for my neighbours //
			int NextLine = -1;
			int PrevLine = -1;

			
//			for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
//				if ( !CollisionLine[ idx2 ].Used ) {
//					if ( CollisionLine[ idx ].b == CollisionLine[ idx2 ].a ) {
//						NextLine = idx2;
//					}
//					if ( CollisionLine[ idx ].a == CollisionLine[ idx2 ].b ) {
//						PrevLine = idx2;
//					}
//				}
//			}

			
			Real BestNext = Real(10*10);
			Real BestPrev = Real(10*10);
			
			for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
				if ( !CollisionLine[ idx2 ].Used ) {
					//Log( 10, "+ b " << idx << " " << CollisionLine[ idx ].b.x<< " " << CollisionLine[ idx ].b.y );
					//Log( 10, "+ a " << idx2 << " " << CollisionLine[ idx2 ].a.x<< " " << CollisionLine[ idx2 ].a.y );
					if ( (CollisionLine[ idx ].b - CollisionLine[ idx2 ].a).MagnitudeSquared() < BestNext ) {
						//Log( 10, "++ Better " << idx2 );
						NextLine = idx2;
						BestNext = (CollisionLine[ idx ].b - CollisionLine[ idx2 ].a).MagnitudeSquared();
					}
					//Log( 10, "- a " << idx << " " << CollisionLine[ idx ].a.x<< " " << CollisionLine[ idx ].a.y );
					//Log( 10, "- b " << idx2 << " " << CollisionLine[ idx2 ].b.x<< " " << CollisionLine[ idx2 ].b.y );
					if ( (CollisionLine[ idx ].a - CollisionLine[ idx2 ].b).MagnitudeSquared() < BestPrev ) {
						//Log( 10, "-- Better " << idx2 );
						PrevLine = idx2;
						BestPrev = (CollisionLine[ idx ].a - CollisionLine[ idx2 ].b).MagnitudeSquared();
					}
				}
			}

			if ( NextLine != -1 ) {
				CollisionLine[ NextLine ].Used = true;
				Polygon.back().push_back( CollisionLine[ NextLine ] );
			}
			else {
				Log( 10, "Error!! Polygon \"NEXT\" never found!!!" );
			}
			
			if ( PrevLine == -1 ) {
				Log( 10, "Error!! Polygon \"END\" never found!!!" );
//				CollisionLine[ PrevLine ].Used = true;
//				Polygon.front().push_back( CollisionLine[ PrevLine ] );
			}
			
			
			
			// Find every line attached to my neighbour and his neighbour and so on //
			int MyNextLine = -1;
			while ( MyNextLine != PrevLine ) {
				MyNextLine = -1;

//				for( size_t idx2 = 0; idx2 < CollisionLine.size(); idx2++ ) {
//					if ( !CollisionLine[ idx2 ].Used ) {
//						if ( CollisionLine[ NextLine ].b == CollisionLine[ idx2 ].a ) {
//							MyNextLine = idx2;
//						}
//					}
//				}

				Real Best = Real(10*10);
			
				//Log( 10, "**** b " << NextLine << " " << CollisionLine[ NextLine ].b.x<< " " << CollisionLine[ NextLine ].b.y );
				for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
					if ( !CollisionLine[ idx2 ].Used ) {
						//Log( 10, "* a " << idx2 << " " << CollisionLine[ idx2 ].a.x<< " " << CollisionLine[ idx2 ].a.y );
						if ( (CollisionLine[ NextLine ].b - CollisionLine[ idx2 ].a).MagnitudeSquared() < Best ) {
							//Log( 10, "** Better " << idx2 );
							MyNextLine = idx2;
							Best = (CollisionLine[ NextLine ].b - CollisionLine[ idx2 ].a).MagnitudeSquared();
						}
					}
				}
	
				if ( MyNextLine != -1 ) {
					CollisionLine[ MyNextLine ].Used = true;
					Polygon.back().push_back( CollisionLine[ MyNextLine ] );
					NextLine = MyNextLine;
				}
				else {
					Log( 10, "Error!! Polygon never closes!!!" );
					break;
				}
			}
			
			Log( 10, Polygon.back().size() << " Elements found" );
		}
	}
	Log( 10, Polygon.size() << " Polygons found in this object" );


	// Add Edges //
	for( size_t idx = 0; idx < Polygon.size(); idx++ ) {
//		// Add a new static object to the end //
//		StaticObject.push_back( new cStaticObject( Polygon[idx].size() ) );
//
//		for( size_t idx2 = 0; idx2 < Polygon[idx].size(); idx2++ ) {
//			StaticObject.back()->Pos( idx2 ) = Polygon[idx][ idx2 ].a;
//			StaticObject.back()->Edge[ idx2 ] = cStaticEdge( idx2, idx2 + 1 );
//		}
//
//		// Set the last entries "B" to element 0 //
//		StaticObject.back()->Edge.back().b = 0;

		// Make room for the used nodes and edges //
		Nodes.Resize( Nodes.Size() + Polygon[ idx ].size() );
		this->Edge.resize( this->Edge.size() + Polygon[ idx ].size() );

		// Loop through every polygon, and extract the edges //
		for( size_t idx2 = 0; idx2 < Polygon[idx].size(); idx2++ ) {
			Nodes.Pos( idx2 ) = Polygon[ idx ][ idx2 ].a;
			this->Edge[ idx2 ] = cStaticEdge( idx2, idx2 + 1 );
		}
		
		// Set the last entries "B" to element 0 //
		this->Edge.back().b = 0;		
		
// ??		Edge.push_back( 

//		this->Edge.resize( Polygon[ idx ].size() );
//		Nodes.Resize( Polygon[ idx ].size() );
//
//		for ( size_t idx2 = 0; idx2 < this->Edge.size(); idx2++ ) {
//			this->Edge[ idx2 ].CalcNormal( Nodes );
//			this->Edge[ idx2 ].CalcBoundingRect( Nodes );
//		}

	}

//	// Calculate Normal and Bounding Rectangle for Edge //
//	for( size_t idx = 0; idx < StaticObject.size(); idx++ ) {
//		for( size_t idx2 = 0; idx2 < StaticObject[idx]->Edge.size(); idx2++ ) {
//			StaticObject[ idx ]->Edge[ idx2 ].CalcNormal( *StaticObject[ idx ] );
//			StaticObject[ idx ]->Edge[ idx2 ].CalcBoundingRect( *StaticObject[ idx ] );
//		}
//	}

	// Calculate Normal and Bounding Rectangle for Edge //
	for( size_t idx2 = 0; idx2 < this->Edge.size(); idx2++ ) {
		this->Edge[ idx2 ].CalcNormal( Nodes );
		this->Edge[ idx2 ].CalcBoundingRect( Nodes );
	}
	
	
	Log( 10, "" );

	// Subdivide polygons in to convex polygons (not my code) //
	for ( size_t idx = 0; idx < Polygon.size(); idx++ ) {
		int n = Polygon[idx].size();
		__vertex v[Polygon[idx].size()];
		
		for ( size_t idx2 = 0; idx2 < Polygon[idx].size(); idx2++ ) {
			v[idx2].x = Polygon[idx][idx2].a.x;
			v[idx2].y = Polygon[idx][idx2].a.y;
			v[idx2].z = 0;//Polygon[idx][idx2].a.z;
		}
		
		{
			extern int __vp[V_MAX];
		    int prev, cur, next;        /* Three points currently being considered */
		    //int vp[V_MAX];              /* Pointers to vertices still left */
		    int count;                  /* How many vertices left */
		    int min_vert;               /* Vertex with minimum distance */
		    int i;                      /* Iterative counter */
		    float dist;                 /* Distance across this one */
		    float min_dist;             /* Minimum distance so far */
		    int poly_orientation;       /* Polygon orientation */
		    __triangle t;                 /* __triangle structure */
		
		    if (n > V_MAX) {
		        //fprintf( stderr, "Error, more than %d vertices.\n", V_MAX);
		        Log( 10, "Error, more than " << V_MAX << " vertices.\n" );
		        return;
		    }
		
		    poly_orientation = __orientation( n, v );
		
		    for (i = 0; i < n; i++)
		        __vp[i] = i;              /* Put vertices in order to begin */
		
		/* Slice off clean __triangles until nothing remains */
		
		    count = n;
		    while (count > 3) {
		        min_dist = BIG;         /* A real big number */
		        min_vert = 0;           /* Just in case we don't find one... */
		        for (cur = 0; cur < count; cur++) {
		            prev = cur - 1;
		            next = cur + 1;
		            if (cur == 0)       /* Wrap around on the ends */
		                prev = count - 1;
		            else if (cur == count - 1)
		                next = 0;
		            /* Pick out shortest distance that forms a good __triangle */
		            if (   (__determinant( __vp[prev], __vp[cur], __vp[next], v ) == poly_orientation)
		                    /* Same orientation as polygon */
		                && __no_interior( __vp[prev], __vp[cur], __vp[next], v, __vp, count, poly_orientation )
		                    /* No points inside */
		                && ((dist = __distance2( v[__vp[prev]].x, v[__vp[prev]].y,
		                                       v[__vp[next]].x, v[__vp[next]].y )) < min_dist) )
		                    /* Better than any so far */
		            {
		                min_dist = dist;
		                min_vert = cur;
		            }
		        } /* End of for each vertex (cur) */
		
		        /* The following error should "never happen". */
		        if (min_dist == BIG)
		            Log( 10, "Error: Didn't find a __triangle.\n" );
		
		        prev = min_vert - 1;
		        next = min_vert + 1;
		        if (min_vert == 0)      /* Wrap around on the ends */
		            prev = count - 1;
		        else if (min_vert == count - 1)
		            next = 0;
		
				// Output this Triangle //
				this->Polygon.push_back( cStaticPolygon( 3 ) );
				this->Polygon.back().Index[0] = __vp[prev];
				this->Polygon.back().Index[1] = __vp[min_vert];
				this->Polygon.back().Index[2] = __vp[next];
				this->Polygon.back().CalcBoundingRect( Nodes );
		
				/* Remove the __triangle from the polygon */
		        count -= 1;
		        for (i = min_vert; i < count; i++)
		            __vp[i] = __vp[i+1];
		    }
		
			// Output the final Triangle //
			this->Polygon.push_back( cStaticPolygon( 3 ) );
			this->Polygon.back().Index[0] = __vp[0];
			this->Polygon.back().Index[1] = __vp[1];
			this->Polygon.back().Index[2] = __vp[2];
			this->Polygon.back().CalcBoundingRect( Nodes );
		}	
	}
	
/*	
	Log( 10, "Polygon Optimization" );
	
	// Optimize triangles that can join together to become convex polygons //
	for( size_t ObjectIdx = 0; ObjectIdx < StaticObject.size(); ObjectIdx++ ) {
		cStaticObject& Obj = *StaticObject[ObjectIdx];
		Log( 10, "Object " << ObjectIdx );
		Log( 10, Obj.Polygon.size() << " polygons before optimization" );
		
		// For every polygon versus every other polygon inside the static object //
		for ( size_t PolyIdx = 0; PolyIdx < Obj.Polygon.size(); PolyIdx++ ) {
//			Log( 10, "Polygon " << PolyIdx );
			for ( size_t PolyIdx2 = PolyIdx+1; PolyIdx2 < Obj.Polygon.size(); PolyIdx2++ ) {
//				Log( 10, "Versus Polygon " << PolyIdx2 );
				cStaticPolygon& Polygon1 = Obj.Polygon[PolyIdx];
				cStaticPolygon& Polygon2 = Obj.Polygon[PolyIdx2];
				
				// Bail if an edge was found... may be a wasteful optimization //
				bool EdgeFound = false;
								
				// Test to see if we have a common edge //
				for ( size_t FirstMarkerA = 0; FirstMarkerA < Polygon1.Index.size(); FirstMarkerA++ ) {
					for ( size_t SecondMarkerB = 0; SecondMarkerB < Polygon2.Index.size(); SecondMarkerB++ ) {
						// If 1stA and 2ndB markers are equal, we may have a common edge //
						if ( Polygon1.Index[ FirstMarkerA ] == Polygon2.Index[ SecondMarkerB ] ) {
							// Calculate the 2ndA and 1stB markers // 
							size_t SecondMarkerA = FirstMarkerA + 1;
							if ( SecondMarkerA == Polygon1.Index.size() )
								SecondMarkerA = 0;

							size_t FirstMarkerB = SecondMarkerB - 1;
							if ( SecondMarkerB == 0 )
								FirstMarkerB = Polygon2.Index.size() - 1;
							
							// If 2ndA and 1stB markers are equal we have a common edge //
							if ( Polygon1.Index[ SecondMarkerA ] == Polygon2.Index[ FirstMarkerB ] ) {
//								Log( 10, "Common Edge Found, accumulating parts" );
								// Create new polygon //
								cStaticPolygon NewPolygon( Polygon1.Index.size() + Polygon2.Index.size() - 2 );
								
								// Populate polygon with all verts using the common edge to join //
								size_t Index = 0;
								
								
								// All of A, up to and including 1st marker //
								for ( size_t idx = 0; idx <= FirstMarkerA; idx++ ) {
									NewPolygon.Index[ Index ] = Polygon1.Index[ idx ];
									Index++;
								}

								// All after 2nd marker in B //
								for ( size_t idx = SecondMarkerB + 1; idx < Polygon2.Index.size(); idx++ ) {
									if ( idx != FirstMarkerB ) {
										NewPolygon.Index[ Index ] = Polygon2.Index[ idx ];
										Index++;
									}
								}

								// All of B, up to 1st marker, if it's not the last one //
								if ( FirstMarkerB != Polygon2.Index.size() - 1 ) {
									for ( size_t idx = 0; idx < FirstMarkerB; idx++ ) {
										NewPolygon.Index[ Index ] = Polygon2.Index[ idx ];
										Index++;
									}
								}

								// 2nd Marker of A to the end, if it's not the first one //
								if ( SecondMarkerA != 0 ) {
									for ( size_t idx = SecondMarkerA; idx < Polygon1.Index.size(); idx++ ) {
										NewPolygon.Index[ Index ] = Polygon1.Index[ idx ];
										Index++;
									}
								}

								
								// Debug info //
//								{
//									if ( Index == NewPolygon.Index.size() ) {
//										Log( 10, "*+* Equal " << Index );
//									}
//									else {
//										Log( 10, "*+* NOT EQUAL!! Added: " << Index << "   Size:" << NewPolygon.Index.size() );
//									}
//	
//									std::cout << "*+* Elements:";
//									for ( size_t idx = 0; idx < NewPolygon.Index.size(); idx++ ) {
//										std::cout << " " << NewPolygon.Index[ idx ];
//									}
//									std::cout << std::endl;
//								}
								
								
								// Verify polygon is convex //
								int Convex = 0;
								
								// For all points, follow neighbours and verify convexity //
								for ( size_t idx = 0; idx < NewPolygon.Index.size(); idx++ ) {
									int IdxNext = (idx + 1) % NewPolygon.Index.size();
									int IdxNextNext = (idx + 2) % NewPolygon.Index.size();
									
									Vector2D VecA = Obj.Pos( NewPolygon.Index[IdxNext] ) - Obj.Pos( NewPolygon.Index[idx] );
									Vector2D VecB = Obj.Pos( NewPolygon.Index[IdxNextNext] ) - Obj.Pos( NewPolygon.Index[IdxNext] );
									
									if ( VecA * -VecB.Tangent() >= Real::Zero ) {
										Convex++;
									}
									else {
										Convex--;
									}
								}
								
								// Debug Info //
//								Log( 10, "*** Convex: " << Convex << " " << NewPolygon.Index.size() );
								
								// If they're equal, we're convex //
								if ( Convex == (int)NewPolygon.Index.size() ) {
//									Log( 10, "New Polygon is Convex!" );
									
									// Replace and delete the original two //
									Obj.Polygon[PolyIdx] = NewPolygon;
									Obj.Polygon.erase( Obj.Polygon.begin() + PolyIdx2 );

									// An edge was found //
									EdgeFound = true;
									break;
								}
							}
						}
					}
					// An edge was found //
					if ( EdgeFound )
						break;
				}

				// An edge was found, re-do this polygon //
				if ( EdgeFound ) {
					PolyIdx--;
					break;
				}
			}			
		}
		
		Log( 10, Obj.Polygon.size() << " polygons after optimization" );
		Log( 10, "" );
	}	
*/	
	
	// Calculate bounding rectangles for all polygons // 	
	for ( size_t idx2 = 0; idx2 < this->Polygon.size(); idx2++ ) {
		this->Polygon[idx2].CalcBoundingRect( Nodes );
	}
	
	// Calculate mine //
	CalcBoundingRect();

//
////	Log( LOG_HIGHEST_LEVEL, "----- Generating Collision... -------------------------" );
//
//
//	// Lines calculated from the collision //
//	vector< cCollisionLine > CollisionLine;
//	vector< std::vector< cCollisionLine > > Polygon;
//	
//	//CollisionLine.clear();
//	//Polygon.clear();
//	
//	// For all polygons, get the line segments //
////	for( size_t ObjectIndex = 0; ObjectIndex < Model[0].Model->Object.size(); ++ObjectIndex ) {
////		for( size_t GroupIndex = 0; GroupIndex < Model[0].Model->Object[ ObjectIndex ].Group.size(); ++GroupIndex ) {
//			//if ( Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].NoCollision ) {
//			if ( _Mesh.NoCollision() ) {
//				Log( LOG_HIGHEST_LEVEL, "Skipping Collision Generation for this Shape" ); 
////				continue;
//				return;
//			}
//			
//			//for( size_t FaceIndex = 0; FaceIndex < Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face.size(); ++FaceIndex ) {
//			for ( size_t Index = 0; Index < (*_Mesh.Indices).Size(); Index+=3 ) {
//				// Test if polygon if it crosses the Z axis //
//				int Sign = 0;
//				
////				const Vector3D* V1 = &Model[0].Model->Object[ ObjectIndex ].Vertex[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Vertex.a ];
////				const Vector3D* V2 = &Model[0].Model->Object[ ObjectIndex ].Vertex[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Vertex.b ];
////				const Vector3D* V3 = &Model[0].Model->Object[ ObjectIndex ].Vertex[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Vertex.c ];
//
//				const Vector3D* V1 = &((*_Mesh.Vertex)[ ((*_Mesh.Indices)[ Index ]) + 0 ]);
//				const Vector3D* V2 = &((*_Mesh.Vertex)[ ((*_Mesh.Indices)[ Index ]) + 1 ]);
//				const Vector3D* V3 = &((*_Mesh.Vertex)[ ((*_Mesh.Indices)[ Index ]) + 2 ]);
//
//				const Vector3D* Positive = V1;
//				const Vector3D* Negative = V1;
//
//				
//				if ( V1->z < Real::Zero ) {
//					Negative = V1;
//					Sign--;
//				}
//				else {
//					Positive = V1;
//					Sign++;
//				}
//	
//				if ( V2->z < Real::Zero ) {
//					Negative = V2;
//					Sign--;
//				}
//				else {
//					Positive = V2;
//					Sign++;
//				}
//	
//				if ( V3->z < Real::Zero ) {
//					Negative = V3;
//					Sign--;
//				}
//				else {
//					Positive = V3;
//					Sign++;
//				}
//
//
//				// If if did //
//				if ( abs( Sign ) != 3 ) {
//					// Add a new Collision Line //
//					CollisionLine.push_back( cCollisionLine() );
//					
//					// Get the approximate normal (zero z and perhaps normalize) //
////					CollisionLine.back().Normal = Model[0].Model->VertexNormal[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Normal.a ].ToVector2D();
//					//CollisionLine.back().Normal = Vector2D( Model[0].Model->VertexNormal[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Normal.a ].x,Model[0].Model->VertexNormal[ Model[0].Model->Object[ ObjectIndex ].Group[ GroupIndex ].Face[ FaceIndex ].Normal.a ].z ); 
//						
//					// Determine which two lines are the crossing lines //
//					const Vector3D* Point;
//					
//					if ( Sign == 1 ) {
//						Point = Negative;
//					}
//					else {
//						Point = Positive;
//					}
//
//					const Vector3D* PointA = V1;
//					const Vector3D* PointB = V2;
//					
//					if ( PointA == Point ) {
//						PointA = V2;
//						PointB = V3;
//					}
//					else if ( PointB == Point ) {
//						PointB = V3;
//					}
//					
//					// Get points on each line segment to make new 2D line //
//					Vector3D OriginNormal( Real::Zero, Real::Zero, Real::One );
//					
//					Vector3D RayA = *PointA - *Point;
//					Real DistanceA = -(OriginNormal * *Point) / (OriginNormal * RayA);
//					CollisionLine.back().a = (*Point + ( DistanceA * RayA )).ToVector2D();
//					
//					Vector3D RayB = *PointB - *Point;
//					Real DistanceB = -(OriginNormal * *Point) / (OriginNormal * RayB);
//					CollisionLine.back().b = (*Point + ( DistanceB * RayB )).ToVector2D();
//				}
//			}				
////		}
////	}
//
//	
//	
//	Log( 10, "Redundant... " << CollisionLine.size() << " lines total" );
//
//	// Remove redundant entries (ones nearly equal on both ends) //
//	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
//		if ( CollisionLine[ idx ].a == CollisionLine[ idx ].b ) {
//			//Log( 10, "Error!!  CollisionLine " << idx << " is itself!" );
//			CollisionLine.erase( CollisionLine.begin() + idx );
//			if ( idx != 0 )
//				idx--;
//		}
//	}
//	
//	Log( 10, "Optimized down to " << CollisionLine.size() << " lines" );
//
//
//	// Rearrange the A/B order based on the normal //
//	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
//		Vector2D Ray = CollisionLine[ idx ].b - CollisionLine[ idx ].a;
//		
//		if ( Ray.Tangent() * CollisionLine[ idx ].Normal >= Real::Zero ) {
//			Vector2D Temp = CollisionLine[ idx ].a;
//			CollisionLine[ idx ].a = CollisionLine[ idx ].b;
//			CollisionLine[ idx ].b = Temp;
//		}
//	}
//	
//	// Re-Normalize //
//	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
//		CollisionLine[ idx ].Normal = (CollisionLine[ idx ].a - CollisionLine[ idx ].b).Tangent().Normal();
//	}
//
//	Log( 10, "Optimizing... " << CollisionLine.size() << " lines total" );
//
//	// Optimize lines //	
//	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {
//		for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
//			// Similar Position //
//			if ( CollisionLine[ idx ].b == CollisionLine[ idx2 ].a ) {
//				// Similar Normal //
//				if ( CollisionLine[ idx ].Normal == CollisionLine[ idx2 ].Normal ) {
//					CollisionLine[ idx ].b = CollisionLine[ idx2 ].b;
//					CollisionLine.erase( CollisionLine.begin() + idx2 );
//					idx2--;
//				}
//			}
//			// Similar Position //
//			else if ( CollisionLine[ idx ].a == CollisionLine[ idx2 ].b ) {
//				// Similar Normal //
//				if ( CollisionLine[ idx ].Normal == CollisionLine[ idx2 ].Normal ) {
//					CollisionLine[ idx ].a = CollisionLine[ idx2 ].a;
//					CollisionLine.erase( CollisionLine.begin() + idx2 );
//					idx2--;
//				}
//			}
//		}
//	}
//	
//	Log( 10, "Optimized down to " << CollisionLine.size() << " lines" );
//
//	Log( 10, "" );
//
//	Log( 10, "Searching for Polygons..." );
//	
//	// Generate Polygons //
//	for( size_t idx = 0; idx < CollisionLine.size(); idx++ ) {		
//		// If found an unused line, create a new polygon //
//		if ( !CollisionLine[ idx ].Used ) {
//			//Log( 10, "Object " << StaticObject.size() << " (Polygon " << idx << ")..." );
//
//			CollisionLine[ idx ].Used = true;
//			Polygon.push_back( vector< cCollisionLine >() );
//			Polygon.back().push_back( CollisionLine[ idx ] );
//				
//			// Search for my neighbours //
//			int NextLine = -1;
//			int PrevLine = -1;
//
//			
////			for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
////				if ( !CollisionLine[ idx2 ].Used ) {
////					if ( CollisionLine[ idx ].b == CollisionLine[ idx2 ].a ) {
////						NextLine = idx2;
////					}
////					if ( CollisionLine[ idx ].a == CollisionLine[ idx2 ].b ) {
////						PrevLine = idx2;
////					}
////				}
////			}
//
//			
//			Real BestNext = Real(10*10);
//			Real BestPrev = Real(10*10);
//			
//			for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
//				if ( !CollisionLine[ idx2 ].Used ) {
//					//Log( 10, "+ b " << idx << " " << CollisionLine[ idx ].b.x<< " " << CollisionLine[ idx ].b.y );
//					//Log( 10, "+ a " << idx2 << " " << CollisionLine[ idx2 ].a.x<< " " << CollisionLine[ idx2 ].a.y );
//					if ( (CollisionLine[ idx ].b - CollisionLine[ idx2 ].a).MagnitudeSquared() < BestNext ) {
//						//Log( 10, "++ Better " << idx2 );
//						NextLine = idx2;
//						BestNext = (CollisionLine[ idx ].b - CollisionLine[ idx2 ].a).MagnitudeSquared();
//					}
//					//Log( 10, "- a " << idx << " " << CollisionLine[ idx ].a.x<< " " << CollisionLine[ idx ].a.y );
//					//Log( 10, "- b " << idx2 << " " << CollisionLine[ idx2 ].b.x<< " " << CollisionLine[ idx2 ].b.y );
//					if ( (CollisionLine[ idx ].a - CollisionLine[ idx2 ].b).MagnitudeSquared() < BestPrev ) {
//						//Log( 10, "-- Better " << idx2 );
//						PrevLine = idx2;
//						BestPrev = (CollisionLine[ idx ].a - CollisionLine[ idx2 ].b).MagnitudeSquared();
//					}
//				}
//			}
//
//			if ( NextLine != -1 ) {
//				CollisionLine[ NextLine ].Used = true;
//				Polygon.back().push_back( CollisionLine[ NextLine ] );
//			}
//			else {
//				Log( 10, "Error!! Polygon \"NEXT\" never found!!!" );
//			}
//			
//			if ( PrevLine == -1 ) {
//				Log( 10, "Error!! Polygon \"END\" never found!!!" );
////				CollisionLine[ PrevLine ].Used = true;
////				Polygon.front().push_back( CollisionLine[ PrevLine ] );
//			}
//			
//			
//			
//			// Find every line attached to my neighbour and his neighbour and so on //
//			int MyNextLine = -1;
//			while ( MyNextLine != PrevLine ) {
//				MyNextLine = -1;
//
////				for( size_t idx2 = 0; idx2 < CollisionLine.size(); idx2++ ) {
////					if ( !CollisionLine[ idx2 ].Used ) {
////						if ( CollisionLine[ NextLine ].b == CollisionLine[ idx2 ].a ) {
////							MyNextLine = idx2;
////						}
////					}
////				}
//
//				Real Best = Real(10*10);
//			
//				//Log( 10, "**** b " << NextLine << " " << CollisionLine[ NextLine ].b.x<< " " << CollisionLine[ NextLine ].b.y );
//				for( size_t idx2 = idx+1; idx2 < CollisionLine.size(); idx2++ ) {
//					if ( !CollisionLine[ idx2 ].Used ) {
//						//Log( 10, "* a " << idx2 << " " << CollisionLine[ idx2 ].a.x<< " " << CollisionLine[ idx2 ].a.y );
//						if ( (CollisionLine[ NextLine ].b - CollisionLine[ idx2 ].a).MagnitudeSquared() < Best ) {
//							//Log( 10, "** Better " << idx2 );
//							MyNextLine = idx2;
//							Best = (CollisionLine[ NextLine ].b - CollisionLine[ idx2 ].a).MagnitudeSquared();
//						}
//					}
//				}
//	
//				if ( MyNextLine != -1 ) {
//					CollisionLine[ MyNextLine ].Used = true;
//					Polygon.back().push_back( CollisionLine[ MyNextLine ] );
//					NextLine = MyNextLine;
//				}
//				else {
//					Log( 10, "Error!! Polygon never closes!!!" );
//					break;
//				}
//			}
//			
//			Log( 10, Polygon.back().size() << " Elements found" );
//		}
//	}
//	Log( 10, Polygon.size() << " Polygons found in this object" );
//
//
//	// Add Edges //
////	for( size_t idx = 0; idx < Polygon.size(); idx++ ) {
////		// Add a new static object to the end //
////		StaticObject.push_back( new cStaticObject( Polygon[idx].size() ) );
//
//		this->Edge.resize( Polygon[0].size() );
//		Nodes.Resize( Polygon[0].size() );
//
////		for( size_t idx2 = 0; idx2 < Polygon[idx].size(); idx2++ ) {
////			StaticObject.back()->Pos( idx2 ) = Polygon[idx][ idx2 ].a;
////			StaticObject.back()->Edge[ idx2 ] = cStaticEdge( idx2, idx2 + 1 );
////		}
//
//		for( size_t idx2 = 0; idx2 < Polygon[0].size(); idx2++ ) {
//			this->Nodes.Pos( idx2 ) = Polygon[0][ idx2 ].a;
//			this->Edge[ idx2 ] = cStaticEdge( idx2, idx2 + 1 );
//		}
//
//		// Set the last entries "B" to element 0 //
////		StaticObject.back()->Edge.back().b = 0;
//		this->Edge.back().b = 0;
////	}
//
//	// Calculate Normal and Bounding Rectangle for Edge //
////	for( size_t idx = 0; idx < StaticObject.size(); idx++ ) {
////		for( size_t idx2 = 0; idx2 < StaticObject[idx]->Edge.size(); idx2++ ) {
////			StaticObject[ idx ]->Edge[ idx2 ].CalcNormal( *StaticObject[ idx ] );
////			StaticObject[ idx ]->Edge[ idx2 ].CalcBoundingRect( *StaticObject[ idx ] );
////		}
//
//		for ( size_t idx2 = 0; idx2 < this->Edge.size(); idx2++ ) {
//			this->Edge[ idx2 ].CalcNormal( Nodes );
//			this->Edge[ idx2 ].CalcBoundingRect( Nodes );
//		}
////	}
//
//	
//	
//	Log( 10, "" );
//
//	// Subdivide polygons in to convex polygons (not my code) //
//	//for ( size_t idx = 0; idx < Polygon.size(); idx++ )
//	{
//		size_t idx = 0;
//		
//		int n = Polygon[idx].size();
//		__vertex v[Polygon[idx].size()];
//		
//		for ( size_t idx2 = 0; idx2 < Polygon[idx].size(); idx2++ ) {
//			v[idx2].x = Polygon[idx][idx2].a.x;
//			v[idx2].y = Polygon[idx][idx2].a.y;
//			v[idx2].z = 0;//Polygon[idx][idx2].a.z;
//		}
//		
//		{
//			extern int __vp[V_MAX];
//		    int prev, cur, next;        /* Three points currently being considered */
//		    //int vp[V_MAX];              /* Pointers to vertices still left */
//		    int count;                  /* How many vertices left */
//		    int min_vert;               /* Vertex with minimum distance */
//		    int i;                      /* Iterative counter */
//		    float dist;                 /* Distance across this one */
//		    float min_dist;             /* Minimum distance so far */
//		    int poly_orientation;       /* Polygon orientation */
//		    __triangle t;                 /* __triangle structure */
//		
//		    if (n > V_MAX) {
//		        //fprintf( stderr, "Error, more than %d vertices.\n", V_MAX);
//		        Log( 10, "Error, more than " << V_MAX << " vertices.\n" );
//		        return;
//		    }
//		
//		    poly_orientation = __orientation( n, v );
//		
//		    for (i = 0; i < n; i++)
//		        __vp[i] = i;              /* Put vertices in order to begin */
//		
//		/* Slice off clean __triangles until nothing remains */
//		
//		    count = n;
//		    while (count > 3) {
//		        min_dist = BIG;         /* A real big number */
//		        min_vert = 0;           /* Just in case we don't find one... */
//		        for (cur = 0; cur < count; cur++) {
//		            prev = cur - 1;
//		            next = cur + 1;
//		            if (cur == 0)       /* Wrap around on the ends */
//		                prev = count - 1;
//		            else if (cur == count - 1)
//		                next = 0;
//		            /* Pick out shortest distance that forms a good __triangle */
//		            if (   (__determinant( __vp[prev], __vp[cur], __vp[next], v ) == poly_orientation)
//		                    /* Same orientation as polygon */
//		                && __no_interior( __vp[prev], __vp[cur], __vp[next], v, __vp, count, poly_orientation )
//		                    /* No points inside */
//		                && ((dist = __distance2( v[__vp[prev]].x, v[__vp[prev]].y,
//		                                       v[__vp[next]].x, v[__vp[next]].y )) < min_dist) )
//		                    /* Better than any so far */
//		            {
//		                min_dist = dist;
//		                min_vert = cur;
//		            }
//		        } /* End of for each vertex (cur) */
//		
//		        /* The following error should "never happen". */
//		        if (min_dist == BIG)
//		            Log( 10, "Error: Didn't find a __triangle.\n" );
//		
//		        prev = min_vert - 1;
//		        next = min_vert + 1;
//		        if (min_vert == 0)      /* Wrap around on the ends */
//		            prev = count - 1;
//		        else if (min_vert == count - 1)
//		            next = 0;
//		
//				// Output this Triangle //
//				this->Polygon.push_back( cStaticPolygon( 3 ) );
//				this->Polygon.back().Index[0] = __vp[prev];
//				this->Polygon.back().Index[1] = __vp[min_vert];
//				this->Polygon.back().Index[2] = __vp[next];
//				this->Polygon.back().CalcBoundingRect( Nodes );
//		
//				/* Remove the __triangle from the polygon */
//		        count -= 1;
//		        for (i = min_vert; i < count; i++)
//		            __vp[i] = __vp[i+1];
//		    }
//		
//			// Output the final Triangle //
//			this->Polygon.push_back( cStaticPolygon( 3 ) );
//			this->Polygon.back().Index[0] = __vp[0];
//			this->Polygon.back().Index[1] = __vp[1];
//			this->Polygon.back().Index[2] = __vp[2];
//			this->Polygon.back().CalcBoundingRect( Nodes );
//		}	
//	}
//	
//	
//	Log( 10, "Polygon Optimization" );
//	
//	// Re-add this later... there's enough code that needs testing //
//	
////	// Optimize triangles that can join together to become convex polygons //
////	for( size_t ObjectIdx = 0; ObjectIdx < StaticObject.size(); ObjectIdx++ ) {
////		cStaticObject& Obj = *StaticObject[ObjectIdx];
////		Log( 10, "Object " << ObjectIdx );
////		Log( 10, Obj.Polygon.size() << " polygons before optimization" );
////		
////		// For every polygon versus every other polygon inside the static object //
////		for ( size_t PolyIdx = 0; PolyIdx < Obj.Polygon.size(); PolyIdx++ ) {
//////			Log( 10, "Polygon " << PolyIdx );
////			for ( size_t PolyIdx2 = PolyIdx+1; PolyIdx2 < Obj.Polygon.size(); PolyIdx2++ ) {
//////				Log( 10, "Versus Polygon " << PolyIdx2 );
////				cStaticPolygon& Polygon1 = Obj.Polygon[PolyIdx];
////				cStaticPolygon& Polygon2 = Obj.Polygon[PolyIdx2];
////				
////				// Bail if an edge was found... may be a wasteful optimization //
////				bool EdgeFound = false;
////								
////				// Test to see if we have a common edge //
////				for ( size_t FirstMarkerA = 0; FirstMarkerA < Polygon1.Index.size(); FirstMarkerA++ ) {
////					for ( size_t SecondMarkerB = 0; SecondMarkerB < Polygon2.Index.size(); SecondMarkerB++ ) {
////						// If 1stA and 2ndB markers are equal, we may have a common edge //
////						if ( Polygon1.Index[ FirstMarkerA ] == Polygon2.Index[ SecondMarkerB ] ) {
////							// Calculate the 2ndA and 1stB markers // 
////							size_t SecondMarkerA = FirstMarkerA + 1;
////							if ( SecondMarkerA == Polygon1.Index.size() )
////								SecondMarkerA = 0;
////
////							size_t FirstMarkerB = SecondMarkerB - 1;
////							if ( SecondMarkerB == 0 )
////								FirstMarkerB = Polygon2.Index.size() - 1;
////							
////							// If 2ndA and 1stB markers are equal we have a common edge //
////							if ( Polygon1.Index[ SecondMarkerA ] == Polygon2.Index[ FirstMarkerB ] ) {
//////								Log( 10, "Common Edge Found, accumulating parts" );
////								// Create new polygon //
////								cStaticPolygon NewPolygon( Polygon1.Index.size() + Polygon2.Index.size() - 2 );
////								
////								// Populate polygon with all verts using the common edge to join //
////								size_t Index = 0;
////								
////								
////								// All of A, up to and including 1st marker //
////								for ( size_t idx = 0; idx <= FirstMarkerA; idx++ ) {
////									NewPolygon.Index[ Index ] = Polygon1.Index[ idx ];
////									Index++;
////								}
////
////								// All after 2nd marker in B //
////								for ( size_t idx = SecondMarkerB + 1; idx < Polygon2.Index.size(); idx++ ) {
////									if ( idx != FirstMarkerB ) {
////										NewPolygon.Index[ Index ] = Polygon2.Index[ idx ];
////										Index++;
////									}
////								}
////
////								// All of B, up to 1st marker, if it's not the last one //
////								if ( FirstMarkerB != Polygon2.Index.size() - 1 ) {
////									for ( size_t idx = 0; idx < FirstMarkerB; idx++ ) {
////										NewPolygon.Index[ Index ] = Polygon2.Index[ idx ];
////										Index++;
////									}
////								}
////
////								// 2nd Marker of A to the end, if it's not the first one //
////								if ( SecondMarkerA != 0 ) {
////									for ( size_t idx = SecondMarkerA; idx < Polygon1.Index.size(); idx++ ) {
////										NewPolygon.Index[ Index ] = Polygon1.Index[ idx ];
////										Index++;
////									}
////								}
////
////								
////								// Debug info //
//////								{
//////									if ( Index == NewPolygon.Index.size() ) {
//////										Log( 10, "*+* Equal " << Index );
//////									}
//////									else {
//////										Log( 10, "*+* NOT EQUAL!! Added: " << Index << "   Size:" << NewPolygon.Index.size() );
//////									}
//////	
//////									std::cout << "*+* Elements:";
//////									for ( size_t idx = 0; idx < NewPolygon.Index.size(); idx++ ) {
//////										std::cout << " " << NewPolygon.Index[ idx ];
//////									}
//////									std::cout << std::endl;
//////								}
////								
////								
////								// Verify polygon is convex //
////								int Convex = 0;
////								
////								// For all points, follow neighbours and verify convexity //
////								for ( size_t idx = 0; idx < NewPolygon.Index.size(); idx++ ) {
////									int IdxNext = (idx + 1) % NewPolygon.Index.size();
////									int IdxNextNext = (idx + 2) % NewPolygon.Index.size();
////									
////									Vector2D VecA = Obj.Pos( NewPolygon.Index[IdxNext] ) - Obj.Pos( NewPolygon.Index[idx] );
////									Vector2D VecB = Obj.Pos( NewPolygon.Index[IdxNextNext] ) - Obj.Pos( NewPolygon.Index[IdxNext] );
////									
////									if ( VecA * -VecB.Tangent() >= Real::Zero ) {
////										Convex++;
////									}
////									else {
////										Convex--;
////									}
////								}
////								
////								// Debug Info //
//////								Log( 10, "*** Convex: " << Convex << " " << NewPolygon.Index.size() );
////								
////								// If they're equal, we're convex //
////								if ( Convex == (int)NewPolygon.Index.size() ) {
//////									Log( 10, "New Polygon is Convex!" );
////									
////									// Replace and delete the original two //
////									Obj.Polygon[PolyIdx] = NewPolygon;
////									Obj.Polygon.erase( Obj.Polygon.begin() + PolyIdx2 );
////
////									// An edge was found //
////									EdgeFound = true;
////									break;
////								}
////							}
////						}
////					}
////					// An edge was found //
////					if ( EdgeFound )
////						break;
////				}
////
////				// An edge was found, re-do this polygon //
////				if ( EdgeFound ) {
////					PolyIdx--;
////					break;
////				}
////			}			
////		}
////		
////		Log( 10, Obj.Polygon.size() << " polygons after optimization" );
////		Log( 10, "" );
////	}	
//	
//	
//	// Calculate bounding rectangles for all polygons // 	
////	for( size_t idx = 0; idx < StaticObject.size(); idx++ ) {
//		for ( size_t idx2 = 0; idx2 < Polygon.size(); idx2++ ) {
//			this->Polygon[idx2].CalcBoundingRect( Nodes );
//		}
//		CalcBoundingRect();
////	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
