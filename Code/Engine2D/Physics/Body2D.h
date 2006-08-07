// - ------------------------------------------------------------------------------------------ - //
// Body2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_H__
#define __Engine2D_Physics_Body2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>

#include <Physics/DynamicNodes.h>
#include <Physics/CollisionFlags.h>

#include <Physics/Constraints/Spring.h>
#include <Physics/Constraints/Sphere.h>
#include <Physics/Constraints/Anchor.h>
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
	
	
	// Flags //
	cCollisionFlags Collision;

public:	
	// Bounding Rectangle of all colliding objects //
	typedef RadiusRect2D RectType;
	RectType BoundingRect;

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
