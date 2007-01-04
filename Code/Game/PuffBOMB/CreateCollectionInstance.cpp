// - ------------------------------------------------------------------------------------------ - //
// CreateCollectionInstance //
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"

#include "DynamicComponent/ComponentAnimationSet/ComponentAnimationSetPool.h"

#include "Objects/HamsterCharacter/HamsterCharacter.h"
// - ------------------------------------------------------------------------------------------ - //
Engine2D::cDynamicCollection* CreateCollectionInstance( const unsigned int Id, const Vector2D& Pos, const int Argument ) {
	// Switch based on the Id passed to the function //
	switch ( Id ) {
		case 1: {
			return new Engine2D::cDynamicCollection( "2D/Hamster/Hamster.coll", Pos );
			break;
		}
		case 2: {
			return new Engine2D::cDynamicCollection( "2D/HighFive/HighFive.coll", Pos );
			break;
		}
		case 3: {
			return new Engine2D::cDynamicCollection( "2D/Phatastic/Phatastic.coll", Pos );
			break;
		}

		case 64: {
			cHamsterCharacter* NewChar = new cHamsterCharacter( Pos );
			if ( Engine2D::cEngine2D::Current ) {
				Engine2D::cEngine2D::Current->Message( 1, NewChar );
			}
			return NewChar;
			break;
		}
		
		case 128: {
			return new Engine2D::cDynamicCollection( "2D/BubblePlant/BubblePlant.coll", Pos );
			break;
		}	
		case 129: {
			return new Engine2D::cDynamicCollection( "2D/Bridge/Bridge.coll", Pos );
			break;
		}
		case 130: {
			return new Engine2D::cDynamicCollection( "2D/Phatastic/PhatBridge.coll", Pos );
			break;
		}
		case 131: {
			return new Engine2D::cDynamicCollection( "2D/TreeOne/TreeOne.coll", Pos );
			break;
		}
		case 132: {
			return new Engine2D::cDynamicCollection( "2D/PurpleRock/PurpleRockBody.coll", Pos );
			break;
		}

		
		default: {
			// No object with Id requested found, so return a null object //
			return 0;
			break;
		}
	}
	
	// Say something loud to note that a Collection Intance wasn't created correctly //
	
	// In case the function accidentially doesn't return anything //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
