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
#include <Particle2D/ParticleFactory.h>
#include <Particle2D/NewParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SplashScreen/SplashScreen.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Game.h>
#include <MainMenu/MainMenu.h>
// - ------------------------------------------------------------------------------------------ - //
cSuperFlow::cSuperFlow() :
	State( 0 )
{
	SetHudData();
	
	// Populate the particle factorys with their max number of particles //
	FlatParticle.Populate( 500 );
	AdditiveParticle.Populate( 500 );

	NewParticle.Populate( 40000 );

	Log( LOG_HIGHEST_LEVEL, "****** Loading Fonts ******" );
	cFonts::LoadFonts();
	
	StateFlow();
	
}
// - ------------------------------------------------------------------------------------------ - //
void cSuperFlow::StateFlow()
{
	while( !Global::Shutdown )
	{
		Input::Update();

		switch( State )
		{
			case 0:
			{
				// Display the Sykhronics spash screen //
				{
					cSplashScreen SplashScreen;
				}
				State = 1;
				break;
			}
			case 1:
			{
				// Display the MainMenu screen //
				{
					cMainMenu MainMenu;
					State = MainMenu.Form.DialogBox[ 0 ].SuperFlowState;
				}
				break;
			}
			case 2:
			{
				// Start the game //
				{
					cGame Game;
				}
				State = 1;
				break;
			}
			case 3:
			{
				// Creating Editor //
				{
					Log( LOG_HIGHEST_LEVEL, "Creating Editor..." );
					cEditor Editor;
				}
				State = 1;
				break;
			}
			default:
			{
				Global::Shutdown = true;
				break;
			}
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
