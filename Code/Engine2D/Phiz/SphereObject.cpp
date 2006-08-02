// - ------------------------------------------------------------------------------------------ - //
#include "SphereObject.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Physics.h"
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <sstream>

using namespace std;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cSphereObject::cSphereObject( const cScriptParser& Obj, const Real _x, const Real _y, const Real Scalar ) :
	cDynamicNodes( Obj.NodeCount ),
	Control( 0 )
{
	Log( LOG_PHIZOBJECT_CREATE, "Creating SphereObject from Instance \"" << Obj.Name << "\"" );
	
	// The Total Quantity of Mass //
	TotalMass = 10.0f;
		
	// Load Mesh //
	int NodeIndex = -1;
	for ( size_t idx = 0; idx < Obj.Instruction.size(); idx++ ) {
		if ( Obj.Instruction[ idx ].Command == "TotalMass" ) {
			Log( LOG_PHIZOBJECT_INFO, "- Found Total Mass" );
			
			TotalMass = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) ) * Scalar;
		}
		else if ( Obj.Instruction[ idx ].Command == "Control" ) {
			Log( LOG_PHIZOBJECT_INFO, "- Found Control Suggestion" );

			Control = atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
		}			
		else if ( Obj.Instruction[ idx ].Command == "Inactive" ) {
			Log( LOG_PHIZOBJECT_INFO, "- SphereObject set to Inactive" );
			
			Flags.SetInactive();
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
			else if ( Obj.Instruction[ idx ].Command == "Sphere" ) {
				Log( LOG_PHIZOBJECT_INFO, "- Found Sphere " << Sphere.size() );
				
				Sphere.push_back( cSphere() );
				Sphere.back().Index = NodeIndex;
				Sphere.back().Radius = Real( atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ) ) * Scalar;
				//Sphere.back().InvMass = cPhysics::DefaultInvMass;
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
			else if ( Obj.Instruction[ idx ].Command == "ConstrainMinimum" ) {
				Spring.back().Flags = cSpring::flMinConstrain;
			}
			else if ( Obj.Instruction[ idx ].Command == "ConstrainMaximum" ) {
				Spring.back().Flags = cSpring::flMaxConstrain;
			}
			else {
				Log( LOG_PHIZOBJECT_INFO, "Error: Unknown Command \"" << Obj.Instruction[ idx ].Command << "\"" );
			}
		}
	}
	
	// Set all spring lengths.  This is done after as the positions are not all known durring. //
	Log( LOG_PHIZOBJECT_INFO, "- Adjust Spring lengths..." );
	CalculateSpringLength();
		
	// Calculate Mass //
	Real TotalMassWeight = Real::Zero;
	for ( size_t idx = 0; idx < size(); idx++ ) {
		TotalMassWeight += InvMass( idx );
	}

	for ( size_t idx = 0; idx < size(); idx++ ) {
		// InvMass currently stores the weight //
		Real CalcMass = InvMass( idx ) / TotalMassWeight;
		Mass[ idx ] = (CalcMass * TotalMass);
		InvMass( idx ) = (Real::One / (CalcMass * TotalMass));
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - -------------------------------------------------------------------------------------- - //
void cSphereObject::Step() {
	// Step physics for all nodes //
	cDynamicNodes::Step();

	if ( IsAwake() ) {
		// step physics for spring constraints //
		for ( size_t idx = 0; idx < Spring.size(); idx++ )
			Spring[ idx ].Step( *this );
	
		// Dampen Rotational Energy and Reset friction for Spheres //
		for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
			//AddForce( Sphere[ idx ].Index, Sphere[ idx ].RotationalEnergy* )
			//Sphere[ idx ].RotationalEnergy *= Real( 0.95 );
			
			SetFriction( idx, cPhysics::AirFriction );
		}
		
		// Hard Node Constrant //
		for ( size_t idx = 0; idx < Hard.size(); idx++ ) {
			if ( Hard[ idx ].Enabled ) {
				Pos( Hard[ idx ].Index ) = Hard[ idx ].Point;//HomePos( Hard[ idx ].Index );
				Old( Hard[ idx ].Index ) = Hard[ idx ].Point;//HomePos( Hard[ idx ].Index );
			}
		}

		// Finally, Calculate the rectangle around it //
		CalcBoundingRect();
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Should probably take a camera or camera matrix as an argument //
void cSphereObject::DebugDraw( /*const Vector2D& Offset*/ ) {

	if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
		// Draw the bounding Rectangle //
		gfx::Rect( BoundingRect.ToRect(), gfx::RGB( 128, 128, 128 ) );
		
		// Draw springs //
		{
			Vector2D DrawMeA, DrawMeB;
			int SpringCount = Spring.size();
			for ( int idx = 0; idx < SpringCount; idx++ ) {
				DrawMeA = Pos( Spring[ idx ].IndexA );
				DrawMeB = Pos( Spring[ idx ].IndexB );
				
				gfx::Line( DrawMeA, DrawMeB, gfx::RGB( 0, 255, 0 ) );
			};
		}
	}
	
	if ( cGlobal::DebugDraw & cGlobal::flCollision ) {
		// Draw Sphere's //
		{
			int SphereCount = Sphere.size();
			for ( int idx = 0; idx < SphereCount; idx++ ) {
				// The radius should be appropriately scaled based on Z... later //
				gfx::Circle( Pos( Sphere[ idx ].Index ), Sphere[ idx ].Radius, gfx::RGB( 255, 0, 0 ) );
			};
		}
	}

	if ( cGlobal::DebugDraw & cGlobal::flExtraInfo ) {
		// Draw nodes last, as their the lowest level of the heiarchy //
		{
			for ( size_t idx = 0; idx < size(); idx++ ) {
				gfx::Circle( Pos( idx ), 1, gfx::RGB( 255, 255, 255 ) );
			};
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::DebugDraw( int SpringColour, int SphereColour, Vector2D MapPos ) {

	CalcBoundingRect();

	// Draw the bounding Rectangle //
	Vector2D Point1 = BoundingRect.P1() + MapPos;
	Vector2D Point2 = BoundingRect.P2() + MapPos;
	
	gfx::Rect( Point1, Point2, gfx::RGB( 128, 128, 128 ) );
	
	// Draw springs //
	{
		Vector2D DrawMeA, DrawMeB;
		int SpringCount = Spring.size();
		for ( int idx = 0; idx < SpringCount; idx++ ) {
			DrawMeA = MapPos + Pos( Spring[ idx ].IndexA );
			DrawMeB = MapPos + Pos( Spring[ idx ].IndexB );
			
			gfx::Line( DrawMeA, DrawMeB, SpringColour );
		};
	}
	
	// Draw Sphere's //
	{
		int SphereCount = Sphere.size();
		for ( int idx = 0; idx < SphereCount; idx++ ) {
			// The radius should be appropriately scaled based on Z... later //
			gfx::Circle( MapPos + Pos( Sphere[ idx ].Index ), Sphere[ idx ].Radius, SphereColour );
		};
	}

/*	// Draw nodes last, as their the lowest level of the heiarchy //
	{
		for ( size_t idx = 0; idx < size(); idx++ ) {
			gfx::Circle( Pos( idx ), 1, gfx::RGB( 255, 255, 255 ) );
		};
	}
*/
}
// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::Reset() {
	for ( size_t idx = 0; idx < size(); idx++ ) {
		cDynamicNodes::Reset( idx );

		Pos( idx ) = HomePos( idx );
		Old( idx ) = HomeOld( idx );
	}
	
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::SetHome() {
	for ( size_t idx = 0; idx < size(); idx++ ) {
		cDynamicNodes::Reset( idx );

		HomePos( idx ) = Pos( idx );
		HomeOld( idx ) = Old( idx );
	}
	
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::CalcBoundingRect() {
	if ( Sphere.empty() )
		return;

	Vector2D MinPoint;
	Vector2D MaxPoint;
	
	// Some initial Value (first sphere) //
	MinPoint.x = Pos( Sphere[ 0 ].Index ).x - Sphere[ 0 ].Radius;
	MinPoint.y = Pos( Sphere[ 0 ].Index ).y - Sphere[ 0 ].Radius;

	MaxPoint.x = Pos( Sphere[ 0 ].Index ).x + Sphere[ 0 ].Radius;
	MaxPoint.y = Pos( Sphere[ 0 ].Index ).y + Sphere[ 0 ].Radius;
	
	// For all spheres //
	int SphereCount = Sphere.size();
	for ( int idx = 1; idx < SphereCount; idx++ ) {
		if ( MinPoint.x > (Pos( Sphere[ idx ].Index ).x - Sphere[ idx ].Radius) ) {
			MinPoint.x = Pos( Sphere[ idx ].Index ).x - Sphere[ idx ].Radius;
		}
		if ( MinPoint.y > (Pos( Sphere[ idx ].Index ).y - Sphere[ idx ].Radius) ) {
			MinPoint.y = Pos( Sphere[ idx ].Index ).y - Sphere[ idx ].Radius;
		}

		if ( MaxPoint.x < (Pos( Sphere[ idx ].Index ).x + Sphere[ idx ].Radius) ) {
			MaxPoint.x = Pos( Sphere[ idx ].Index ).x + Sphere[ idx ].Radius;
		}
		if ( MaxPoint.y < (Pos( Sphere[ idx ].Index ).y + Sphere[ idx ].Radius) ) {
			MaxPoint.y = Pos( Sphere[ idx ].Index ).y + Sphere[ idx ].Radius;
		}
	};
	
	// Set the Rectangle //
	BoundingRect = RectType::Pair( MinPoint, MaxPoint );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::CalculateSpringLength() {
	for ( size_t idx = 0; idx < Spring.size(); idx++ ) {
		Vector2D Diff = Pos( Spring[ idx ].IndexA ) - Pos( Spring[ idx ].IndexB );
		Spring[ idx ].Length = Diff.Magnitude();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cSphereObject::SaveFile( const char* File ) {
	cScriptParser Script;
	
	// Get Total Mass //
	Real TotalMass = Real::Zero;
	for( size_t idx = 0; idx < size(); idx++ ) {
		TotalMass += Mass[ idx ];
	}
	Script.Append( "TotalMass", TotalMass );
	
	// Generate all Instructions //
	for( size_t idx = 0; idx < size(); idx++ ) {
		Script.Append( "Node", HomePos( idx ).x, HomePos( idx ).y );
		Script.Append( "Weight", Mass[ idx ] );
			
		// Find my Spheres //
		for( size_t idx2 = 0; idx2 < Sphere.size(); idx2++ ) {
			if ( Sphere[ idx2 ].Index == idx ) {
				Script.Append( "Sphere", Sphere[ idx2 ].Radius );
			}			
		}
		
		// Find my Hard's //
		for( size_t idx2 = 0; idx2 < Hard.size(); idx2++ ) {
			if ( Hard[ idx2 ].Index == idx ) {
				Script.Append( "Hard" );
			}
		}
		
		// Find my springs //
		for( size_t idx2 = 0; idx2 < Spring.size(); idx2++ ) {
			// Ignore springs connecting to lesser numbered nodes //
			if ( Spring[ idx2 ].IndexA == idx ) {
				if ( Spring[ idx2 ].IndexB > idx ) {
					std::stringstream Text;
					Text << Spring[ idx2 ].IndexB - Spring[ idx2 ].IndexA;
					
					Script.Append( "Spring", Text.str(), Spring[ idx2 ].Strength );
				}
			}
			if ( Spring[ idx2 ].IndexB == idx ) {
				if ( Spring[ idx2 ].IndexA > idx ) {
					std::stringstream Text;
					Text << Spring[ idx2 ].IndexA - Spring[ idx2 ].IndexB;
					
					Script.Append( "Spring", Text.str(), Spring[ idx2 ].Strength );
				}
			}
			
		}
	}
		
	Script.SaveFile( File );
}
// - ------------------------------------------------------------------------------------------ - //
