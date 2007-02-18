// ---------------------------------------------------------------------------------------------- //
#include <cstdio>
#include <cstdlib>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <SDL/SDL.h>
// ---------------------------------------------------------------------------------------------- //
using namespace std;
// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------------------- //
#include <Util/Debug.h>
#include <Global.h>
// ---------------------------------------------------------------------------------------------- //
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SuperFlow.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern void QuitGame( int ReturnCode );
// ---------------------------------------------------------------------------------------------- //
void QuitGame( int ReturnCode ) {
	Log( 101, "Shutting down..." );
    SDL_Quit();
    exit( ReturnCode );
}
// ---------------------------------------------------------------------------------------------- //

// - ------------------------------------------------------------------------------------------ - //
bool IsActive = true;
bool IsSplitScreen = false;
// ---------------------------------------------------------------------------------------------- //

SDL_Surface* SetVideoMode() {
	// Get information about our video hardware // 
	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
	
	// In the incredibly unlikely case that we have no video hardware... // 
	if ( !VideoInfo ) {
	    Log( LOG_HIGHEST_LEVEL, "Video query failed: " << SDL_GetError() );
	    QuitGame( 1 );
	}

	// Construct our list of SDL video options //
#ifdef WINDOWED
	int VideoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE; // SDL_FULLSCREEN | SDL_RESIZABLE
#else // WINDOWED //
	int VideoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_FULLSCREEN; // SDL_FULLSCREEN | SDL_RESIZABLE  
#endif // WINDOWED //
	
	// Depeding on if our hardware supports a hardware framebuffer //
    if ( VideoInfo->hw_available )
		VideoFlags |= SDL_HWSURFACE;
    else
		VideoFlags |= SDL_SWSURFACE;
	
	// Hardware blitting support (a good thing) //
    if ( VideoInfo->blit_hw )
		VideoFlags |= SDL_HWACCEL;

	Global::ScreenW = 1920;
	Global::ScreenH = 1200;

#ifdef SCREEN_W
	Global::ScreenW = SCREEN_W;
#endif // SCREEN_W //

#ifdef SCREEN_H
	Global::ScreenH = SCREEN_H;
#endif // SCREEN_H //
	
	int ColorDepth = 32;
	Global::AspectRatio = Real( Global::ScreenW ) / Real( Global::ScreenH );
	
	// Pre window creation GL Attributes //
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	
//	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, true );	
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
//	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 32 );

//	SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 8 );
//	SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 8 );
//	SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 8 );
//	SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 8 );
	
	//SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
	//SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 ); 

//	SDL_GL_SetAttribute( SDL_GL_SUGGEST, SDL_GL_DOUBLEBUFFER | SDL_GL_Z_DEPTH | SDL_GL_RENDERMETHOD | SDL_GL_SAMPLE_BUFFERS | SDL_GL_SAMPLES );

	SDL_WM_SetCaption( "PuffBOMB", NULL );


//	float largest_supported_anisotropy;
//	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy); 
//-	Log( LOG_HIGHEST_LEVEL, "largest_supported_anisotropy: " << largest_supported_anisotropy );
	
	// Create our Screen //
	Log( LOG_HIGHEST_LEVEL, "Setting Video Mode: " << Global::ScreenW << "x" << Global::ScreenH );
	return SDL_SetVideoMode( Global::ScreenW, Global::ScreenH, ColorDepth, VideoFlags );	
}
// ---------------------------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------------------------- //
int main( int argc, char* argv[] ) {
	Log( LOG_HIGHEST_LEVEL, "" );
	Log( LOG_HIGHEST_LEVEL,
		"----- Game Initialized ------------------------------------------------" );
	Log( LOG_HIGHEST_LEVEL,
		"(" << argv[0] << ", " << argc << ")" );
	Log( LOG_HIGHEST_LEVEL, "" );

	// Initialize SDL //
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) ) {
	    Log( LOG_HIGHEST_LEVEL, "SDL initialization failed: " << SDL_GetError() );	    
	    QuitGame( 1 );
	}

	// Scan to see what Joysticks are available //
	Log( LOG_HIGHEST_LEVEL, "Number of Joysticks found: " << SDL_NumJoysticks() );
	for ( int idx = 0; idx < SDL_NumJoysticks(); idx++ ) {
		Log( LOG_HIGHEST_LEVEL, "- " << SDL_JoystickName( idx ) );
	}
	
	Log( LOG_HIGHEST_LEVEL, "" );

	// Acquire Input devices (Joysticks only really.  This prefer's 360 controllers) //
	Input::Init();
	
	Log( LOG_HIGHEST_LEVEL, "" );
	
	// Create our Screen //
	SDL_Surface* Surface = SetVideoMode();
	
	// Disable Vertical Sync //	 
/*	{
		typedef void (APIENTRY * WGLSWAPINTERVALEXT) ( int ) ;
				
		WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT) SDL_GL_GetProcAddress( "wglSwapIntervalEXT" ) ;
		if ( wglSwapIntervalEXT != 0 ) {
			// Disable vertical synchronisation :
			wglSwapIntervalEXT( 0 ) ;
		} 
	}*/
	
	Global::Shutdown = false;

	// Be sure creation didn't just fail //
    if ( !Surface ) {
	    Log( LOG_HIGHEST_LEVEL, "Video mode set failed: " << SDL_GetError() );
	    QuitGame( 1 );
	}

	{
		glCullFace( GL_BACK );
		glFrontFace( GL_CCW );
		// This enables backface culling // 
		glEnable( GL_CULL_FACE );
	
		glEnable( GL_LINE_SMOOTH );
//		glEnable( GL_POLYGON_SMOOTH );  // used in the bad anti-aliasing
		glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
		glLineWidth( 1.0 );
		
		glShadeModel( GL_SMOOTH );
//		glEnable( GL_DEPTH_TEST );
		glDisable( GL_DEPTH_TEST );
		glDepthFunc( GL_LEQUAL );
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		cSuperFlow SuperFlow;
	}

	QuitGame( 0 );
	return 0;
}
// ---------------------------------------------------------------------------------------------- //
