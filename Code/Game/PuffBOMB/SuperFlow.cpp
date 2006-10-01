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
cSuperFlow::cSuperFlow()
{
	SetHudData();
	
	// Populate the particle factorys with their max number of particles //
	FlatParticle.Populate( 500 );
	AdditiveParticle.Populate( 500 );

	NewParticle.Populate( 40000 );

	// Display the Sykhronics spash screen //
	{
		cSplashScreen SplashScreen;
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
//void cSuperFlow::EngineFlow()
//{
/*	// Engine //
	Log( LOG_HIGHEST_LEVEL, "Creating Engine..." );
	Engine2D::cEngine2D Engine;

	int LastTime = GetTime();
	
	Platform::FrameClock = LastTime;
	Platform::FPS = 0;
	int FramesPast = 0;

	// Standard Rendering Loop //
	while( !cGlobal::Shutdown ) {

		MessageLoop();

		// A whole bunch of complicated crap to give us a flexible framerate //			
		int FPS = 60;
		int MS = 1000 / FPS;
		
		int ThisTime = GetTime();
		
		if ( Platform::FrameClock + 1000 < ThisTime ) {
			Platform::FrameClock = ThisTime;
			Platform::FPS = FramesPast;
			FramesPast = 0;
		}
		
		if ( ThisTime - LastTime >= MS ) {
			int Loops = (ThisTime - LastTime) / MS;
			LastTime += Loops * MS;
			FramesPast++;
			// Step the engine //
			for ( int idx = 0; idx < Loops; idx ++ ) {
				// Update controls //
				Input::Update();
				
				// Reset Hack //					
				if ( Input::Button[ KEY_TAB ] ) {
					if ( Input::Button[ KEY_BACKSPACE ].Pressed() ) {
						break;
					}
				}
				
				if ( !Input::Button[ KEY_SPACE ] ) {
					// Normal Game Loopage //
					Engine.Step();
				}
			}

			// Draw the Game //
			{
				Gfx::ClearColorDepth();

				// Draw Game //
				Engine.Draw();

				Gfx::Circle( Vector2D::Zero, Real( 25 ), Gfx::RGB( 255, 255, 255 ) );
				
				// Draw Hud //
				Engine.HudDraw();
			}
			
		    Gfx::SwapBuffers();
		}
	}*/
//}
// - ------------------------------------------------------------------------------------------ - //
