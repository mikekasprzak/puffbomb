#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Editor.h"
#include <Platform/Global.h>
#include <Input/Input.h>

#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cEditor::cEditor( cGame& _Game ) :
	CurEditor( 4 ),
	Game( &_Game )
{
	Mesh2DEdit = new cMesh2DEdit();
	MapEdit = new cMapEdit( _Game, *Mesh2DEdit );
	AnimationEdit = new cAnimationEdit();
	

}
// - ------------------------------------------------------------------------------------------ - //	
cEditor::~cEditor()
{
	Log( LOG_HIGHEST_LEVEL, "~cEditor() Delete Map and Mesh Editor" );
	delete MapEdit;
	delete Mesh2DEdit;
	delete AnimationEdit;
}
// - ------------------------------------------------------------------------------------------ - //	
void cEditor::Step()
{
	if( cGlobal::IsMesh2DEditor )
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
	else
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

	if( Button[ KEY_F1 ].Pressed() )
	{

		if( cGlobal::IsMesh2DEditor )
		{
			Mesh2DEdit->IsHelp = !Mesh2DEdit->IsHelp;
			// Resets the zoom
			Mesh2DEdit->Scale = Real::One;
			cGlobal::Origin.x = 0;
			cGlobal::Origin.y = 0;
				
			Mesh2DEdit->Camera->Pos.x = 0.0;
			Mesh2DEdit->Camera->Pos.y = 0.0;
			Mesh2DEdit->Camera->Pos.z = cGlobal::HudZoom;
			
			Mesh2DEdit->Camera->View.x = Mesh2DEdit->Camera->Pos.x;
			Mesh2DEdit->Camera->View.y = Mesh2DEdit->Camera->Pos.y;
			Mesh2DEdit->Camera->View.z = 0.0;		
		}
		else
		{
			MapEdit->IsHelp = !MapEdit->IsHelp;
			// Resets the zoom
			MapEdit->Scale = Real::One;
			cGlobal::Origin.x = 0;
			cGlobal::Origin.y = 0;
				
			MapEdit->Camera->Pos.x = 0.0;
			MapEdit->Camera->Pos.y = 0.0;
			MapEdit->Camera->Pos.z = cGlobal::HudZoom;
			
			MapEdit->Camera->View.x = MapEdit->Camera->Pos.x;
			MapEdit->Camera->View.y = MapEdit->Camera->Pos.y;
			MapEdit->Camera->View.z = 0.0;
		}

	}
	
/*	if ( Button[ KEY_F2 ].Pressed() )
	{
		cGlobal::IsMesh2DEditor = !cGlobal::IsMesh2DEditor;
		
		// Swaps the active zoom with the non active one
		Real tempZoom = NonActiveZoom;
		NonActiveZoom = cGlobal::EditorZoom;
		cGlobal::EditorZoom = tempZoom;
			
		// Swaps the active Origin with the non active one
		Vector2D tempOrigin = NonActiveOrigin;
		NonActiveOrigin = cGlobal::Origin;
		cGlobal::Origin = tempOrigin;
		
	}*/
	if( Button[ KEY_F4 ].Pressed() )
	{
		cGlobal::IsMesh2DEditor = false;
		CurEditor = MAP_EDITOR;
	}
	else if( Button[ KEY_F5 ].Pressed() )
	{
		cGlobal::IsMesh2DEditor = true;
		CurEditor = COLLECTION_EDITOR;
	}
	else if( Button[ KEY_F6 ].Pressed() )
	{
		cGlobal::IsMesh2DEditor = true;
		CurEditor = BODY_EDITOR;
	}
	else if( Button[ KEY_F7 ].Pressed() )
	{
		cGlobal::IsMesh2DEditor = true;
		CurEditor = ANIMATION_EDITOR;
	}
	else if( Button[ KEY_F8 ].Pressed() )
	{
		cGlobal::IsMesh2DEditor = true;
		CurEditor = MESH2D_EDITOR;
	}
	
}
// - ------------------------------------------------------------------------------------------ - //	
void cEditor::Draw()
{
	if( cGlobal::IsMesh2DEditor )
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
	}
	else
	{	
		if( MapEdit->IsHelp )
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
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
