// - ------------------------------------------------------------------------------------------ - //
// Global //
// - ------------------------------------------------------------------------------------------ - //
#include "Global.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Global {
	// - -------------------------------------------------------------------------------------- - //
	Real Top = Real( 540.0 );
	Real Bottom = Real( -540.0 );
	Real Left = Real( -960.0 );
	Real Right = Real( 960.0 );

	int HudH = Real( 1080.0 );
	int HudW = Real( 1920.0 );

	int ScreenW = 800;
	int ScreenH = 600;

	Real AspectRatio;
	
	int FrameClock;
	int FPS;
	int FrameRate = 100;
		
	Real HudZoom = 1302.5;
	
	bool Shutdown = false;
	// - -------------------------------------------------------------------------------------- - //
	
	int DebugDraw = flCollision;
	// - -------------------------------------------------------------------------------------- - //
	
};
/*// - ---------------------------------------------------------------------------------------- - //
Real Global::Top = Real( 540.0 );
Real Global::Bottom = Real( -540.0 );
Real Global::Left = Real( -960.0 );
Real Global::Right = Real( 960.0 );

int Global::HudH = Real( 1080.0 );
int Global::HudW = Real( 1920.0 );

int Global::ScreenW = 800;
int Global::ScreenH = 600;

Real Global::HudZoom = 1302.5;
std::vector< size_t > Global::SwitchTexture;

bool Global::IsEditMode = false;
	
bool Global::Shutdown = false;

int Global::CurEditor = 4;
	
Uint8 *Global::key;

int Global::DebugDraw = Global::flCollision;
// - ------------------------------------------------------------------------------------------ - //
Global::cGlobal( int _ScreenW, int _ScreenH )
{
	ScreenW = _ScreenW;
	ScreenH = _ScreenH;
	
	DebugDraw = 0;//flCollision;
	
	Log( LOG_HIGHEST_LEVEL, 
		"Global entity created.\n" );

}
// - ------------------------------------------------------------------------------------------ - //
*/
