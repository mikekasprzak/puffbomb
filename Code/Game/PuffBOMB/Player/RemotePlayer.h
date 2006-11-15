// - ------------------------------------------------------------------------------------------ - //
// RemotePlayer //
// An arbitrary player, I don't care what it is on the other end, but it's remote from me //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_Player_RemotePlayer_H__
#define __Game_PuffBOMB_Player_RemotePlayer_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Player.h"
// - ------------------------------------------------------------------------------------------ - //
class cRemotePlayer: public cPlayer { 
public:
public:
	cRemotePlayer();
	virtual ~cRemotePlayer();
	
public:
	virtual void Control();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Player_RemotePlayer_H__ // 
// - ------------------------------------------------------------------------------------------ - //
