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
#ifdef EDITOR
// For FPS test //
#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <sstream>
// ------------ //
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
cGolfGameEngine::cGolfGameEngine() :
	CurrentPlayer( 0 ),
	State( 1 )
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
	 
 	LoadMap( "Maps/Golf/Level02.map" );
 	
 	DenseParticle.Clear();
 	SolidParticle.Clear();
 	
 	// Add the start point (temporarily) //
 	StartPoint = CreatePassiveInstance( 5, Vector2D( 0, 0 ) );
 	PassiveObject.push_back( StartPoint );
 	
 	// Add Players //
 	for ( int idx = 0; idx < 4; idx++ ) {
 		Engine2D::cDynamicCollection* MyCol = CreateCollectionInstance( 64, StartPoint->Pos );
 		AddCollection( MyCol );
 		Player.push_back( new cLocalJoyPlayer( MyCol ) );
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
void cGolfGameEngine::Step() {
	// Stuff my engine does before //
	// ... //
	
	// Original Engine Step Stuff //
	cEngine2D::Step();
	
	// Stuff my engine does after //
	TurnBasedPlay();

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
				Player[ CurrentPlayer ]->MyObject->Activate();

				State = 3;
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
					
					Engine2D::cEngine2D::Current->Impulse.push_back( 
						Engine2D::cImpulse(
							BombPos,
							// Inner Radius, Intensity, Tangent //
							Real( 0 ), Real( 30 ), Real( 0 ),
							// Outer Radius, Intensity, Tangent //
							Real( 512 ), Real( 0 ), Real( 0 )
							)
						);
					
					// Change State, to play it out //
					State = 4;
				}
				
				break;
			}
			case 4: {
				// Stage 4 - Acting on input (and waiting for the turn to end) ---------------- - //		
				Camera->UpdateTarget( Player[ CurrentPlayer ]->MyObject->Component[ 0 ].Body.BoundingRect.Center() );
				
				// If Turn is over //
				if ( Input::Pad[ 0 ].Button[ 0 ].Pressed() ) {
					// Next Player //
					CurrentPlayer++;
					if ( CurrentPlayer >= Player.size() ) {
						CurrentPlayer = 0;
					}
					
					// Change State, to ask player for his control (input) //
					State = 2;
				}
				
				break;
			}
		};
	}
}
// - ------------------------------------------------------------------------------------------ - //
