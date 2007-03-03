// - ------------------------------------------------------------------------------------------ - //
// MenuManager //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __MenuFlow_PuffBOMB_MenuManager_H__
#define __MenuFlow_PuffBOMB_MenuManager_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Gui/WindowManager.h>
// - ------------------------------------------------------------------------------------------ - //
#include <ClassicSaveData.h>
// - ------------------------------------------------------------------------------------------ - //
class cMenuManager : public cWindowManager
{
public:
	cClassicSaveData* ClassicSaveData;

	bool BreakLoop;
	
	unsigned int CurForm;
	unsigned int LastForm;
	
	unsigned int SuperFlowState;
	
	int TransTime;
	Real LastZOffset;
	Real CurZOffset;
	
	int CurLevelPivot;
	
public:
	cMenuManager( cClassicSaveData* _ClassicSaveData );
	~cMenuManager();

public:
	void Step();
	void Draw();

public:
	void UpdateClassicLevelSelect();
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // MenuManager // 
// - ------------------------------------------------------------------------------------------ - //
