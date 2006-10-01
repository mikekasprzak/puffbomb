// - ------------------------------------------------------------------------------------------ - //
#include "SuperFlow.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
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
	
/*	// Display the Sykhronics spash screen //
	{
		cSplashScreen SplashScreen;
	}
	
	// Display the MainMenu screen //
	{
		cMainMenu MainMenu;
	}

#ifdef EDITOR
	{
		Log( LOG_HIGHEST_LEVEL, "Creating Editor..." );
		cEditor Editor;
	}
#endif // EDITOR //

	{
		Log( LOG_HIGHEST_LEVEL, "Creating Engine..." );
		Engine2D::cEngine2D Engine;
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cSuperFlow::StateFlow()
{
	while( !cGlobal::Shutdown )
	{
	//	Log( LOG_HIGHEST_LEVEL, "State " << State );
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
					MainMenu.ResetMenu();
					State = MainMenu.Form.DialogBox[ 0 ].SuperFlowState;
				}
				break;
			}
			case 2:
			{
				// Creating Engine //
				{
					Log( LOG_HIGHEST_LEVEL, "Creating Engine..." );
					Engine2D::cEngine2D Engine;
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
				cGlobal::Shutdown = true;
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
	if( Platform::AspectRatio > Real( 1.75 ) && Platform::AspectRatio < Real( 1.81 ) )
	{
		HudZoom = 1302.5;

		cGlobal::Top = Real( 540.0 );
		cGlobal::Bottom = Real( -540.0 );
		cGlobal::Left = Real( -960.0 );
		cGlobal::Right = Real( 960.0 );
	}
	// 16:10
	else if( Platform::AspectRatio > Real( 1.57 ) && Platform::AspectRatio < Real( 1.63 ) )
	{
		HudZoom = 1447.0;
		
		cGlobal::Top = Real( 600.0 );
		cGlobal::Bottom = Real( -600.0 );
		cGlobal::Left = Real( -960.0 );
		cGlobal::Right = Real( 960.0 );

	}
	// 4:3
	else if( Platform::AspectRatio > Real( 1.30 ) && Platform::AspectRatio < Real( 1.36 ) )
	{
		HudZoom = 1266.0;
		
		cGlobal::Top = Real( 525.0 );
		cGlobal::Bottom = Real( -525.0 );
		cGlobal::Left = Real( -700.0 );
		cGlobal::Right = Real( 700.0 );

	}
	
	// 5:4
	else if( Platform::AspectRatio > Real( 1.22 ) && Platform::AspectRatio < Real( 1.28 ) )
	{
		HudZoom = 1234.0;
		
		cGlobal::Top = Real( 512.0 );
		cGlobal::Bottom = Real( -512.0 );
		cGlobal::Left = Real( -640.0 );
		cGlobal::Right = Real( 640.0 );

	}
	// 3:4 // Tablet pc res //
	else if( Platform::AspectRatio > Real( 0.70 ) && Platform::AspectRatio < Real( 0.79 ) )
	{
		HudZoom = 1690.5;
		
		cGlobal::Top = Real( 700.0 );
		cGlobal::Bottom = Real( -700.0 );
		cGlobal::Left = Real( -525.0 );
		cGlobal::Right = Real( 525.0 );
	}
	
	
	cGlobal::HudH = Real( cGlobal::Top * Real( 2.0 ) );
	cGlobal::HudW = Real( cGlobal::Right * Real( 2.0 ) );
	
	cGlobal::HudZoom = HudZoom;
}
// - ------------------------------------------------------------------------------------------ - //
