// - ------------------------------------------------------------------------------------------ - //
// StaticBody2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_StaticBody2D_H__
#define __Engine2D_Physics_StaticBody2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Physics.h>

#include "StaticNodes.h"
#include "Constraints/StaticEdge.h"
#include "Constraints/StaticPolygon.h"

#include "../Mesh3D/Mesh3D.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticBody2D {
public:
	// Nodes //
	cStaticNodes Nodes;

	// Constraints //
	std::vector< cStaticEdge > Edge;
	std::vector< cStaticPolygon > Polygon;
	
public:	
	// Bounding rectangle, for early out test //
	cPhysics::BoundingRectType BoundingRect;
	// Calculate the rectangle for the object //
	void CalcBoundingRect();
	
public:
	// - -------------------------------------------------------------------------------------- - //
	cStaticBody2D() {
	}

	// - -------------------------------------------------------------------------------------- - //
	// Generate some 2D collision from a 3D mesh //
	void GenerateCollision( const std::vector< cMesh3D >& Mesh );
	
public:
	// - -------------------------------------------------------------------------------------- - //
	// Debug Drawing Functions //
	void DrawNode( const size_t Index, const bool Selected = false ) const;	
	void DrawEdge( const size_t Index, const bool Selected = false ) const;
	void DrawPolygon( const size_t Index, const bool Selected = false ) const;
	void DrawEdgeRect( const size_t Index, const bool Selected = false ) const;
	void DrawPolygonRect( const size_t Index, const bool Selected = false ) const;

	void DrawNodes( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawEdges( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawPolygons( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawEdgeRects( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawPolygonRects( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	
	void DrawBoundingRect( const bool Selected = false ) const;
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_StaticBody2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
