// - ------------------------------------------------------------------------------------------ - //
#include "SuperFlow.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef EDITOR
#include <Editor/Editor.h>
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/AnimParticleFactory.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SplashScreen/SplashScreen.h>
// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGame/ClassicGame.h"
#include "GolfGame/GolfGame.h"

#include <MainMenu/MainMenu.h>
#include <PlayerSelect/PlayerSelect.h>
#include <LevelEnd/LevelEnd.h>

// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/DirectoryCache.h>
#include <Util/String.h>
// - ------------------------------------------------------------------------------------------ - //
// Use an ENUM to generate unique numbers for each SuperFlow State //
/*enum {
	// Dummy state, so you can bounds check the generated state numbers //
	stFirstState = 0,
	
	// Super-Flow States (of the U-S-A) //
	stMainMenu,
	stSykhronicsSplash,
	stStartGame,
	stEditor,
	
	// Dummy state, so you can bounds check the generated state numbers //
	stLastState
};*/
#define stSykhronicsSplash 0
#define stMainMenu 1
#define stBackMainMenu 7
#define stClassicGame 2
#define stGolfGame 4
#define stGolfPlayers 6
#define stEditor 3

// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cSuperFlow::cSuperFlow() :
	State( stMainMenu ),
	ClassicPath( "Maps/Classic/" ),
	GolfPath( "Maps/Golf/" ),
	Players( 4 ),
	CurClassicMap( 0 ),
	CurGolfMap( 0 ),
	CurrentStartPlayer( 0 )
{
	SetHudData();
	
	// Populate the particle factorys with their max number of particles //
	AnimFlatParticle.Populate( 500 );
	AnimAdditiveParticle.Populate( 500 );

	SolidParticle.Populate( 20000 );
	DenseParticle.Populate( 20000 );

	Log( LOG_HIGHEST_LEVEL, "****** Loading Fonts ******" );
	cFonts::LoadFonts();
	
	FindMaps( ClassicPath, ClassicMaps );
	FindMaps( GolfPath, GolfMaps );
	
	srand ( time(NULL) );

	FXLibrary::InitAnims();

	StateFlow(); // This must be the last thing in the constructor //
}
// - ------------------------------------------------------------------------------------------ - //
void cSuperFlow::StateFlow()
{
	// While our means of global shutdown hasn't been triggered //
	while( !Global::Shutdown )
	{
		// Get up-to-date controller input (to not endlessly loop an exit) //
		Input::Update();

		// Switch/Branch between super flow states //
		switch( State )
		{
			// - ------------------------------------------------------------------------------ - //
			case stSykhronicsSplash:
			{
				// Display the Sykhronics spash screen //
				{
					cSplashScreen SplashScreen( "Textures/Menu/Sykhronics.pack.tx" );
				}
				State = stMainMenu;
				break;
			}
			// - ------------------------------------------------------------------------------ - //
			case stMainMenu:
			case stBackMainMenu:
			{
				CurClassicMap = 0;
				CurGolfMap = 0;
			
				// Display the MainMenu screen //
				{
					cMainMenu MainMenu;

					State = MainMenu.Form.SuperFlowState;
				}
				break;
			}
			// - ------------------------------------------------------------------------------ - //
			case stClassicGame:
			{
				
/*				if( CurClassicMap == 0 )
				{
					cSplashScreen SplashScreen( "Textures/Menu/ClassicControls.pack.tx", 10000, Real( 2.0 ) );
				}*/
								
				// Start the game //	
				int OldClassicMap = CurClassicMap;
				{
					cClassicGame Game( ClassicPath + ClassicMaps[ CurClassicMap ] );
					
					if( Game.Engine->LevelComplete ) // Re-add this if all the levels become beatable
					{	
						if( size_t( CurClassicMap ) < ClassicMaps.size() - 1 )
						{
							CurClassicMap++;
						}
						//cLevelEnd( Game.Engine );
					}
				}
				if( OldClassicMap == CurClassicMap )
				{
					State = stMainMenu;
				}
				else
				{
					State = stClassicGame;
				}
				
				break;
			}
			// - ------------------------------------------------------------------------------ - //
			case stGolfGame:
			{
			
/*			if( CurGolfMap == 0 )
			{
				cSplashScreen SplashScreen( "Textures/Menu/TournamentControls.pack.tx", 10000, Real( 2.0 ) );
			}*/
			
			// Start the game //	
				int OldGolfMap = CurGolfMap;
				{
					cGolfGame Game( GolfPath + GolfMaps[ CurGolfMap ], Players, CurrentStartPlayer );
					
					if( Game.Engine->LevelComplete ) // Re-add this if all the levels become beatable
					{	
						// Extract Golf Scores //
						for ( size_t idx = 0; idx < Players.size(); idx++ ) {
							Players[ idx ].Score = Game.Engine->Player[ idx ]->Score;
						}
						
						// Go te next map //
						if( size_t( CurGolfMap ) < GolfMaps.size() - 1 )
						{
							// Play the next level //
							CurGolfMap++;

							// Let the next player shoot first //
							CurrentStartPlayer++;
							if ( size_t( CurrentStartPlayer ) >= Players.size() ) {
								CurrentStartPlayer = 0;
							}
						}
						cLevelEnd( Game.Engine );
					}
				}
				if( OldGolfMap == CurGolfMap )
				{
					State = stMainMenu;
				}
				else
				{
					State = stGolfGame;
				}				
				break;
			}
			// - ------------------------------------------------------------------------------ - //
			case stEditor:
			{
				#ifdef EDITOR
				// Creating Editor //
				{
					Log( LOG_HIGHEST_LEVEL, "Creating Editor..." );
					cEditor Editor;
				}
				#endif // EDITOR //
				
				State = stMainMenu;
				break;
			}
			// - ------------------------------------------------------------------------------ - //
			case stGolfPlayers:
			{
				// Display the Player Select screen //
				{
					cPlayerSelect PlayerSelect;
					
					if( PlayerSelect.Form.Focus <= 4 )
					{
						Players.clear();
						
						Players.resize( PlayerSelect.Form.Focus + 1 );
					}
					
					State = PlayerSelect.Form.SuperFlowState;
				}
				break;
			}
			// - ------------------------------------------------------------------------------ - //
			default:
			{
				Global::Shutdown = true;
				break;
			}
			// - ------------------------------------------------------------------------------ - //
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cSuperFlow::SetHudData()
{
	// Default is 16:9 Aspect Ratio
	Real HudZoom = 1302.5;
	
	// 16:9
	if( Global::AspectRatio > Real( 1.75 ) && Global::AspectRatio < Real( 1.81 ) )
	{
		HudZoom = 1302.5;

		Global::Top = Real( 540.0 );
		Global::Bottom = Real( -540.0 );
		Global::Left = Real( -960.0 );
		Global::Right = Real( 960.0 );
	}
	// 16:10
	else if( Global::AspectRatio > Real( 1.57 ) && Global::AspectRatio < Real( 1.63 ) )
	{
		HudZoom = 1447.0;
		
		Global::Top = Real( 600.0 );
		Global::Bottom = Real( -600.0 );
		Global::Left = Real( -960.0 );
		Global::Right = Real( 960.0 );

	}
	// 24:11 // 720x480 widescreen 480p
	else if( Global::AspectRatio > Real( 1.47 ) && Global::AspectRatio < Real( 1.53 ) )
	{
		HudZoom = 1158.0;
		
		Global::Top = Real( 480.0 );
		Global::Bottom = Real( -480.0 );
		Global::Left = Real( -720.0 );
		Global::Right = Real( 720.0 );

	}
	// 4:3
	else if( Global::AspectRatio > Real( 1.30 ) && Global::AspectRatio < Real( 1.36 ) )
	{
		HudZoom = 1266.0;
		
		Global::Top = Real( 525.0 );
		Global::Bottom = Real( -525.0 );
		Global::Left = Real( -700.0 );
		Global::Right = Real( 700.0 );

	}
	// 5:4
	else if( Global::AspectRatio > Real( 1.22 ) && Global::AspectRatio < Real( 1.28 ) )
	{
		HudZoom = 1234.0;
		
		Global::Top = Real( 512.0 );
		Global::Bottom = Real( -512.0 );
		Global::Left = Real( -640.0 );
		Global::Right = Real( 640.0 );

	}
	// 3:4 // Tablet pc res //
	else if( Global::AspectRatio > Real( 0.70 ) && Global::AspectRatio < Real( 0.79 ) )
	{
		HudZoom = 1690.5;
		
		Global::Top = Real( 700.0 );
		Global::Bottom = Real( -700.0 );
		Global::Left = Real( -525.0 );
		Global::Right = Real( 525.0 );
	}
	
	
	Global::HudH = Real( Global::Top * Real( 2.0 ) );
	Global::HudW = Real( Global::Right * Real( 2.0 ) );
	
	Global::HudZoom = HudZoom;
}
// - ------------------------------------------------------------------------------------------ - //
void cSuperFlow::FindMaps( const std::string& Path, std::vector< std::string >& Maps )
{
	
	// Find all the .map files //
	cDirectoryCache MapDirCache( Path );
	
	for( size_t idx = 0; idx < MapDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( MapDirCache.File[idx] ) == ".map" )
		{
			//std::string TmpString = String::FileName( MapDirCache.File[idx] );
			
			//Log( LOG_HIGHEST_LEVEL, "Map " << TmpString );
			Maps.push_back( MapDirCache.File[idx] );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
