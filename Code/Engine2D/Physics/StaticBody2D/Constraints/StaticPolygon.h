// - ------------------------------------------------------------------------------------------ - //
// StaticPolygon //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_StaticBody2D_Constraints_StaticPolygon_H__
#define __Engine2D_Physics_StaticBody2D_Constraints_StaticPolygon_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Geometry/Rect.h>
#include "../StaticNodes.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticPolygon {
public:
	typedef RadiusRect2D RectType;
	RectType BoundingRect;

	// Index List.  A reference to verts in the object. //
	std::vector< size_t > Index;	
	
public:
	cStaticPolygon( ) {
	}

	cStaticPolygon( const size_t& _Count ) :
		Index( _Count )
	{
	}

public:
	inline void CalcBoundingRect( cStaticNodes& Node ) {
		// Bail if there are no entries in the Index List //
		if ( Index.empty() )
			return;
		
		Vector2D MinPoint;
		Vector2D MaxPoint;
		
		// Some initial Value (first point) //
		MinPoint = Node.Pos( Index[ 0 ] );
		MaxPoint = MinPoint;

		for ( size_t idx = 1; idx < Index.size(); idx++ ) {
			MinPoint.x = MinPoint.x.Min( Node.Pos( Index[ idx ] ).x );
			MinPoint.y = MinPoint.y.Min( Node.Pos( Index[ idx ] ).y );
			
			MaxPoint.x = MaxPoint.x.Max( Node.Pos( Index[ idx ] ).x );
			MaxPoint.y = MaxPoint.y.Max( Node.Pos( Index[ idx ] ).y );
		}
		
		// Set it //
		BoundingRect = RectType::Pair( MinPoint, MaxPoint );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_StaticBody2D_Constraints_StaticPolygon_H__ //
// - ------------------------------------------------------------------------------------------ - //
