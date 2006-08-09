// - ------------------------------------------------------------------------------------------ - //
// Zone //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Engine2D.h>

#include "Zone.h"
#include <Engine/DynamicObject/DynamicObjectComponent.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cZone::Action( cDynamicObjectComponent& _Vs ) {
	switch ( Id ) {
		// Camera Boundary //
		case 1: {
			
		}

		// Level Boundary //
		case 2: {
			
		}
		
		// ??? //
		case 3: {
			if ( _Vs.Body.Sphere.size() ) {
				// Uhh //	
			}
		}
	};
}
// - ------------------------------------------------------------------------------------------ - //
bool cZone::InitZone( ) {
	switch ( Id ) {
		// Camera Boundary //
		case 1: {
//			cEngine2D::Current->Camera->CameraBounds = BoundingRect.ToPairRect();
//
//			Log( 10, "New Camera Bounds: (" <<
//				cEngine2D::Current->Camera->CameraBounds.P1().x << ", " <<
//				cEngine2D::Current->Camera->CameraBounds.P1().y << ") -> (" <<
//				cEngine2D::Current->Camera->CameraBounds.P2().x << ", " <<
//				cEngine2D::Current->Camera->CameraBounds.P2().y << ")" );
		}

		// Level Boundary //
		case 2: {
			//cEngine2D::Current->Camera->LevelBounds = BoundingRect;			
		}
		
		default: {
			return false;
		}
	};
	
	// Remove self //
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
