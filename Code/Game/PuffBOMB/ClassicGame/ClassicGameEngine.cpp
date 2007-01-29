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
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#ifdef EDITOR
// For FPS test //
#include <sstream>
// ------------ //
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::cClassicGameEngine( const std::string& FileName ) :
	GameActive( false ),
	LevelComplete( false ),
	Score( 0 ),
	ArrowAnimator( "TrackingArrow.anim" ),
	IsHelp( false ),
	HelpTex( TexturePool.Load( "ClassicControls.pack.tx" ) )
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
	
	std::string MiniMapName = FileName.substr( 5, FileName.size() - 4 - 5 ) + ".tx";
	
	Log( 10, "FileName " << FileName );
	Log( 10, "MiniMapName " << MiniMapName );
	
	MiniMapTex = TexturePool.Load( MiniMapName );

	SolidParticle.Clear();
	DenseParticle.Clear();
	
	PointsOfInterestAnimators.push_back( cAnimator( "TrackingCircleEnd.anim" ) );
	
	Gfx::DisableMouseDraw();
	
// 	Gfx::Rotate( Real( 45 ), Real( 0 ), Real( 0 ), Real( 20 ) );
	
//	PassiveObject.push_back( CreatePassiveInstance( 33, Vector2D( 0, 1000 ), 600 ) );
//	PassiveObject.push_back( CreatePassiveInstance( 32, Vector2D( 200, 1000 ), 20 ) );

