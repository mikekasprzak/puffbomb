// - ------------------------------------------------------------------------------------------ - //
#include "Physics.h"
#include "StaticObject.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
/*cStaticObject::cStaticObject( const cScriptParser& Obj, Real _x, Real _y ) :
	cStaticNodes( Obj.NodeCount ),
	Friction( cPhysics::SurfaceFriction )
{
	
	Log( 8, "Creating static object from instance \"" << Obj.Name << "\"" );
	
	// Load Mesh //
	int NodeIndex = -1;
	for ( size_t idx = 0; idx < Obj.Instruction.size(); idx++ ) {
		if ( Obj.Instruction[ idx ].Command == "Node" ) {
			NodeIndex++;

			Log( 8, "- Found Node " << NodeIndex );
			Pos( NodeIndex ).x = _x + Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
			Pos( NodeIndex ).y = _y + Real( atof( Obj.Instruction[ idx ].Arg[ 1 ].c_str() ) );

//				cNodes::Reset( NodeIndex );
							
			Log( 8, "  - X: " << Pos( NodeIndex ).x << " Y: " << Pos( NodeIndex ).y );
		}
		else {
			if ( NodeIndex == -1 ) {
				Log( 8, "Error: No initial node found when creating \"" << Obj.Instruction[ idx ].Command << "\"" );
			}
			else if ( Obj.Instruction[ idx ].Command == "Friction" ) {
				Log( 8, "- Found Friction" );
				
				Friction = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
			}
//				else if ( Obj.Instruction[ idx ].Command == "Sphere" ) {
//					Log( 8, "- Found Sphere " << Sphere.size() );
//					
//					Sphere.push_back( cSphere() );
//					Sphere.back().Index = NodeIndex;
//					Sphere.back().Radius = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
//				}
//				else if ( Obj.Instruction[ idx ].Command == "Hard" ) {
//					Log( 8, "- Found Hard " << Hard.size() );
//					
//					Hard.push_back( cHard() );
//					Hard.back().Index = NodeIndex;
//				}
			else if ( Obj.Instruction[ idx ].Command == "Quad" ) {
				Log( 8, "- Found Quad " << Quad.size() );

				Quad.push_back( cQuad() );
				Quad.back().IndexA = NodeIndex;
				Quad.back().IndexB = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				Quad.back().IndexC = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() );
				Quad.back().IndexD = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 2 ].c_str() );
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "Tri" ) {
				Log( 8, "- Found Triangle " << Triangle.size() );

				Triangle.push_back( cTriangle() );
				Triangle.back().IndexA = NodeIndex;
				Triangle.back().IndexB = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				Triangle.back().IndexC = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() );
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "Polygon" ) {
				Log( 8, "- Found Polygon " << Polygon.size() );

				Polygon.push_back( cPolygon() );
				Polygon.back().Index.push_back( NodeIndex );
				Polygon.back().Normal.push_back( Vector2D::Identity );
				Polygon.back().Flag.push_back( 1 );
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "AddToPolygon" ) {
				Log( 8, "- Add to Polygon " << Polygon.back().Index.size() );

				Polygon.back().Index.push_back( NodeIndex );
				Polygon.back().Normal.push_back( Vector2D::Identity );
				Polygon.back().Flag.push_back( 1 );
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "NextVertex" ) {
				Log( 8, "- Next " << Polygon.back().Index.size() );

				Polygon.back().Index.push_back( NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
				Polygon.back().Normal.push_back( Vector2D::Identity );
				Polygon.back().Flag.push_back( 1 );
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "NoCollision" ) {
				Log( 8, "- Next " << Polygon.back().Index.size() );

				Polygon.back().Flag.back() = 0;
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "Box" ) {
				Log( 8, "- Found Box " << Box.size() );

				Box.push_back( cBox() );
				Box.back().IndexA = NodeIndex;
				int IndexB = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				Box.back().IndexB = IndexB;
				Log( 8, "  - A: " << Box.back().IndexA << " B: " << Box.back().IndexB );
				
				// Error checking for offset ranges //
				if ( Box.back().IndexA == Box.back().IndexB ) {
					Log( 8, "Error: Offset argument should not be zero" );
				}
				else if ( IndexB < 0 ) {
					Log( 8, "Error: Offset outside range (" << Box.back().IndexB << "/" << size() << ")" );
				}
				else if ( Box.back().IndexB >= size() ) {
					Log( 8, "Error: Offset outside range (" << Box.back().IndexB << "/" << size() << ")" );
				}
			}
			else {
				Log( 8, "Error: Unknown Command \"" << Obj.Instruction[ idx ].Command << "\"" );
			}
		}
	}

	// Refresh Co-ordinates, Bounding Rectangles, Normals //
	Refresh();		
}
*/
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Should probably take a camera or camera matrix as an argument //
void cStaticObject::DebugDraw( /*const Vector2D& Offset*/ ) {
	if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
		// Draw the bounding Rectangle (First, so blank boxes show up first) //
		gfx::Rect( BoundingRect.ToRect(), gfx::RGB( 128, 128, 255 ) );
	}

