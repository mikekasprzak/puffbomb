// - ------------------------------------------------------------------------------------------ - //
#include "MenuManager.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
cMenuManager::cMenuManager() :
	BreakLoop( false ),
	CurForm( 0 ),
	LastForm( 0 ),
	SuperFlowState( 1 ),
	TransTime( 0 ),
	LastZOffset( 400.0 ),
	CurZOffset( 800.0 )
{
	//	Load( "2D/Menu/MainMenuUnregistered.form" );


	#ifdef EDITOR
	//	Load( "2D/Menu/MainMenuUnregistered.form" );
	//	Load( "2D/Menu/MainMenu.form" );
		Load( "2D/Menu/MainMenuEditor.form" );
		Load( "2D/Menu/PlayerSelect.form" );
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
	if( TransTime > GetTime() )
	{
		Gfx::PushMatrix();
		{
			Gfx::Translate( Vector3D( 0, 0, -CurZOffset ) );
			
			if( CurForm < Form.size() )
			{
				Form[ CurForm ].Draw();
			}
			
			CurZOffset *= Real( 0.75 );
		}
		Gfx::PopMatrix();
		
		Gfx::PushMatrix();
		{
			Gfx::Translate( Vector3D( 0, 0, -LastZOffset + Real( 400.0 ) ) );
			
			if( LastForm < Form.size() )
			{
				Form[ LastForm ].Draw( Form[ LastForm ].FormAlpha );
				
				Form[ LastForm ].FormAlpha *= Real( 0.65 );
			}
			
			LastZOffset *= Real( 0.75 );
			
			
		}
		Gfx::PopMatrix();
	}
	else
	{
		if( CurForm < Form.size() )
		{
			Form[ CurForm ].Draw();
		}

	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::Step()
{
	if( CurForm < Form.size() )
	{
		Form[ CurForm ].Step();
	
		bool BackPressed = false;
		
		if( Input::Button[ KEY_BACKSPACE ].Pressed() || Input::Pad[0].Button[ PAD_B ].Pressed() )
		{
			if( Form[ CurForm ].BackID != -1 )
			{
				Form[ CurForm ].SuperFlowState = Form[ CurForm ].BackID;
				BackPressed = true;
		 	}
		}

		if( Input::Button[ KEY_ENTER ].Pressed()
			|| Input::Pad[0].Button[ PAD_A ].Pressed()
			|| Input::Pad[0].Button[ PAD_START ].Pressed()
			|| BackPressed )
		{
		
			TransTime = GetTime() + 250;
			CurZOffset = Real( 800.0 );
			LastZOffset = Real( 400.0 );
			
			if( LastForm < Form.size() )
			{
				Form[ LastForm ].FormAlpha = 192;
			}
			if( CurForm < Form.size() )
			{
				Form[ CurForm ].FormAlpha = 192;
			}

			LastForm = CurForm;
			
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
				case 11: // Unlock Full Version Form //
				{
					CurForm = 0;
				break;	
				}
				default:
				{
				
				break;	
				}
			}
			// Stops the fade in and out effect from happening //
			if( CurForm == LastForm )
			{
				TransTime = GetTime();
			}

		}
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