/*
	PassiveObject.push_back( CreatePassiveInstance( 32, Vector2D( 0, 1000 ), 1 ) );

	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( 400, 1300 ), 1 ) );
	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( 400, 701 ), 1 ) );
	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( -400, 1301 ), 1 ) );
	PassiveObject.push_back( CreatePassiveInstance( 1, Vector2D( -400, 700 ), 1 ) );*/
	
	//Real HalfWidth = HelpTex.Width / 2;
	//Real HalfHeight = HelpTex.Height / 2;

	Real HalfWidth = HelpTex.Width;
	Real HalfHeight = HelpTex.Height;
	
	HelpTexVertex[0] = Vector3D( -HalfWidth, -HalfHeight, 0.0 );
	HelpTexVertex[1] = Vector3D( HalfWidth, -HalfHeight, 0.0 );
	HelpTexVertex[2] = Vector3D( HalfWidth, HalfHeight, 0.0 );
	HelpTexVertex[3] = Vector3D( -HalfWidth, HalfHeight, 0.0 );

	HelpTexUV[0] = Vector2D( 0.0, 1.0 );
	HelpTexUV[1] = Vector2D( 1.0, 1.0 );
	HelpTexUV[2] = Vector2D( 1.0, 0.0 );
	HelpTexUV[3] = Vector2D( 0.0, 0.0 );

	HelpTexIndices[0] = 0;
	HelpTexIndices[1] = 1;
	HelpTexIndices[2] = 2;
	HelpTexIndices[3] = 3;
	
	// MiniMap //
	Real MiniMapWidth = 1920.0;
	Real MiniMapHeight = 1200.0;
	
	MiniMapWidth /= Real( 4 ); 
	MiniMapHeight /= Real( 4 );
	
	MiniMapTexVertex[0] = Vector3D( -MiniMapWidth, Real::Zero, 0.0 );
	MiniMapTexVertex[1] = Vector3D( Real::Zero, Real::Zero, 0.0 );
	MiniMapTexVertex[2] = Vector3D( Real::Zero, MiniMapHeight, 0.0 );
	MiniMapTexVertex[3] = Vector3D( -MiniMapWidth, MiniMapHeight, 0.0 );

	MiniMapTexUV[0] = Vector2D( 0.0, 0.0 );
	MiniMapTexUV[1] = Vector2D( 1.0, 0.0 );
	MiniMapTexUV[2] = Vector2D( 1.0, 1.0 );
	MiniMapTexUV[3] = Vector2D( 0.0, 1.0 );

	MiniMapTexIndices[0] = 0;
	MiniMapTexIndices[1] = 1;
	MiniMapTexIndices[2] = 2;
	MiniMapTexIndices[3] = 3;
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
		
		// Coin //
		case 10: {
			Log( 10, "+ Coin 50" );
			
			AddScore( 50 );
			break;
		};
		// Coin //
		case 11: {
			Log( 10, "+ Coin 100" );

			AddScore( 100 );
			break;
		};
		// Coin //
		case 12: {
			Log( 10, "+ Coin 150" );

			AddScore( 150 );
			break;
		};
		// Coin //
		case 13: {
			Log( 10, "+ Coin 250" );

			AddScore( 250 );
			break;
		};
		// Coin //
		case 14: {
			Log( 10, "+ Coin 500" );

			AddScore( 500 );
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

		case 3: {
			Log( 10, "+ Max Bomb count recieved \"" << Sender->Argument << "\"" );
			Cursor.BombLimit = Sender->Argument;
			break;
		};

		// Points of Interest //
		case 7: {
			Log( 10, "+ Point of Interest" );
			PointsOfInterest.push_back( Sender );
			
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
		if ( CharactersAtEndZones == (int)CameraTracking.size() ) {
			LevelComplete = true;
			cMessageEntity::Current->BreakLoop = true;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::Step() {
	if( Input::Button[ KEY_F1 ].Pressed() )
	{
		IsHelp = !IsHelp;
	}
	else if( Input::Pad[0].Button[ PAD_START ].Pressed() )
	{
		cMessageEntity::Current->BreakLoop = true;
	}

	if( !IsHelp )
	{
		FrameStart();
		
		// ------------------------------------------------------------------------------------------ //
		
		// When you push space, toggle activity //
		if( Input::Button[ KEY_SPACE ].Pressed() || Input::Pad[0].Button[ PAD_X ].Pressed() ) {
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
				PointsOfInterest.clear();
	
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
				PointsOfInterest.clear();
	
				// Reset here, to restore everything back to it's home position, before we edit //
				ResetMap();
				
				// Add our bombs //
				AddBombs();
			}
		}
		
		// Only step the engine whilst we are active //
		if ( GameActive ) {
			// Stuff my engine does before //
			Camera->MinZoom = Global::HudZoom * Real( 2 );
					
			if( Input::Pad[ 0 ].Button[ PAD_Y ] ) {
				Camera->MinZoom = Global::HudZoom * Real( 3.5 );
			}
		
			// Hack to follow the hamster.  we need a way to identify the collection to follow //
			if( CameraTracking.size() >= 1 )
			{
				Rect2D FollowRect = CameraTracking[ 0 ]->Component[ 0 ].Body.BoundingRect.ToRect();
				
				for ( size_t idx = 1; idx < CameraTracking.size(); idx++ ) {
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
			
			for ( size_t idx = 0; idx < AlwaysActivePassives.size(); idx++ ) {
				AlwaysActivePassives[ idx ]->Work();
			}
	
	
	//		if ( Cursor.Selection != -1 ) {
	//			Camera->Pos.z -= Real( 100 );
	//		}
			
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

	// Draw Points of interest tracking //
	for ( size_t idx = 0; idx < PointsOfInterest.size(); idx++ ) {
		ElementTracker( ArrowAnimator, PointsOfInterest[ idx ]->BoundingRect.ToRect(), true, -Real( 48 ) );
		
		if( PointsOfInterestAnimators.size() == PointsOfInterest.size() )
		{
			ElementTracker( PointsOfInterestAnimators[ idx ], PointsOfInterest[ idx ]->BoundingRect.ToRect(), false, Real( 32 ) );
		}
	}

	Gfx::PushMatrix();
	{
		Gfx::Translate( Vector2D( Global::Right, Global::Bottom ) );
	
		Gfx::DrawQuads(
			&MiniMapTexVertex[0],
			&MiniMapTexUV[0],
			MiniMapTexIndices,
			4,
			MiniMapTex.Id,
			Gfx::White()
		); 
	}
	Gfx::PopMatrix();

	
/*#ifdef EDITOR
	//	//  DISPLAYS FPS  //
	std::stringstream Temp;
	Temp << Global::FPS;
	std::string TempString = Temp.str();
	
	Vector3D TempPos = Vector3D( Global::Left, Global::Top - Real( 45 ), 0.0 );

	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 0, 200, 0, 255 ) );
	// -------------- //
#endif // EDITOR //

	{
		//  Display Score //
		std::stringstream Temp;
		Temp << "Score:  " << Score;
		std::string TempString = Temp.str();
		
		Vector3D TempPos = Vector3D( Global::Right - Real( 545 ), Global::Top - Real( 45 ), 0.0 );
	
		cFonts::FlangeLight.Write( TempString, TempPos, Real( 0.5 ), Gfx::RGBA( 50, 200, 55, 255 ) );
	}*/

	if( IsHelp )
	{
		Gfx::DrawQuads(
			&HelpTexVertex[0],
			&HelpTexUV[0],
			HelpTexIndices,
			4,
			HelpTex.Id,
			Gfx::White()
		); 
	}

	{
		Vector3D TempPos = Vector3D( Global::Left + Real( 100 ), Global::Bottom + Real( 15 ), 0.0 );
		cFonts::FlangeLight.Write( "F1 - Help", TempPos, Real( 0.75 ), Gfx::RGBA( 255, 255, 255, 155 ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::AddBombs() {
	// 15 - 4 per second //
	// 12 - 5 per second //
	// 10 - 6 per second //
	// 6 - 10 per second //
	// 5 - 12 per second //
	// 4 - 15 per second //
	const int TimeScalar = 10;
	
	for ( int idx = 0; idx < Cursor.Bomb.size(); idx++ ) {
		PassiveObject.push_back( CreatePassiveInstance( 2, Cursor.Bomb[ idx ].Pos, (Cursor.Bomb[ idx ].Time * TimeScalar) + 1 ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
