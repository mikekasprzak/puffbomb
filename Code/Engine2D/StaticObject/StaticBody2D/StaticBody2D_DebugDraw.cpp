// - ------------------------------------------------------------------------------------------ - //
// Displayed Debug Information //
// - ------------------------------------------------------------------------------------------ - //
#include "StaticBody2D.h"

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawThickEdge( const size_t Index, const Vector3D& Offset) const {
	const cStaticEdge& MyEdge = Edge[ Index ];
	const Vector3D& PointA = (Nodes.Pos( MyEdge.a )).ToVector3D() + Offset;
	const Vector3D& PointB = (Nodes.Pos( MyEdge.b )).ToVector3D() + Offset;

	// Draw the Edge //
	Gfx::Line(
		PointA, PointB,
		Gfx::RGBA(255, 255, 255, 255)
		);
}
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawNode( const size_t Index, const Vector2D& Offset, const bool Selected ) const {
	const Vector2D& MyNode = Nodes.Pos( Index );

	// Draw a circle for our node //
	Gfx::Circle(
		MyNode + Offset,
		Selected ? Gfx::RGBA(192, 192, 192, 192) : Gfx::RGBA(128, 128, 128, 128),
		Real( 2 )
		);
}
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawEdge( const size_t Index, const Vector2D& Offset, const bool Selected ) const {
	const cStaticEdge& MyEdge = Edge[ Index ];
	const Vector2D& PointA = Nodes.Pos( MyEdge.a );
	const Vector2D& PointB = Nodes.Pos( MyEdge.b );

	// Draw the Edge //
	Gfx::Line(
		PointA + Offset, PointB + Offset,
		Selected ? Gfx::RGBA(255, 255, 64, 255) : Gfx::RGBA(255, 255, 0, 192)
		);
	
	// Draw the Edge Normal //
	{
		// Calculate the center of the line //
		Vector2D Center = PointA + ( MyEdge.DirectionalNormal() * MyEdge.Length * Real::Half );
		
		// Draw the Normal //
		Gfx::Line(
			Center + Offset,
			Center + Offset + (MyEdge.SurfaceNormal() * Real( 10 )),
			Selected ? Gfx::RGBA(255, 255, 255, 192) : Gfx::RGBA(255, 255, 255, 128)
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawPolygon( const size_t Index, const Vector2D& Offset, const bool Selected ) const {
	const cStaticPolygon& MyPolygon = Polygon[ Index ];

	// Draw the Edges of the Polygon //
	{
		Vector2D DrawMeA, DrawMeB, DrawMeC;
		int NodesLeft = MyPolygon.Index.size();
		int CurrentIndex = 0;
		
		// Determine the color to draw the edges in //
		Gfx::Color PolyColor =
			Selected ? Gfx::RGBA(255, 128, 0, 192) : Gfx::RGBA(192, 64, 0, 128);
		
		// Step in two's //
		for( ; NodesLeft > 2; NodesLeft -= 2 ) {
			// Get the positions //
			DrawMeA = Nodes.Pos( MyPolygon.Index[ CurrentIndex + 0 ] ) + Offset;
			DrawMeB = Nodes.Pos( MyPolygon.Index[ CurrentIndex + 1 ] ) + Offset;	
			DrawMeC = Nodes.Pos( MyPolygon.Index[ CurrentIndex + 2 ] ) + Offset;

			// Draw a pair of lines //
			Gfx::Line( DrawMeA, DrawMeB, PolyColor );
			Gfx::Line( DrawMeB, DrawMeC, PolyColor );
	
			// Advance to the next set //
			CurrentIndex += 2;
		}
			
		// Do linkage to front differently, depending on how many nodes are left //
		if ( NodesLeft == 2 ) {
			// Two left, Get the positions //
			DrawMeA = Nodes.Pos( MyPolygon.Index[ CurrentIndex + 0 ] ) + Offset;
			DrawMeB = Nodes.Pos( MyPolygon.Index[ CurrentIndex + 1 ] ) + Offset;	
			DrawMeC = Nodes.Pos( MyPolygon.Index[ 0 ] ) + Offset;
	
			// Draw the last pair of lines //
			Gfx::Line( DrawMeA, DrawMeB, PolyColor );
			Gfx::Line( DrawMeB, DrawMeC, PolyColor );
		}
		else {
			// One left, Get the positions //
			DrawMeA = Nodes.Pos( MyPolygon.Index[ CurrentIndex + 0 ] ) + Offset;
			DrawMeB = Nodes.Pos( MyPolygon.Index[ 0 ] ) + Offset;	
	
			// Draw the last line //
			Gfx::Line( DrawMeA, DrawMeB, PolyColor );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawEdgeRect( const size_t Index, const Vector2D& Offset, const bool Selected ) const {
	const cStaticEdge& MyEdge = Edge[ Index ];
	
	// Draw surrounding Rectangle //
	Gfx::Rect(
		MyEdge.BoundingRect.ToRect() + Offset,
		Selected ? Gfx::RGBA(128, 128, 255, 192) : Gfx::RGBA(64, 64, 192, 128)
		);
}
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawPolygonRect( const size_t Index, const Vector2D& Offset, const bool Selected ) const {
	const cStaticPolygon& MyPolygon = Polygon[ Index ];

	// Draw surrounding Rectangle //
	Gfx::Rect(
		MyPolygon.BoundingRect.ToRect() + Offset,
		Selected ? Gfx::RGBA(128, 128, 255, 192) : Gfx::RGBA(64, 64, 192, 128)
		);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawNodes( const std::vector< size_t >& SelectionVector, const Vector2D& Offset ) const {
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
		DrawNode( idx, Offset, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawEdges( const std::vector< size_t >& SelectionVector, const Vector2D& Offset ) const {
	// For every node //
	for ( size_t idx = 0; idx < Edge.size(); idx++ ) {
		bool Selected = false;
		
		// Search for this index on the selection list //
		for ( size_t idx2 = 0; idx2 < SelectionVector.size(); idx2++ ) {
			if ( SelectionVector[ idx2 ] == idx ) {
				Selected = true;
				break;
			}
		}
		
		// Draw our node //
		DrawEdge( idx, Offset, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawPolygons( const std::vector< size_t >& SelectionVector, const Vector2D& Offset ) const {
	// For every node //
	for ( size_t idx = 0; idx < Polygon.size(); idx++ ) {
		bool Selected = false;
		
		// Search for this index on the selection list //
		for ( size_t idx2 = 0; idx2 < SelectionVector.size(); idx2++ ) {
			if ( SelectionVector[ idx2 ] == idx ) {
				Selected = true;
				break;
			}
		}
		
		// Draw our node //
		DrawPolygon( idx, Offset, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawEdgeRects( const std::vector< size_t >& SelectionVector, const Vector2D& Offset ) const {
	// For every node //
	for ( size_t idx = 0; idx < Edge.size(); idx++ ) {
		bool Selected = false;
		
		// Search for this index on the selection list //
		for ( size_t idx2 = 0; idx2 < SelectionVector.size(); idx2++ ) {
			if ( SelectionVector[ idx2 ] == idx ) {
				Selected = true;
				break;
			}
		}
		
		// Draw our node //
		DrawEdgeRect( idx, Offset, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawPolygonRects( const std::vector< size_t >& SelectionVector, const Vector2D& Offset ) const {
	// For every node //
	for ( size_t idx = 0; idx < Polygon.size(); idx++ ) {
		bool Selected = false;
		
		// Search for this index on the selection list //
		for ( size_t idx2 = 0; idx2 < SelectionVector.size(); idx2++ ) {
			if ( SelectionVector[ idx2 ] == idx ) {
				Selected = true;
				break;
			}
		}
		
		// Draw our node //
		DrawPolygonRect( idx, Offset, Selected );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::DrawBoundingRect( const bool Selected, const Vector2D& Offset ) const {
	Gfx::Rect(
		BoundingRect.ToRect() + Offset,
		Selected ? Gfx::RGBA(128, 128, 255, 192) : Gfx::RGBA(64, 64, 192, 128)
		);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
