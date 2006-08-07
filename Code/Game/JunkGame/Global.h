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
#define MAP_EDITOR 			4
#define COLLECTION_EDITOR 	5
#define BODY2D_EDITOR 		6
#define ANIMATION_EDITOR 	7
#define MESH2D_EDITOR 		8
// - ------------------------------------------------------------------------------------------ - //

class cGlobal {
public:
	static Real Top;
	static Real Bottom;
	static Real Left;
	static Real Right;

	static int HudH;
	static int HudW;
		
	static int ScreenW;
	static int ScreenH;
	
	static Real HudZoom;
	
	static bool IsEditMode;
	static bool Shutdown;	
	
	static int CurEditor;
		
	static Uint8 *key;
	
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
