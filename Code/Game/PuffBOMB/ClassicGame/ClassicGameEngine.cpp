// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"
// - ------------------------------------------------------------------------------------------ - //

#include <Input/Input.h>

// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>

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
		1000.0,											// NearClip
		100000.0,										// FarClip
		Global::HudZoom,								// MinZoom
		Global::HudZoom,								// MaxZoom
		Global::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Global::ScreenW ),						// Width
		Real( Global::ScreenH )						// Height
	 );

	SetActive();

	LoadMap( FileName );
	
	SolidParticle.Clear();
	DenseParticle.Clear();
// 	Gfx::Rotate( Real( 45 ), Real( 0 ), Real( 0 ), Real( 20 ) );
	
//	PassiveObject.push_back( CreatePassiveInstance( 33, Vector2D( 0, 1000 ), 600 ) );
//	PassiveObject.push_back( CreatePassiveInstance( 32, Vector2D( 200, 1000 ), 20 ) );

/*
	PassiveObject.push_back( CreatePassiveInstance( 32, Vector2D( 0, 1000 ), 1 ) );

	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( 400, 1300 ), 1 ) );
	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( 400, 701 ), 1 ) );
	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( -400, 1301 ), 1 ) );
	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( -400, 700 ), 1 ) );*/
}
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::~cClassicGameEngine() {
	// Destroy my Custom Camera //
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cClassicGameEngine::Message( int Msg, Engine2D::cDynamicCollection* Sender ) {
	switch ( Msg ) {
		// Add me to the follow list //
		case 1: {
			Log( 10, "+ Player to follow added" );
			CameraTracking.push_back( Sender );
			break;
		};
		// I am at the end of the level //
		case 2: {
			CharactersAtEndZones++;
			break;
		};
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
int cClassicGameEngine::Message( int Msg, Engine2D::cPassiveObject* Sender ) {
	switch ( Msg ) {
		// Add me to the follow list //
		case 1: {
			Log( 10, "+ Passive to run whilst in edit mode added" );
			AlwaysActivePassives.push_back( Sender );
			break;
		};
	};
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::FrameStart() {
	CharactersAtEndZones = 0;	
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::FrameEnd() {
	if ( CameraTracking.size() != 0 ) {
		if ( CharactersAtEndZones == CameraTracking.size() ) {
			LevelComplete = true;
			cMessageEntity::Current->BreakLoop = true;	
		}
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
			// Clear various lists, 'cause we're about to repopulate them //
			CameraTracking.clear();
			Impulse.clear();
			AlwaysActivePassives.clear();

			// Reset here, to restore everything back to it's home position, before we edit //
			ResetMap();
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
			// Clear various lists, 'cause we're about to repopulate them //
			CameraTracking.clear();
			Impulse.clear();
			AlwaysActivePassives.clear();

			// Reset here, to restore everything back to it's home position, before we edit //
			ResetMap();
			
			// Add our bombs //
			AddBombs();
		}
	}
	
	// Only step the engine whilst we are active //
	if ( GameActive ) {
		// Stuff my engine does before //
	
		// Hack to follow the hamster.  we need a way to identify the collection to follow //
		if( CameraTracking.size() >= 1 )
		{
			Rect2D FollowRect = CameraTracking[ 0 ]->Component[ 0 ].Body.BoundingRect.ToRect();
			
			for ( int idx = 1; idx < CameraTracking.size(); idx++ ) {
				FollowRect += CameraTracking[ idx ]->Component[ 0 ].Body.BoundingRect.ToRect();
			}
			
			Camera->UpdateTarget( FollowRect.Center() );
		}
		
		// Original Engine Step Stuff //
		cEngine2D::Step();
		
		if( Input::Button[ MOUSE_1 ] )
		{
			Vector2D BobPos = Vector2D(
					Real( ( int( Input::Mouse.x * Real( Global::HudW ) ) )
					- ( -Camera->Pos.x / Real( Camera->Pos.z / Global::HudZoom ) )
					- ( Real(Global::HudW >> 1) ) )
					* Real( Camera->Pos.z / Global::HudZoom ),
					Real( ( int( -Input::Mouse.y * Real( Global::HudH ) ) )
					+ ( Camera->Pos.y / Real( Camera->Pos.z / Global::HudZoom ) )
					+ ( Global::HudH >> 1 ) )
					* Real( Camera->Pos.z / Global::HudZoom )
			);
		
			Engine2D::cEngine2D::Current->Impulse.push_back( 
				Engine2D::cImpulse(
					BobPos,
					// Inner Radius, Intensity, Tangent //
					Real( 0 ), Real( -2 ), Real( 0.5 ),
					// Outer Radius, Intensity, Tangent //
					Real( 512 ), Real( 0 ), Real( 0.1 )
					)
				);
		}

		
		// Stuff my engine does after //

	}
	// If the engine is not active, then we'r in edit mode //
	else {
		// Clear Impulses (passive hack) //
		Impulse.clear();
		
		for ( int idx = 0; idx < AlwaysActivePassives.size(); idx++ ) {
			AlwaysActivePassives[ idx ]->Work();
		}
		
		Cursor.Step();
		
		// Update Camera //
		Camera->UpdateTarget( Cursor.Pos );
	}
	
	// Run the Particle systems always in both active and non active modes of the game //
	SolidParticle.Step();
	DenseParticle.Step();

	// ------------------------------------------------------------------------------------------ //
	
	FrameEnd();
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::Draw() {
	
//	Gfx::PushMatrix();

//	Gfx::Rotate( Real( 22 ), Real( 0 ), Real( 221 ), Real( 20 ) );
//	Gfx::Translate( Real( 0 ), Real( 220 ), Real( 0 ) );

	// -- Stuff my engine does before --------------- //
	// ... //
	
	// -- Original Engine Draw ---------------------- //
	cEngine2D::Draw();

//	Gfx::PopMatrix();

	// -- Stuff my engine does after ---------------- //

	Gfx::DisableDepth();

	// Particle System //
	SolidParticle.Draw();
	DenseParticle.Draw();

	Gfx::EnableDepth();

	// Things to draw only when the game isn't active //
	if ( !GameActive ) {
		Gfx::DisableDepth();
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
