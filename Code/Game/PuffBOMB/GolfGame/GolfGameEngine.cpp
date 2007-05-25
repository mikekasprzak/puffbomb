// - ------------------------------------------------------------------------------------------ - //
#include "GolfGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"

#include <Engine2D/PassiveObject/PassiveCommonClockObject.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Player/LocalJoyPlayer.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Framework/MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Font/Fonts.h>
#include <Graphics/Gfx.h>
#include <sstream>

// - ------------------------------------------------------------------------------------------ - //
cGolfGameEngine::cGolfGameEngine( const std::string& FileName, const std::vector< cPlayerInfo >& _Players, int _StartPlayer ) :
	StartPoint( 0 ),
	CurrentPlayer( _StartPlayer ),
	BombGraphic( "GolfBomb.anim" ),
	State( 1 ),
	LevelComplete( false ),
	HitBoundery( false ),
 	ArrowAnimator( "TrackingArrow.anim" ),
 	IsHelp( false ),
	HelpTex( TexturePool.Load( "TournamentControls.pack.tx" ) )
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
	 
 	LoadMap( FileName );
 
	MiniMapName = FileName.substr( 5, FileName.size() - 4 - 5 ) + ".pack.tx";
	
	MiniMapTex = TexturePool.Load( MiniMapName );
 	
 	DenseParticle.Clear();
 	SolidParticle.Clear();
 	
 	Gfx::DisableMouseDraw();
	 	
 	// Add the start point (temporarily) //
