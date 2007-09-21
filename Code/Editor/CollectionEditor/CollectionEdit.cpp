#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "CollectionEdit.h"

#include <FileIO/DirectoryCache.h>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cCollectionEdit::cCollectionEdit() :
	CollBaseDirName( "../../../../Content/PuffBOMB/2D/" ),
	CompBaseDirName( "2D/" ),
	CurColl( 0 ),
	CurComp( 0 ),
	CurSelComp( 0 ),
	LastComp( 0 ),
	LastNode( 0 )
{
	Camera->Pos.z = Global::HudZoom;
	Camera->NearClip = Real( 1.0 );
	
	Physics.ZeroGravity();
	Physics.Friction = Real( 0.8 );
	
	Log( LOG_HIGHEST_LEVEL, "Collection editor physics created" );

	FindCollCompPaths();

	Component = Engine2D::cDynamicComponent( 0, CompBaseDirName + ComponentPath[ CurComp ], Vector2D::Zero );

	if( !CollectionPath.empty() )
	{
		Collection.LoadBinary( CollBaseDirName + CollectionPath[ CurColl ] );
		
		Collection.UpdateAnchors();
	}
	
	CurMode = COLL_STATIC_COMP;
}
// - ------------------------------------------------------------------------------------------ - //
cCollectionEdit::~cCollectionEdit()
{

}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Draw()
{
	Camera->Update();
	
	Gfx::EnableBlend();
	
	Gfx::EnableTex2D();

	// Draw our collection //
	Collection.Draw();

	Gfx::AddBlend();

	if( CurMode == COLL_STATIC_COMP )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Collection.Component[ CurSelected[ idx ] ].Draw( 1 );
		}
	}
	else if( CurMode == COLL_DYNAMIC_COMP )
	{
		Collection.Component[ CurSelComp ].Draw( 1 );
	}
	else if( CurMode == COLL_NODE_LINK )
	{
		
	}
	else if( CurMode == COLL_HARD_NODE )
	{

	}
	
	Gfx::StandardBlend();

	Gfx::DisableTex2D();

	Gfx::SetLineWidth( 1.0 );

	Collection.DebugDraw();

	if( CurMode == COLL_DYNAMIC_COMP || CurMode == COLL_NODE_LINK || CurMode == COLL_HARD_NODE )
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
	}
	Gfx::SetLineWidth( 1.0 );

	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
		
	DrawSelBox();

	Gfx::DisableBlend();
	
	HudDraw();
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::HudDraw()
{
	HudCamera->Update();
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	DisplayText();
	
	Gfx::PushMatrix();
	{
		Gfx::Translate( Global::Right - Real( 256 ), Global::Bottom + Real( 256 ), 0 );
		
		Component.Draw( 1 );
		
		Gfx::DisableTex2D();
			
		Component.DrawBody();

	}
	Gfx::PushMatrix();
	
	Gfx::DisableBlend();	

}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Step()
{
	// Makes my physics active //
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
		DynSelect();
		NodeAddLink();
		NodeDeleteLink();
		
		if( Button[ KEY_LSHIFT ] )
		{
			NodeStrength( Real( 0.1 ) );
			NodeBreakPoint( Real( 0.1 ) );
		}
		else
		{
			NodeStrength( Real( 1 ) );
			NodeBreakPoint( Real( 1 ) );
		}
	}
	else if( CurMode == COLL_HARD_NODE )
	{
		DynSelect();
		HardAdd();
		HardDelete();
		
		if( Button[ KEY_LSHIFT ] )
		{
			HardStrength( Real( 0.1 ) );
			HardBreakPoint( Real( 0.1 ) );
		}
		else
		{
			HardStrength( Real( 1 ) );
			HardBreakPoint( Real( 1 ) );
		}
	}

	// Handles scrolling around the map
	Scroll( Camera );
	
	if( !Button[ KEY_LCTRL ] && !Button[ KEY_LALT ] )
	{
		// Handles the zooming in and out of a map
		Zoom( Real( 64.0 ), Camera );
	}
	
	SwitchColl();
	SwitchComp();
	
	SwitchMode();
	
	Save();
	
	Undo();
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cCollectionEdit::CalcMousePos()
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
void cCollectionEdit::Undo()
{
	// Resets the zoom
	if ( Button[ KEY_TAB ].Pressed() )
	{
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Global::HudZoom;
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
// Goes through all the dirs finding the .coll .comp files then stores them and there locations   //
void cCollectionEdit::FindCollCompPaths()
{
	cDirectoryCache CollDirCache( CollBaseDirName );
	
	for( size_t idx = 0; idx < CollDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( CollDirCache.File[idx] ) == ".coll" )
		{
			CollectionPath.push_back( CollDirCache.File[idx] );
		}
	}
	
	cDirectoryCache CompDirCache( CompBaseDirName );
	
	for( size_t idx = 0; idx < CompDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( CompDirCache.File[idx] ) == ".comp" )
		{
			Log( LOG_HIGHEST_LEVEL, "CompDirCache.File[idx] " << CompDirCache.File[idx] );
			
			ComponentPath.push_back( CompDirCache.File[idx] );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::UpdateColl()
{
	if( !Collection.Component.empty() )
	{
		/*for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
		{
			delete Collection.Component[ idx ].Animator.AnimationSet;
		}*/
		Collection.Component.clear();
		Collection.ComponentName.clear();
		Collection.NodeLink.clear();
		Collection.NodeAnchor.clear();
	}
	if( !CollectionPath.empty() )
	{
		Collection.LoadBinary( CollBaseDirName + CollectionPath[ CurColl ] );
		
		Collection.UpdateAnchors();
	}
	
	CurSelected.clear();	
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::UpdateCompPreview()
{
	Component = Engine2D::cDynamicComponent( 0, CompBaseDirName + ComponentPath[ CurComp ], Vector2D::Zero );
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::SwitchColl()
{
	if( IsSaved )
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::SwitchComp()
{
	if ( Button[ KEY_LEFT ].Pressed() ) 
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
			
			UpdateCompPreview();
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
				
			UpdateCompPreview();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::SwitchMode()
{	
	unsigned int LastMode = CurMode;

	if( Button[ KEY_1 ].Pressed() )
	{
		CurMode = COLL_STATIC_COMP;
	}
	else if( Button[ KEY_2 ].Pressed() )
	{
		CurMode = COLL_DYNAMIC_COMP;
	}
	else if( Button[ KEY_3 ].Pressed() )
	{
		CurMode = COLL_NODE_LINK;
	}
	else if( Button[ KEY_4 ].Pressed() )
	{
		CurMode = COLL_HARD_NODE;
	}
	
	if( LastMode != CurMode )
	{
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::ActiveAction()
{
	IsSaved = false;
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Save()
{
	if( Button[ KEY_LCTRL ] && Button[ KEY_S ].Pressed() && !IsSaved )
	{
		if( !CollectionPath.empty() )
		{
			Collection.SaveBinary( CollBaseDirName + CollectionPath[ CurColl ] );
		}

		IsSaved = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