/*
	
	if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
		// Draw Boxes //
		{
			for ( size_t idx = 0; idx < Box.size(); idx++ ) {
				gfx::Rect( Pos( Box[ idx ].IndexA ), Pos( Box[ idx ].IndexB ), gfx::RGB( 255, 255, 0 ) );
			}
		}
	}

	// Draw Triangles //
	{
		Vector2D DrawMeA, DrawMeB, DrawMeC;
		for ( size_t idx = 0; idx < Triangle.size(); idx++ ) {
			// Get the positions //
			DrawMeA = Pos( Triangle[ idx ].IndexA );
			DrawMeB = Pos( Triangle[ idx ].IndexB );	
			DrawMeC = Pos( Triangle[ idx ].IndexC );

			if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
				// Draw the root lines //
				gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 0, 128, 128 ) );
				gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 0, 160, 160 ) );
				gfx::Line( DrawMeC, DrawMeA, gfx::RGB( 0, 192, 192 ) );
			}

			if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
				// Calculate the offset to the center of each line //
				DrawMeA += (Pos( Triangle[ idx ].IndexB ) - Pos( Triangle[ idx ].IndexA )) * Real( 0.5 );
				DrawMeB += (Pos( Triangle[ idx ].IndexC ) - Pos( Triangle[ idx ].IndexB )) * Real( 0.5 );
				DrawMeC += (Pos( Triangle[ idx ].IndexA ) - Pos( Triangle[ idx ].IndexC )) * Real( 0.5 );

				// Draw the normals //
				gfx::Line(
					DrawMeA,
					(DrawMeA + (Triangle[ idx ].NormalA * Real( 16 ))),
					gfx::RGB( 128, 255, 255 ) );
	
				gfx::Line(
					DrawMeB,
					(DrawMeB + (Triangle[ idx ].NormalB * Real( 16 ))),
					gfx::RGB( 128, 255, 255 ) );
	
				gfx::Line(
					DrawMeC,
					(DrawMeC + (Triangle[ idx ].NormalC * Real( 16 ))),
					gfx::RGB( 128, 255, 255 ) );
			}
		}
	}
	

	// Draw Quads //
	{
		Vector2D DrawMeA, DrawMeB, DrawMeC, DrawMeD;
		for ( size_t idx = 0; idx < Quad.size(); idx++ ) {
			// Get the position //
			DrawMeA = Pos( Quad[ idx ].IndexA );
			DrawMeB = Pos( Quad[ idx ].IndexB );	
			DrawMeC = Pos( Quad[ idx ].IndexC );
			DrawMeD = Pos( Quad[ idx ].IndexD );
			
			if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
				// Draw the root lines //
				gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 128, 0, 128 ) );
				gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 160, 0, 160 ) );
				gfx::Line( DrawMeC, DrawMeD, gfx::RGB( 192, 0, 192 ) );
				gfx::Line( DrawMeD, DrawMeA, gfx::RGB( 224, 0, 224 ) );
			}

			if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
				// Calculate the offset to the center of each line //
				DrawMeA += (Pos( Quad[ idx ].IndexB ) - Pos( Quad[ idx ].IndexA )) * Real( 0.5 );
				DrawMeB += (Pos( Quad[ idx ].IndexC ) - Pos( Quad[ idx ].IndexB )) * Real( 0.5 );
				DrawMeC += (Pos( Quad[ idx ].IndexD ) - Pos( Quad[ idx ].IndexC )) * Real( 0.5 );
				DrawMeD += (Pos( Quad[ idx ].IndexA ) - Pos( Quad[ idx ].IndexD )) * Real( 0.5 );
	
				// Draw the Normals //
				gfx::Line(
					DrawMeA,
					(DrawMeA + (Quad[ idx ].NormalA * Real( 16 ))),
					gfx::RGB( 255, 128, 255 ) );
	
				gfx::Line(
					DrawMeB,
					(DrawMeB + (Quad[ idx ].NormalB * Real( 16 ))),
					gfx::RGB( 255, 128, 255 ) );
	
				gfx::Line(
					DrawMeC,
					(DrawMeC + (Quad[ idx ].NormalC * Real( 16 ))),
					gfx::RGB( 255, 128, 255 ) );
	
				gfx::Line(
					DrawMeD,
					(DrawMeD + (Quad[ idx ].NormalD * Real( 16 ))),
					gfx::RGB( 255, 128, 255 ) );
			}
		}
	}
*/

	// Draw Polygons //
	{
		Vector2D DrawMeA, DrawMeB, DrawMeC;
		for ( size_t idx = 0; idx < Polygon.size(); idx++ ) {
			if ( cGlobal::DebugDraw & cGlobal::flExtraInfo )
				gfx::Rect( Polygon[idx].BoundingRect.ToRect(), gfx::RGB( 0, 0, 128 ) );
			
			int NodesLeft = Polygon[ idx ].Index.size();
			int CurrentIndex = 0;
			
			// Step in two's //
			for( ; NodesLeft > 2; NodesLeft -= 2 ) {
				// Get the positions //
				DrawMeA = Pos( Polygon[ idx ].Index[ CurrentIndex + 0 ] );
				DrawMeB = Pos( Polygon[ idx ].Index[ CurrentIndex + 1 ] );	
				DrawMeC = Pos( Polygon[ idx ].Index[ CurrentIndex + 2 ] );

				if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
					// Draw the root lines. Use different color when collision should be ignored //
//					if ( Polygon[ idx ].Flag[ CurrentIndex + 0 ] )
						gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 255, 128, 0 ) );
//					else
//						gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 128, 0, 0 ) );
					
//					if ( Polygon[ idx ].Flag[ CurrentIndex + 1 ] )	
						gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 255, 128, 0 ) );
