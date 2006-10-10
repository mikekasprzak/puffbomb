#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Editor.h"
#include <Global.h>
#include <Input/Input.h>

#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cEditor::cEditor()
{
	CollectionEdit = new cCollectionEdit();
	ComponentEdit = new cComponentEdit();
//	AnimationEdit = new cAnimationEdit();

	CurEditor = COMPONENT_EDITOR;
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //	
cEditor::~cEditor()
{
	Log( LOG_HIGHEST_LEVEL, "~cEditor() Delete Map and Mesh Editor" );
	delete CollectionEdit;
	delete ComponentEdit;
//	delete AnimationEdit;
}
// - ------------------------------------------------------------------------------------------ - //	
/*
cEditor::cEditor( cGame& _Game ) :
	Game( &_Game )
{
	CollectionEdit = new cCollectionEdit();
	ComponentEdit = new cComponentEdit();
	AnimationEdit = new cAnimationEdit();
//	Mesh2DEdit = new cMesh2DEdit();

//	MapEdit = new cMapEdit( _Game, *Mesh2DEdit );
	MapEdit = new cMapEdit( _Game );
}
// - ------------------------------------------------------------------------------------------ - //	
cEditor::~cEditor()
{
	Log( LOG_HIGHEST_LEVEL, "~cEditor() Delete Map and Mesh Editor" );
	delete MapEdit;
	delete CollectionEdit;
	delete ComponentEdit;
	delete AnimationEdit;
//	delete Mesh2DEdit;
}
*/
// - ------------------------------------------------------------------------------------------ - //	
void cEditor::Step()
{
/*	if( CurEditor == MAP_EDITOR )
	{
		if( MapEdit->IsHelp )
		{
			// Handles scrolling around the map
			MapEdit->Scroll( MapEdit->Camera );
			
			// Handles the zooming in and out of a map
			MapEdit->Zoom( Real( 256.0 ), MapEdit->Camera );

		}
		else
		{
			MapEdit->Step();
		}
	}
	else */
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
/*	else if( CurEditor == MESH2D_EDITOR )
	{
		if( Mesh2DEdit->IsHelp )
		{
			// Handles scrolling around the map
			Mesh2DEdit->Scroll( Mesh2DEdit->Camera );
			
			// Handles the zooming in and out of a map
			Mesh2DEdit->Zoom( Real( 256.0 ), Mesh2DEdit->Camera );
			
		}
		else
		{
			Mesh2DEdit->Step();
		}
	}
*/
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
/*		else if( CurEditor == MESH2D_EDITOR )
		{
			Mesh2DEdit->IsHelp = !Mesh2DEdit->IsHelp;
			// Resets the zoom
			Mesh2DEdit->Scale = Real::One;
	
			Mesh2DEdit->Camera->Pos.x = 0.0;
			Mesh2DEdit->Camera->Pos.y = 0.0;
			Mesh2DEdit->Camera->Pos.z = Global::HudZoom;
			
			Mesh2DEdit->Camera->View.x = Mesh2DEdit->Camera->Pos.x;
			Mesh2DEdit->Camera->View.y = Mesh2DEdit->Camera->Pos.y;
			Mesh2DEdit->Camera->View.z = 0.0;		
		}*/
	}
	
/*	if ( Button[ KEY_F2 ].Pressed() )
	{
		Global::IsMesh2DEditor = !Global::IsMesh2DEditor;
		
		// Swaps the active zoom with the non active one
		Real tempZoom = NonActiveZoom;
		NonActiveZoom = Global::EditorZoom;
		Global::EditorZoom = tempZoom;
			
		// Swaps the active Origin with the non active one
		Vector2D tempOrigin = NonActiveOrigin;
		NonActiveOrigin = Global::Origin;
		Global::Origin = tempOrigin;
		
	}*/
	if( Button[ KEY_F4 ].Pressed() )
	{
		CurEditor = MAP_EDITOR;
	}
	else if( Button[ KEY_F5 ].Pressed() )
	{
		CurEditor = COLLECTION_EDITOR;
	}
	else if( Button[ KEY_F6 ].Pressed() )
	{
		CurEditor = ANIMATION_EDITOR;
	}
	else if( Button[ KEY_F7 ].Pressed() )
	{
		CurEditor = COMPONENT_EDITOR;
	}
	else if( Button[ KEY_F8 ].Pressed() )
	{
		CurEditor = MESH2D_EDITOR;
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
		else
		{
			MapEdit->Draw();
		}*/
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
/*	else if( CurEditor == MESH2D_EDITOR )
	{
		if( Mesh2DEdit->IsHelp )
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

			Mesh2DEdit->DisplayHelp();
		
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			Mesh2DEdit->Draw();
		}
	}*/

}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
