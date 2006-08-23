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
	if ( _IndexA >= Nodes.Size() )
		return -1;
	if ( _IndexB >= Nodes.Size() )
		return -1;
	// Test for less than zero too //
	
	Pose->Spring.push_back( cSpring( _IndexA, _IndexB ) );
	
	return Pose->Spring.size() - 1;
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DeleteSpring( size_t Number ) {
	// Make this an assert //
	if ( Number >= Pose->Spring.size() )
		return;
	// Test for less than zero too //
	
	Pose->Spring.erase( Pose->Spring.begin() + Number );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cBody2D::AddSphere( size_t _Index ) {
	// Make this an assert //
	if ( _Index >= Nodes.Size() )
		return -1;
	// Test for less than zero too //
	
	Pose->Sphere.push_back( cSphere( _Index ) );

	return Pose->Sphere.size() - 1;
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DeleteSphere( size_t Number ) {
	// Make this an assert //
	if ( Number >= Pose->Sphere.size() )
		return;
	// Test for less than zero too //
	
//		std::vector< cSphere >::iterator Iterator = Sphere.begin();
//		for( size_t idx = 0; idx < Number; idx++ ) {
//			Iterator++;
//		}
	
	Pose->Sphere.erase( Pose->Sphere.begin() + Number );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cBody2D::AddNode() {
	Pose->Node.push_back( cPoseNode() );
	return Nodes.Add();
}
// - ------------------------------------------------------------------------------------------ - //
void cBody2D::DeleteNode( size_t Number ) {
	// Remove Spheres //
	for( size_t idx = 0; idx < Pose->Sphere.size(); idx++ ) {
		if ( Pose->Sphere[ idx ].Index == Number ) {
			DeleteSphere( idx );
		}
	}
	// Update offsets //
	for( size_t idx = 0; idx < Pose->Sphere.size(); idx++ ) {
		if ( Pose->Sphere[ idx ].Index > Number ) {
			Pose->Sphere[ idx ].Index--;
		}
	}
	
	// Remove Springs, and offset greater ones //
	for( size_t idx = 0; idx < Pose->Spring.size(); idx++ ) {
		if ( Pose->Spring[ idx ].IndexA == Number ) {
			DeleteSpring( idx );
		}
		if ( Pose->Spring[ idx ].IndexB == Number ) {
			DeleteSpring( idx );
		}
	}
	for( size_t idx = 0; idx < Pose->Spring.size(); idx++ ) {			
		if ( Pose->Spring[ idx ].IndexA > Number ) {
			Pose->Spring[ idx ].IndexA--;
		}
		if ( Pose->Spring[ idx ].IndexB > Number ) {
			Pose->Spring[ idx ].IndexB--;
		}
	}
		
	// Remove the Node //
	Pose->Node.erase( Pose->Node.begin() + Number );
	Nodes.Remove( Number );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
