// - ------------------------------------------------------------------------------------------ - //
// ClockHud //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_Classic_ClockHud_H__
#define __Game_PuffBOMB_Classic_ClockHud_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Gui/Form.h>
// - ------------------------------------------------------------------------------------------ - //
class cClockHud  { 
private:
	class cClassicGameEngine* Engine;
public:
	cForm Hud;

	// Clock used for action mode frame counting //
	int FrameClock;
	bool FrameClockActive;
	// Clock used to make the : and numbers (on win) flicker //
	int FlickerClock;
	// Clock of the best time //
	int BestClock;

	// The number of bombs //
	int MaxBombCount;
	int BombCount;
	
public:
	cClockHud();
	~cClockHud();

public:
	void StartActionMode();
	void StartEditMode();
	void StartActiveFlicker();

	void SetBombs( const int _Count );

public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Classic_ClockHud_H__ // 
// - ------------------------------------------------------------------------------------------ - //
