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

Real cGlobal::HudZoom = 1302.5;
std::vector< size_t > cGlobal::SwitchTexture;

bool cGlobal::IsEditMode = false;
	
bool cGlobal::Shutdown = false;

int cGlobal::CurEditor = 4;
	
Uint8 *cGlobal::key;

int cGlobal::DebugDraw = cGlobal::flCollision;
// - ------------------------------------------------------------------------------------------ - //
cGlobal::cGlobal( int _ScreenW, int _ScreenH )
{
	ScreenW = _ScreenW;
	ScreenH = _ScreenH;
	
	DebugDraw = 0;//flCollision;
	
	Log( LOG_HIGHEST_LEVEL, 
		"Global entity created.\n" );

}
// - ------------------------------------------------------------------------------------------ - //
