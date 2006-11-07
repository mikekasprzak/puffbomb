// - ------------------------------------------------------------------------------------------ - //
// CreateCollectionInstance //
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"

#include "DynamicComponent/ComponentAnimationSet/ComponentAnimationSetPool.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cDynamicCollection* CreateCollectionInstance( const unsigned int Id, const Vector2D& Pos, const int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			return new cDynamicCollection( "2D/Hamster/Hamster.coll", Pos );
			break;
		}
		case 2: {
			return new cDynamicCollection( "2D/HighFive/HighFive.coll", Pos );
			break;
		}
		case 3: {
			return new cDynamicCollection( "2D/Phatastic/Phatastic.coll", Pos );
			break;
		}
		
		default: {
			// No object with Id requested found, so return a null object //
			return 0;
			break;
		}
	}
	
	// In case the function accidentially doesn't return anything //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
