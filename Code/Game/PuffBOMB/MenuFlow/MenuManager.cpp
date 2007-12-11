// - ------------------------------------------------------------------------------------------ - //
#include "MenuManager.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Graphics/Gfx.h>
#include <String/String.h>
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
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
	CurLevelPivot( 0 ),
	LevelsPerPage( 0 ),
	LevelsOnPage( 0 ),
	MiniMapName( "" )
{
	//	Load( "2D/Menu/MainMenuUnregistered.form" );

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
	Load( "2D/Menu/ClassicLevelPreview.form" );			// 4
	Load( "2D/Menu/ClassicLevelConfirm.form" );			// 5

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
				Form[ CurForm ]->Draw( 254 ); // To fix the disappearing Animation problem //
				if( CurForm == 3 && CurForm != 5 && LastForm != 5  )
				{
					Form[ 4 ]->Draw( 254 );
					
					// Draw Minimap //
					Gfx::PushMatrix();
					{
						Gfx::Translate( Vector2D( Global::Right - Real( 300 ), Global::Bottom + Real( 280 ) ) );
					
						Gfx::EnableTex2D();
				
						Gfx::DrawQuads(
							&MiniMapTexVertex[0],
							&MiniMapTexUV[0],
							MiniMapTexIndices,
							4,
							MiniMapTex.Id,
							Gfx::White()
						);
						
						Gfx::DisableTex2D();
					}
					Gfx::PopMatrix();
				}
			}
			
			CurZOffset *= Real( 0.75 );
		}
		Gfx::PopMatrix();
			
		Gfx::EnableTex2D();
			
		Gfx::PushMatrix();
		{
			Gfx::Translate( Vector3D( 0, 0, -LastZOffset + Real( 400.0 ) ) );
			
			if( LastForm < Form.size() )
			{
				Form[ LastForm ]->Draw( Form[ LastForm ]->FormAlpha );
				
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
//	if( CurForm == 3 && LastForm == 5 || LastForm == 3 && CurForm == 5 || TransTime <= GetTime() && CurForm == 3 )
	if( CurForm == 3 && LastForm == 5 || CurForm == 5 || TransTime <= GetTime() && CurForm == 3 )
	{
		Form[ 4 ]->Draw();
			
		// Draw Minimap //
		Gfx::PushMatrix();
		{
			Gfx::Translate( Vector2D( Global::Right - Real( 300 ), Global::Bottom + Real( 280 ) ) );
		
			Gfx::EnableTex2D();
	
			Gfx::DrawQuads(
				&MiniMapTexVertex[0],
				&MiniMapTexUV[0],
				MiniMapTexIndices,
				4,
				MiniMapTex.Id,
				Gfx::White()
			);
			
			Gfx::DisableTex2D();
		}
		Gfx::PopMatrix();
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
					int Focus = Form[ 3 ]->Focus;
					
					Form[ 3 ]->Clear();
					Form[ 3 ]->Load( "2D/Menu/ClassicLevelSelect.form" );
					
					Form[ 3 ]->Focus = Focus;

					UpdateClassicLevelSelect();
					CurForm = 3;
				break;	
				}
				case 13: // Golf Level Select Form //
				{
					CurForm = 4;
				break;	
				}
				case 14: // Classic Previous Page Level Select //
				{
					Form[ 3 ]->Clear();
					Form[ 3 ]->Load( "2D/Menu/ClassicLevelSelect.form" );

					CurLevelPivot -= LevelsPerPage;
															
					UpdateClassicLevelSelect();
					CurForm = 3;
				break;	
				}
				case 15: // Classic Next Page Level Select //
				{
					Form[ 3 ]->Clear();
					Form[ 3 ]->Load( "2D/Menu/ClassicLevelSelect.form" );

					CurLevelPivot += LevelsOnPage;
					LevelsPerPage = LevelsOnPage;
					
					UpdateClassicLevelSelect();
					CurForm = 3;
				break;
				}
				case 16: // Classic Level Confirm Form //
				{
					
					CurForm = 5;
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
	if( CurForm == 3 )
	{
		if( Input::Button[ KEY_UP ].Pressed()
			|| Input::Button[ KEY_DOWN ].Pressed()
			|| int( Input::Pad[0].Stick1.HarshKeyRepeat().y ) == 1
			|| int( Input::Pad[0].DPad.HarshKeyRepeat().y ) == 1
			|| int( Input::Pad[0].Stick1.HarshKeyRepeat().y ) == -1 
			|| int( Input::Pad[0].DPad.HarshKeyRepeat().y ) == -1
			)
		{
			UpdateMiniMap();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::UpdateMiniMap()
{
	if( Form[ CurForm ]->Focus + CurLevelPivot < (int)ClassicSaveData->MapData.size() &&
		Form[ CurForm ]->Focus < LevelsOnPage )
	{

		// Explicitly remove the minimap from the texture pool //
		if( MiniMapName != "" )
		{
			TexturePool.Remove( MiniMapName );
		}

		// Load the appropriate minimap for this level //
		MiniMapName = "Classic/" + String::BaseName( ClassicSaveData->MapData[ Form[ 3 ]->Focus + CurLevelPivot ].MapName ) + ".pack.tx";
		
		MiniMapTex = TexturePool.Load( MiniMapName );
		
		Real MiniMapWidth = 1920.0;
		Real MiniMapHeight = 1200.0;
		
		MiniMapWidth /= Real( 4 ); 
		MiniMapHeight /= Real( 4 );
		
		MiniMapTexVertex[0] = Vector3D( -MiniMapWidth, Real::Zero, 0.0 );
		MiniMapTexVertex[1] = Vector3D( Real::Zero, Real::Zero, 0.0 );
		MiniMapTexVertex[2] = Vector3D( Real::Zero, MiniMapHeight, 0.0 );
		MiniMapTexVertex[3] = Vector3D( -MiniMapWidth, MiniMapHeight, 0.0 );
	
		MiniMapTexUV[0] = Vector2D( 0.01, 0.01 );
		MiniMapTexUV[1] = Vector2D( 0.99, 0.01 );
		MiniMapTexUV[2] = Vector2D( 0.99, 0.99 );
		MiniMapTexUV[3] = Vector2D( 0.01, 0.99 );
	
		MiniMapTexIndices[0] = 0;
		MiniMapTexIndices[1] = 1;
		MiniMapTexIndices[2] = 2;
		MiniMapTexIndices[3] = 3;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::UpdateClassicLevelSelect()
{
	if( ClassicSaveData->MapData.size() > 2 )
	{
		LevelsOnPage = 1;
		
		size_t FormLabelSize = Form[ 3 ]->Labels.size();

		size_t LastTextLabelIdx = Form[ 3 ]->Labels.size() - 1;
			
		for( size_t idx = 0; idx < FormLabelSize; ++idx )
		{
			if( Form[ 3 ]->Labels[ idx ]->TextLabel() )
			{
				Form[ 3 ]->Labels[ idx ]->TextLabel()->Text = String::BaseName( ClassicSaveData->MapData[ idx + CurLevelPivot ].MapName );
			}
			
			CompletedTest( idx, idx );
		}
		
		for( size_t idx = FormLabelSize; idx < ClassicSaveData->MapData.size() - CurLevelPivot; ++idx )
		{
			LevelsOnPage++;
			
			cTextLabel* TempLabel = Form[ 3 ]->Labels[ LastTextLabelIdx ]->TextLabel();
			
			// Push back the text label //
			Form[ 3 ]->Labels.push_back(
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
				Form[ 3 ]->ActiveLabels.push_back( Form[ 3 ]->Labels.size() - 1 );
			}
			
			LastTextLabelIdx = Form[ 3 ]->Labels.size() - 1;
						
			if( ClassicSaveData->MapData[ idx + CurLevelPivot ].Locked )
			{
				// Set the Color to grey if the Label is locked and the SelColor to red //
				Form[ 3 ]->Labels.back()->TextLabel()->Color = Gfx::RGBA( 128, 128, 128, 255 );
				Form[ 3 ]->Labels.back()->TextLabel()->SelColor = Gfx::RGBA( 255, 64, 64, 255 );
					
				// Place the Locked animation to the left of the grey level name //
				Form[ 3 ]->Labels.push_back( 
					new cAniLabel(
						Vector2D( Real( 40 ), Form[ 3 ]->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
						true,
						0,
						AnimationPool.Load( "ColoredLockedIcon.anim" ),
						AnimationPool.Load( "ColoredLockedIcon.anim" ),
						0
					)
				);
			}
			
			CompletedTest( idx, LastTextLabelIdx );
			
			if( Form[ 3 ]->Labels[ LastTextLabelIdx ]->TextLabel()->Pos.y < ( Form[ 3 ]->Size.y * Real( 2 ) + Real( 150 ) ) )
			{
				break;
			}			
		}
		// Place the down arrow at the bottom //
		if( LevelsOnPage + CurLevelPivot < (int)ClassicSaveData->MapData.size() )
		{
			Form[ 3 ]->Labels.push_back( 
				new cAniLabel(
					Vector2D( Real( 190 ), ( Form[ 3 ]->Size.y * Real( 2 ) ) + Real( 30 ) ),
					false,
					15,
					AnimationPool.Load( "ColoredMoreArrow.anim" ),
					AnimationPool.Load( "ColoredMoreArrow.anim" ),
					0
				)
			);
			// If there is no animation for selecting do this //
			Form[ 3 ]->Labels.back()->Color = Gfx::RGBA( 255, 255, 255, 254 );
			Form[ 3 ]->Labels.back()->SelColor = Gfx::RGBA( 64, 255, 64, 255 );
			
			Form[ 3 ]->ActiveLabels.push_back( Form[ 3 ]->Labels.size() - 1 );		
		}
		else
		{
/*			Form[ 3 ]->Labels.push_back( 
				new cAniLabel(
					Vector2D( Real( 190 ), ( Form[ 3 ]->Size.y * Real( 2 ) ) + Real( 30 ) ),
					true,
					0,
					AnimationPool.Load( "GreyMoreArrow.anim" ),
					AnimationPool.Load( "GreyMoreArrow.anim" ),
					0
				)
			);
			// If there is no grey arrow just do this //
			Form[ 3 ]->Labels.back()->Color = Gfx::RGBA( 128, 128, 128, 255 );*/
		}
			
		// Place the up arrow at the top //
		if( CurLevelPivot != 0 )
		{
			Form[ 3 ]->Labels.push_back( 
				new cAniLabel(
					Vector2D( Real( 190 ), Real( -30 ) ),
					false,
					14,
					AnimationPool.Load( "ColoredLessArrow.anim" ),
					AnimationPool.Load( "ColoredLessArrow.anim" ),
					0
				)
			);
			// If there is no animation for selecting do this //
			Form[ 3 ]->Labels.back()->Color = Gfx::RGBA( 255, 255, 255, 254 );
			Form[ 3 ]->Labels.back()->SelColor = Gfx::RGBA( 64, 255, 64, 255 );
			
			Form[ 3 ]->ActiveLabels.push_back( Form[ 3 ]->Labels.size() - 1 );		
		}
		else
		{
/*			Form[ 3 ]->Labels.push_back( 
				new cAniLabel(
					Vector2D( Real( 190 ), Real( -30 ) ),
					true,
					0,
					AnimationPool.Load( "GreyLessArrow.anim" ),
					AnimationPool.Load( "GreyLessArrow.anim" ),
					0
				)
			);
			// If there is no grey arrow just do this //
			Form[ 3 ]->Labels.back()->Color = Gfx::RGBA( 128, 128, 128, 255 );*/
		}
		
		
		if( Form[ 3 ]->Labels[ 0 ]->TextLabel() )
		{
			if( ClassicSaveData->MapData[ CurLevelPivot ].Locked )
			{
				// Set the Color to grey if the Label is locked and the SelColor to red //
				Form[ 3 ]->Labels[ 0 ]->TextLabel()->Color = Gfx::RGBA( 128, 128, 128, 255 );
				Form[ 3 ]->Labels[ 0 ]->TextLabel()->SelColor = Gfx::RGBA( 255, 64, 64, 255 );
					
				// Place the Locked animation to the left of the grey level name //
				Form[ 3 ]->Labels.push_back( 
					new cAniLabel(
						Vector2D( Real( 40 ), Form[ 3 ]->Labels[ 0 ]->Pos.y + Real( 10 ) ),
						true,
						0,
						AnimationPool.Load( "ColoredLockedIcon.anim" ),
						AnimationPool.Load( "ColoredLockedIcon.anim" ),
						0
					)
				);
			}
		}
		
		UpdateMiniMap();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuManager::CompletedTest( size_t idx, size_t LastTextLabelIdx )
{
	if( ClassicSaveData->MapData[ idx + CurLevelPivot ].NormalCompleted )
	{
		// Place the Completed animation to the right level name //
		Form[ 3 ]->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 265 ), Form[ 3 ]->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				true,
				0,
				AnimationPool.Load( "ColoredCompletedIcon.anim" ),
				AnimationPool.Load( "ColoredCompletedIcon.anim" ),
				0
			)
		);
	}
	else
	{
		// Place the grey Completed animation to the right level name //
		Form[ 3 ]->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 265 ), Form[ 3 ]->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				true,
				0,
				AnimationPool.Load( "GreyCompletedIcon.anim" ),
				AnimationPool.Load( "GreyCompletedIcon.anim" ),
				0
			)
		);
	}

	if( ClassicSaveData->MapData[ idx + CurLevelPivot ].AlternateCompleted )
	{
		// Place the alternate completed animation to the right level name //
		Form[ 3 ]->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 340 ), Form[ 3 ]->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				true,
				0,
				AnimationPool.Load( "ColoredAlternativeIcon.anim" ),
				AnimationPool.Load( "ColoredAlternativeIcon.anim" ),
				0
			)
		);
	}
	else
	{
		// Place the grey alternate completed animation to the right level name //
		Form[ 3 ]->Labels.push_back( 
			new cAniLabel(
				Vector2D( Real( 340 ), Form[ 3 ]->Labels[ LastTextLabelIdx ]->Pos.y + Real( 10 ) ),
				true,
				0,
				AnimationPool.Load( "GreyAlternativeIcon.anim" ),
				AnimationPool.Load( "GreyAlternativeIcon.anim" ),
				0
			)
		);
	}	
}
// - ------------------------------------------------------------------------------------------ - //
