// - ------------------------------------------------------------------------------------------ - //
#include "MenuManager.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Graphics/Gfx.h>
#include <Util/String.h>
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
cMenuManager::cMenuManager( cClassicSaveData* _ClassicSaveData ) :
	ClassicSaveData( _ClassicSaveData ),
	BreakLoop( false ),
	CurForm( 0 ),
	LastForm( 0 ),
	SuperFlowState( 1 ),
	TransTime( 0 ),
	LastZOffset( 400.0 ),
	CurZOffset( 800.0 ),
	CurLevelPivot( 0 )
{
	//	Load( "2D/Menu/MainMenuUnregistered.form" );

Log( 10, "BAAA" );

	#ifdef EDITOR
	//	Load( "2D/Menu/MainMenuUnregistered.form" );
	//	Load( "2D/Menu/MainMenu.form" );
		Load( "2D/Menu/MainMenuEditor.form" );			// 0
		Load( "2D/Menu/PlayerSelect.form" );			// 1
	#else
		Load( "2D/Menu/MainMenu.form" );				// 0
		Load( "2D/Menu/PlayerSelect.form" );			// 1
	#endif // EDITOR //

	Load( "2D/Menu/HelpOptions.form" );					// 2
	Load( "2D/Menu/ClassicLevelSelect.form" );			// 3
	
	UpdateClassicLevelSelect();
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
//			Vector2D FormPos = Form[ LastForm ].Size + Form[ LastForm ].Pos;

//			Gfx::Translate( Vector3D( FormPos.x, FormPos.y, -CurZOffset ) );
			Gfx::Translate( Vector3D( 0, 0, -CurZOffset ) );
			
			if( CurForm < Form.size() )
			{
//				Form[ CurForm ].Draw();
				Form[ CurForm ]->Draw( 254 ); // To fix the disappearing Animation problem //
			}
			
			CurZOffset *= Real( 0.75 );
		}
		Gfx::PopMatrix();
		
		Gfx::PushMatrix();
		{
//			Vector2D FormPos = Form[ LastForm ].Size + Form[ LastForm ].Pos;
			
//			Gfx::Translate( Vector3D( FormPos.x, FormPos.y, -LastZOffset + Real( 400.0 ) ) );
			Gfx::Translate( Vector3D( 0, 0, -LastZOffset + Real( 400.0 ) ) );
			
			if( LastForm < Form.size() )
			{
				Form[ LastForm ]->Draw( Form[ LastForm ]->FormAlpha );
				
//				Form[ LastForm ].FormAlpha *= Real( 0.65 );
				Form[ LastForm ]->FormAlpha = int( Form[ LastForm ]->FormAlpha * Real( 0.65 ) );
			}
			
			LastZOffset *= Real( 0.75 );
			
			
		}
		Gfx::PopMatrix();
	}
	else
	{
		if( CurForm < Form.size() )
		{
			Form[ CurForm ]->Draw();
		}

	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::Step()
{
	if( CurForm < Form.size() )
	{
		Form[ CurForm ]->Step();
	
		bool BackPressed = false;
		
		if( Input::Button[ KEY_BACKSPACE ].Pressed() || Input::Pad[0].Button[ PAD_B ].Pressed() )
		{
			if( Form[ CurForm ]->BackID != -1 )
			{
				Form[ CurForm ]->SuperFlowState = Form[ CurForm ]->BackID;
				BackPressed = true;
		 	}
		}

		if( Input::Button[ KEY_ENTER ].Pressed()
			|| Input::Pad[0].Button[ PAD_A ].Pressed()
			|| Input::Pad[0].Button[ PAD_START ].Pressed()
			|| BackPressed )
		{
		
			TransTime = GetTime() + 350;
			CurZOffset = Real( 800.0 );
			LastZOffset = Real( 400.0 );
			
			if( LastForm < Form.size() )
			{
				Form[ LastForm ]->FormAlpha = 192;
			}
			if( CurForm < Form.size() )
			{
				Form[ CurForm ]->FormAlpha = 192;
			}

			LastForm = CurForm;
			
			switch( Form[ CurForm ]->SuperFlowState )
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
				case 12: // Classic Level Select Form //
				{
					CurForm = 3;
				break;	
				}
				case 13: // Golf Level Select Form //
				{
					CurForm = 4;
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
void cMenuManager::UpdateClassicLevelSelect()
{
	if( ClassicSaveData->MapData.size() > 2 )
	{
		size_t FormLabelSize = Form.back()->Labels.size();

		size_t LastTextLabelIdx = Form.back()->Labels.size() - 1;
			
		for( size_t idx = 0; idx < FormLabelSize; ++idx )
		{
			if( Form.back()->Labels[ idx ]->TextLabel() )
			{
				Form.back()->Labels[ idx ]->TextLabel()->Text = String::BaseName( ClassicSaveData->MapData[ idx + CurLevelPivot ].MapName );
			}
			
			CompletedTest( idx, idx );
		
		}
		
		for( size_t idx = FormLabelSize; idx < ClassicSaveData->MapData.size() - CurLevelPivot; ++idx )
		{
			cTextLabel* TempLabel = Form.back()->Labels[ LastTextLabelIdx ]->TextLabel();
			
			// Push back the text label //
			Form.back()->Labels.push_back(
				new cTextLabel(
					Vector2D( TempLabel->Pos.x, TempLabel->Pos.y - Real( 75 ) ),
					TempLabel->IsPassive,
					TempLabel->ActionID,
					String::BaseName( ClassicSaveData->MapData[ idx + CurLevelPivot ].MapName ),
					TempLabel->Scale,
					Gfx::RGBA( 255, 255, 255, 255 ),
					TempLabel->Align
				)
			);
			
			if( !TempLabel->IsPassive )
			{
				Form.back()->ActiveLabels.push_back( Form.back()->Labels.size() - 1 );
			}
			
			LastTextLabelIdx = Form.back()->Labels.size() - 1;
						
			if( ClassicSaveData->MapData[ idx + CurLevelPivot ].Locked )
			{
				// Set the Color to gray if the Label is locked and the SelColor to red //
				Form.back()->Labels.back()->TextLabel()->Color = Gfx::RGBA( 128, 128, 128, 255 );
				Form.back()->Labels.back()->TextLabel()->SelColor = Gfx::RGBA( 255, 64, 64, 255 );
					
				// Place the Locked animation to the left of the gray level name //
				Form.back()->Labels.push_back( 
					new cAniLabel(
						Vector2D( Real( 40 ), Form.back()->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
						false,
						0,
						AnimationPool.Load( "ColoredLockedIcon.anim" ),
						AnimationPool.Load( "ColoredLockedIcon.anim" ),
						0
					)
				);
			}
			
			CompletedTest( idx, LastTextLabelIdx );
			
			if( Form.back()->Labels[ LastTextLabelIdx ]->TextLabel()->Pos.y < ( Form.back()->Size.y * Real( 2 ) + Real( 150 ) ) )
			{
				break;	
			}			
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::CompletedTest( size_t idx, size_t LastTextLabelIdx )
{
	if( ClassicSaveData->MapData[ idx + CurLevelPivot ].NormalCompleted )
	{
		// Place the Completed animation to the right level name //
		Form.back()->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 265 ), Form.back()->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				false,
				0,
				AnimationPool.Load( "ColoredCompletedIcon.anim" ),
				AnimationPool.Load( "ColoredCompletedIcon.anim" ),
				0
			)
		);
	}
	else
	{
		// Place the gray Completed animation to the right level name //
		Form.back()->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 265 ), Form.back()->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				false,
				0,
				AnimationPool.Load( "GrayCompletedIcon.anim" ),
				AnimationPool.Load( "GrayCompletedIcon.anim" ),
				0
			)
		);
	}

	if( ClassicSaveData->MapData[ idx + CurLevelPivot ].AlternateCompleted )
	{
		// Place the alternate completed animation to the right level name //
		Form.back()->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 340 ), Form.back()->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				false,
				0,
				AnimationPool.Load( "ColoredAlternativeIcon.anim" ),
				AnimationPool.Load( "ColoredAlternativeIcon.anim" ),
				0
			)
		);
	}
	else
	{
		// Place the gray alternate completed animation to the right level name //
		Form.back()->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 340 ), Form.back()->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				false,
				0,
				AnimationPool.Load( "GrayAlternativeIcon.anim" ),
				AnimationPool.Load( "GrayAlternativeIcon.anim" ),
				0
			)
		);
	}	
}
// - ------------------------------------------------------------------------------------------ - //
