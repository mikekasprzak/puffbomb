// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"

#include <Engine2D/PassiveObject/PassiveCommonClockObject.h>
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

#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::cClassicGameEngine( const std::string& FileName ) :
	GameActive( false ),
	LevelComplete( false ),
	CharactersAtEndZones( 0 ),
	Score( 0 ),
	ArrowAnimator( "TrackingArrow.anim" ),
	IsHelp( false ),
	HelpTex( TexturePool.Load( "ClassicControls.pack.tx" ) )
{
	// Camera for drawing the hud information //
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

	// Load the requested map //
	LoadMap( FileName );
	
	
	// Load the appropriate minimap for this level //
	MiniMapName = FileName.substr( 5, FileName.size() - 4 - 5 ) + ".pack.tx";
	MiniMapTex = TexturePool.Load( MiniMapName );
	
	
	// Empty the particle systems //
	SolidParticle.Clear();
	DenseParticle.Clear();
	
	
	// Load the end of level flag animation/graphic for the tracking circles //
	PointsOfInterestAnimators.push_back( cAnimator( "TrackingCircleEnd.anim" ) );
	
	
	// Don't draw the mouse cursor //
	Gfx::DisableMouseDraw();
	
	
	// Pop-up Help Menu Hack //
	{
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
	}	
	
	
	// MiniMap //
	MiniMapInit();
}
// - ------------------------------------------------------------------------------------------ - //
cClassicGameEngine::~cClassicGameEngine() {
	// Destroy the Camera for the hud //
	delete HudCamera;
	
	// Explicitly remove the minimap from the texture pool, so to not waste memory anymore //
	TexturePool.Remove( MiniMapName );
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
		
		// I am at the end of the level, or rather I represent someone who is //
		case 2: {
			CharactersAtEndZones++;
			break;
		};
				
		// Noted a bomb limit via a dummy Passive Object //
		case 3: {
			Log( 10, "+ Max Bomb count recieved \"" << Sender->Argument << "\"" );
			Cursor.BombLimit = Sender->Argument;
			// We do this test because this happens every time the level resets //
			// If we remove this, the 2 systems (active bombs and such) get out of sync //
			if ( ClockHud.MaxBombCount != Cursor.BombLimit ) {
				ClockHud.SetBombs( Cursor.BombLimit );
			}
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
	//CharactersAtEndZones = 0;	
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
void cClassicGameEngine::PhysicsStart() {
	//CharactersAtEndZones = 0;
}
// - ------------------------------------------------------------------------------------------ - //	
void cClassicGameEngine::PhysicsEnd() {
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

	ClockHud.Step();

	if( !IsHelp )
	{
		FrameStart();
		
		// ------------------------------------------------------------------------------------------ //
		// Step the common clock of passive objects //
		Engine2D::cPassiveCommonClockObject::StepClock();	
		
		// When you push space, toggle activity //
		if( Input::Button[ KEY_SPACE ].Pressed() || Input::Pad[0].Button[ PAD_X ].Pressed() ) {
			GameActive = !GameActive;
			
			if ( GameActive ) {
				// Add bombs here, 'cause they could be tweaked up until this point //
				AddBombs();
				// Deselect the current bomb //
				Cursor.Selection = -1;
				
				// Tell the clock hud the mode has changed //
				ClockHud.StartActionMode();
			}
			else {
				// Clear various lists, 'cause we're about to repopulate them //
				CameraTracking.clear();
				Impulse.clear();
				AlwaysActivePassives.clear();
				PointsOfInterest.clear();
	
				// Reset here, to restore everything back to it's home position, before we edit //
				ResetMap();
				CharactersAtEndZones = 0;

				// Tell the clock hud the mode has changed //
				ClockHud.StartEditMode();
			}
		}
		
		// Only step the engine whilst we are active //
		if ( GameActive ) {
			// Stuff my engine does before ------------------------------------------------------ //
			//Camera->MinZoom = Global::HudZoom * Real( 2 );
			//Camera->MinZoom = Global::HudZoom * Real( 2.5 );
			Camera->IsZoomedOut = false;
					
			if( Input::Pad[ 0 ].Button[ PAD_Y ] ) {
				//Camera->MinZoom = Global::HudZoom * Real( 3.5 );
				//Camera->MinZoom = ( ( Camera->CameraBounds.P2().x - Camera->CameraBounds.P1().x ) / Real( 4800 ) ) * Camera->MinZoom;
				Camera->IsZoomedOut = true;

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
			
			// Engine Step ---------------------------------------------------------------------- //
			cEngine2D::Step();

			// Stuff my engine does after ------------------------------------------------------- //			
			if( Input::Button[ MOUSE_1 ] ) {
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
			// ---------------------------------------------------------------------------------- //
		}
		// If the engine is not active, then we'r in edit mode //
		else {
			// Clear Impulses (passive hack) //
			Impulse.clear();
						
			for ( size_t idx = 0; idx < AlwaysActivePassives.size(); idx++ ) {
				AlwaysActivePassives[ idx ]->Work();
				AlwaysActivePassives[ idx ]->StepAnimation();
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
	
		// -------------------------------------------------------------------------------------- //
		
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
	
	
	Gfx::DisableDepth();
		
	// Draw MiniMap and draw the view box //
	Gfx::PushMatrix();
	{
		Gfx::Translate( Vector2D( Global::Right, Global::Bottom ) );

		Gfx::DisableTex2D();
		
		Vector2D CameraBounds = ( ( Camera->CameraBounds._P2 - Camera->CameraBounds._P1 ) ) / Real( 4 ) / MiniMapRatio;
		
		Gfx::RFilledRect(
			Vector2D( -CameraBounds.x, CameraBounds.y ),
			Vector2D::Zero,
			Gfx::RGBA( 0, 0, 0, 80 )
		);

		// Draw the end zones on the minimap //
		for( size_t idx = 0; idx < Map.ZoneInstanceInfo.size(); idx++ )
		{
			if( Map.ZoneInstanceInfo[ idx ].Id == 9 )
			{
				Vector2D EndBounds = ( ( Map.ZoneInstanceInfo[ idx ].BoundingRect.P2() - Map.ZoneInstanceInfo[ idx ].BoundingRect.P1() ) ) / Real( 4 ) / MiniMapRatio;
				Vector2D EndOffset = Vector2D( Camera->CameraBounds._P2.x, Camera->CameraBounds._P1.y ) / Real( 4 ) / MiniMapRatio;
				
				Gfx::FilledRect(
					Map.ZoneInstanceInfo[ idx ].BoundingRect.P1() / Real( 4 ) / MiniMapRatio - EndOffset,
					Map.ZoneInstanceInfo[ idx ].BoundingRect.P2() / Real( 4 ) / MiniMapRatio - EndOffset,
					Gfx::RGBA( 255, 255, 255, 80 )
				);

			}
		}

		Gfx::EnableTex2D();
		
		Gfx::DrawQuads(
			&MiniMapTexVertex[0],
			&MiniMapTexUV[0],
			MiniMapTexIndices,
			4,
			MiniMapTex.Id,
			Gfx::White()
		);
		
		Gfx::DisableTex2D();
		
		Vector2D TempPos = Vector2D( Camera->Pos.x, Camera->Pos.y );
		
		TempPos.x -= Camera->CameraBounds._P2.x;
		TempPos.y -= Camera->CameraBounds._P1.y;
				
		Gfx::SetLineWidth( 3.0 );

		// Draw the camerabounds on the minimap //
		Gfx::Rect(
			( Camera->ViewArea._P1 + TempPos ) / Real( 4 ) / MiniMapRatio,
			( Camera->ViewArea._P2 + TempPos ) / Real( 4 ) / MiniMapRatio,
			Gfx::RGBA( 192, 192, 192, 255 )
		);
		
		// Draw the characters on the minimap //
		for( size_t idx = 0; idx < Map.DynamicObjectInstanceInfo.size(); idx++ )
		{
			if( Map.DynamicObjectInstanceInfo[ idx ].Id == 64 )
			{
				Vector2D CharPos = DynamicCollection[ idx ]->Component[ 0 ].Body.BoundingRect.ToRect().Center();
						
				Gfx::Circle(
					Vector2D( CharPos.x - Camera->CameraBounds._P2.x, CharPos.y - Camera->CameraBounds._P1.y ) / Real( 4 ) / MiniMapRatio, Real( 4 ),
					Gfx::RGBA( 192, 192, 192, 255 )
				);
			}
		}
		
		Gfx::SetLineWidth( 1.0 );
		
		Gfx::EnableTex2D();

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


	ClockHud.Draw();

	// Temporary Help Menu F1 popup //
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
	else
	{
		Vector3D TempPos = Vector3D( Real::Zero, Global::Bottom + Real( 15 ), 0.0 );
		cFonts::FlangeLight.Write( "F1 - Help", TempPos, Real( 0.75 ), Gfx::RGBA( 255, 255, 255, 155 ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::MiniMapInit()
{
	Vector2D CameraCenter = Vector2D::Zero;
	Vector2D P1 = Vector2D::Zero;
	Vector2D P2 = Vector2D::Zero;
	
	for( size_t idx = 0; idx < Map.ZoneInstanceInfo.size(); ++idx )
	{
		if( Map.ZoneInstanceInfo[ idx ].Id == 1 )
		{
			CameraCenter = Map.ZoneInstanceInfo[ idx ].BoundingRect.Center();
			
			P1 = Map.ZoneInstanceInfo[ idx ].BoundingRect.P1();
			P2 = Map.ZoneInstanceInfo[ idx ].BoundingRect.P2();
		}
	}
	
	MiniMapXRatio = ( P2.x - P1.x ) / Real( 2 );
	MiniMapYRatio = ( P2.y - P1.y ) / Real( 2 );
	
	MiniMapXRatio /= ( 1920 / 2 );
	MiniMapYRatio /= ( 1200 / 2 );

	MiniMapCenterShift = Vector2D( Real::Zero, Real::Zero );

	if( MiniMapXRatio > MiniMapYRatio )
	{
		MiniMapRatio = MiniMapXRatio;
		MiniMapCenterShift = Vector2D( Real::Zero, ( 1200 * MiniMapRatio ) - ( P2.y - P1.y ) );
	}	
	else
	{
		MiniMapRatio = MiniMapYRatio;
		MiniMapCenterShift = Vector2D( ( -1920 * MiniMapRatio ) + ( P2.x - P1.x ), Real::Zero );
	}
	
	MiniMapCenterShift = MiniMapCenterShift / Real( 4 ) / MiniMapRatio / Real( 2 );

	Real MiniMapWidth = 1920.0;
	Real MiniMapHeight = 1200.0;
	
	MiniMapWidth /= Real( 4 ); 
	MiniMapHeight /= Real( 4 );
	
	MiniMapTexVertex[0] = Vector3D( -MiniMapWidth, Real::Zero, 0.0 ) - MiniMapCenterShift.ToVector3D();
	MiniMapTexVertex[1] = Vector3D( Real::Zero, Real::Zero, 0.0 ) - MiniMapCenterShift.ToVector3D();
	MiniMapTexVertex[2] = Vector3D( Real::Zero, MiniMapHeight, 0.0 ) - MiniMapCenterShift.ToVector3D();
	MiniMapTexVertex[3] = Vector3D( -MiniMapWidth, MiniMapHeight, 0.0 ) - MiniMapCenterShift.ToVector3D();

	MiniMapTexUV[0] = Vector2D( 0.01, 0.01 );
	MiniMapTexUV[1] = Vector2D( 0.99, 0.01 );
	MiniMapTexUV[2] = Vector2D( 0.99, 0.99 );
	MiniMapTexUV[3] = Vector2D( 0.01, 0.99 );

	MiniMapTexIndices[0] = 0;
	MiniMapTexIndices[1] = 1;
	MiniMapTexIndices[2] = 2;
	MiniMapTexIndices[3] = 3;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicGameEngine::AddBombs() {
	const int TimeScalar = 20;
	// 15 = 4 ticks per second //
	// 12 = 5 ticks per second //
	// 10 = 6 ticks per second //
	// 6 = 10 ticks per second //
	// 5 = 12 ticks per second //
	// 4 = 15 ticks per second //
	
	// Add every bomb //
	for ( size_t idx = 0; idx < Cursor.Bomb.size(); idx++ ) {
		PassiveObject.push_back( CreatePassiveInstance( 2, Cursor.Bomb[ idx ].Pos, (Cursor.Bomb[ idx ].Time * TimeScalar) + 1 + 120 ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
