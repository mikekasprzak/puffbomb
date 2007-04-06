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
		case 133: {
			return new Engine2D::cDynamicCollection( "2D/Rope/SmallRope.coll", Pos );
			break;
		}
		case 134: {
			return new Engine2D::cDynamicCollection( "2D/Rope/LargeRope.coll", Pos );
			break;
		}
		case 135: {
			return new Engine2D::cDynamicCollection( "2D/PendPlatform/PendPlatform.coll", Pos );
			break;
		}
		case 136: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundPinecone.coll", Pos );
			break;
		}
		case 137: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundTree.coll", Pos );
			break;
		}
		case 138: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundAcorn.coll", Pos );
			break;
		}
		case 139: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundRockOne.coll", Pos );
			break;
		}
		case 140: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundRockTwo.coll", Pos );
			break;
		}
		case 141: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundRockThree.coll", Pos );
			break;
		}
		case 142: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundSunflower.coll", Pos );
			break;
		}
		case 143: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsOne/ForegroundMushroomOne.coll", Pos );
			break;
		}
		case 144: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsTwo/ForegroundPlatformOne.coll", Pos );
			break;
		}
		case 145: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsTwo/ForegroundPlatformTwo.coll", Pos );
			break;
		}
		case 146: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsTwo/ForegroundRockPlatform.coll", Pos );
			break;
		}
		case 147: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsTwo/ForegroundBerryBush.coll", Pos );
			break;
		}
		case 148: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsTwo/ForegroundTreeStumpOne.coll", Pos );
			break;
		}
		case 149: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsTwo/ForegroundTreeStumpTwo.coll", Pos );
			break;
		}
		case 150: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsTwo/ForegroundMushroomTwo.coll", Pos );
			break;
		}

		case 158: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsFour/ForegroundPotOne.coll", Pos );
			break;
		}
		case 159: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsFour/ForegroundPotTwo.coll", Pos );
			break;
		}
		case 160: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsFour/ForegroundPotThree.coll", Pos );
			break;
		}
		case 161: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsFour/ForegroundPotFour.coll", Pos );
			break;
		}
		case 162: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsFour/ForegroundPotFive.coll", Pos );
			break;
		}
		case 163: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsFour/ForegroundPotSix.coll", Pos );
			break;
		}
		case 164: {
			return new Engine2D::cDynamicCollection( "2D/ForegroundElementsFour/ForegroundPotSeven.coll", Pos );
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
