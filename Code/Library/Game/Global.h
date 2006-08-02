// - ------------------------------------------------------------------------------------------ - //
// Global //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_Global_H__
#define __Game_Global_H__
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/ClassDesigner.h>

#include <vector>

#include <Geometry/Real.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //

class cGlobal {
public:
	static Real Top;
	static Real Bottom;
	static Real Left;
	static Real Right;

	static int HudH;
	static int HudW;
		
	static Vector2D Origin;
	static int ScreenW;
	static int ScreenH;
	
	static Real HudZoom;
	
	static Real Zoom;
	static Real EditorZoom;
	static bool IsEditMode;
	static bool IsMesh2DEditor;
	static bool Shutdown;	
	
	static Uint8 *key;
	
//	static SDL_Cursor *mouse;
	
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
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_Global_H__ //
// - ------------------------------------------------------------------------------------------ - //
