// - ------------------------------------------------------------------------------------------ - //
// Zone //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Graphics/Gfx.h>

#include <DynamicComponent/DynamicComponent.h>
#include <Engine2D.h>

#include "Zone.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cZone::Action( cDynamicComponent& _Vs ) {
	switch ( Id ) {
		// Camera Boundary //
		case 1: {
			
		}

		// Level Boundary //
		case 2: {
			
		}
		
		// ??? //
		case 3: {
			if ( _Vs.Body.Pose->Sphere.size() ) {
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

// - ------------------------------------------------------------------------------------------ - //
void cZone::DebugDraw() const {
	DrawBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cZone::DrawBoundingRect( const bool Selected ) const {
	// Draw rectangle //
	Gfx::Rect(
		BoundingRect.ToRect(),
		Selected ? Gfx::RGBA(255, 255, 64, 192) : Gfx::RGBA(192, 192, 0, 128)
		);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
