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

#include <Framework/MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef EDITOR
// For FPS test //
#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <sstream>
// ------------ //
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::cClassicGameEngine( const std::string& FileName ) :
	GameActive( false ),
	LevelComplete( false )
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

	LoadMap( FileName );
	
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
int cClassicGameEngine::Message( int Msg, Engine2D::cDynamicCollection* const Sender ) {
	switch ( Msg ) {
		case 2: {
			CharactersAtEndZones++;
			break;
		};
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
int cClassicGameEngine::Message( int Msg, Engine2D::cPassiveObject* const Sender ) {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::FrameStart() {
	CharactersAtEndZones = 0;	
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::FrameEnd() {
	//if ( CharactersAtEndZones == 2 ) {
	if ( CharactersAtEndZones == 1 ) {
		LevelComplete = true;
		cMessageEntity::Current->BreakLoop = true;	
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::Step() {
	FrameStart();

	// ------------------------------------------------------------------------------------------ //
	
	// When you push space, toggle activity //
	if( Input::Button[ KEY_SPACE ].Pressed() || Input::Pad[0].Button[ PAD_START ].Pressed() ) {
		GameActive = !GameActive;
		
		if ( GameActive ) {
			// Add bombs here, 'cause they could be tweaked up until this point //
			AddBombs();
		}
		else {
			// Reset here, to restore everything back to it's home position, before we edit //
			ResetMap();			
			Impulse.clear();
		}
	}

	// temporary keys //
	{
		// Toggle play //
		if( Input::Button[ KEY_BACKSPACE ].Pressed() ) {
			GameActive = !GameActive;
		}
		
		// When you push backspace, reload/reset the level //
		if( Input::Button[ KEY_TAB ].Pressed() ) {
			ResetMap();
			Impulse.clear();
			AddBombs();
		}
	}
	
	// Only step the engine whilst we are active //
	if ( GameActive ) {
		// Stuff my engine does before //
		
		// Hack to follow the hamster.  we need a way to identify the collection to follow //
		if( DynamicCollection.size() >= 1 )
		{
			Camera->UpdateTarget( DynamicCollection[ 0 ]->Component[ 0 ].Body.BoundingRect.Center() );
		}
		
		// Original Engine Step Stuff //
		cEngine2D::Step();
		
		// Stuff my engine does after //
		NewParticle.Step();
	}
	// If the engine is not active, then we'r in edit mode //
	else {
		Cursor.Step();
		
		// Update Camera //
		Camera->UpdateTarget( Cursor.Pos );
	}
	
	// ------------------------------------------------------------------------------------------ //
	
	FrameEnd();
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::Draw() {
	// -- Stuff my engine does before --------------- //
	// ... //
	
	// -- Original Engine Draw ---------------------- //
	cEngine2D::Draw();
	
	// -- Stuff my engine does after ---------------- //

	// Particle System //
	NewParticle.Draw();

	// Things to draw only when the game isn't active //
	if ( !GameActive ) {
		Cursor.Draw();
	}	

	// -- Hud Camera Space -------------------------- //
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
	for ( int idx = 0; idx < Cursor.Bomb.size(); idx++ ) {
		PassiveObject.push_back( CreatePassiveInstance( 2, Cursor.Bomb[ idx ].Pos, Cursor.Bomb[ idx ].Time ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
