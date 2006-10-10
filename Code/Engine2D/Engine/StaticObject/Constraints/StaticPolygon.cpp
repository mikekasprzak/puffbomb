// - ------------------------------------------------------------------------------------------ - //
#include "StaticPolygon.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cStaticPolygon::CalcBoundingRect( const cStaticNodes& Node ) {
	// Bail if there are no entries in the Index List //
	if ( Index.empty() )
		return;
	
	Vector2D MinPoint;
	Vector2D MaxPoint;
	
	// Some initial Value (first point) //
	MinPoint = Node.Pos( Index[ 0 ] );
	MaxPoint = MinPoint;

	// For all indices //
	for ( size_t idx = 1; idx < Index.size(); idx++ ) {
		// Should work! //
		MinPoint.MinClamp( Node.Pos( Index[ idx ] ) );			
		MaxPoint.MaxClamp( Node.Pos( Index[ idx ] ) );
	}	

	// Set the Rectangle //
	BoundingRect = cPhysics::BoundingRectType::Pair( MinPoint, MaxPoint );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