// 	StartPoint = CreatePassiveInstance( 5, Vector2D( 0, 0 ) );
// 	PassiveObject.push_back( StartPoint );
 	
 	// Add Players //
 	for ( size_t idx = 0; idx < _Players.size(); idx++ ) {
 		Engine2D::cDynamicCollection* MyCol = CreateCollectionInstance( 65, StartPoint->Pos );
 		AddCollection( MyCol );
 		Player.push_back( new cLocalJoyPlayer( MyCol ) );
 		Player.back()->MyLastDropPos = StartPoint->Pos;
 		Player.back()->BombPos = (StartPoint->Pos - PointsOfInterest[ 0 ]->Pos).Normal() * Real( 256 );
 		Player.back()->Score = _Players[ idx ].Score;
 		MyCol->SetInactive();
 	}
 	
 	PlayerAnimators.push_back( cAnimator( "TrackingCircleP1.anim" ) );
	PlayerAnimators.push_back( cAnimator( "TrackingCircleP2.anim" ) );
	PlayerAnimators.push_back( cAnimator( "TrackingCircleP3.anim" ) );
	PlayerAnimators.push_back( cAnimator( "TrackingCircleP4.anim" ) );
	
	//PointsOfInterestAnimators.push_back( cAnimator( "TrackingCircleEnd.anim" ) );
	
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
	
	MiniMapInit();
	
	// Set the scoreboard //
	for ( int idx = 0; idx < Player.size(); idx++ ) {
		ScoreHud.StartScore( idx, Player[ idx ]->Score );
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
cGolfGameEngine::~cGolfGameEngine() {
	// Destroy my Custom Camera //
	delete HudCamera;
	
	// Deletes all our players //
	for ( size_t idx = 0; idx < Player.size(); idx++ ) {
		delete Player[ idx ];
	}
	
	TexturePool.Remove( MiniMapName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cGolfGameEngine::Message( int Msg, Engine2D::cDynamicCollection* Sender ) {
	switch ( Msg ) {
		// I am at the end of the level //
		case 2: {
			//CharacterAtEndZone++;
			Sender->SetInactive();

			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Player[ idx ]->Finished = true;
					break;
				}	
			}

			break;
		};

		// Player 'Go Back To My Last Best Drop' Zone //
		case 4: {
			Log( 10, "+ Player hit a 'Go Back To Safe' Zone" );
			if ( Sender == Player[ CurrentPlayer ]->MyObject ) {
				HitBoundery = true;

				// We went out of bounds, add a stroke //
				//Player[ CurrentPlayer ]->AddStroke();
			}
			// Deactivate this player, to dissapear and stop moving //
			Sender->SetInactive();
			
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Sender->SetPos( Player[ idx ]->MyLastDropPos );
					
					Player[ idx ]->Spawned = true;
					break;
				}	
			}

			// Make us an ObjectSensor, until we decide not to be //
			//Sender->Component[ 0 ].Body.Flags.SetObjectSensor();			
						
			break;
		};
		// Player 'Go To Nearest Drop' Zone //
		case 5: {
			Log( 10, "+ Player hit a 'Go To Nearest Drop' Zone" );
			if ( Sender == Player[ CurrentPlayer ]->MyObject ) {
				HitBoundery = true;

				// We went out of bounds, add a stroke //
				//Player[ CurrentPlayer ]->AddStroke();
			}
			Sender->SetInactive();
			Sender->SetPos( FindNearestDrop( *Sender ) );

			// Make us an ObjectSensor, until we decide not to be //
			//Sender->Component[ 0 ].Body.Flags.SetObjectSensor();			

			// Note this player as spawned //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					
					Player[ idx ]->Spawned = true;
					break;
				}	
			}			
			
			break;
		};


		// Coin //
		case 10: {
			Log( 10, "+ Coin 50" );
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Player[ idx ]->AddPickupScore( 50 );
					break;
				}	
			}
			break;
		};
		// Coin //
		case 11: {
			Log( 10, "+ Coin 100" );
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Player[ idx ]->AddPickupScore( 100 );
					break;
				}	
			}
			break;
		};
		// Coin //
		case 12: {
			Log( 10, "+ Coin 150" );
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Player[ idx ]->AddPickupScore( 150 );
					break;
				}	
			}
			break;
		};
		// Coin //
		case 13: {
			Log( 10, "+ Coin 250" );
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Player[ idx ]->AddPickupScore( 250 );
					break;
				}	
			}
			break;
		};
		// Coin //
		case 14: {
			Log( 10, "+ Coin 500" );
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Player[ idx ]->AddPickupScore( 500 );
					break;
				}	
			}
			break;
		};
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
int cGolfGameEngine::Message( int Msg, Engine2D::cPassiveObject* Sender ) {
	switch ( Msg ) {
//		// I am at the end of the level, or I represent someone who is //
//		case 2: {
//			//CharacterAtEndZone++;
//			Sender->SetInactive();
//
//			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
//				if ( Sender == Player[ idx ]->MyObject ) {
//					Player[ idx ]->Finished = true;
//					break;
//				}	
//			}
//
//			break;
//		};		
//		
		// Golf Start //
		case 5: {
			Log( 10, "+ Golf Start" );
			StartPoint = Sender;
			DropPoint.push_back( Sender );
			
			break;
		};
		// Golf Drop Point //
		case 6: {
			Log( 10, "+ Golf Drop Point" );
			DropPoint.push_back( Sender );
			
			break;
		};

		// Points of Interest //
		case 7: {
			Log( 10, "+ Point of Interest" );
			PointsOfInterest.push_back( Sender );
			// Temporary, until I have more associated graphics for points of interest //
			PointsOfInterestAnimators.push_back( cAnimator( "TrackingCircleEnd.anim" ) );
			
			break;
		};
		
		
	};
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGolfGameEngine::PhysicsStart() {

}
// - ------------------------------------------------------------------------------------------ - //	
void cGolfGameEngine::PhysicsEnd() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGolfGameEngine::Step() {
	if( Input::Button[ KEY_F1 ].Pressed() )
	{
		IsHelp = !IsHelp;
	}
	else if( Input::Pad[0].Button[ PAD_START ].Pressed() )
	{
		cMessageEntity::Current->BreakLoop = true;
	}
	
	ScoreHud.Step();
	
	if( !IsHelp )
	{
		// Stuff my engine does before //
		HitBoundery = false;
		
		// Step the common clock of passive objects //
		Engine2D::cPassiveCommonClockObject::StepClock();	
		
		// Original Engine Step Stuff //
		cEngine2D::Step();
		
		// Stuff my engine does after //
		TurnBasedPlay();
	
		// For all players, accumulate motion //	
		for ( size_t idx = 0; idx < Player.size(); idx++ ) {
			Player[ idx ]->AccumulateMotion();
		}
		
		// Step Particle Systems //
		SolidParticle.Step();
		DenseParticle.Step();
		
		if( Input::Pad[ 0 ].Button[ PAD_Y ] ) {
			//Camera->MinZoom = Global::HudZoom * Real( 3.5 );
			//Camera->MinZoom = ( ( Camera->CameraBounds.P2().x - Camera->CameraBounds.P1().x ) / Real( 4800 ) ) * Camera->MinZoom;
			Camera->IsZoomedOut = true;

		}
		else {
			//Camera->MinZoom = Global::HudZoom * Real( 2.5 );
			Camera->IsZoomedOut = false;
		}
		
		// Update Scoreboard //
		for ( int idx = 0; idx < Player.size(); idx++ ) {
			ScoreHud.SetScore( idx, Player[ idx ]->Score );
			ScoreHud.SetStroke( idx, Player[ idx ]->Stroke );
		}
		
	//	PlayerAnimator.Step();
	//	EndingAnimator.Step();
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
void cGolfGameEngine::Draw() {
	// Stuff my engine does before //
	// ... //
	
	// Original Engine Stuff //
	cEngine2D::Draw();
	
	// Stuff my engine does after //

	// Particle System //
	if ( State == 3 ) {
		Gfx::DisableTex2D();
		Gfx::DisableDepth();
		
		Vector2D CharacterCenter = Player[ CurrentPlayer ]->MyObject->Component[ 0 ].Body.BoundingRect.Center();
		Vector2D CursorPos = Player[ CurrentPlayer ]->BombPos + CharacterCenter;
		
		{	
			Gfx::EnableTex2D();
			
			// Cursor //
			BombGraphic.DrawQuad( CursorPos );
			//Gfx::Circle( CursorPos, Real( 3 ), Gfx::RGBA( 255, 255, 255, 255 ) );
		
			Gfx::DisableTex2D();
		}
		Gfx::SetLineWidth( 3 );	
			
		// Inner Circle //
		Gfx::Circle( CharacterCenter, Real( 128 ), Gfx::RGBA( 255, 0, 0, 128 ) );
		
		// Outer Circle //
		Gfx::Circle( CharacterCenter, Real( 512 - 32 ), Gfx::RGBA( 0, 255, 0, 128 ) );
			
		Gfx::SetLineWidth( 1 );	

		Gfx::EnableDepth();
		Gfx::EnableTex2D();
	}

	Gfx::DisableDepth();
	
	SolidParticle.Draw();
	DenseParticle.Draw();

	Gfx::EnableDepth();

	HudCamera->Update();

	// Draw player tracking //	
	for( size_t idx = 0; idx < Player.size(); idx++ ) {
		// Only draw the player finder when I've actually made a shot //
		if ( (Player[ idx ]->Stroke != 0) && (!Player[ idx ]->Finished) ) {
			ElementTracker( ArrowAnimator, Player[ idx ]->GetRect(), true, -Real( 48 ) );
			
			ElementTracker( PlayerAnimators[ idx ], Player[ idx ]->GetRect(), false, Real( 32 ) );
		}
	}
	
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
		
		for( size_t idx = 0; idx < Player.size(); idx++ )
		{
			// Only draw the player finder when I've actually made a shot //
			if ( (Player[ idx ]->Stroke != 0) && (!Player[ idx ]->Finished) )
			{
				Vector2D CharPos = Player[ idx ]->GetCenter();
				
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
	{
		//  DISPLAYS FPS  //
		std::stringstream Temp;
		Temp << Global::FPS;
		std::string TempString = Temp.str();
		
		Vector3D TempPos = Vector3D( Global::Left, Global::Top - Real( 45 ), 0.0 );
	
		cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 0, 200, 0, 255 ) );
	}
#endif // EDITOR //*/

	{
		//  Display Stroke //
		std::stringstream Temp;
		Temp << Player[ CurrentPlayer ]->Stroke;
		std::string TempString = Temp.str();
		
		Vector3D TempPos = Vector3D( Global::Right - Real( 45 ), Global::Top - Real( 45 ), 0.0 );
	
		cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 50, 100, 255, 255 ) );
	}

	{
		//  Display Score //
		std::stringstream Temp;
		Temp << "Score:  " << Player[ CurrentPlayer ]->Score;
		std::string TempString = Temp.str();
		
		Vector3D TempPos = Vector3D( Global::Right - Real( 545 ), Global::Top - Real( 45 ), 0.0 );
	
		cFonts::FlangeLight.Write( TempString, TempPos, Real( 0.5 ), Gfx::RGBA( 50, 200, 55, 255 ) );
	}

	{
		// Display Player Number //
		std::stringstream Temp;
		Temp << "Player  " << (CurrentPlayer + 1);
		std::string TempString = Temp.str();
		
		Vector3D TempPos = Vector3D( Global::Left + Real( 100 ), Global::Top - Real( 45 ), 0.0 );
	
		cFonts::FlangeLight.Write( TempString, TempPos, Real( 0.5 ), Gfx::RGBA( 50, 100, 255, 255 ) );
	}
	

	ScoreHud.Draw();

	// Help //	
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
		Vector3D TempPos = Vector3D( Real::Zero, Global::Bottom + Real( 15 ), 0.0 );
		cFonts::FlangeLight.Write( "F1 - Help", TempPos, Real( 0.75 ), Gfx::RGBA( 255, 255, 255, 155 ) );
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
void cGolfGameEngine::MiniMapInit()
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
void cGolfGameEngine::TurnBasedPlay() {
	if ( !Player.empty() ) {
		switch( State ) {
			case 1: {
				// Stage 1 - Attract Mode ----------------------------------------------------- - //
				State = 2;
				
				break;
			};
			case 2: {
				// Stage 2 - Activate Players (if not activated) ------------------------------ - //
				if ( !Player[ CurrentPlayer ]->Finished ) {
					// Since we're about to take action, add a stroke //
					Player[ CurrentPlayer ]->AddStroke();
				}

				if ( Player[ CurrentPlayer ]->Stroke == 10 ) {
					Player[ CurrentPlayer ]->Finished = true;
				}
				
				if ( !Player[ CurrentPlayer ]->Finished ) {
					// Activate the character, if not already activated //
					Player[ CurrentPlayer ]->MyObject->SetActive();

					// Make us an ObjectSensor, until we decide not to be //
					if ( Player[ CurrentPlayer ]->Spawned ) {
						Player[ CurrentPlayer ]->MyObject->Component[ 0 ].Body.Flags.SetObjectSensor();
						Player[ CurrentPlayer ]->Spawned = false;
					}
					
					
					// Since we're about to take action, add a stroke //
					//Player[ CurrentPlayer ]->AddStroke();

					
					// Gather input //
					State = 3;
				}
				else {
					// This player is done //
					State = 5;
				}
				
				break;
			};
			case 3: {
				// Stage 3 - Asking for input ------------------------------------------------- - //
				Camera->UpdateTarget( Player[ CurrentPlayer ]->MyObject->Component[ 0 ].Body.BoundingRect.Center() );
				
				// If our control is all done, and wants action //
				if ( Player[ CurrentPlayer ]->Control() ) {					
					// Create Bomb at position requested //
					Vector2D BombPos =
						Player[ CurrentPlayer ]->BombPos + 
						Player[ CurrentPlayer ]->MyObject->Component[ 0 ].Body.BoundingRect.Center();
					
					FXLibrary::Bomb( BombPos );
						
					Player[ CurrentPlayer ]->InsignificantMotion = 0;
					
					Engine2D::cImpulse MyImpulse(
							BombPos,
							// Inner Radius, Intensity, Tangent //
							Real( 0 ), Real( 18 ), Real( 0 ),
							// Outer Radius, Intensity, Tangent //
							Real( 512 ), Real( 0 ), Real( 0 )
							);

					Player[ CurrentPlayer ]->MyObject->Component[ 0 ].Body.ApplyImpulse( MyImpulse );
					Player[ CurrentPlayer ]->MyObject->Message( MyImpulse );
					
					// Change State, to play it out //
					State = 4;
				}
				
				break;
			}
			case 4: {
				// Stage 4 - Acting on input (and waiting for the turn to end) ---------------- - //		
				Camera->UpdateTarget( Player[ CurrentPlayer ]->MyObject->Component[ 0 ].Body.BoundingRect.Center() );

				// See how many players are moving //
				int MovingPlayers = 0;				
				for ( size_t idx = 0; idx < Player.size(); idx++ ) {
					if ( Player[ idx ]->InsignificantMotion < 30 ) {
						MovingPlayers++;
					}
				}
				
				// If Turn is over //
				if ( Input::Pad[ 0 ].Button[ PAD_BACK ].Pressed() || HitBoundery || MovingPlayers == 0 || Player[ CurrentPlayer ]->Finished ) {
					// If we ended a turn successufully, note the nearest drop zone;
					if ( !HitBoundery ) {
						Player[ CurrentPlayer ]->MyLastDropPos = FindNearestDrop( *Player[ CurrentPlayer ]->MyObject );
					}
					
					State = 5;
				}
				
				break;
			}
			case 5: {
				// Next Player //
				CurrentPlayer++;
				if ( CurrentPlayer >= Player.size() ) {
					CurrentPlayer = 0;
				}

				// Confirm all players aren't done //
				{
					int PlayersDone = 0;
					for ( size_t idx = 0; idx < Player.size(); idx++ ) {
						if ( Player[ idx ]->Finished ) {
							PlayersDone++;
						}
					}
					if ( PlayersDone == (int)Player.size() ) {
						LevelComplete = true;
						cMessageEntity::Current->BreakLoop = true;

						// All done, so lets calculate bonus //
						
						// Calculate Lowest Stroke //
						int LowestStroke = 10;
						for ( size_t idx = 0; idx < Player.size(); idx++ ) {
							if ( Player[ idx ]->Stroke < LowestStroke ) {
								LowestStroke = Player[ idx ]->Stroke;
							}
						}

						// Calculate Bonus //
						for ( size_t idx = 0; idx < Player.size(); idx++ ) {
							Player[ idx ]->Bonus = (5 - (Player[ idx ]->Stroke - LowestStroke)) * 100;
							if ( Player[ idx ]->Bonus < 0 )
								Player[ idx ]->Bonus = 0;
							
							if ( Player[ idx ]->Stroke == 10 ) {
								Player[ idx ]->Bonus = 0;
							}
								
							Player[ idx ]->Score += Player[ idx ]->Bonus;
						}
					}
				}
				
				// Change State, to ask player for his control (input) //
				State = 2;

				break;
			}
		};
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const Vector2D cGolfGameEngine::FindNearestDrop( const Engine2D::cDynamicCollection& Obj ) {
	Vector2D Pos = Obj.Component[ 0 ].Body.BoundingRect.Center();
	Real BestDistance = (Pos - StartPoint->Pos).MagnitudeSquared();
	Vector2D BestDrop = StartPoint->Pos;
	
	for ( size_t idx = 0; idx < DropPoint.size(); idx++ ) {
		Real Distance = (Pos - DropPoint[ idx ]->Pos).MagnitudeSquared();
		if ( Distance < BestDistance ) {
			BestDistance = Distance;
			BestDrop = DropPoint[ idx ]->Pos;
		}
	}
	
	return BestDrop;
}
// - ------------------------------------------------------------------------------------------ - //
