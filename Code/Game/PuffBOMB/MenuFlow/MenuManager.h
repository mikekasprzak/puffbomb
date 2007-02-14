// - ------------------------------------------------------------------------------------------ - //
// MenuManager //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __MenuFlow_PuffBOMB_MenuManager_H__
#define __MenuFlow_PuffBOMB_MenuManager_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Gui/WindowManager.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cMenuManager : public cWindowManager
{
public:
	bool BreakLoop;
	
	unsigned int CurForm;
	unsigned int LastForm;
	
	unsigned int SuperFlowState;
	
	int TransTime;
	Real LastZOffset;
	Real CurZOffset;
	
public:
	cMenuManager();
	~cMenuManager();

public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // MenuManager // 
// - ------------------------------------------------------------------------------------------ - //
