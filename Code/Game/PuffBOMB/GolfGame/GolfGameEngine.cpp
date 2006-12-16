// - ------------------------------------------------------------------------------------------ - //
#include "GolfGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Player/LocalJoyPlayer.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
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
cGolfGameEngine::cGolfGameEngine() :
	StartPoint( 0 ),
	CurrentPlayer( 0 ),
	State( 1 ),
	HitBoundery( false ),
 	ElementAnimator( "OldPuff.anim" )
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
	 
 	LoadMap( "Maps/Golf/Level02.map" );
 	
 	DenseParticle.Clear();
 	SolidParticle.Clear();
 	
	 	
 	// Add the start point (temporarily) //
// 	StartPoint = CreatePassiveInstance( 5, Vector2D( 0, 0 ) );
// 	PassiveObject.push_back( StartPoint );
 	
 	// Add Players //
 	for ( int idx = 0; idx < 4; idx++ ) {
 		Engine2D::cDynamicCollection* MyCol = CreateCollectionInstance( 64, StartPoint->Pos );
 		AddCollection( MyCol );
 		Player.push_back( new cLocalJoyPlayer( MyCol ) );
 		Player.back()->MyLastDropPos = StartPoint->Pos;
 		MyCol->Deactivate();
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
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cGolfGameEngine::Message( int Msg, Engine2D::cDynamicCollection* Sender ) {
	switch ( Msg ) {
		// I am at the end of the level //
		case 2: {
			//CharacterAtEndZone++;
			Sender->Deactivate();

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
				Player[ CurrentPlayer ]->AddStroke();
			}
			// Deactivate this player, to dissapear and stop moving //
			Sender->Deactivate();
			
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Sender->SetPos( Player[ idx ]->MyLastDropPos );
					break;
				}	
			}
			
			//Sender->SetPos( StartPoint->Pos );			
			
			break;
		};
		// Player 'Go To Nearest Drop' Zone //
		case 5: {
			Log( 10, "+ Player hit a 'Go To Nearest Drop' Zone" );
			if ( Sender == Player[ CurrentPlayer ]->MyObject ) {
				HitBoundery = true;

				// We went out of bounds, add a stroke //
				Player[ CurrentPlayer ]->AddStroke();
			}
			Sender->Deactivate();
			Sender->SetPos( FindNearestDrop( *Sender ) );
			
			break;
		};


		// Coin //
		case 10: {
			Log( 10, "+ Coin 50" );
			// Find this players last drop position //
			for ( size_t idx = 0; idx < Player.size(); idx++ ) {
				if ( Sender == Player[ idx ]->MyObject ) {
					Player[ idx ]->AddScore( 50 );
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
					Player[ idx ]->AddScore( 100 );
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
					Player[ idx ]->AddScore( 150 );
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
					Player[ idx ]->AddScore( 250 );
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
					Player[ idx ]->AddScore( 500 );
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
	};
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGolfGameEngine::Step() {
	// Stuff my engine does before //
	HitBoundery = false;
	
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
			
		// Cursor //
		Gfx::Circle( CursorPos, Real( 3 ), Gfx::RGBA( 255, 255, 255, 255 ) );
		
		// Inner Circle //
		Gfx::Circle( CharacterCenter, Real( 128 ), Gfx::RGBA( 0, 255, 0, 255 ) );
		
		// Outer Circle //
		Gfx::Circle( CharacterCenter, Real( 512 ), Gfx::RGBA( 255, 0, 0, 255 ) );

		Gfx::EnableDepth();
		Gfx::EnableTex2D();
	}

	Gfx::DisableDepth();
	
	SolidParticle.Draw();
	DenseParticle.Draw();

	Gfx::EnableDepth();

	HudCamera->Update();
	
	ElementTracker();
	
#ifdef EDITOR
	{
		//  DISPLAYS FPS  //
		std::stringstream Temp;
		Temp << Global::FPS;
		std::string TempString = Temp.str();
		
		Vector3D TempPos = Vector3D( Global::Left, Global::Top - Real( 45 ), 0.0 );
	
		cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 0, 200, 0, 255 ) );
	}
