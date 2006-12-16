// - ------------------------------------------------------------------------------------------ - //
#include <allegro.h>
#include <alleggl.h>

#include <GL/glu.h>
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
using namespace std;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include "Util/Input.h"
#include "Game.h"
#include "Editor/Editor.h"
#include "Phiz/Global.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Platform/Mouse.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void SwitchIn() {
	Log( LOG_WINDOW_FOCUS, "Window in focus" );
}
// - ------------------------------------------------------------------------------------------ - //
void SwitchOut() {
	Log( LOG_WINDOW_FOCUS, "Window lost focus" );
}
// - ------------------------------------------------------------------------------------------ - //
bool ShutDown;
// - ------------------------------------------------------------------------------------------ - //
void ShutDownFunc() {
	ShutDown = true;
}
// - ------------------------------------------------------------------------------------------ - //
int FramesPassed;
// - ------------------------------------------------------------------------------------------ - //
void TimerInterrupt() {
	FramesPassed++;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( /*int argc, char* argv[]*/ ) {
	Log( LOG_HIGHEST_LEVEL, "----- Game Initialized -------------------------" );
		
	allegro_init();

	install_allegro_gl();

	install_keyboard();
	install_joystick( JOY_TYPE_AUTODETECT );
	three_finger_flag = false;
	install_mouse();
	install_timer();

	srand( time (0) );

	set_window_title( "Spider Game" );

	// 1.33 Aspect Ratio // 
	// Regular Mode //
	// (Doesn't crash) //
//	Global::ScreenW = 800;
//	Global::ScreenH = 600;
	// 720P PC Friendly Mode //
	// (Doesn't crash) //
//	Global::ScreenW = 1024;
//	Global::ScreenH = 768;
	// Max resolution of monitor //
	// (Crashes) //
//	Global::ScreenW = 1280;
//	Global::ScreenH = 1024;

	// (Aparently Does crash) //
//	Global::ScreenW = 1200;
//	Global::ScreenH = 900;

	// 480P Mode //
	// (Crashes) //
//	Global::ScreenW = 720;
//	Global::ScreenH = 480;
	// 720P Mode //
	// (Doesn't crash) //
//	Global::ScreenW = 1280;
//	Global::ScreenH = 720;
	// 1080P Mode //
	// (Doesn't crash) //
//	Global::ScreenW = 1920;
//	Global::ScreenH = 1080;

	Global::ScreenW = 1920;
	Global::ScreenH = 1200;


	// (Doesn't crash) //
//	Global::ScreenW = 1220;
//	Global::ScreenH = 686;

	Global::ScreenW = Global::ScreenW;
	Global::ScreenH = Global::ScreenH;

	Real AspectRatio = Real( Global::ScreenW ) / Real( Global::ScreenH );
	//Real ScreenSize = Real( Global::ScreenW / 40 ); // 40 being a scale ratio that makes 1280 equal to 32 //
	Real ScreenSize = Real( 32 );
	Vector2D Dimension( ScreenSize, ScreenSize * (Real::One / AspectRatio) );
	
	Log( LOG_HIGHEST_LEVEL, "There are " << num_joysticks << " Joysticks connected" );
	
	for ( int idx = 0; idx < num_joysticks; idx++ ) {
		//Log( LOG_HIGHEST_LEVEL, "Sticks: " joy[ idx ].num_sticks << " " << joy[ idx ].num_buttons );
		// debug!! //
		cout << "Sticks: " << joy[ idx ].num_sticks << "  Buttons: " << joy[ idx ].num_buttons << endl;
		for ( int idx2 = 0; idx2 < joy[ idx ].num_sticks; idx2++ ) {
			for ( int idx3 = 0; idx3 < joy[ idx ].stick[ idx2 ].num_axis; idx3++ ) {
				cout << joy[ idx ].stick[ idx2 ].name << " Axis \"" << joy[ idx ].stick[ idx2 ].axis[ idx3 ].name << "\": " << joy[ idx ].stick[ idx2 ].num_axis << endl;
			}			
		}
	}

	//int ColorDepth = 16;
	int ColorDepth = 32;
	Log( LOG_HIGHEST_LEVEL, "Setting Video Mode " << Global::ScreenW << "x" << Global::ScreenH << "x" << ColorDepth << " ..." );	
	
		
    allegro_gl_set(AGL_DOUBLEBUFFER, true);
    allegro_gl_set(AGL_Z_DEPTH, 32);
    allegro_gl_set(AGL_RENDERMETHOD, true);
	allegro_gl_set(AGL_SAMPLE_BUFFERS, 1);
    allegro_gl_set(AGL_SAMPLES, 4);
    allegro_gl_set(AGL_SUGGEST, AGL_DOUBLEBUFFER | AGL_Z_DEPTH | AGL_RENDERMETHOD | AGL_SAMPLE_BUFFERS | AGL_SAMPLES );

    allegro_gl_set( AGL_COLOR_DEPTH, ColorDepth );
	//set_gfx_mode(GFX_OPENGL_WINDOWED, Global::ScreenW, Global::ScreenH, 0, 0);
	set_gfx_mode(GFX_OPENGL_FULLSCREEN, Global::ScreenW, Global::ScreenH, 0, 0);

	glEnable( GL_LINE_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glLineWidth( 1.5 );

	allegro_gl_begin();

	glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glDepthMask( GL_TRUE );

    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
//    glMatrixMode(GL_PROJECTION);
//	glFrustum( -Dimension.x, Dimension.x, -Dimension.y, Dimension.y, 1.0, 800.0 );
//	glMatrixMode(GL_MODELVIEW);
	
//	glViewport(0, 0, Global::ScreenW, Global::ScreenH);		/* Reset The Current Viewport And Perspective Transformation */


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	bool IsSplitScreen = false;

	{
		Log( LOG_HIGHEST_LEVEL, "Creating Objects..." );
		
		{
			Log( LOG_HIGHEST_LEVEL, "Creating Game..." );
			cGame Game( Global::ScreenW, Global::ScreenH );
			Global::Zoom = Real( -32.0 );

			Log( LOG_HIGHEST_LEVEL, "Creating Editor..." );
			cEditor Editor( Game );

			install_int( TimerInterrupt, 1 );
			set_close_button_callback( ShutDownFunc );
			set_display_switch_callback( SWITCH_IN, SwitchIn );
			set_display_switch_callback( SWITCH_OUT, SwitchOut );

			ShutDown = false;
	
			// Using the windows api call timeGetTime(), wraped behind GetTime //
//			int LastTime = GetTime();
//			while( !key[ KEY_ESC ] ) {
//				int ThisTime = GetTime();

			Log( LOG_HIGHEST_LEVEL, "----- Starting Game... -------------------------" );
			// Using the Allegro Thread based timer //
			int LastTime = FramesPassed;//GetTime();
			while( !key[ KEY_ESC ] && !ShutDown ) {
				int ThisTime = FramesPassed;//GetTime();
				
				if ( ThisTime - LastTime >= 10 ) {
					glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
										
					int Loops = (ThisTime - LastTime) / 10;
					LastTime += Loops * 10;
					for ( int idx = 0; idx < Loops; idx ++ ) {
						input::Poll();
						Global::Mouse.Update();

						if( key[ KEY_F1 ] )
						{
							while( key[ KEY_F1 ] );
							IsSplitScreen = !IsSplitScreen;
						}
						if( key[ KEY_F12 ] )
						{
							while( key[ KEY_F12 ] );
							if( Global::IsEditMode )
							{
								Editor.MapEdit->ToggleGame();
								
							}
							else
							{
								Editor.MapEdit->ToggleEdit();
							}
							Global::IsEditMode = !Global::IsEditMode;
							
						}
						
						if( Global::IsEditMode )
						{
							Editor.Step();
						}
						else
						{
							Game.Step();					
						}
					}
					if( Global::IsEditMode )
					{
						glDisable( GL_DEPTH_TEST );
						
						if( Global::IsMeshEditor )	
						{
							// Screen 1 (Left Side) //	
							glViewport( 0, 0, Real( Global::ScreenW * 0.75), Global::ScreenH );
							glMatrixMode (GL_PROJECTION);
							glLoadIdentity();
							gluPerspective( 45.0, AspectRatio * Real(0.75), 1.0, 100000.0 ); 
							glMatrixMode(GL_MODELVIEW);
							
							glLoadIdentity();
							glTranslatef ( 0, 0, Global::EditorZoom );
							
							Editor.Draw();
							if( mouse_x < (Global::ScreenW * 0.75) )
							{
								Editor.MeshEdit->DrawLeftMouse();
							}
							// Screen 2 (Right Screen) //
							glViewport(
								Real(Global::ScreenW * 0.75),
								0,
								Real( Global::ScreenW * 0.25 ),
								Global::ScreenH);
							glMatrixMode (GL_PROJECTION);
							glLoadIdentity();
							gluPerspective( 45.0, AspectRatio / Real( 4.0 ), 1.0, 100000.0 );
							glMatrixMode(GL_MODELVIEW);
							
							glLoadIdentity();
							glTranslatef ( 0, 0, -900 );
							
							Editor.MeshEdit->DrawPreview();
							if( mouse_x > (Global::ScreenW * 0.73) )
							{
								Editor.MeshEdit->DrawRightMouse();
							}
						}
						else
						{
							glViewport( 0, 0, Global::ScreenW, Global::ScreenH );
							glMatrixMode (GL_PROJECTION);
							glLoadIdentity();
							gluPerspective( 45.0, AspectRatio, 1.0, 100000.0 ); 
							glMatrixMode(GL_MODELVIEW);
							
							glLoadIdentity();
							glTranslatef ( 0, 0, Global::EditorZoom );
							
							Editor.Draw();
						}
						glEnable( GL_DEPTH_TEST );
						
					}
					else if( IsSplitScreen )
					{	
						// Screen 1 (Left Side) //	
						glViewport( 0, 0, Global::ScreenW / 2, Global::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, AspectRatio / Real( 2.0 ), 1.0, 10000.0 ); 
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef ( 0, 0, Global::Zoom );
						
						Global::Origin = -Game.Focus1->BoundingRect.Center();
						Game.Draw();
						
						// Screen 2 (Right Screen) //
						glViewport (Global::ScreenW / 2, 0, Global::ScreenW / 2, Global::ScreenH);
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, AspectRatio / Real( 2.0 ), 1.0, 10000.0 );
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef ( 0, 0, Global::Zoom );
						
						Global::Origin = -Game.Focus2->BoundingRect.Center();
						Game.Draw();
					}
					else
					{
						// One Screen Only //
						glViewport( 0, 0, Global::ScreenW, Global::ScreenH );
						glMatrixMode (GL_PROJECTION);
						glLoadIdentity();
						gluPerspective( 45.0, AspectRatio, 1.0, 10000.0 ); 
						glMatrixMode(GL_MODELVIEW);
						
						glLoadIdentity();
						glTranslatef ( 0, 0, Global::Zoom );
						
						Global::Origin = -Game.Focus1->BoundingRect.Center();
						Game.Draw();
					}
				}

				rest( 0 );
				allegro_gl_flip();

			};
			Log( LOG_HIGHEST_LEVEL, "----- Shutting Down... -------------------------" );
			Log( LOG_HIGHEST_LEVEL, "Destroying Game..." );
			
			remove_int( TimerInterrupt );
		}
		Log( LOG_HIGHEST_LEVEL, "Game destroyed." );
	}
	//destroy_bitmap( Buffer );
	allegro_gl_end();
	Log( LOG_HIGHEST_LEVEL, "=====allegro_gl_end finished===================" );
	allegro_exit();
	Log( LOG_HIGHEST_LEVEL, "=====allegro_exit finished====================" );

	return 0;	
}
END_OF_MAIN();
// - ------------------------------------------------------------------------------------------ - //
