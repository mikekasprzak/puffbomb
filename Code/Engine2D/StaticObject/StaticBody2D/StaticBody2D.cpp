// - ------------------------------------------------------------------------------------------ - //
#include "StaticBody2D.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cStaticBody2D::CalcBoundingRect() {    
	// If no nodes, bail (change to assert?) //
	if ( Nodes.Size() == 0 )
		return;

	Vector2D MinPoint;
	Vector2D MaxPoint;
	
	// Some initial Value (first sphere) //
	MinPoint = Nodes.Pos( 0 );
	MaxPoint = Nodes.Pos( 0 );
	
	// For all Nodes //
	int NodeCount = Nodes.Size();
	for ( int idx = 1; idx < NodeCount; idx++ ) {
		// Should work! //
		MinPoint.MinClamp( Nodes.Pos( idx ) );
		MaxPoint.MaxClamp( Nodes.Pos( idx ) );
	};
	
	// Set the Rectangle //
	BoundingRect = cPhysics::BoundingRectType::Pair( MinPoint, MaxPoint );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
