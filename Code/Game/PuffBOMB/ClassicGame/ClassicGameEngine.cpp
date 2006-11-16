// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"
#include "CreateZoneInstance.h"

// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/NewParticleFactory.h>

// - ------------------------------------------------------------------------------------------ - //
#ifdef EDITOR
// For FPS test //
#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <sstream>
// ------------ //
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::cClassicGameEngine()
{
	// Create Camera //
	HudCamera = new cCamera(
		Vector3D( 0.0, 0.0, Global::HudZoom ),			// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Global::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		Global::HudZoom,								// MinZoom
		Global::HudZoom,								// MaxZoom
		Global::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Global::ScreenW ),						// Width
		Real( Global::ScreenH )						// Height
	 );
	 
	 
	PassiveObject.push_back( CreatePassiveInstance( 2, Vector2D( -1200, 700 ), 10 ) );
	//PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( -1000, 600 ), 10 ) ); 
}
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::~cClassicGameEngine() {
	// Destroy my Custom Camera //
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::Step() {
	// Stuff my engine does before //
	// ... //
	
	// Original Engine Step Stuff //
	cEngine2D::Step();
	
	// Stuff my engine does after //
	NewParticle.Step();
	
//	TurnBasedPlay();
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::Draw() {
	// Stuff my engine does before //
	// ... //
	
	// Original Engine Stuff //
	cEngine2D::Draw();
	
	// Particle System //
	NewParticle.Draw();
	
	// Stuff my engine does after //
	HudCamera->Update();
	
#ifdef EDITOR
	//	//  DISPLAYS FPS  //
	std::stringstream Temp;
	Temp << Global::FPS;
	std::string TempString = Temp.str();
	
	Vector3D TempPos = Vector3D( Global::Left, Global::Top - Real( 45 ), 0.0 );

	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 0, 200, 0, 255 ) );
	// -------------- //
#endif // EDITOR //

}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//void cClassicGameEngine::RealTimePlay() {
//	if ( !Player.empty() ) {
//		for ( size_t idx = 0; idx < Player.size(); idx++ ) {
//			Player[ idx ]->Control();
//		}
//	}
//}
// - ------------------------------------------------------------------------------------------ - //