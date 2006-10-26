#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "CollectionEdit.h"

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
	CurComp( 0 )
{
	Camera->Pos.z = Global::HudZoom;
	
	Physics.ZeroGravity();
	
	Log( LOG_HIGHEST_LEVEL, "Collection editor physics created" );

	FindCollCompPaths();
	
	Component.AnimationSet = new Engine2D::cComponentAnimationSet();
	Component.AnimationSet->LoadBinary( CompBaseDirName + ComponentPath[ CurComp ] );
	Component.Body = Component.AnimationSet->BodyPose[ 0 ];

/*	Collection.Component.push_back( Engine2D::cDynamicComponent() );
	Collection.Component[ 0 ].AnimationSet = new Engine2D::cComponentAnimationSet();
	Collection.Component[ 0 ].AnimationSet->LoadBinary( "2D/Hamster/Body/HamsterBody.bin.comp" );
	Collection.Component[ 0 ].Body = Collection.Component[ 0 ].AnimationSet->BodyPose[ 0 ];*/
	
	CurMode = COLL_STATIC_COMP;
	
}
// - ------------------------------------------------------------------------------------------ - //
cCollectionEdit::~cCollectionEdit()
{
	for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
	{
		delete Collection.Component[ idx ].AnimationSet;
	}

	delete Component.AnimationSet;
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Draw()
{
	Camera->Update();
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	Gfx::EnableDepth();


	Gfx::DisableDepth();

	// Draw our collection //
	Collection.Draw();

	Gfx::EnableAddBlend();

	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		Collection.Component[ CurSelected[ idx ] ].Draw();
	}

	Gfx::DisableAddBlend();
	
	Gfx::DisableTex2D();

	Collection.DebugDraw();


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
		
		Component.Draw();
		
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

	// Handles scrolling around the map
	Scroll( Camera );
	
	// Handles the zooming in and out of a map
	Zoom( Real( 64.0 ), Camera );
	
	SwitchComp();
	
	SwitchMode();
	
	AddComp();
	
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
			ComponentPath.push_back( CompDirCache.File[idx] );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::UpdatePreviewComp()
{
	delete Component.AnimationSet;	
	
	Component.AnimationSet = new Engine2D::cComponentAnimationSet();
	Component.AnimationSet->LoadBinary( CompBaseDirName + ComponentPath[ CurComp ] );
	Component.Body = Component.AnimationSet->BodyPose[ 0 ];
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::AddComp()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{	
		CurSelected.clear();
		
		Collection.Component.push_back( Engine2D::cDynamicComponent() );
		
		int CSize = Collection.Component.size() - 1;
				
		Collection.Component[ CSize ].AnimationSet = new Engine2D::cComponentAnimationSet();
		Collection.Component[ CSize ].AnimationSet->LoadBinary( CompBaseDirName + ComponentPath[ CurComp ] );
		
		Vector2D AddPos = CurMousePos;
		
		if( !Button[ KEY_LSHIFT ] )
		{
			SetGridDepth( Camera, CurrentGridDepth, 40.0 );
			SetGridArray( CurrentGridDepth, GridDepth );

			CalcSnapToGrid( AddPos, CurrentGridDepth, GridDepth );
		}
		
		for( size_t idx = 0; idx < Collection.Component[ CSize ].AnimationSet->BodyPose.size(); ++idx )
		{
			for( size_t idx2 = 0; idx2 < Collection.Component[ CSize ].AnimationSet->BodyPose[ idx ].Node.size(); ++idx2 )
			{
				Collection.Component[ CSize ].AnimationSet->BodyPose[ idx ].Node[ idx2 ].Pos += AddPos;
			}
		}
		
		Collection.Component[ CSize ].Body = Collection.Component[ CSize ].AnimationSet->BodyPose[ 0 ];
		
		//Collection.Component[ CSize ].Body.CalcBoundingRect();
		
		CurSelected.push_back( CSize );
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
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
