// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"
#include "CreateZoneInstance.h"
// - ------------------------------------------------------------------------------------------ - //

#include <Input/Input.h>

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
cClassicGameEngine::cClassicGameEngine() :
	GameActive( false )
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

	LoadMap( "Maps/Classic/Level01.map" );
	
	NewParticle.Clear();
	
	AddBombs();		
}
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::~cClassicGameEngine() {
	// Destroy my Custom Camera //
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::Step() {
	// When you push space, toggle activity //
	if( Input::Button[ KEY_SPACE ].Pressed() ) {
		GameActive = !GameActive;
	}

	// When you push backspace, reload/reset the level //
	if( Input::Button[ KEY_BACKSPACE ].Pressed() ) {
		ResetMap();
		Impulse.clear();
		AddBombs();
	}
	
	// Only step the engine whilst we are active //
	if ( GameActive ) {
		// Stuff my engine does before //
		
		// Hack to follow the hamster.  we need a way to identify the collection to follow //
		if( DynamicCollection.size() >= 8 )
		{
			Camera->UpdateTarget( DynamicCollection[ 7 ]->Component[ 0 ].Body.BoundingRect.Center() );
		}
		
		// Original Engine Step Stuff //
		cEngine2D::Step();
		
		// Stuff my engine does after //
		NewParticle.Step();
		
	//	TurnBasedPlay();
	}
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
void cClassicGameEngine::AddBombs() {
	PassiveObject.push_back( CreatePassiveInstance( 2, Vector2D( -1200, 700 ), 10 ) );
	//PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( -1000, 600 ), 10 ) ); 
	
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
