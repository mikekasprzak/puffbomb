// - ------------------------------------------------------------------------------------------ - //
// PassiveObject //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Engine/PassiveObject.h>
#include <DynamicComponent/DynamicComponent.h>

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cPassiveObject::Action( cDynamicComponent& _Vs ) {
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
void cPassiveObject::Work() {
}
// - ------------------------------------------------------------------------------------------ - //
void cPassiveObject::Draw() const {
	// Draw the animation //
}
// - ------------------------------------------------------------------------------------------ - //
void cPassiveObject::DebugDraw() const {
	// Draw a crosshair if point is inside //
	if ( BoundingRect == Pos ) {
		// Horizontal //
		Gfx::Line(
			Vector2D( Pos.x, BoundingRect.P1().y ),
			Vector2D( Pos.x, BoundingRect.P2().y ),
			Gfx::RGBA(255, 128, 64, 192)	
			);

		// Vertical //
		Gfx::Line(
			Vector2D( BoundingRect.P1().x, Pos.y ),
			Vector2D( BoundingRect.P2().x, Pos.y ),
			Gfx::RGBA(255, 128, 64, 192)	
			);
	}
	
	// Draw a circle at the point //
	Gfx::Circle(
		Pos,
		Real( 3 ),
		Gfx::RGBA(255, 255, 64, 192)
		);
	
	// Draw a bounding Rectangle around it //
	DrawBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cPassiveObject::DrawBoundingRect( const bool Selected ) const {
	// Draw rectangle //
	Gfx::Rect(
		BoundingRect.ToRect(),
		Selected ? Gfx::RGBA(255, 64, 64, 192) : Gfx::RGBA(192, 0, 0, 128)
		);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
