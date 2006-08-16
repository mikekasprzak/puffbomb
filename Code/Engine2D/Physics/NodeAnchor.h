// - ------------------------------------------------------------------------------------------ - //
// NodeAnchor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_NodeAnchor_H__
#define __Engine2D_Physics_NodeAnchor_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <Engine/DynamicObjectCollection/DynamicObject.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cNodeAnchor {
public:
	// Where to pull the anchored point towards //
	Vector2D Pos;	

	// How well to solve the spring.  1.0 is a normal stiff spring.  Less than .5 gets gooey. //
	Real Strength;
	// When to detach the spring (if enabled) //
	Real BreakPoint;


	// Object number and Index numbers used //
	unsigned int Object, Index;
		
public:
	void Step( std::vector< cDynamicObject >& Component ) {
		Vector2D& Point = Component[ Object ].Body.Nodes.Pos( Index );
		
		// Do spring thing //
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_NodeAnchor_H__ //
// - ------------------------------------------------------------------------------------------ - //
