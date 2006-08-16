// - ------------------------------------------------------------------------------------------ - //
// NodeLink //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_NodeLink_H__
#define __Engine2D_Physics_NodeLink_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>

#include <Engine/DynamicObjectCollection/DynamicObject.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cNodeLink {
public:
	// Length of the Spring //
	Real Length;	
	// How well to solve the spring.  1.0 is a normal stiff spring.  Less than .5 gets gooey. //
	Real Strength;
	// When to detach the spring (if enabled) //
	Real BreakPoint;


	// Object number and Index numbers used //
	unsigned int ObjectA, IndexA;
	unsigned int ObjectB, IndexB;
	
public:
	void Step( std::vector< cDynamicObject >& Component ) {
		Vector2D& PointA = Component[ ObjectA ].Body.Nodes.Pos( IndexA );
		Vector2D& PointB = Component[ ObjectB ].Body.Nodes.Pos( IndexB );
		
		// Do spring thing //
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_NodeLink_H__ //
// - ------------------------------------------------------------------------------------------ - //
