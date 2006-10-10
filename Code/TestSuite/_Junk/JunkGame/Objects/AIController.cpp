// - ------------------------------------------------------------------------------------------ - //
#include "AIController.h"

//#include <Util/Input.h>
#include <Input/Input.h>

#include <iostream>
using namespace std;

// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cAIController::cAIController( cSphereObject* _Object, const std::string& File ) :
	cObjectController( _Object, File )
{
	CurrentStrength = 1.0f;
	CollisionCount = 0;
}
// - ------------------------------------------------------------------------------------------ - //	
void cAIController::Step() {
	//SphereObject->AddForce( 0, input::Stick * 0.2f );

	// Do Rotation //
	for ( int idx = 0; idx < 16; idx++ )
	{

		if( SphereObject->Sphere[idx+1].Flags.Scenery() )
		{
			++CollisionCount;
		}
			
		SphereObject->AddForce(
			 + idx,
			(CurrentStrength * Real( 0.1 )) * 
				(SphereObject->Pos( 1 + idx ) - SphereObject->Pos( 0 )).Tangent().Normal()
			);
			
	}

	if( CollisionCount > 4 )
		CurrentStrength *= -1;
	
	CollisionCount = 0;

}	
// - ------------------------------------------------------------------------------------------ - //