//					else
//						gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 128, 0, 0 ) );
				}

//				if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
//					// Calculate the offset to the center of each line (note, A is destroyed here) //
//					DrawMeA += (DrawMeB - DrawMeA) * Real( 0.5 );
//					DrawMeB += (DrawMeC - DrawMeB) * Real( 0.5 );
//						
//					// Draw the normals //
//					gfx::Line(
//						DrawMeA,
//						(DrawMeA + (Polygon[ idx ].Normal[ CurrentIndex + 0 ] * Real( 16 ))),
//						gfx::RGB( 255, 255, 0 ) );
//	
//					gfx::Line(
//						DrawMeB,
//						(DrawMeB + (Polygon[ idx ].Normal[ CurrentIndex + 1 ] * Real( 16 ))),
//						gfx::RGB( 255, 255, 0 ) );
//				}
				
				// Advance to the next set //
				CurrentIndex += 2;
			}
				
			// Do linkage to front differently, depending on how many nodes are left //
			if ( NodesLeft == 2 ) {
				// Get the positions //
				DrawMeA = Pos( Polygon[ idx ].Index[ CurrentIndex + 0 ] );
				DrawMeB = Pos( Polygon[ idx ].Index[ CurrentIndex + 1 ] );	
				DrawMeC = Pos( Polygon[ idx ].Index[ 0 ] );

				if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
					// Draw the root lines //
//					if ( Polygon[ idx ].Flag[ CurrentIndex + 0 ] )
						gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 255, 128, 0 ) );
//					else
//						gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 128, 0, 0 ) );
	
//					if ( Polygon[ idx ].Flag[ CurrentIndex + 1 ] )
						gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 255, 128, 0 ) );
//					else
//						gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 128, 0, 0 ) );
				}

