// - ------------------------------------------------------------------------------------------ - //
// Editing specific needs //
// - ------------------------------------------------------------------------------------------ - //
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
int cBody2D::AddSpring( size_t _IndexA, size_t _IndexB ) {
	// Make this an assert //
	if ( _IndexA >= size() )
		return -1;
	if ( _IndexB >= size() )
		return -1;
	// Test for less than zero too //
	
	Spring.push_back( cSpring( _IndexA, _IndexB ) );
	
	return Spring.size() - 1;
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DeleteSpring( size_t Number ) {
	// Make this an assert //
	if ( Number >= Spring.size() )
		return;
	// Test for less than zero too //
	
	Spring.erase( Spring.begin() + Number );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cBody2D::AddSphere( size_t _Index ) {
	// Make this an assert //
	if ( _Index >= size() )
		return -1;
	// Test for less than zero too //
	
	Sphere.push_back( cSphere( _Index ) );

	return Sphere.size() - 1;
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DeleteSphere( size_t Number ) {
	// Make this an assert //
	if ( Number >= Sphere.size() )
		return;
	// Test for less than zero too //
	
//		std::vector< cSphere >::iterator Iterator = Sphere.begin();
//		for( size_t idx = 0; idx < Number; idx++ ) {
//			Iterator++;
//		}
	
	Sphere.erase( Sphere.begin() + Number );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cBody2D::AddNode() {
	return Body.AddNode();
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DeleteNode( size_t Number ) {
	// Remove Spheres //
	for( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		if ( Sphere[ idx ].Index == Number ) {
			DeleteSphere( idx );
		}
	}
	// Update offsets //
	for( size_t idx = 0; idx < Sphere.size(); idx++ ) {
		if ( Sphere[ idx ].Index > Number ) {
			Sphere[ idx ].Index--;
		}
	}
	
	// Remove Springs, and offset greater ones //
	for( size_t idx = 0; idx < Spring.size(); idx++ ) {
		if ( Spring[ idx ].IndexA == Number ) {
			DeleteSpring( idx );
		}
		if ( Spring[ idx ].IndexB == Number ) {
			DeleteSpring( idx );
		}
	}
	for( size_t idx = 0; idx < Spring.size(); idx++ ) {			
		if ( Spring[ idx ].IndexA > Number ) {
			Spring[ idx ].IndexA--;
		}
		if ( Spring[ idx ].IndexB > Number ) {
			Spring[ idx ].IndexB--;
		}
	}
		
	// Remove the Node //
	Nodes.DeleteNode( Number );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
