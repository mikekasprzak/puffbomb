// - ------------------------------------------------------------------------------------------ - //
#include "Body2D.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::Step() {
	// Clear Collision Flags //
	CollisionFlags.Clear();
	for ( size_t idx = 0; idx < SphereFlags.size(); idx++ ) {
		SphereFlags[ idx ].Clear();
	}
	
	// Step each Node //
	Nodes.Step();
	
	// Calculate Bounding Rectange //
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::StepSprings() {
	// Convert our pose parts in to something local //
	std::vector< cSpring >& Spring = Pose->Spring;
	
	// Solve all springs in the component //
	for ( size_t idx = 0; idx < Spring.size(); idx++ ) {
		Spring[ idx ].Step( Nodes );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::CalcBoundingRect() {
	// Convert our pose parts in to something local //
	std::vector< cSphere >& Sphere = Pose->Sphere;
	
	// If no nodes, bail (change to assert?) //
	if ( Sphere.empty() )
		return;

	Vector2D MinPoint;
	Vector2D MaxPoint;
	
	// Some initial Value (first sphere) //
	MinPoint.x = Nodes.Pos( Sphere[ 0 ].Index ).x - Sphere[ 0 ].Radius;
	MinPoint.y = Nodes.Pos( Sphere[ 0 ].Index ).y - Sphere[ 0 ].Radius;

	MaxPoint.x = Nodes.Pos( Sphere[ 0 ].Index ).x + Sphere[ 0 ].Radius;
	MaxPoint.y = Nodes.Pos( Sphere[ 0 ].Index ).y + Sphere[ 0 ].Radius;
	
	// For all spheres //
	int SphereCount = Sphere.size();
	for ( int idx = 1; idx < SphereCount; idx++ ) {
		// Should work! //
		MinPoint.MinClamp( (Nodes.Pos( Sphere[ idx ].Index ) - Sphere[ idx ].Radius) );
		MaxPoint.MaxClamp( (Nodes.Pos( Sphere[ idx ].Index ) + Sphere[ idx ].Radius) );
		
//		if ( MinPoint.x > (Pos( Sphere[ idx ].Index ).x - Sphere[ idx ].Radius) ) {
//			MinPoint.x = Pos( Sphere[ idx ].Index ).x - Sphere[ idx ].Radius;
//		}
//		if ( MinPoint.y > (Pos( Sphere[ idx ].Index ).y - Sphere[ idx ].Radius) ) {
//			MinPoint.y = Pos( Sphere[ idx ].Index ).y - Sphere[ idx ].Radius;
//		}
//
//		if ( MaxPoint.x < (Pos( Sphere[ idx ].Index ).x + Sphere[ idx ].Radius) ) {
//			MaxPoint.x = Pos( Sphere[ idx ].Index ).x + Sphere[ idx ].Radius;
//		}
//		if ( MaxPoint.y < (Pos( Sphere[ idx ].Index ).y + Sphere[ idx ].Radius) ) {
//			MaxPoint.y = Pos( Sphere[ idx ].Index ).y + Sphere[ idx ].Radius;
//		}
	};
	
	// Set the Rectangle //
	BoundingRect = cPhysics::BoundingRectType::Pair( MinPoint, MaxPoint );
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::GrowBoundingRectBySphere( const size_t _Index ) {
	// Convert our pose parts in to something local //
	std::vector< cSphere >& Sphere = Pose->Sphere;

	// In theory, grow the bounding Rectangle by an added sphere //
	BoundingRect = cPhysics::BoundingRectType::Pair( 
		BoundingRect.P1().Min( (Nodes.Pos( Sphere[ _Index ].Index ) - Sphere[ _Index ].Radius) ),
		BoundingRect.P2().Max( (Nodes.Pos( Sphere[ _Index ].Index ) + Sphere[ _Index ].Radius) )
		);
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::CalculateSpringLength() {
	// Convert our pose parts in to something local //
	std::vector< cSpring >& Spring = Pose->Spring;

	// For all springs, calculate their length //
	for ( size_t idx = 0; idx < Spring.size(); idx++ ) {
		// *** Make this use local nodes instead of my nodes!!! *** //
		
		// If it's an auto length spring //
		//if ()
		Spring[ idx ].CalcLength( Nodes );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
