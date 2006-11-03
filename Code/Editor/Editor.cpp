#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Editor.h"
#include <Global.h>
#include <Input/Input.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cEditor::cEditor()
{

	MapEdit = new cMapEdit();

	CurEditor = MAP_EDITOR;
	LastEditor = MAP_EDITOR;
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //	
cEditor::~cEditor()
{
	Log( LOG_HIGHEST_LEVEL, "~cEditor()" );
	
	FreeEditorMemory();
}
// - ------------------------------------------------------------------------------------------ - //	
void cEditor::FreeEditorMemory()
{
	if( LastEditor == MAP_EDITOR )
	{
		Log( LOG_HIGHEST_LEVEL, "Delete Map Editor" );
		delete MapEdit;
	}
	else if( LastEditor == COLLECTION_EDITOR )
	{
		Log( LOG_HIGHEST_LEVEL, "Delete Collection Editor" );
		delete CollectionEdit;
	}
	else if( LastEditor == COMPONENT_EDITOR )
	{
		Log( LOG_HIGHEST_LEVEL, "Delete Component Editor" );
		delete ComponentEdit;
	}
/*	else if( CurEditor == ANIMATION_EDITOR )
	{
		
	}
	*/
}
// - ------------------------------------------------------------------------------------------ - //	
void cEditor::Step()
{
	if( CurEditor == MAP_EDITOR )
	{
/*		if( MapEdit->IsHelp )
		{
			// Handles scrolling around the map
			MapEdit->Scroll( MapEdit->Camera );
			
			// Handles the zooming in and out of a map
			MapEdit->Zoom( Real( 256.0 ), MapEdit->Camera );

		}
		else*/
		{
			MapEdit->Step();
		}
	}
	else 
	if( CurEditor == COLLECTION_EDITOR )
	{
		CollectionEdit->Step();
	}
	else if( CurEditor == COMPONENT_EDITOR )
	{
		ComponentEdit->Step();
	}
	else if( CurEditor == ANIMATION_EDITOR )
	{
//		AnimationEdit->Step();
	}
	if( Button[ KEY_F1 ].Pressed() )
	{

/*		if( CurEditor == MAP_EDITOR )
		{
			MapEdit->IsHelp = !MapEdit->IsHelp;
			// Resets the zoom
			MapEdit->Scale = Real::One;

			MapEdit->Camera->Pos.x = 0.0;
			MapEdit->Camera->Pos.y = 0.0;
			MapEdit->Camera->Pos.z = Global::HudZoom;
			
			MapEdit->Camera->View.x = MapEdit->Camera->Pos.x;
			MapEdit->Camera->View.y = MapEdit->Camera->Pos.y;
			MapEdit->Camera->View.z = 0.0;
		}
		else*/
		if( CurEditor == COLLECTION_EDITOR )
		{
	
		}
		else if( CurEditor == COMPONENT_EDITOR )
		{
	
		}
		else if( CurEditor == ANIMATION_EDITOR )
		{
			
		}
	}
	if( Button[ KEY_F5 ].Pressed() )
	{
		if( CurEditor != MAP_EDITOR )
		{
			CurEditor = MAP_EDITOR;
			MapEdit = new cMapEdit();
		}
	}
	else if( Button[ KEY_F6 ].Pressed() )
	{
		if( CurEditor != COLLECTION_EDITOR )
		{
			CurEditor = COLLECTION_EDITOR;
			CollectionEdit = new cCollectionEdit();
		}
	}
/*	else if( Button[ KEY_F7 ].Pressed() )
	{
		if( CurEditor != ANIMATION_EDITOR )
		{
			CurEditor = ANIMATION_EDITOR;
		}
	}*/
	else if( Button[ KEY_F8 ].Pressed() )
	{
		if( CurEditor != COMPONENT_EDITOR )
		{
			CurEditor = COMPONENT_EDITOR;
			ComponentEdit = new cComponentEdit();
		}
	}
	
	if( CurEditor != LastEditor )
	{
		FreeEditorMemory();
		LastEditor = CurEditor;
	}	
}
// - ------------------------------------------------------------------------------------------ - //	
void cEditor::Draw()
{
	if( CurEditor == MAP_EDITOR )
	{
/*		if( MapEdit->IsHelp )
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

			MapEdit->DisplayHelp();
					
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);

		}
		else*/
		{
			MapEdit->Draw();
		}
	}
	else if( CurEditor == COLLECTION_EDITOR )
	{
		CollectionEdit->Draw();
	}
	else if( CurEditor == COMPONENT_EDITOR )
	{
		ComponentEdit->Draw();
	}
	else if( CurEditor == ANIMATION_EDITOR )
	{
//		AnimationEdit->Draw();
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
