// - ------------------------------------------------------------------------------------------ - //
// Displayed Debug Information //
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DrawNode( const size_t Index, const bool Selected ) const {
	const Vector2D& MyNode = Nodes.Pos( Index );
//	const Vector2D& MyNode = Pose->Node[Index].Pos;

	// Draw a circle for our node //
	Gfx::Circle(
		MyNode,
		Real( 3 ),
		Selected ? Gfx::RGBA(192, 192, 192, 192) : Gfx::RGBA(128, 128, 128, 192)
		);
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DrawSpring( const size_t Index, const bool Selected ) const {
	const cSpring& MySpring = Pose->Spring[ Index ];
	const Vector2D& PointA = Nodes.Pos( MySpring.IndexA );
	const Vector2D& PointB = Nodes.Pos( MySpring.IndexB );
	
	if ( MySpring.Flags.IgnoreMinimum() ) {
		// Never gets too big //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(148, 192, 64, 192) : Gfx::RGBA(96, 128, 0, 128)
			);
	}
	else if ( MySpring.Flags.IgnoreMaximum() ) {
		// Never gets too small //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(192, 148, 64, 192) : Gfx::RGBA(128, 96, 0, 128)
			);
	}
	else {
		// Normal spring //
		Gfx::Line(
			PointA, PointB,
			Selected ? Gfx::RGBA(64, 192, 64, 192) : Gfx::RGBA(0, 128, 0, 128)
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DrawSphere( const size_t Index, const bool Selected ) const {
	const cSphere& MySphere = Pose->Sphere[ Index ];
	const Vector2D& Pos = Nodes.Pos( MySphere.Index );

	if ( MySphere.Sensor ) {
		// A sphere acting as a sensor //
		Gfx::Circle(
			Pos,
			MySphere.Radius,
			Selected ? Gfx::RGBA(192, 192, 64, 255) : Gfx::RGBA(128, 128, 0, 192)
			);
	}
	else {
		// A normal sphere //
		Gfx::Circle(
			Pos,
			MySphere.Radius,
			Selected ? Gfx::RGBA(192, 96, 64, 255) : Gfx::RGBA(128, 32, 0, 192)
			);
	}	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DrawNodes( const std::vector< size_t >& SelectionVector ) const {
	// For every node //
	for ( size_t idx = 0; idx < Nodes.Size(); idx++ ) {
		bool Selected = false;
		
		// Search for this index on the selection list //
		for ( size_t idx2 = 0; idx2 < SelectionVector.size(); idx2++ ) {
			if ( SelectionVector[ idx2 ] == idx ) {
				Selected = true;
				break;
			}
		}
		
		// Draw our node //
		DrawNode( idx, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DrawSprings( const std::vector< size_t >& SelectionVector ) const {
	// Convert our pose parts in to something local //
	std::vector< cSpring >& Spring = Pose->Spring;

	// For every spring //
	for ( size_t idx = 0; idx < Spring.size(); idx++ ) {
		bool Selected = false;
		
		// Search for this index on the selection list //
		for ( size_t idx2 = 0; idx2 < SelectionVector.size(); idx2++ ) {
			if ( SelectionVector[ idx2 ] == idx ) {
				Selected = true;
				break;
			}
		}
		
		// Draw our spring //
		DrawSpring( idx, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DrawSpheres( const std::vector< size_t >& SelectionVector ) const {
	// Convert our pose parts in to something local //
	std::vector< cSphere >& Sphere = Pose->Sphere;

	// For every sphere //
	for ( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		bool Selected = false;
		
		// Search for this index on the selection list //
		for ( size_t idx2 = 0; idx2 < SelectionVector.size(); idx2++ ) {
			if ( SelectionVector[ idx2 ] == idx ) {
				Selected = true;
				break;
			}
		}
		
		// Draw our Sphere //
		DrawSphere( idx, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DrawBoundingRect( const bool Selected ) const {
	Gfx::Rect(
		BoundingRect.ToRect(),
		Selected ? Gfx::RGBA(128, 128, 255, 192) : Gfx::RGBA(64, 64, 192, 128)
		);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
