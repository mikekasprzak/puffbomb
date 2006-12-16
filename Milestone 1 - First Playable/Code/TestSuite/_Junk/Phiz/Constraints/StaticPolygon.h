// - ------------------------------------------------------------------------------------------ - //
// StaticPolygon //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_StaticPolygon_H__
#define __Phiz_StaticPolygon_H__
// - ------------------------------------------------------------------------------------------ - //

#include <vector>

#include <Geometry/Rect.h>
#include "../StaticNodes.h"

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

//			// Minimum Point //
//			if ( MinPoint.x > Node.Pos( Index[ idx ] ).x ) {
//				MinPoint.x = Node.Pos( Index[ idx ] ).x;
//			}
//			if ( MinPoint.y > Node.Pos( Index[ idx ] ).y ) {
//				MinPoint.y = Node.Pos( Index[ idx ] ).y;
//			}
//	
//			// Maximum point //
//			if ( MaxPoint.x < Node.Pos( Index[ idx ] ).x ) {
//				MaxPoint.x = Node.Pos( Index[ idx ] ).x;
//			}
//			if ( MaxPoint.y < Node.Pos( Index[ idx ] ).y ) {
//				MaxPoint.y = Node.Pos( Index[ idx ] ).y;
//			}			
		}
		
		// Set it //
		BoundingRect = RectType::Pair( MinPoint, MaxPoint );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_StaticPolygon_H__ //
// - ------------------------------------------------------------------------------------------ - //
