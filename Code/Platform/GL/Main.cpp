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
#include "Platform/Global.h"
// ---------------------------------------------------------------------------------------------- //
#include "Input/Input.h"
// ---------------------------------------------------------------------------------------------- //
#include <Util/Debug.h>

#include <Game/Global.h>
#include "Game.h"
#include "Editor/Editor.h"
#include <Particle2D/ParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //

// ---------------------------------------------------------------------------------------------- //
extern void QuitGame( int ReturnCode );
// ---------------------------------------------------------------------------------------------- //
void QuitGame( int ReturnCode ) {
    SDL_Quit();
    exit( ReturnCode );
}
// ---------------------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------------------- //
//bool Shutdown = false;

bool IsActive = true;
bool IsSplitScreen = false;
// ---------------------------------------------------------------------------------------------- //

//#ifdef EDITOR
//void GlobalInput( cEditor& Editor ) {
//#else // EDITOR //
void GlobalInput() {
//#endif // Editor //
	// Test for global keys //
	if ( Input::Button[ KEY_F10 ].Pressed() ) {
	    //QuitGame( 0 );
	    cGlobal::Shutdown = true;
	}
//	if ( Input::Button[ KEY_F7 ].Pressed() ) {
//		IsSplitScreen = false;
//	}
//	if ( Input::Button[ KEY_F8 ].Pressed() ) {
//		IsSplitScreen = true;
//	}
	#ifdef EDITOR
/*	if ( Input::Button[ KEY_F3 ].Pressed() ) {
		cGlobal::IsEditMode = !cGlobal::IsEditMode;

		if ( cGlobal::IsEditMode ) {
			Editor.MapEdit->ToggleEdit();
		}
		else {
			if ( cGlobal::IsMesh2DEditor ) {
				cGlobal::IsMesh2DEditor = false;
				Editor.MapEdit->ToggleEdit();
				cGlobal::IsEditMode = true;
			}
			else {
				Editor.MapEdit->ToggleGame();
			}
		}
		
		glViewport( 0, 0, Platform::ScreenW, Platform::ScreenH );
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( 45.0, Platform::AspectRatio, 1.0, 100000.0 ); 
		glMatrixMode(GL_MODELVIEW);
	}
	if ( Input::Button[ KEY_F2 ].Pressed() ) {
		
		glViewport( 0, 0, Platform::ScreenW, Platform::ScreenH );
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( 45.0, Platform::AspectRatio, 1.0, 100000.0 ); 
		glMatrixMode(GL_MODELVIEW);

	}*/
	if ( Input::Button[ KEY_ESC ].Pressed()  )
	{
		cGlobal::IsEditMode = false;
	}
	if( Input::Button[ KEY_F4 ] || Input::Button[ KEY_F5 ] || Input::Button[ KEY_F6 ]
	 || Input::Button[ KEY_F7 ] || Input::Button[ KEY_F8 ] )
	{
		cGlobal::IsEditMode = true;
	}

	
	#endif // EDITOR //	
}
// ---------------------------------------------------------------------------------------------- //
void MessageLoop() {
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
}
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
	int VideoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE; // SDL_FULLSCREEN | SDL_RESIZABLE | SDL_FULLSCREEN
#else // WINDOWED //
	int VideoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_FULLSCREEN; // SDL_FULLSCREEN | SDL_RESIZABLE | SDL_FULLSCREEN
#endif // WINDOWED //
	
	// Depeding on if our hardware supports a hardware framebuffer //
    if ( VideoInfo->hw_available )
		VideoFlags |= SDL_HWSURFACE;
    else
		VideoFlags |= SDL_SWSURFACE;
	
	// Hardware blitting support (a good thing) //
    if ( VideoInfo->blit_hw )
		VideoFlags |= SDL_HWACCEL;


// 4:3 Aspect Ratio // 

//	Platform::ScreenW = 320;
//	Platform::ScreenH = 240;

//	Platform::ScreenW = 640;
//	Platform::ScreenH = 480;

//	Platform::ScreenW = 800;
//	Platform::ScreenH = 600;

//	Platform::ScreenW = 1024;
//	Platform::ScreenH = 768;

//	Platform::ScreenW = 1400;
//	Platform::ScreenH = 1050;


// 5:4 Aspect Ratio // 

//	Platform::ScreenW = 1280;
//	Platform::ScreenH = 1024;

// 16:10 Aspect Ratio // 

	Platform::ScreenW = 1920;
	Platform::ScreenH = 1200;

//	Platform::ScreenW = 1680;
//	Platform::ScreenH = 1050;


// 16:9 Aspect Ratio // 
	// 720P Mode //
//	Platform::ScreenW = 1280;
//	Platform::ScreenH = 720;
	// 1080P Mode //
