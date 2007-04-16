// - ------------------------------------------------------------------------------------------ - //
#include "PolyObject.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cPolyObject::cPolyObject( const cScriptParser& Obj, const Real _x, const Real _y ) :
	cDynamicNodes( Obj.NodeCount ),
	Flags( flActive ),
	Control( 0 )
{
	Log( LOG_PHIZOBJECT_CREATE, "Creating poly object from instance \"" << Obj.Name << "\"" );

	// The Total Quantity of Mass //
	Real TotalMass = 10.0f;
	
	Real Scalar = 1.0;
	
	// Load Mesh //
	int NodeIndex = -1;
	for ( size_t idx = 0; idx < Obj.Instruction.size(); idx++ ) {
		if ( Obj.Instruction[ idx ].Command == "TotalMass" ) {
			Log( LOG_PHIZOBJECT_INFO, "- Found Total Mass" );
			
			TotalMass = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
		}				
		else if ( Obj.Instruction[ idx ].Command == "Control" ) {
			Log( LOG_PHIZOBJECT_INFO, "- Found Control Suggestion " << Obj.Instruction[ idx ].Arg[ 0 ].c_str() );

			Control = atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
		}						
		else if ( Obj.Instruction[ idx ].Command == "Inactive" ) {
			Log( LOG_PHIZOBJECT_INFO, "- SphereObject set to Inactive" );
			
			Flags &= ~flActive;
		}				
		else if ( Obj.Instruction[ idx ].Command == "Node" ) {
			NodeIndex++;

			Log( LOG_PHIZOBJECT_INFO, "- Found Node " << NodeIndex );
			HomePos( NodeIndex ).x = _x + (Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) ) * Scalar);
			HomePos( NodeIndex ).y = _y + (Real( atof( Obj.Instruction[ idx ].Arg[ 1 ].c_str() ) ) * Scalar);

			Pos( NodeIndex ) = HomePos( NodeIndex );
			Old( NodeIndex ) = HomePos( NodeIndex );
			HomeOld( NodeIndex ) = Old( NodeIndex );

			// Give this node the default mass distribution weight of 1 //
			InvMass( NodeIndex ) = 1;
			Mass[ NodeIndex ] = 1;
			cDynamicNodes::Reset( NodeIndex );
							
			Log( LOG_PHIZOBJECT_INFO, "  - X: " << Pos( NodeIndex ).x << " Y: " << Pos( NodeIndex ).y );
		}
		else {
			if ( NodeIndex == -1 ) {
				Log( LOG_PHIZOBJECT_INFO, "Error: No initial node found when creating \"" << Obj.Instruction[ idx ].Command << "\"" );
			}
			else if ( Obj.Instruction[ idx ].Command == "Weight" ) {
				Log( LOG_PHIZOBJECT_INFO, "- Found Mass Weight" << NodeIndex );
				
				//Sphere.back().InvMass = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
				// Store it temporarily inside the Inverse Mass //
				InvMass( NodeIndex ) = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
			}
			else if ( Obj.Instruction[ idx ].Command == "Quad" ) {
				Log( LOG_PHIZOBJECT_INFO, "- Found Quad " << Quad.size() );

				Quad.push_back( cQuad() );
				Quad.back().IndexA = NodeIndex;
				Quad.back().IndexB = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				Quad.back().IndexC = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() );
				Quad.back().IndexD = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 2 ].c_str() );
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "Tri" ) {
				Log( LOG_PHIZOBJECT_INFO, "- Found Triangle " << Triangle.size() );

				Triangle.push_back( cTriangle() );
				Triangle.back().IndexA = NodeIndex;
				Triangle.back().IndexB = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				Triangle.back().IndexC = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() );
				
				// Error Checking //
			}
			else if ( Obj.Instruction[ idx ].Command == "Weight" ) {
				Log( LOG_PHIZOBJECT_INFO, "- Found Mass Weight" << NodeIndex );
				
				//Sphere.back().InvMass = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
				// Store it temporarily inside the Inverse Mass //
				InvMass( NodeIndex ) = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) );
				Mass[ NodeIndex ] = InvMass( NodeIndex );
			}
			else if ( Obj.Instruction[ idx ].Command == "Hard" ) {
				Log( LOG_PHIZOBJECT_INFO, "- Found Hard " << Hard.size() );
				
				Hard.push_back( cHard() );
				Hard.back().Index = NodeIndex;
				Hard.back().Enabled = true;
				Hard.back().Point = HomePos( NodeIndex );
				
				// If an argument "true" is passed, then lock the node //
				if ( Obj.Instruction[ idx ].Arg[ 0 ] == "false" )
					Hard.back().Unlock();
			}
			else if ( Obj.Instruction[ idx ].Command == "Spring" ) {
				Log( LOG_PHIZOBJECT_INFO, "- Found Spring " << Spring.size() );
				
				Spring.push_back( cSpring() );
				Spring.back().IndexA = NodeIndex;
				int IndexB = NodeIndex + atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				Spring.back().IndexB = IndexB;
				
				if ( Obj.Instruction[ idx ].Arg[ 1 ] != "" ) {
					Spring.back().Strength = atof( Obj.Instruction[ idx ].Arg[ 1 ].c_str() );
				}
				else {
					Spring.back().Strength = Real::One;
				}
				
				Log( LOG_PHIZOBJECT_INFO, "  - A: " << Spring.back().IndexA << " B: " << Spring.back().IndexB );
				
				// Error checking for offset ranges //
				if ( Spring.back().IndexA == Spring.back().IndexB ) {
					Log( LOG_PHIZOBJECT_INFO, "Error: Offset argument should not be zero" );
				}
				else if ( IndexB < 0 ) {
					Log( LOG_PHIZOBJECT_INFO, "Error: Offset outside range (" << Spring.back().IndexB << "/" << size() << ")" );
				}
				else if ( Spring.back().IndexB >= size() ) {
					Log( LOG_PHIZOBJECT_INFO, "Error: Offset outside range (" << Spring.back().IndexB << "/" << size() << ")" );
				}
				
			}
			else {
				Log( LOG_PHIZOBJECT_INFO, "Error: Unknown Command \"" << Obj.Instruction[ idx ].Command << "\"" );
			}
		}
	}
	
	// Connect all springs.  This is done after as the positions are not all known durring. //
	Log( LOG_PHIZOBJECT_INFO, "- Connecting Springs..." );
	for ( size_t idx = 0; idx < Spring.size(); idx++ ) {
//			Log( LOG_PHIZOBJECT_INFO, "X: " << Pos( Spring[ idx ].IndexA ).x << " Y: " << Pos( Spring[ idx ].IndexA ).y );
//			Log( LOG_PHIZOBJECT_INFO, "X: " << Pos( Spring[ idx ].IndexB ).x << " Y: " << Pos( Spring[ idx ].IndexB ).y );
		
		Vector2D Diff = Pos( Spring[ idx ].IndexA ) - Pos( Spring[ idx ].IndexB );
//			Log( LOG_PHIZOBJECT_INFO, "X: " << Diff.x << " Y: " << Diff.y );
		
		Spring[ idx ].Length = Diff.Magnitude();
		Log( LOG_PHIZOBJECT_INFO, 
			"  - " << idx <<
			" A: " << Spring[ idx ].IndexA <<
			" B: " << Spring[ idx ].IndexB <<
			" Length: " << Spring[ idx ].Length
			);
	}

	// Calculate Mass //
	Real TotalMassWeight = Real::Zero;
	for ( size_t idx = 0; idx < size(); idx++ ) {
		TotalMassWeight += InvMass( idx );
	}

	for ( size_t idx = 0; idx < size(); idx++ ) {
		// InvMass currently stores the weight //
		Real CalcMass = InvMass( idx ) / TotalMassWeight;			
		InvMass( idx ) = (Real::One / (CalcMass * TotalMass));
	}


	// Calculate Normals of the Shape //	
	CalcNormals();
	// Calculate the Bounding Rectangle around all shapes in this object //
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::Step() {
	// Step physics for nodes.  It's a self contained object, so //
	cDynamicNodes::Step();
	
	// step physics for spring constraints //
	for ( size_t idx = 0; idx < Spring.size(); idx++ )
		Spring[ idx ].Step( *this );
	
	// step physics for Spheres (set friction) //
	for ( size_t idx = 0; idx < size(); idx++ )
		SetFriction( idx, cPhysics::AirFriction );
	
	// Hard Node Constrant //
	for ( size_t idx = 0; idx < Hard.size(); idx++ ) {
		if ( Hard[ idx ].Enabled ) {
			Pos( Hard[ idx ].Index ) = Hard[ idx ].Point;//HomePos( Hard[ idx ].Index );
			Old( Hard[ idx ].Index ) = Hard[ idx ].Point;//HomePos( Hard[ idx ].Index );
		}
	}

	// Finally, Calculate the rectangle around it //
	CalcNormals();
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::DebugDraw( /*const Vector2D& Offset*/ ) {
	if ( Global::DebugDraw & Global::flExtraInfo ) {
		// Draw the bounding Rectangle //
		Gfx::Rect( BoundingRect.ToRect(), Gfx::RGB( 128, 128, 128 ) );
		
		// Draw springs //
		{
			Vector2D DrawMeA, DrawMeB;
			int SpringCount = Spring.size();
			for ( int idx = 0; idx < SpringCount; idx++ ) {
				DrawMeA = Pos( Spring[ idx ].IndexA );
				DrawMeB = Pos( Spring[ idx ].IndexB );
				
				Gfx::Line( DrawMeA, DrawMeB, Gfx::RGB( 0, 255, 0 ) );
			};
		}
	}

	// Draw Triangles //
	if ( Global::DebugDraw & Global::flCollision ) {
		Vector2D DrawMeA, DrawMeB, DrawMeC;
		for ( size_t idx = 0; idx < Triangle.size(); idx++ ) {
			// Positions of Normals //
			DrawMeA = Pos( Triangle[ idx ].IndexA );
			DrawMeB = Pos( Triangle[ idx ].IndexB );
			DrawMeC = Pos( Triangle[ idx ].IndexC );
			
			// Draw Triangle Lines //
//			gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 128, 0, 128 ) );
//			gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 160, 0, 160 ) );
//			gfx::Line( DrawMeC, DrawMeA, gfx::RGB( 192, 0, 192 ) );

			// Calculate line centers, to place normals //
			DrawMeA += (Pos( Triangle[ idx ].IndexB ) - Pos( Triangle[ idx ].IndexA )) * Real::Half;
			DrawMeB += (Pos( Triangle[ idx ].IndexC ) - Pos( Triangle[ idx ].IndexB )) * Real::Half;
			DrawMeC += (Pos( Triangle[ idx ].IndexA ) - Pos( Triangle[ idx ].IndexC )) * Real::Half;
				
			// Draw Triangle Normals //
			Gfx::Line(
				DrawMeA,
				DrawMeA + (Triangle[ idx ].NormalA * Real( 16 )),
				Gfx::RGB( 255, 128, 255 ) );

			Gfx::Line(
				DrawMeB,
				DrawMeB + (Triangle[ idx ].NormalB * Real( 16 )),
				Gfx::RGB( 255, 128, 255 ) );

			Gfx::Line(
				DrawMeC,
				DrawMeC + (Triangle[ idx ].NormalC * Real( 16 )),
				Gfx::RGB( 255, 128, 255 ) );
		};
	}
	

	// Draw Quads //
	if ( Global::DebugDraw & Global::flCollision ) {
		Vector2D DrawMeA, DrawMeB, DrawMeC, DrawMeD;
		for ( size_t idx = 0; idx < Quad.size(); idx++ ) {
			// Positions of Normals //
			DrawMeA = Pos( Quad[ idx ].IndexA );
			DrawMeB = Pos( Quad[ idx ].IndexB );
			DrawMeC = Pos( Quad[ idx ].IndexC );
			DrawMeD = Pos( Quad[ idx ].IndexD );

			// Draw Quad Lines //
//			gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 128, 0, 128 ) );
//			gfx::Line( DrawMeB, DrawMeC, gfx::RGB( 160, 0, 160 ) );
//			gfx::Line( DrawMeC, DrawMeD, gfx::RGB( 192, 0, 192 ) );
//			gfx::Line( DrawMeD, DrawMeA, gfx::RGB( 224, 0, 224 ) );

			// Calculate line centers, to place normals //
			DrawMeA += (Pos( Quad[ idx ].IndexB ) - Pos( Quad[ idx ].IndexA )) * Real::Half;
			DrawMeB += (Pos( Quad[ idx ].IndexC ) - Pos( Quad[ idx ].IndexB )) * Real::Half;
			DrawMeC += (Pos( Quad[ idx ].IndexD ) - Pos( Quad[ idx ].IndexC )) * Real::Half;
			DrawMeD += (Pos( Quad[ idx ].IndexA ) - Pos( Quad[ idx ].IndexD )) * Real::Half;

			// Draw Quad Normals //
			Gfx::Line(
				DrawMeA,
				DrawMeA + (Quad[ idx ].NormalA * Real( 16 )),
				Gfx::RGB( 255, 128, 255 ) );

			Gfx::Line(
				DrawMeB,
				DrawMeB + (Quad[ idx ].NormalB * Real( 16 )),
				Gfx::RGB( 255, 128, 255 ) );

			Gfx::Line(
				DrawMeC,
				DrawMeC + (Quad[ idx ].NormalC * Real( 16 )),
				Gfx::RGB( 255, 128, 255 ) );

			Gfx::Line(
				DrawMeD,
				DrawMeD + (Quad[ idx ].NormalD * Real( 16 )),
				Gfx::RGB( 255, 128, 255 ) );
		};
	}

	// Draw nodes last, as their the lowest level of the heiarchy //
	if ( Global::DebugDraw & Global::flExtraInfo ) {
		Vector2D DrawMe;
		for ( size_t idx = 0; idx < size(); idx++ ) {
			Gfx::Circle( Pos( idx ), 1, Gfx::RGBA( 255, 255, 255, 255 ) );
		};
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::Reset() {
	for ( size_t idx = 0; idx < size(); idx++ ) {
		cDynamicNodes::Reset( idx );

		Pos( idx ) = HomePos( idx );
		Old( idx ) = HomeOld( idx );
	}
	
	CalcNormals();
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::SetHome() {
	for ( size_t idx = 0; idx < size(); idx++ ) {
		cDynamicNodes::Reset( idx );

		HomePos( idx ) = Pos( idx );
		HomeOld( idx ) = Old( idx );
	}
	
	CalcNormals();
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::CalcBoundingRect() {
	Vector2D MinPoint;
	Vector2D MaxPoint;
	
	// Some initial Value (first sphere) //
	MinPoint.x = Pos( 0 ).x;
	MinPoint.y = Pos( 0 ).y;

	MaxPoint = MinPoint;
	
	// For all spheres //
	for ( size_t idx = 1; idx < size(); idx++ ) {
		if ( MinPoint.x > (Pos( idx ).x) ) {
			MinPoint.x = Pos( idx ).x;
		}
		if ( MinPoint.y > (Pos( idx ).y) ) {
			MinPoint.y = Pos( idx ).y;
		}

		if ( MaxPoint.x < (Pos( idx ).x) ) {
			MaxPoint.x = Pos( idx ).x;
		}
		if ( MaxPoint.y < (Pos( idx ).y) ) {
			MaxPoint.y = Pos( idx ).y;
		}
	};
	
	// Set the Rectangle //
	BoundingRect = RectType::Pair( MinPoint, MaxPoint );
}
// - ------------------------------------------------------------------------------------------ - //
void cPolyObject::CalcNormals() {
	// Calculate all Normals //
	for ( size_t idx = 0; idx < Quad.size(); idx++ ) {
		Quad[ idx ].CalculateNormals( *this );
	}		

	for ( size_t idx = 0; idx < Triangle.size(); idx++ ) {
		Triangle[ idx ].CalculateNormals( *this );
	}
}
// - ------------------------------------------------------------------------------------------ - //
