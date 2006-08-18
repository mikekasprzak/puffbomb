// - ------------------------------------------------------------------------------------------ - //
// Displayed Debug Information //
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/DynamicObjectCollection.h>

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectCollection::DrawComponent( const size_t Index, const bool Selected ) const {
	// Draw specific component //
	Component[ Index ].DrawBody( Selected );
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectCollection::DrawNodeLink( const size_t Index, const bool Selected ) const {
	const cNodeLink& MySpring = NodeLink[ Index ];
	const Vector2D& PointA = Component[ MySpring.ObjectA ].Body.Nodes.Pos( MySpring.IndexA );
	const Vector2D& PointB = Component[ MySpring.ObjectB ].Body.Nodes.Pos( MySpring.IndexB );
	
	if ( MySpring.Flags.IgnoreMinimum() ) {
		// Never gets too big //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(255, 192, 64, 192) : Gfx::RGBA(192, 128, 0, 128)
			);
	}
	else if ( MySpring.Flags.IgnoreMaximum() ) {
		// Never gets too small //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(255, 64, 192, 192) : Gfx::RGBA(192, 0, 128, 128)
			);
	}
	else if ( MySpring.Flags.Broken() ) {
		// Bail if broken spring distance exceeds threshold // 
		if ( (PointB - PointA).MagnitudeSquared() > (Real(256) * Real(256)) )
			return;
		
		// Spring Broke //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(128, 128, 128, 192) : Gfx::RGBA(96, 96, 96, 128)
			);		
	}
	else {
		// Normal spring //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(255, 64, 64, 192) : Gfx::RGBA(192, 0, 0, 128)
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectCollection::DrawNodeAnchor( const size_t Index, const bool Selected ) const {
	const cNodeAnchor& MySpring = NodeAnchor[ Index ];
	const Vector2D& PointA = Component[ MySpring.Object ].Body.Nodes.Pos( MySpring.Index );
	const Vector2D& PointB = MySpring.Pos;
	
	if ( MySpring.Flags.Broken() ) {
		// Bail if broken spring distance exceeds threshold // 
		if ( (PointB - PointA).MagnitudeSquared() > (Real(256) * Real(256)) )
			return;
		
		// Spring Broke //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(128, 128, 128, 192) : Gfx::RGBA(96, 96, 96, 128)
			);		
	}
	else {
		// Normal spring //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(255, 128, 64, 192) : Gfx::RGBA(192, 96, 0, 128)
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectCollection::DrawBoundingRect( const bool Selected ) const {
	
//	Gfx::Rect(
//		BoundingRect.ToRect(),
//		Selected ? Gfx::RGBA(128, 128, 255, 192) : Gfx::RGBA(64, 64, 192, 128)
//		);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
