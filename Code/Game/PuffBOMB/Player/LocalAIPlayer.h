// - ------------------------------------------------------------------------------------------ - //
// LocalAIPlayer //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_Player_LocalAIPlayer_H__
#define __Game_PuffBOMB_Player_LocalAIPlayer_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Player.h"
// - ------------------------------------------------------------------------------------------ - //
class cLocalAIPlayer: public cPlayer { 
public:
public:
	cLocalAIPlayer();
	virtual ~cLocalAIPlayer();
	
public:
	virtual bool Control();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Player_LocalAIPlayer_H__ // 
// - ------------------------------------------------------------------------------------------ - //
