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
	#ifdef EDITOR
		Load( "2D/Menu/MainMenuEditor.form" );
		Load( "2D/Menu/PlayerSelectEditor.form" );
	#else
		Load( "2D/Menu/MainMenu.form" );
		Load( "2D/Menu/PlayerSelect.form" );
	#endif // EDITOR //

	Load( "2D/Menu/HelpOptions.form" );

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
				case 8: // Leaderboard Form //
				{
					CurForm = 0;
				break;	
				}
				case 9: // Achievements Form //
				{
					CurForm = 0;
				break;	
				}
				case 10: // Help & Options Form //
				{
					CurForm = 2;
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