#endif // EDITOR //

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
				if ( Player[ CurrentPlayer ]->Stroke == 10 ) {
					Player[ CurrentPlayer ]->Finished = true;
				}
				
				if ( !Player[ CurrentPlayer ]->Finished ) {
					// Activate the character, if not already activated //
					Player[ CurrentPlayer ]->MyObject->Activate();
					// Since we're about to take action, add a stroke //
					Player[ CurrentPlayer ]->AddStroke();
					
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
							Real( 0 ), Real( 30 ), Real( 0 ),
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
				if ( Input::Pad[ 0 ].Button[ 3 ].Pressed() || HitBoundery || MovingPlayers == 0 || Player[ CurrentPlayer ]->Finished ) {
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
					if ( PlayersDone == Player.size() ) {
						cMessageEntity::Current->BreakLoop = true;
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
void cGolfGameEngine::ElementTracker()
{
	Real ZoomOffset = Real( Camera->Pos.z / Camera->HudZoom );
		
	for( size_t idx = 0; idx < Player.size(); idx++ )
	{
		if( idx != CurrentPlayer )
		{
			if( Player[ idx ]->GetRect() != Camera->ViewArea.ToRect() + Camera->Pos.ToVector2D() )
			{
				if( ( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset ) > Global::Bottom + Real( 76 ) &&
					( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset ) < Global::Top - Real( 76 ) )
				{
					if( Player[ idx ]->GetCenter().x < Player[ CurrentPlayer ]->GetCenter().x )
					{
						ElementAnimator.DrawQuad(
							Vector2D(
								Global::Left + Real( 64 ),
								( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset )
							)
						);
					}
					if( Player[ idx ]->GetCenter().x > Player[ CurrentPlayer ]->GetCenter().x )
					{
						ElementAnimator.DrawQuad(
							Vector2D(
								Global::Right - Real( 64 ),
								( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset )
							)
						);
					}					
				}
				else if( ( ( Player[ idx ]->GetCenter().x - Camera->Pos.x ) / ZoomOffset ) > Global::Left + Real( 64 ) &&
					( ( Player[ idx ]->GetCenter().x - Camera->Pos.x ) / ZoomOffset ) < Global::Right - Real( 64 ) )
				{
					if( Player[ idx ]->GetCenter().y < Player[ CurrentPlayer ]->GetCenter().y )
					{
						ElementAnimator.DrawQuad(
							Vector2D( 
								( ( Player[ idx ]->GetCenter().x - Camera->Pos.x ) / ZoomOffset ),
								Global::Bottom + Real( 76 )
							)
						);
					}
					if( Player[ idx ]->GetCenter().y > Player[ CurrentPlayer ]->GetCenter().y )
					{
						ElementAnimator.DrawQuad(
							Vector2D( 
								( ( Player[ idx ]->GetCenter().x - Camera->Pos.x ) / ZoomOffset ),
								Global::Top - Real( 76 )
							)
						);
					}
				}
			}
		}	
	}
}
// - ------------------------------------------------------------------------------------------ - //
/*
				if( Player[ idx ]->GetCenter().x < Player[ CurrentPlayer ]->GetCenter().x )
				{
					if( ( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset ) > Global::Bottom + Real( 76 ) &&
						( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset ) < Global::Top - Real( 76 ) )
					{
						ElementAnimator.DrawQuad(
							Vector2D(
								Global::Left + Real( 64 ),
								( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset )
							)
						);
					}
					else
					{
							
					}
				}
				if( Player[ idx ]->GetCenter().x > Player[ CurrentPlayer ]->GetCenter().x )
				{
					ElementAnimator.DrawQuad(
						Vector2D(
							Global::Right - Real( 64 ),
							( ( Player[ idx ]->GetCenter().y - Camera->Pos.y ) / ZoomOffset )
						)
					);
				}

				if( Player[ idx ]->GetCenter().y < Player[ CurrentPlayer ]->GetCenter().y )
				{
					ElementAnimator.DrawQuad(
						Vector2D( 
							( ( Player[ idx ]->GetCenter().x - Camera->Pos.x ) / ZoomOffset ),
							Global::Bottom + Real( 76 )
						)
					);
				}
				if( Player[ idx ]->GetCenter().y > Player[ CurrentPlayer ]->GetCenter().y )
				{
					ElementAnimator.DrawQuad(
						Vector2D( 
							( ( Player[ idx ]->GetCenter().x - Camera->Pos.x ) / ZoomOffset ),
							Global::Top - Real( 76 )
						)
					);
				}*/
