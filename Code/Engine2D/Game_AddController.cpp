// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Game/Objects/GenericController.h>
#include <Game/Objects/SpiderController.h>
#include <Game/Objects/AIController.h>
#include <Game/Objects/TankController.h>
#include <Game/Objects/HamsterController.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::AddController( int _ControllerId, cSphereObject* _Object, const std::string& File ) {
	switch ( _ControllerId ) {
		case 0: {
			ObjectController.push_back( new cGenericController( _Object, File ) );
			break;
		}
		case 1: {
			cScriptParser Shot("src/Content/Experimental/Meshes/SpiderShot.mesh");

			cSphereObject* Shot1;			
			SphereObject.push_back( Shot1 = new cSphereObject( Shot, Real::Zero, Real::Zero, Real::One) );
			Shot1->Flags.SetInactive();
			
			ObjectController.push_back(
				new cTankController( _Object, Shot1, File )
				);
			break;
		}
		case 2: {
			//cScriptParser SpiderShot("src/Content/Experimental/Meshes/SpiderShot.mesh");
			cScriptParser SpiderShot("src/Content/Experimental/Meshes/SpiderRope.mesh");

			cSphereObject* Shot1;			
			SphereObject.push_back( Shot1 = new cSphereObject( SpiderShot, Real::Zero, Real::Zero, Real::One) );
			Shot1->Flags.SetInactive();
			
			cNodeLink* Link1;
			NodeLink.push_back( Link1 = new cNodeLink( _Object, 0, Shot1, 15 ) );
			Link1->SetInactive();
			Link1->IgnoreMinimum();
			Link1->Strength = 0.2;

			cSphereObject* Shot2;
			SphereObject.push_back( Shot2 = new cSphereObject( SpiderShot, Real::Zero, Real::Zero, Real::One) );
			Shot2->Flags.SetInactive();
			
			cNodeLink* Link2;
			NodeLink.push_back( Link2 = new cNodeLink( _Object, 0, Shot2, 15 ) );
			Link2->SetInactive();
			Link2->IgnoreMinimum();
			Link2->Strength = 0.2;
			
			ObjectController.push_back(
				new cSpiderController( _Object, Shot1, Link1, Shot2, Link2, File )
				);
			
			break;
		}
		case 3: {
			ObjectController.push_back( new cAIController( _Object, File ) );
			break;
		}
		case 4: {
			ObjectController.push_back( new cHamsterController( _Object, File ) );
			break;
		}
	};
}
// - ------------------------------------------------------------------------------------------ - //
