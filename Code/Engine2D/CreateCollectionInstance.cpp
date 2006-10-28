// - ------------------------------------------------------------------------------------------ - //
// CreateCollectionInstance //
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cDynamicCollection* CreateCollectionInstance( unsigned int Id, Vector2D Pos, int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			//return new cDynamicCollection( "Hamster.obj", Pos );
			
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
