// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Global.h>
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
cMessageEntity::cMessageEntity()
{

}
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
			cGlobal::Shutdown = true;
		    //QuitGame( 0 );
		    break;

		default:
		    break;
		}
	}
	
	Input::Update();
	
	if( Input::Button[ KEY_F10 ].Pressed() ) {
	    cGlobal::Shutdown = true;
	}

}
// ---------------------------------------------------------------------------------------------- //
