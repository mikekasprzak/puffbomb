#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"

#include <Util/DirectoryCache.h>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cMapEdit::cMapEdit()/* :
	CollBaseDirName( "../../../../Content/PuffBOMB/2D/" ),
	CompBaseDirName( "2D/" ),
	CurColl( 0 ),
	CurComp( 0 ),
	CurSelComp( 0 )*/
{
	Camera->Pos.z = Global::HudZoom;
	
/*	Physics.ZeroGravity();
	Physics.Friction = Real( 0.8 );
	
	Log( LOG_HIGHEST_LEVEL, "Collection editor physics created" );

	FindCollCompPaths();
	
	Component.AnimationSet = new Engine2D::cComponentAnimationSet();
	Component.AnimationSet->LoadBinary( CompBaseDirName + ComponentPath[ CurComp ] );
	Component.Body = Component.AnimationSet->BodyPose[ 0 ];

	if( !CollectionPath.empty() )
	{
		Collection.LoadBinary( CollBaseDirName + CollectionPath[ CurColl ] );
	}
	*/
	CurMode = TILE_MODE;
}
// - ------------------------------------------------------------------------------------------ - //
cMapEdit::~cMapEdit()
{
	/*for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
	{
		delete Collection.Component[ idx ].AnimationSet;
	}*/
	
	//delete Component.AnimationSet;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Draw()
{
	Camera->Update();
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	Gfx::EnableDepth();

/*	// Draw our collection //
	Collection.Draw();

	Gfx::EnableAddBlend();

	if( CurMode == COLL_STATIC_COMP )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Collection.Component[ CurSelected[ idx ] ].Draw();
		}
	}
	else if( CurMode == COLL_DYNAMIC_COMP )
	{
		Collection.Component[ CurSelComp ].Draw();
	}
	else if( CurMode == COLL_NODE_LINK )
	{
		
	}
	else if( CurMode == COLL_HARD_NODE )
	{
		
	}
	

	Gfx::DisableAddBlend();
	
	Gfx::DisableTex2D();

	Gfx::SetLineWidth( 1.0 );

	Collection.DebugDraw();

	if( CurMode == COLL_DYNAMIC_COMP )
	{
		Gfx::SetLineWidth( 4.0 );
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Collection.Component[ CurSelComp ].Body.DrawNode( CurSelected[ idx ], true );
			
			for( size_t SphereIdx = 0; SphereIdx < Collection.Component[ CurSelComp ].Body.SphereSize(); ++SphereIdx )
			{
				if( CurSelected[idx] == Collection.Component[ CurSelComp ].Body.Sphere( SphereIdx ).Index )
				{
					Collection.Component[ CurSelComp ].Body.DrawSphere( SphereIdx, true );
				}
			}
		}
	}*/

	Gfx::DisableTex2D();
	Gfx::DisableDepth();
		
	Gfx::SetLineWidth( 1.0 );

	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
	
	DrawSelBox();

	Gfx::DisableBlend();
	
	HudDraw();
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::HudDraw()
{
	HudCamera->Update();
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	DisplayText();
/*	
	Gfx::PushMatrix();
	{
		Gfx::Translate( Global::Right - Real( 256 ), Global::Bottom + Real( 256 ), 0 );
		
		Component.Draw();
		
		Gfx::DisableTex2D();
			
		Component.DrawBody();

	}
	Gfx::PushMatrix();*/
	
	Gfx::DisableBlend();	

}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Step()
{
/*	// Makes my physics active //
	Physics.SetActive();
	// Step our collection (intenal physics system, based on physics above) //
	Collection.Step();
	
	CurMousePos = CalcMousePos();

	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CurMousePos;
	}
	
	if( CurMode == COLL_STATIC_COMP )
	{
		if( !isGroupMove )
		{
			StaticSelect();
			StaticAddComp();
			StaticDelete();
		}
		StaticMove();
	}
	else if( CurMode == COLL_DYNAMIC_COMP )
	{
		if( !isGroupMove )
		{
			DynSelect();
		}
		DynMove();		
	}
	else if( CurMode == COLL_NODE_LINK )
	{
		
	}
	else if( CurMode == COLL_HARD_NODE )
	{
		
	}
	SwitchColl();
	SwitchComp();
*/	
	SwitchMode();
	
	Save();

	// Handles scrolling around the map
	Scroll( Camera );
	
	// Handles the zooming in and out of a map
	Zoom( Real( 64.0 ), Camera );
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cMapEdit::CalcMousePos()
{
	Vector2D tempMousPos = Vector2D(
			Real( ( int( Mouse.x * Real( Global::HudW ) ) )
			- ( -Camera->Pos.x / Real( Camera->Pos.z / Global::HudZoom ) )
			- ( Real(Global::HudW >> 1) ) )
			* Real( Camera->Pos.z / Global::HudZoom ),
			Real( ( int( -Mouse.y * Real( Global::HudH ) ) )
			+ ( Camera->Pos.y / Real( Camera->Pos.z / Global::HudZoom ) )
			+ ( Global::HudH >> 1 ) )
			* Real( Camera->Pos.z / Global::HudZoom )
	);
	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchColl()
{
/*	if( IsSaved )
	{
		if( !CollectionPath.empty() )
		{
			if( Button[ KEY_MINUS_PAD ].Pressed() )
			{
				if( CurColl > 0 )
				{
					--CurColl;
				}
				else
				{
					CurColl = CollectionPath.size() - 1;
				}
				
				UpdateColl();
			}
			else if( Button[ KEY_PLUS_PAD ].Pressed() )
			{
				if( CurColl < CollectionPath.size() - 1 )
				{
					++CurColl;
				}
				else
				{
					CurColl = 0;	
				}
					
				UpdateColl();
			}
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchComp()
{
/*	if ( Button[ KEY_LEFT ].Pressed() ) 
	{
		if( !ComponentPath.empty() )
		{
			if( CurComp > 0 )
			{
				--CurComp;
			}
			else
			{
				CurComp = ComponentPath.size() - 1;
			}
			
			UpdatePreviewComp();
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( !ComponentPath.empty() )
		{
			if( CurComp < ComponentPath.size() - 1 )
			{
				++CurComp;
			}
			else
			{
				CurComp = 0;	
			}
				
			UpdatePreviewComp();
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchMode()
{	
	unsigned int LastMode = CurMode;

	if( Button[ KEY_1 ].Pressed() )
	{
		CurMode = TILE_MODE;
	}
	else if( Button[ KEY_2 ].Pressed() )
	{
		CurMode = ZONE_MODE;
	}
	else if( Button[ KEY_3 ].Pressed() )
	{
		CurMode = OBJECT_MODE;
	}
	else if( Button[ KEY_4 ].Pressed() )
	{
		CurMode = FREE_OBJECT_MODE;
	}
	else if( Button[ KEY_5 ].Pressed() )
	{
		CurMode = PASSIVE_OBJECT_MODE;
	}
	
	if( LastMode != CurMode )
	{
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ActiveAction()
{
	IsSaved = false;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Save()
{
	if( Button[ KEY_LCTRL ] && Button[ KEY_S ].Pressed() && !IsSaved )
	{
		/*if( !CollectionPath.empty() )
		{
			Collection.SaveBinary( CollBaseDirName + CollectionPath[ CurColl ] );
		}*/

		IsSaved = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
