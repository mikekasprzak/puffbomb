// - ------------------------------------------------------------------------------------------ - //
// Actions //
// - ------------------------------------------------------------------------------------------ - //
#include "Actions.h"

#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
void cActions::Quit()
{
	Global::Shutdown = true;
}
// - ------------------------------------------------------------------------------------------ - //
int cActions::StartClassic()
{
	return 2;
}
// - ------------------------------------------------------------------------------------------ - //
int cActions::StartGolf()
{
	return 4;
}
// - ------------------------------------------------------------------------------------------ - //
#ifdef EDITOR
int cActions::StartEditor()
{
	return 3;
}
#endif // EDITOR //
// - ------------------------------------------------------------------------------------------ - //
int cActions::SplashScreen()
{
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
int cActions::ExecuteAction( int _ActionID )
{
	int SuperFlowState = 0;
	switch( _ActionID )
	{
		case 0:
		{
		
		break;
		}
		case 1:
		{
			Quit();
		break;
		}
		case 2:
		{
			SuperFlowState = StartClassic();
		break;
		}
#ifdef EDITOR
		case 3:
		{
			SuperFlowState = StartEditor();
		break;
		}
#endif // EDITOR //
		case 4:
		{
			SuperFlowState = SplashScreen();
		break;
		}
		case 5:
		{
			SuperFlowState = StartGolf();
		break;
		}
	}
	
	return SuperFlowState;
}
// - ------------------------------------------------------------------------------------------ - //
