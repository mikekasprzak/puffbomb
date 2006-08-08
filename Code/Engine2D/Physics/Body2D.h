// - ------------------------------------------------------------------------------------------ - //
// Body2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_H__
#define __Engine2D_Physics_Body2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>

#include "Body2D/DynamicNodes.h"
#include "Body2D/CollisionFlags.h"

#include "Body2D/Constraints/Spring.h"
#include "Body2D/Constraints/Sphere.h"
#include "Body2D/Constraints/Anchor.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cBody2D {
public:
	// Nodes //
	cDynamicNodes Nodes;
	
	// Constraints //
	std::vector< cSpring > Spring;
	std::vector< cSphere > Sphere;
	std::vector< cAnchor > Anchor;
		
//	std::vector< cCylinder > Cylinder;	// A ?
//	std::vector< cCapsule > Capsule;	// or B ?

//	std::vector< cTriangle > Triangle;	// A ?
//	std::vector< cQuad > Quad;			// or B ?
//	std::vector< cPolygon > Polygon;	// or C ?
	
	
	// Member collision monitoring flags //
	cCollisionFlags Collision;

public:	
	typedef RadiusRect2D RectType;
	
	// Bounding rectangle, for early out test //
	RectType BoundingRect;
	// Calculate the rectangle for the object //
	void CalcBoundingRect();
	// Given a Sphere that caused a change, grow the bounding rectangle //
	void GrowBoundingRectBySphere( const size_t _Index );

public:
	// Step the nodes in the body. //
	// Unlike cDynamicObject/Component, this is not a self sufficent physics system. //
	void Step();
	// Step the springs in the body. //
	void StepSprings();
	// Calculate the length of all springs (given their current positions) //
	void CalculateSpringLength();

public:	
	// Solve Collisions/Actions //
	void Solve( cBody2D& _Vs );
	void Solve( class cStaticBody2D& _Vs );
	void Solve( class cPassiveObject& _Vs );
	void Solve( class cZone& _Vs );
	void Solve( class cImpulse& _Vs );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