//	Platform::ScreenW = 1920;
//	Platform::ScreenH = 1080;


// Unknown Aspect Ratio //
	// 480P Mode //
//	Platform::ScreenW = 720;
//	Platform::ScreenH = 480;

#ifdef RICHARD
	Platform::ScreenW = 1280;
	Platform::ScreenH = 720;
#endif // RICHARD //

#ifdef SCREEN_W
	Platform::ScreenW = SCREEN_W;
#endif // SCREEN_X //

#ifdef SCREEN_H
	Platform::ScreenH = SCREEN_H;
#endif // SCREEN_X //

	int ColorDepth = 32;
	Platform::AspectRatio = Real( Platform::ScreenW ) / Real( Platform::ScreenH );
	
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
	
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 );	

//	SDL_GL_SetAttribute( SDL_GL_SUGGEST, SDL_GL_DOUBLEBUFFER | SDL_GL_Z_DEPTH | SDL_GL_RENDERMETHOD | SDL_GL_SAMPLE_BUFFERS | SDL_GL_SAMPLES );

	SDL_WM_SetCaption( "Spiders are cool, to eat", NULL );


	// Create our Screen //
	Log( LOG_HIGHEST_LEVEL, "Setting Video Mode: " << Platform::ScreenW << "x" << Platform::ScreenH );
	return SDL_SetVideoMode( Platform::ScreenW, Platform::ScreenH, ColorDepth, VideoFlags );	
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
//	{
//		typedef void (APIENTRY * WGLSWAPINTERVALEXT) ( int ) ;
//				
//		WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT) SDL_GL_GetProcAddress( "wglSwapIntervalEXT" ) ;
//		if ( wglSwapIntervalEXT != 0 ) {
//			// Disable vertical synchronisation :
//			wglSwapIntervalEXT( 0 ) ;
//		} 
//	}
	
	
	cGlobal::Shutdown = false;

	// Populates the particle factory with a number of particles //
	FlatParticle.Populate( 5000 );
	AdditiveParticle.Populate( 5000 );
	
	// Be sure creation didn't just fail //
    if ( !Surface ) {
	    Log( LOG_HIGHEST_LEVEL, "Video mode set failed: " << SDL_GetError() );
	    QuitGame( 1 );
	}

	// Master Loop //	
	while( !cGlobal::Shutdown ) {
		glCullFace( GL_BACK );
		glFrontFace( GL_CCW );
		// This enables backface culling //
		glEnable( GL_CULL_FACE );
	
		glEnable( GL_LINE_SMOOTH );
		glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
		glLineWidth( 1.5 );
		
		glShadeModel( GL_SMOOTH );
		glEnable( GL_DEPTH_TEST );
		glDepthFunc( GL_LEQUAL );
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		Log( LOG_HIGHEST_LEVEL, "Creating Objects..." );
		
		Log( LOG_HIGHEST_LEVEL, "Creating Game..." );
		cGame Game( Platform::ScreenW, Platform::ScreenH );
//		cGlobal::Zoom = Real( -32.0 );
		
		#ifdef EDITOR		
		Log( LOG_HIGHEST_LEVEL, "Creating Editor..." );
		cEditor Editor( Game );
		#endif // EDITOR //

//		glViewport( 0, 0, Platform::ScreenW, Platform::ScreenH );
//		glMatrixMode (GL_PROJECTION);
//		glLoadIdentity();
//		gluPerspective( Camera.FovY, Camera.Aspect, Camera.NearClip, Camera.FarClip ); 
//		glMatrixMode(GL_MODELVIEW); 
	//	cGlobal::Origin = Vector2D( 0, 0 );
		//cGlobal::Origin = -Game.Focus1->BoundingRect.Center();
		
		extern int GetTime();
		//int LastTime = GetTime();//SDL_GetTicks();//GetTime();
		int LastTime = SDL_GetTicks();
		
		Platform::FrameClock = LastTime;
		Platform::FPS = 0;
		int FramesPast = 0;
		
		// Standard Rendering Loop //
		while( !cGlobal::Shutdown ) {
			// The SDL Message Loop, correctly setting input flags and shutdown stuff //
			MessageLoop();
	
			// A whole bunch of complicated crap to give us a flexible framerate //			
			int FPS = 60;
			int MS = 1000 / FPS;
			
			//int ThisTime = GetTime();// SDL_GetTicks(); //GetTime();
			int ThisTime = SDL_GetTicks();// SDL_GetTicks(); //GetTime();
			
			if ( Platform::FrameClock + 1000 < ThisTime ) {
				Platform::FrameClock = ThisTime;
				Platform::FPS = FramesPast;
				FramesPast = 0;
			}
			if ( ThisTime - LastTime >= MS )  // !!!! //
			{
				int Loops = (ThisTime - LastTime) / MS;
				LastTime += Loops * MS;
				FramesPast++;
				// Step the engine //
				//for ( int idx = 0; idx < Loops; idx ++ )  // WTF!?
				{
					// Update this frames state of controls //
					Input::Update();
					//#ifdef EDITOR
					// Do our global input, cleaning up this function //
					//GlobalInput( Editor );
					//#else // EDITOR //
					GlobalInput();
					//#endif // EDITOR //
					
					// Step appropriately the editor or the game, depending on the mode //
					if( cGlobal::IsEditMode ) {
						// Editor Loopage //
					#ifdef EDITOR
						Editor.Step();
					#endif // EDITOR //
					}
					else
					{
						// Do Game Specific Debug Key Input //
						Game.Input();
						
						if ( Input::Button[ KEY_TAB ] ) {
							if ( Input::Button[ KEY_BACKSPACE ].Pressed() ) {
								break;
							}
						}
						
						if ( !Input::Button[ KEY_SPACE ] ) {
							// Normal Game Loopage //
							Game.Step();
						}
					}
				}
	
				// Draw the Game //
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				
				if( cGlobal::IsEditMode )
				{
					#ifdef EDITOR
				
					glDisable( GL_DEPTH_TEST );
								
					if( cGlobal::CurEditor == MESH2D_EDITOR )	
					{
		
						// Screen 1 (Left Side) //	
						glViewport( 0, 0, Real( Platform::ScreenW * 0.75), Platform::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, Platform::AspectRatio * Real(0.75), 1.0, 100000.0 ); 
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef( 	-Editor.Mesh2DEdit->Camera->Pos.x,
										-Editor.Mesh2DEdit->Camera->Pos.y,
										-Editor.Mesh2DEdit->Camera->Pos.z
									);
						
						Editor.Draw();


						// Screen 2 (Upper Right Screen) //
						glViewport(
							Real(Platform::ScreenW * 0.75 ),
							Real(Platform::ScreenH * Editor.Mesh2DEdit->UVHeight ),
							Real( Platform::ScreenW * Editor.Mesh2DEdit->UVWidth ),
							Platform::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, Editor.Mesh2DEdit->UVHeight, 1.0, 100000.0 );
						//gluPerspective( 45.0, 0.4, 1.0, 100000.0 );
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef(	-Editor.Mesh2DEdit->PreviewCamera->Pos.x,
										-Editor.Mesh2DEdit->PreviewCamera->Pos.y,
										-Editor.Mesh2DEdit->PreviewCamera->Pos.z
						);
		
						Editor.Mesh2DEdit->DrawPreview();
						
						
						// Screen 3 (Lower Right Screen) //
						glViewport(
							Real(Platform::ScreenW * 0.75),
							0,
							Real( Platform::ScreenW * Editor.Mesh2DEdit->UVWidth ),
							Real( Platform::ScreenH * Editor.Mesh2DEdit->UVHeight ) );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, 1.0, 1.0, 100000.0 );
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef(	-Editor.Mesh2DEdit->UVCamera->Pos.x,
										-Editor.Mesh2DEdit->UVCamera->Pos.y,
										-Editor.Mesh2DEdit->UVCamera->Pos.z
						);
						Editor.Mesh2DEdit->DrawTextureCoord();
						
						// Draw Hud Info //
						glViewport( 0, 0, Platform::ScreenW, Platform::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, Platform::AspectRatio, 1.0, 100000.0 ); 
						glMatrixMode(GL_MODELVIEW);
				
						glLoadIdentity();
						glTranslatef(	-Editor.Mesh2DEdit->HudCamera->Pos.x,
										-Editor.Mesh2DEdit->HudCamera->Pos.y,
										-Editor.Mesh2DEdit->HudCamera->Pos.z
						);
						Editor.Mesh2DEdit->HudDraw();
						
					}
					else if( cGlobal::CurEditor == COLLECTION_EDITOR )
					{

					}
					else if( cGlobal::CurEditor == BODY2D_EDITOR )
					{
						
					}
					else if( cGlobal::CurEditor == ANIMATION_EDITOR )
					{
						// Screen 1 (Left Side) //	
						glViewport( 0, 0, Real( Platform::ScreenW * 0.75), Platform::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, Platform::AspectRatio * Real(0.75), 1.0, 100000.0 ); 
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef( 	-Editor.AnimationEdit->Camera->Pos.x,
										-Editor.AnimationEdit->Camera->Pos.y,
										-Editor.AnimationEdit->Camera->Pos.z
									);
						
						Editor.Draw();


	/*					// Screen 2 (Upper Right Screen) //
						glViewport(
							Real(Platform::ScreenW * 0.75 ),
							Real(Platform::ScreenH * Editor.Mesh2DEdit->UVHeight ),
							Real( Platform::ScreenW * Editor.Mesh2DEdit->UVWidth ),
							Platform::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, Editor.Mesh2DEdit->UVHeight, 1.0, 100000.0 );
						//gluPerspective( 45.0, 0.4, 1.0, 100000.0 );
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef(	-Editor.AnimationEdit->PreviewCamera->Pos.x,
										-Editor.AnimationEdit->PreviewCamera->Pos.y,
										-Editor.AnimationEdit->PreviewCamera->Pos.z
						);
		
						Editor.Mesh2DEdit->DrawPreview();
						
						
						// Screen 3 (Lower Right Screen) //
						glViewport(
							Real(Platform::ScreenW * 0.75),
							0,
							Real( Platform::ScreenW * Editor.Mesh2DEdit->UVWidth ),
							Real( Platform::ScreenH * Editor.Mesh2DEdit->UVHeight ) );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, 1.0, 1.0, 100000.0 );
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef(	-Editor.AnimationEdit->UVCamera->Pos.x,
										-Editor.AnimationEdit->UVCamera->Pos.y,
										-Editor.AnimationEdit->UVCamera->Pos.z
						);
						Editor.Mesh2DEdit->DrawTextureCoord();
						*/
						// Draw Hud Info //
						glViewport( 0, 0, Platform::ScreenW, Platform::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, Platform::AspectRatio, 1.0, 100000.0 ); 
						glMatrixMode(GL_MODELVIEW);
				
						glLoadIdentity();
						glTranslatef(	-Editor.AnimationEdit->HudCamera->Pos.x,
										-Editor.AnimationEdit->HudCamera->Pos.y,
										-Editor.AnimationEdit->HudCamera->Pos.z
						);
						Editor.AnimationEdit->HudDraw();						
					}
					else // MAP_EDITOR //
					{
						// Draw Map Editor // 
						glLoadIdentity();
						glTranslatef( 	-Editor.MapEdit->Camera->Pos.x,
										-Editor.MapEdit->Camera->Pos.y,
										-Editor.MapEdit->Camera->Pos.z
									);
						Editor.Draw();
						
						// Draw Hud //
						glLoadIdentity();
						glTranslatef(	-Editor.MapEdit->HudCamera->Pos.x,
										-Editor.MapEdit->HudCamera->Pos.y,
										-Editor.MapEdit->HudCamera->Pos.z
									);
						Editor.MapEdit->HudDraw();

					}
					glEnable( GL_DEPTH_TEST );
					#endif // EDITOR //
				}
				else if( IsSplitScreen )
				{	
/*					// Screen 1 (Left Side) //	
					glViewport( 0, 0, Platform::ScreenW / 2, Platform::ScreenH );
					glMatrixMode (GL_PROJECTION);
					glLoadIdentity();
					gluPerspective( 45.0, Platform::AspectRatio / Real( 2.0 ), 1.0, 100000.0 ); 
					glMatrixMode(GL_MODELVIEW);
					
					glLoadIdentity();
					glTranslatef ( 0, 0, cGlobal::Zoom );
					
					cGlobal::Origin = -Game.Focus1->BoundingRect.Center();
					Game.Draw();
					
					// Screen 2 (Right Screen) //
					glViewport (Platform::ScreenW / 2, 0, Platform::ScreenW / 2, Platform::ScreenH);
					glMatrixMode (GL_PROJECTION);
					glLoadIdentity();
					gluPerspective( 45.0, Platform::AspectRatio / Real( 2.0 ), 1.0, 100000.0 );
					glMatrixMode(GL_MODELVIEW);
					
					glLoadIdentity();
					glTranslatef ( 0, 0, cGlobal::Zoom );
					
					cGlobal::Origin = -Game.Focus2->BoundingRect.Center();
					Game.Draw();*/
				}
				else
				{
					// Draw Game //
					Game.Camera->GetPos();

					glLoadIdentity();
					glTranslatef ( -Game.Camera->Pos.x, -Game.Camera->Pos.y, -Game.Camera->Pos.z );
					Game.Draw();
					
					// Draw Hud //
					glLoadIdentity();
					glTranslatef ( -Game.HudCamera->Pos.x, -Game.HudCamera->Pos.y, -Game.HudCamera->Pos.z );
					Game.HudDraw();
				}
				
			    SDL_GL_SwapBuffers();
			}
		}
	}
	
	QuitGame( 0 );
	return 0;
}
// ---------------------------------------------------------------------------------------------- //
