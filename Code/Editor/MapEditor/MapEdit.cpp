#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"

#include "CreateCollectionInstance.h"

#include <Util/DirectoryCache.h>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cMapEdit::cMapEdit() :
	MapBaseDirName( "../../../../Content/PuffBOMB/Maps/" ),
	CurMap( 0 ),
	Mesh3DBaseDirName( "3D/" ),
	CurMesh3D( 0 ),
	CurLayer( 0 ),
	CurDyn( 0 )
{
	Camera->Pos.z = Global::HudZoom;
	
	FindMapMesh3DPaths();
	
	if( !Mesh3DName.empty() )
	{
		UpdateMesh3DPreview();
	}
	
	
	for ( size_t idx = 0; idx < 256; idx++ )
	{
		Engine2D::cDynamicCollection* TempDyn = Engine2D::CreateCollectionInstance( idx, Vector2D::Zero );
		
		if( TempDyn != 0 )
		{
			delete TempDyn;
			ActiveDyns.push_back( idx );
		}
	}
	
	if( !ActiveDyns.empty() )
	{
		DynPreview = Engine2D::CreateCollectionInstance( ActiveDyns[ CurDyn ], Vector2D( Global::Left, Global::Bottom ) + Vector2D( 256, 256 ) );
	}

	CurMode = TILE_MODE;
}
// - ------------------------------------------------------------------------------------------ - //
cMapEdit::~cMapEdit()
{
	// Delete the collections //
	for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ ) {
		delete DynamicCollection[ idx ];
	}

	// Delete PassiveObject's //
	for ( size_t idx = 0; idx < PassiveObject.size(); idx++ ) {
		delete PassiveObject[ idx ];
	}

	// Delete Zones //
	for ( size_t idx = 0; idx < Zone.size(); idx++ ) {
		delete Zone[ idx ];
	}
	
	if( DynPreview != 0 )
	{
		delete DynPreview;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Draw()
{
	Camera->Update();
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	Gfx::EnableDepth();

	// Draw Tiles (First, 'cause the objects as flat sprites clip 3D things funny) //
	for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
		StaticObjectInstance[ idx ].Draw();
	}

	for ( size_t idx = 0; idx < DynamicCollection.size(); ++idx ) {
		if ( DynamicCollection[ idx ]->IsActive() ) { 
			DynamicCollection[ idx ]->Draw();
		}
	}

	// Draw selected //
	Gfx::EnableAddBlend();

	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		if( CurMode == TILE_MODE )
		{
			// Draw selected mesh3d's //
			StaticObjectInstance[ CurSelected[ idx ] ].Draw();
		}
		else if( CurMode == ZONE_MODE )
		{
			
		}
		else if( CurMode == OBJECT_MODE )
		{
			// Draw selected mesh3d's //
			DynamicCollection[ CurSelected[ idx ] ]->Draw();
		}
		else if( CurMode == FREE_OBJECT_MODE )
		{
			
		}
		else if( CurMode == PASSIVE_OBJECT_MODE )
		{
			
		}
	}
	Gfx::DisableAddBlend();

	Gfx::DisableDepth();
	Gfx::DisableTex2D();
	
	// Draw Tiles //
	for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
		StaticObjectInstance[ idx ].DrawBody();
	}

	if( CurMode == TILE_MODE )
	{
	
	}
	else if( CurMode == ZONE_MODE )
	{
		
	}
	else if( CurMode == OBJECT_MODE )
	{
		for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
		{
			DynamicCollection[ idx ]->DebugDraw();
		}
	}
	else if( CurMode == FREE_OBJECT_MODE )
	{
		
	}
	else if( CurMode == PASSIVE_OBJECT_MODE )
	{
		
	}

	if( CurMode != ZONE_MODE )
	{
		Gfx::SetLineWidth( 1.0 );
	
		DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
		
		if( !isGroupMove )
		{
			DrawSelBox();
		}
	}

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
	
	Gfx::EnableAddBlend();
		
	if( CurMode == TILE_MODE )
	{
		// Displays the preview mesh3d //
		Gfx::DrawMesh3D(
			Mesh3DPreview.Object->Mesh,
			Mesh3DPreview.Pos.ToVector3D()
		);
	}
	else if( CurMode == ZONE_MODE )
	{
		
	}
	else if( CurMode == OBJECT_MODE )
	{
		if( DynPreview->IsActive() )
		{ 
			DynPreview->Draw();
		}
	}
	else if( CurMode == FREE_OBJECT_MODE )
	{
		
	}
	else if( CurMode == PASSIVE_OBJECT_MODE )
	{
		
	}
	
	Gfx::DisableAddBlend();

	
	
	Gfx::DisableBlend();
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Step()
{
	CurMousePos = CalcMousePos();

	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CurMousePos;
	}
	
	if( CurMode == TILE_MODE )
	{
		if( !isGroupMove )
		{
			SelectMesh3D();	
			AddMesh3D();
			DeleteMesh3D();
			SwitchMesh3D();
			SwitchLayer();
		}
		MoveMesh3D();
	}
	else if( CurMode == ZONE_MODE )
	{
		
	}
	else if( CurMode == OBJECT_MODE )
	{
		if( !isGroupMove )
		{
			SelectDyn();	
			AddDyn();
			DeleteDyn();
			SwitchDyn();
		}
		MoveDyn();
	}
	else if( CurMode == FREE_OBJECT_MODE )
	{
		
	}
	else if( CurMode == PASSIVE_OBJECT_MODE )
	{
		
	}
	
	SwitchMode();
	SwitchMap();
	
	Save();
	
	Reset();

	// Handles scrolling around the map
	Scroll( Camera );

	if( CurMode == ZONE_MODE )
	{
		// Handles the zooming in and out of a map
		Zoom( Real( 256.0 ), Camera );
	}
	else
	{
		// Handles the zooming in and out of a map
		Zoom( Real( 64.0 ), Camera );
	}
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
void cMapEdit::SwitchMap()
{
	if( IsSaved )
	{
		if( !MapPath.empty() )
		{
			if( Button[ KEY_MINUS_PAD ].Pressed() )
			{
				if( CurMap > 0 )
				{
					--CurMap;
				}
				else
				{
					CurMap = MapPath.size() - 1;
				}
			}
			else if( Button[ KEY_PLUS_PAD ].Pressed() )
			{
				if( CurMap < MapPath.size() - 1 )
				{
					++CurMap;
				}
				else
				{
					CurMap = 0;	
				}
			}
		}
	}
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
		/*if( !MapPath.empty() )
		{
			
		}*/

		IsSaved = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Goes through all the dirs finding the .coll .comp files then stores them and there locations   //
void cMapEdit::FindMapMesh3DPaths()
{
	// Find all the .map files //
	cDirectoryCache MapDirCache( MapBaseDirName );
	
	for( size_t idx = 0; idx < MapDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( MapDirCache.File[idx] ) == ".map" )
		{
			//std::string TmpString = String::FileName( MapDirCache.File[idx] );
			
			//Log( LOG_HIGHEST_LEVEL, "Map " << TmpString );
			MapPath.push_back( MapDirCache.File[idx] );
		}
	}

	// Find all the .mesh3d files //
	cDirectoryCache MeshDirCache( Mesh3DBaseDirName );
	
	for( size_t idx = 0; idx < MeshDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( MeshDirCache.File[idx] ) == ".mesh3d" )
		{
			std::string TmpString = String::FileName( MeshDirCache.File[idx] );
			//Log( LOG_HIGHEST_LEVEL, "Mesh3D " << TmpString );
			Mesh3DName.push_back( TmpString );
		}
	}

	// Find all the .coll files //
/*	cDirectoryCache DynDirCache( DynBaseDirName );
	
	for( size_t idx = 0; idx < DynDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( DynDirCache.File[idx] ) == ".coll" )
		{
			//Log( LOG_HIGHEST_LEVEL, "Coll " << DynDirCache.File[idx] );
		//	DynPath.push_back( DynDirCache.File[idx] );
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Reset()
{
	if( Button[ KEY_TAB ].Pressed() )
	{
		// Resets to default values //
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Global::HudZoom;
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