//				if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
//					// Calculate the offset to the center of each line (note, A is destroyed here) //
//					DrawMeA += (DrawMeB - DrawMeA) * Real( 0.5 );
//					DrawMeB += (DrawMeC - DrawMeB) * Real( 0.5 );
//						
//					// Draw the normals //
//					gfx::Line(
//						DrawMeA,
//						(DrawMeA + (Polygon[ idx ].Normal[ CurrentIndex + 0 ] * Real( 16 ))),
//						gfx::RGB( 255, 255, 0 ) );
//	
//					gfx::Line(
//						DrawMeB,
//						(DrawMeB + (Polygon[ idx ].Normal[ CurrentIndex + 1 ] * Real( 16 ))),
//						gfx::RGB( 255, 255, 0 ) );
//				}
			}
			// One Node //
			else {
				// Get the positions //
				DrawMeA = Pos( Polygon[ idx ].Index[ CurrentIndex + 0 ] );
				DrawMeB = Pos( Polygon[ idx ].Index[ 0 ] );	

				if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
					// Draw the root lines //
//					if ( Polygon[ idx ].Flag[ CurrentIndex + 0 ] )
						gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 255, 128, 0 ) );
//					else
//						gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 128, 0, 0 ) );
				}

//				if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
//					// Calculate the offset to the center of each line (note, A is destroyed here) //
//					DrawMeA += (DrawMeB - DrawMeA) * Real( 0.5 );
//						
//					// Draw the normals //
//					gfx::Line(
//						DrawMeA,
//						(DrawMeA + (Polygon[ idx ].Normal[ CurrentIndex + 0 ] * Real( 16 ))),
//						gfx::RGB( 255, 255, 0 ) );					
//				}
			}
		}
	}

	// Draw Edges //
	for ( size_t idx = 0; idx < Edge.size(); idx++ ) {
		if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
			gfx::Line( 
				Pos( Edge[idx].a ),
				Pos( Edge[idx].b ),
				gfx::RGB( 255, 255, 0 ),
				gfx::RGB( 255, 255, 0 )
				);
		}

		if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
			if ( cGlobal::DebugDraw & cGlobal::flExtraInfo )
				gfx::Rect( Edge[idx].BoundingRect.ToRect(), gfx::RGB( 0, 0, 255 ) );

			Vector2D Center =
				Pos( Edge[idx].a ) + 
				( Edge[idx].DirectionalNormal() * Edge[idx].Length * Real::Half );

			gfx::Line( Center, Center + (Edge[idx].Normal * Real( 10 )), gfx::RGB( 255, 255, 255 ) );
		}
	}

	if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
		// Draw nodes last, so they should draw on top //
		{
			Vector2D DrawMe;
			for ( size_t idx = 0; idx < size(); idx++ ) {
				Gfx::Circle( Pos( idx ), 1, Gfx::RGBA( 255, 255, 255, 255 ) );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cStaticObject::CalcBoundingRect() {
	if ( size() == 0 )
		return;
	
	Vector2D MinPoint;
	Vector2D MaxPoint;
	
	// Some initial Value (first point) //
	MinPoint.x = Pos( 0 ).x;
	MinPoint.y = Pos( 0 ).y;

	MaxPoint = MinPoint;
	
	// For all points //
	for ( size_t idx = 1; idx < size(); idx++ ) {
		MinPoint.x = MinPoint.x.Min( Pos( idx ).x );
		MinPoint.y = MinPoint.y.Min( Pos( idx ).y );

		MaxPoint.x = MaxPoint.x.Max( Pos( idx ).x );
		MaxPoint.y = MaxPoint.y.Max( Pos( idx ).y );
	};
	
	// Set the Rectangle //
	BoundingRect = RectType::Pair( MinPoint, MaxPoint );
}	
// - ------------------------------------------------------------------------------------------ - //
void cStaticObject::Refresh() {
/*
	// Calculate all Normals //
	Log( 8, "- Calculate Normals..." );
	for ( size_t idx = 0; idx < Polygon.size(); idx++ ) {
		Polygon[ idx ].CalculateNormals( *this );
	}		

	for ( size_t idx = 0; idx < Quad.size(); idx++ ) {
		Quad[ idx ].CalculateNormals( *this );
	}		

	for ( size_t idx = 0; idx < Triangle.size(); idx++ ) {
		Triangle[ idx ].CalculateNormals( *this );
	}
	
	// Calculate the Bounding Rectangle around all shapes in this object //
	CalcBoundingRect();		
*/
}
// - ------------------------------------------------------------------------------------------ - //
