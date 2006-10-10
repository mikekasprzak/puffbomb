// - ------------------------------------------------------------------------------------------ - //
// Global //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __FlowElements_Global_H__
#define __FlowElements_Global_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/ClassDesigner.h>

#include <Geometry/Real.h>
namespace Global {
	extern Real Top;
	extern Real Bottom;
	extern Real Left;
	extern Real Right;

	extern int HudH;
	extern int HudW;

	extern int ScreenW;
	extern int ScreenH;

	extern Real AspectRatio;
	
	extern int FrameClock;
	extern int FPS;
		
	extern Real HudZoom;
	
	extern bool Shutdown;	
	
	extern int DebugDraw;
	
	enum {
		flCollision = bit0,
		flExtraInfo = bit1,
	};

/*	static Uint8 *key;
	
	enum {
		flCollision = bit0,
		flExtraInfo = bit1,
	};
	
	static int DebugDraw;

	static std::vector< size_t > SwitchTexture;
public:
	
	int Member;
public:
	cGlobal( int _ScreenW, int _ScreenH );
	
	static void ToggleExtraDisplayInfo() {
		DebugDraw ^= flExtraInfo;		
	}
	
	static void ToggleCollisionDisplay() {
		DebugDraw ^= flCollision;		
	}
	*/
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __FlowElements_Global_H__ //
// - ------------------------------------------------------------------------------------------ - //
