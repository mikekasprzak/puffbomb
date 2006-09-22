// - ------------------------------------------------------------------------------------------ - //
#include "SplashScreen.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h> // dont want to make this SDL dependent.  find out how to get time..
// - ------------------------------------------------------------------------------------------ - //
cSplashScreen::cSplashScreen()
{
	//GetTime();
	
	unsigned int EndTime = SDL_GetTicks() + ( 3600 );
	
	
	while( SDL_GetTicks() < EndTime )
	{
		Gfx::ClearColorDepth();
			
		Gfx::LoadIdentity();
		Gfx::Translate( 0 , 0, -900 );

		Gfx::Circle( Vector3D( Real::Zero, Real::Zero, Real::Zero ), Real( 10 ), Gfx::White() );
		
		
		Gfx::SwapBuffers();
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
