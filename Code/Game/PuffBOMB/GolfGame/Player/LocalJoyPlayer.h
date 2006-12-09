// - ------------------------------------------------------------------------------------------ - //
// LocalJoyPlayer //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_Player_LocalJoyPlayer_H__
#define __Game_PuffBOMB_Player_LocalJoyPlayer_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Player.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
class cLocalJoyPlayer: public cPlayer { 
public:
	int MyInputDevice;

public:
	cLocalJoyPlayer( Engine2D::cDynamicCollection* _MyObject, int _MyInputDevice = 0 );
	virtual ~cLocalJoyPlayer();
	
public:
	virtual bool Control();
	
	inline Input::cPadDevice& MyJoy() {
		return Input::Pad[ MyInputDevice ];
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Player_LocalJoyPlayer_H__ // 
// - ------------------------------------------------------------------------------------------ - //
