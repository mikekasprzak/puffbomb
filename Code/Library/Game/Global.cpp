// - ------------------------------------------------------------------------------------------ - //
#include "Global.h"
#include <string>
// - ------------------------------------------------------------------------------------------ - //
Real cGlobal::Top = Real( 540.0 );
Real cGlobal::Bottom = Real( -540.0 );
Real cGlobal::Left = Real( -960.0 );
Real cGlobal::Right = Real( 960.0 );

int cGlobal::HudH = Real( 1080.0 );
int cGlobal::HudW = Real( 1920.0 );

int cGlobal::ScreenW = 800;
int cGlobal::ScreenH = 600;
//Vector2D cGlobal::Origin = Vector2D( 800, 600 );
	
Real cGlobal::HudZoom = 1302.5;
std::vector< size_t > cGlobal::SwitchTexture;
//Real cGlobal::Zoom;
//Real cGlobal::EditorZoom;
bool cGlobal::IsEditMode = false;

bool cGlobal::IsMesh2DEditor = false;
	
bool cGlobal::Shutdown = false;
	
Uint8 *cGlobal::key;

//SDL_Cursor *cGlobal::mouse;

int cGlobal::DebugDraw = cGlobal::flCollision;
// - ------------------------------------------------------------------------------------------ - //
cGlobal::cGlobal( int _ScreenW, int _ScreenH )
{
	ScreenW = _ScreenW;
	ScreenH = _ScreenH;
//	Origin = Vector2D( _ScreenW >> 1, _ScreenH >> 1 );
//	Zoom = Real::Zero;
	
	DebugDraw = 0;//flCollision;
	
	Log( LOG_HIGHEST_LEVEL, 
		"Global entity created.\n" );
		
//	mouse = SDL_GetCursor();
}
// - ------------------------------------------------------------------------------------------ - //
