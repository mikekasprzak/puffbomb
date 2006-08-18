// - ------------------------------------------------------------------------------------------ - //
// StaticPolygon //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_StaticBody2D_Constraints_StaticPolygon_H__
#define __Engine2D_Physics_StaticBody2D_Constraints_StaticPolygon_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>

#include <Physics/Physics.h>

#include "../StaticNodes.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticPolygon {
public:
	// Index List.  A reference to verts in the object. //
	std::vector< size_t > Index;	

public:
	// Bounding rectangle, for early out test //
	cPhysics::BoundingRectType BoundingRect;
	// Calculate the rectangle for the object //
	void CalcBoundingRect( const cStaticNodes& Node );
	
public:
	cStaticPolygon( ) {
	}

	cStaticPolygon( const size_t& _Count ) :
		Index( _Count )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_StaticBody2D_Constraints_StaticPolygon_H__ //
// - ------------------------------------------------------------------------------------------ - //
