// - ------------------------------------------------------------------------------------------ - //
// Actions //
// - ------------------------------------------------------------------------------------------ - //
#include "Actions.h"

#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
void cActions::Quit()
{
	cGlobal::Shutdown = true;
}
// - ------------------------------------------------------------------------------------------ - //
void cActions::ExecuteAction( int _ActionID )
{
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
