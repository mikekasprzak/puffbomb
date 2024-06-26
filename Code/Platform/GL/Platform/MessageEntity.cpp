// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Global.h>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
cMessageEntity* cMessageEntity::Current;
// - ------------------------------------------------------------------------------------------ - //
cMessageEntity::cMessageEntity() :
	EndTime( 0 ),
	HasEndTime( false ),
	BreakLoop( false )
{
	Current = this;
}
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
void cMessageEntity::MessageLoop() {
	
	bool IsActive = true;
	
	SDL_Event event;
	// Do Event Polling //
    while ( SDL_PollEvent( &event ) ) {
	    switch( event.type ) {
			case SDL_ACTIVEEVENT: {
				IsActive = event.active.gain != 0;
		    	
		    	break;
		    }
	    	case SDL_MOUSEBUTTONDOWN: {
	    		if ( event.button.button == 4 ) {
	    			Input::Mouse.Wheel--;
	    		}
	    		else if ( event.button.button == 5 ) {
	    			Input::Mouse.Wheel++;
	    		}
	    		
	    		break;
	    	}

		case SDL_QUIT:
			Global::Shutdown = true;
		    //QuitGame( 0 );
		    break;

		default:
		    break;
		}
	}
	
	GlobalInput();
}
// - ------------------------------------------------------------------------------------------ - //
void cMessageEntity::GlobalInput()
{
	if( Input::Button[ KEY_F10 ] ) {
	    Global::Shutdown = true;
	}
	if ( Input::Button[ KEY_ESC ] ) {
	    BreakLoop = true;
	}
	
	#ifdef EDITOR

/*	if ( Input::Button[ KEY_ESC ].Pressed()  )
	{
		Global::IsEditMode = false;
	}
	if( Input::Button[ KEY_F4 ] || Input::Button[ KEY_F5 ] || Input::Button[ KEY_F6 ]
	 || Input::Button[ KEY_F7 ] || Input::Button[ KEY_F8 ] )
	{
		Global::IsEditMode = true;
	}
*/
	#endif // EDITOR //
}
// ---------------------------------------------------------------------------------------------- //
void cMessageEntity::Work()
{
	Gfx::StandardBlend();
	
	int LastTime = GetTime();
	int BeginTime = LastTime;
	
	Global::FrameClock = LastTime;
	Global::FPS = 0;
	int FramesPast = 0;
	
//	MessageLoop();
//	Input::Update();

	// Standard Rendering Loop //
	while( !Global::Shutdown && !BreakLoop ) {
		MessageLoop();

		// A whole bunch of complicated crap to give us a flexible framerate //			
		int MSPerFrame = 1000 / Global::FrameRate;
			
		if ( Input::Button[ KEY_TAB ] ) {
			MSPerFrame = 1000 / 8;
		}
		
		int ThisTime = GetTime();

		if( HasEndTime )
		{
			if( ThisTime >= ( BeginTime + EndTime ) )
			{
				BreakLoop = true;
			}
		}
		if ( Global::FrameClock + 1000 < ThisTime ) {
			Global::FrameClock = ThisTime;
			Global::FPS = FramesPast;
			FramesPast = 0;
		}
		
		if ( ThisTime - LastTime >= MSPerFrame )
		{
			int Loops = (ThisTime - LastTime) / MSPerFrame;
			LastTime += Loops * MSPerFrame;
			FramesPast++;
			// Step the engine //
			//for ( int idx = 0; idx < Loops; idx ++ ) // This makes the game twitch // could be that 60 doesn't devide perfectly into 1000 //
			//for ( int idx = 0; idx < 2; idx ++ )
			{
				// Update controls //
				Input::Update();
				
				Step();
			}
			
			Gfx::ClearColorDepth();

			Draw();

		    Gfx::SwapBuffers();
		}
	}
}
// ---------------------------------------------------------------------------------------------- //
void cMessageEntity::Work( const int _EndTime )
{
	EndTime = _EndTime;
	HasEndTime = true;
	
	Work();
}
// ---------------------------------------------------------------------------------------------- //
