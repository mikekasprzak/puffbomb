// - ------------------------------------------------------------------------------------------ - //
#include "MenuManager.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
cMenuManager::cMenuManager() :
	BreakLoop( false ),
	CurForm( 0 ),
	LastForm( 0 ),
	SuperFlowState( 1 )
{

}
// - ------------------------------------------------------------------------------------------ - //
cMenuManager::~cMenuManager()
{

}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::Draw()
{
	if( CurForm < Form.size() )
	{
		Form[ CurForm ].Draw();
	}
	
/*	for( size_t idx = 0; idx < Form.size(); ++idx )
	{
		
	} */
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::Step()
{
	if( CurForm < Form.size() )
	{
		Form[ CurForm ].Step();

		if( Input::Button[ KEY_ENTER ].Pressed() || Input::Pad[0].Button[ PAD_A ].Pressed() || Input::Pad[0].Button[ PAD_START ].Pressed() )
		{
			switch( Form[ CurForm ].SuperFlowState )
			{
				case 2:	// Classic Mode Start //
				{
					BreakLoop = true;
					SuperFlowState = 2;	
			
				break;	
				}
				case 3: // Editor Start //
				{
					BreakLoop = true;
					SuperFlowState = 3;	
			
				break;	
				}
				case 4: // SplashScreen Start //
				{
					BreakLoop = true;
					SuperFlowState = 0;	
			
				break;	
				}
				case 5: // Golf Mode Start //
				{
					BreakLoop = true;
					SuperFlowState = 4;	
			
				break;	
				}
				case 6: // Golf Player Select Form //
				{
					CurForm = 1;
			
				break;	
				}
				case 7: // Main Menu Form //
				{
					CurForm = 0;
				break;	
				}
				default:
				{
				
				break;	
				}
			}
			LastForm = CurForm;
		}
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
