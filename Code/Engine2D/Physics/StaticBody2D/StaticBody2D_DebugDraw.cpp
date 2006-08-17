// - ------------------------------------------------------------------------------------------ - //
// Displayed Debug Information //
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/StaticBody2D.h>

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawNode( const size_t Index, const bool Selected ) const {
	const Vector2D& MyNode = Nodes.Pos( Index );

	// Draw a circle for our node //
	Gfx::Circle(
		MyNode,
		Selected ? Gfx::RGBA(192, 192, 192, 192) : Gfx::RGBA(128, 128, 128, 128),
		Real( 2 )
		);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawBoundingRect( const bool Selected ) const {
	Gfx::Rect(
		BoundingRect.ToRect(),
		Selected ? Gfx::RGBA(128, 128, 255, 192) : Gfx::RGBA(64, 64, 192, 128)
		);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
