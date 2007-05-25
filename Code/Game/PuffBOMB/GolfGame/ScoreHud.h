// - ------------------------------------------------------------------------------------------ - //
// ScoreHud //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_Golf_ScoreHud_H__
#define __Game_PuffBOMB_Golf_ScoreHud_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Gui/Form.h>
// - ------------------------------------------------------------------------------------------ - //
class cScoreHud  { 
private:
	class cGolfGameEngine* Engine;
public:
	cForm Hud;
	int Score[4];
	int InterpolatingScore[4];
	
	int Stroke[4];
	
public:
	cScoreHud();
	~cScoreHud();
	
	void SetScore( const int _Player, const int _Score );
	void StartScore( const int _Player, const int _Score );
	void SetStroke( const int _Player, const int _Stroke );

public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Golf_ScoreHud_H__ // 
// - ------------------------------------------------------------------------------------------ - //
