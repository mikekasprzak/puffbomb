// - ------------------------------------------------------------------------------------------ - //
// StaticBody2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_StaticBody2D_H__
#define __Engine2D_Physics_StaticBody2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Physics.h>

#include "StaticBody2D/StaticNodes.h"
#include "StaticBody2D/Constraints/StaticEdge.h"
#include "StaticBody2D/Constraints/StaticPolygon.h"
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
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_StaticBody2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
