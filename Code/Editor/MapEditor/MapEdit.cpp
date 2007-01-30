#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"

#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"

#include <Util/DirectoryCache.h>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
#include <Util/String.h>
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cMapEdit::cMapEdit() :
	MapBaseDirName( "../../../../Content/PuffBOMB/Maps/" ),
	CurMap( 0 ),
	Mesh3DBaseDirName( "3D/" ),
	CurMesh3D( 0 ),
	CurLayer( 0 ),
	CurDyn( 0 ),
	CurSelColl( 0 ),
	CurSelComp( 0 ),
	CurPass( 0 ),
	CurZone( 0 ),
	CornerSize( 128 ),
	ResizeCorner( 0 ),
	CaptureDelay( 200 ), // if the game is running below 20-30fps this number may need to be raised to 600 or more.
	OffsetTime( 0 ),
	MiniMapLastMode( 0 )
{
	Camera->Pos.z = Global::HudZoom * Real( 4 );

	Physics.ZeroGravity();
	Physics.Friction = Real( 0.8 );
	
	Log( LOG_HIGHEST_LEVEL, "Map editor physics created" );
	
	FindMapMesh3DPaths();
	
	if( !Mesh3DName.empty() )
	{
		UpdateMesh3DPreview();
	}
	
	
	for ( size_t idx = 0; idx < 256; idx++ )
	{
		Engine2D::cDynamicCollection* TempDyn = CreateCollectionInstance( idx, Vector2D::Zero );
		
		if( TempDyn != 0 )
		{
			delete TempDyn;
			ActiveDyns.push_back( idx );
		}
		
		Engine2D::cPassiveObject* TempPass = CreatePassiveInstance( idx, Vector2D::Zero );
		
		if( TempPass != 0 )
		{
			delete TempPass;
			ActivePass.push_back( idx );
		}
	}
	
	if( !ActiveDyns.empty() )
	{
		DynPreview = CreateCollectionInstance( ActiveDyns[ CurDyn ], Vector2D( Global::Left, Global::Bottom ) + Vector2D( 256, 256 ) );
	}

	LoadZoneDesc();

	// Loads the map file //
	LoadMap();
	
	// Populate the MiniMapDynList //
	MiniMapDynList.push_back( 128 ); // BubblePlant //
	MiniMapDynList.push_back( 131 ); // TreeOne //
	
	CurMode = TILE_MODE;
	LastMode = CurMode;
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
	/*for ( size_t idx = 0; idx < Zone.size(); idx++ ) {
		delete Zone[ idx ];
	}*/
	
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
//	Gfx::SaturateBlend();

	if( CurMode == MINI_MAP_MODE )
	{
		// Draw Tiles (First, 'cause the objects as flat sprites clip 3D things funny) //
		for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
			
			if( Map.StaticObjectInstanceInfo[ idx ].FileName.find( "Scene" ) == std::string::npos )
			{
				StaticObjectInstance[ idx ].Draw();
			}
		}
	
		for ( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
		{
			bool isDrawn = false;
			for( size_t idx2 = 0; idx2 < MiniMapDynList.size(); ++idx2 )
			{
				if( Map.DynamicObjectInstanceInfo[ idx ].Id == MiniMapDynList[ idx2 ] )
				{
					isDrawn = true;
				}
			}
			if( isDrawn )
			{
				if ( DynamicCollection[ idx ]->IsActive() ) { 
					DynamicCollection[ idx ]->Draw();
				}
			}
		}
	}
	else
	{
		// Draw Tiles (First, 'cause the objects as flat sprites clip 3D things funny) //
		for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
			StaticObjectInstance[ idx ].Draw();
		}
	
		for ( size_t idx = 0; idx < DynamicCollection.size(); ++idx ) {
			if ( DynamicCollection[ idx ]->IsActive() ) { 
				DynamicCollection[ idx ]->Draw();
			}
		}
	
		Gfx::DisableTex2D();
	
		for ( size_t idx = 0; idx < PassiveObject.size(); ++idx ) {
			PassiveObject[ idx ]->DebugDraw();
		}
		
		Gfx::EnableTex2D();
	}
	// Draw selected //
	Gfx::AddBlend();

	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		if( CurMode == TILE_MODE )
		{
			// Draw selected mesh3d's //
			StaticObjectInstance[ CurSelected[ idx ] ].Draw();
		}
		else if( CurMode == OBJECT_MODE )
		{
			// Draw selected mesh3d's //
			DynamicCollection[ CurSelected[ idx ] ]->Draw();
		}
		else if( CurMode == PASSIVE_OBJECT_MODE )
		{
			
		}
	}
	if( CurMode == FREE_OBJECT_MODE )
	{
		if( !DynamicCollection.empty() )
		{
			DynamicCollection[ CurSelColl ]->Draw();
		}
	}

	Gfx::StandardBlend();

	Gfx::DisableDepth();
	Gfx::DisableTex2D();
	
	if( CurMode != ZONE_MODE && CurMode != MINI_MAP_MODE )
	{

		// Draw Tiles //
		for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
			StaticObjectInstance[ idx ].DrawBody();
		}
	}
	
	if( CurMode == TILE_MODE )
	{
	
	}
	else if( CurMode == ZONE_MODE )
	{
		DrawZones();
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
		for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
		{
			DynamicCollection[ idx ]->DebugDraw();
		}

		Gfx::SetLineWidth( 4.0 );
			
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DynamicCollection[ CurSelColl ]->Component[ CurSelComp ].Body.DrawNode( CurSelected[ idx ], true );
			
			for( size_t SphereIdx = 0; SphereIdx < DynamicCollection[ CurSelColl ]->Component[ CurSelComp ].Body.SphereSize(); ++SphereIdx )
			{
				if( CurSelected[idx] == DynamicCollection[ CurSelColl ]->Component[ CurSelComp ].Body.Sphere( SphereIdx ).Index )
				{
					DynamicCollection[ CurSelColl ]->Component[ CurSelComp ].Body.DrawSphere( SphereIdx, true );
				}
			}
		}
	}
	else if( CurMode == PASSIVE_OBJECT_MODE )
	{
		
		Gfx::SetLineWidth( 4.0 );
			
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			PassiveObject[ CurSelected[ idx ] ]->DebugDraw();
		}
	}
	Gfx::SetLineWidth( 1.0 );

	if( CurMode != ZONE_MODE && CurMode != MINI_MAP_MODE )
	{
		DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
		
		if( !isGroupMove )
		{
			DrawSelBox();
		}
	}

	Gfx::DisableBlend();
//	Gfx::DisableDepth();
	
	HudDraw();
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::HudDraw()
{
	HudCamera->Update();
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
//	Gfx::SaturateBlend();
	
	DisplayText();
	
	if( CurMode == TILE_MODE )
	{
		// Displays the preview mesh3d //
		Gfx::EnableDepth();

		Gfx::DrawMesh3D(
			Mesh3DPreview.Object->Mesh,
			Vector3D( Mesh3DPreview.Pos.x * Real( 3 ), Mesh3DPreview.Pos.y * Real( 3 ), Real( -Global::HudZoom * Real( 2 ) ) )
		);

		Gfx::DisableDepth();
	}
	else if( CurMode == ZONE_MODE )
	{
		
	}
	else if( CurMode == OBJECT_MODE )
	{
		if( DynPreview->IsActive() )
		{
	
			Gfx::PushMatrix();
			
			Gfx::Translate( Global::Left * Real( 2 ), Global::Bottom * Real( 2 ), Real( -Global::HudZoom * Real( 2 ) ) );
			
			DynPreview->Draw();
			
			Gfx::PopMatrix();
		}
	}
	else if( CurMode == FREE_OBJECT_MODE )
	{
		
	}
	else if( CurMode == PASSIVE_OBJECT_MODE )
	{
		
	}
	
	Gfx::DisableBlend();
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Step()
{
	// Makes my physics active //
	Physics.SetActive();

	// Step the collections in the map //
	for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
	{
		DynamicCollection[ idx ]->Step();
	}
	
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
		SwitchZone();
		
		if( !isGroupMove )
		{
			ResizeZone();
		}
		if( ResizeCorner == 0 )
		{
			if( !isGroupMove )
			{
				SelectZone();
			}
			MoveZone();
		}
		AddZone();
		DeleteZone();
		ChangeID();
		ChangeArg();
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
		if( !isGroupMove )
		{
			SelectDynFree();
		}
		MoveDynFree();
	}
	else if( CurMode == PASSIVE_OBJECT_MODE )
	{
		if( !isGroupMove )
		{
			SelectPass();	
			AddPass();
			DeletePass();
			SwitchPass();
			
			if( Button[ KEY_LSHIFT ] )
			{
				ChangeArg( 10 );
			}
			else
			{
				ChangeArg( 1 );
			}
		}
		MovePass();
	}
	else if( CurMode == MINI_MAP_MODE )
	{

		Vector2D CameraCenter = Vector2D::Zero;
		Vector2D P1 = Vector2D::Zero;
		Vector2D P2 = Vector2D::Zero;
		
		for( size_t idx = 0; idx < Map.ZoneInstanceInfo.size(); ++idx )
		{
			if( Map.ZoneInstanceInfo[ idx ].Id == 1 )
			{
				CameraCenter = Map.ZoneInstanceInfo[ idx ].BoundingRect.Center();
				
				P1 = Map.ZoneInstanceInfo[ idx ].BoundingRect.P1();
				P2 = Map.ZoneInstanceInfo[ idx ].BoundingRect.P2();
			}
		}
		
		Real XRatio = ( P2.x - P1.x ) / Real( 2 );
		Real YRatio = ( P2.y - P1.y ) / Real( 2 );
		
		XRatio /= Global::Right;
		YRatio /= Global::Top;
		
		if( XRatio > YRatio )
		{
			Camera->Pos = Vector3D( CameraCenter.x, CameraCenter.y, XRatio * Global::HudZoom );
		}	
		else
		{
			Camera->Pos = Vector3D( CameraCenter.x, CameraCenter.y, YRatio * Global::HudZoom );
		}
		
		/*Log( 10, "XRatio " << XRatio );
		Log( 10, "YRatio " << YRatio );
		Log( 10, "HudZoom " << Global::HudZoom );
		Log( 10, "Camera->Pos.z " << Camera->Pos.z );*/
		
		if( GetTime() > OffsetTime && IsSaved )
		{
			CurMode = MiniMapLastMode;
			SaveScreenshot();
		}
	}
		
	SaveMap();

	SwitchMode();
	SwitchMap();

	Reset();

	// Handles scrolling around the map
	Scroll( Camera );

	if( CurMode == ZONE_MODE )
	{
		// Handles the zooming in and out of a map
		Zoom( Real( 512.0 ), Camera );
	}
	else
	{
		if( !Button[ KEY_LCTRL ] )
		{
			// Handles the zooming in and out of a map
			Zoom( Real( 256.0 ), Camera );
		}
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
			size_t LevelValue = 1;
			if( Button[ KEY_LSHIFT ] )
			{
				LevelValue = 10;
			}
			
			if( Button[ KEY_MINUS_PAD ].Pressed() )
			{
				if( CurMap >= LevelValue )
				{
					CurMap -= LevelValue;
				}
				else
				{
					CurMap = MapPath.size() - 1;
				}

				LoadMap();
				CurSelected.clear();
			}
			else if( Button[ KEY_PLUS_PAD ].Pressed() )
			{
				if( CurMap < MapPath.size() - LevelValue )
				{
					CurMap += LevelValue;
				}
				else
				{
					CurMap = 0;	
				}

				LoadMap();
				CurSelected.clear();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchMode()
{	
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
	else if( Button[ KEY_0 ].Pressed() )
	{
		CurMode = MINI_MAP_MODE;
	}
	
	if( LastMode != CurMode )
	{
		CurSelected.clear();
		
		if( CurMode == MINI_MAP_MODE )
		{
			Gfx::DisableMouseDraw();
			MiniMapLastMode = LastMode;
			OffsetTime = GetTime() + CaptureDelay;
		}
		else
		{
			Gfx::EnableMouseDraw();
		}
		
	}
	
	LastMode = CurMode;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ActiveAction()
{
	IsSaved = false;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::LoadMap()
{
	Map.LoadBinary( MapBaseDirName + MapPath[ CurMap ] );
	
	// Static Object part //
	{
		StaticObjectInstance.clear();
		
		for ( size_t idx = 0; idx < Map.StaticObjectInstanceInfo.size(); idx++ )
		{
			StaticObjectInstance.push_back(
				Engine2D::cStaticObjectInstance(
					Map.StaticObjectInstanceInfo[ idx ].FileName,
					Map.StaticObjectInstanceInfo[ idx ].Pos //,
//					Map.StaticObjectInstanceInfo[ idx ].Arg
				)
			);
			
			StaticObjectInstance.back().Object->CalcBoundingRect();
			Map.StaticObjectInstanceInfo[ idx ].Layer = CurLayer;

		}
	}
	
	// Dynamic Object part //
	{
		// Delete the collections //
		for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ ) {
			delete DynamicCollection[ idx ];
		}

		DynamicCollection.clear();
		
		for ( size_t idx = 0; idx < Map.DynamicObjectInstanceInfo.size(); idx++ )
		{
			DynamicCollection.push_back(
				CreateCollectionInstance(
					Map.DynamicObjectInstanceInfo[ idx ].Id,
					Map.DynamicObjectInstanceInfo[ idx ].Pos,
					Map.DynamicObjectInstanceInfo[ idx ].Arg
				)
			);
			
			for ( size_t idx2 = 0; idx2 < Map.DynamicObjectInstanceInfo[ idx ].Component.size(); idx2++ )
			{
				for ( size_t idx3 = 0; idx3 < Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos.size(); idx3++ )
				{
					DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Pos( idx3 ) =
						Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ];
						
					DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Old( idx3 ) =
						Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ];					
				}
			}
		}
	}
	
	
	// Passive Object Part //
	{
		// Delete the collections //
		for ( size_t idx = 0; idx < PassiveObject.size(); idx++ ) {
			delete PassiveObject[ idx ];
		}
		
		PassiveObject.clear();
	
		for( size_t idx = 0; idx < Map.PassiveObjectInstanceInfo.size(); ++idx )
		{
			PassiveObject.push_back( CreatePassiveInstance( 
				Map.PassiveObjectInstanceInfo[ idx ].Id,
				Map.PassiveObjectInstanceInfo[ idx ].Pos,
				Map.PassiveObjectInstanceInfo[ idx ].Arg
				)
			);
		}
	}
	
	// Zones Part //
	{
		Zone.clear();
	
		for( size_t idx = 0; idx < Map.ZoneInstanceInfo.size(); ++idx )
		{
			Zone.push_back( Engine2D::cZone( 
				Map.ZoneInstanceInfo[ idx ].BoundingRect,
				Map.ZoneInstanceInfo[ idx ].Id,
				Map.ZoneInstanceInfo[ idx ].Arg
				)
			);
		}
	}
		
	for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ )
	{
		DynamicCollection[ idx ]->UpdateAnchors();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SaveMap()
{
	if( Button[ KEY_LCTRL ] && Button[ KEY_S ].Pressed() && !IsSaved )
	{
		if( !MapPath.empty() )
		{
			
			// Static Object Part //
			
			// Dynamic Object Part //
			for( size_t idx = 0; idx < Map.DynamicObjectInstanceInfo.size(); ++idx )
			{
				Map.DynamicObjectInstanceInfo[ idx ].Component.clear();
				
				Map.DynamicObjectInstanceInfo[ idx ].Component.resize( DynamicCollection[ idx ]->Component.size() );
	
				for( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); ++idx2 )
				{
					Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos.resize( DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Size() );
	
					for( size_t idx3 = 0; idx3 < DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Size(); ++idx3 )
					{
						Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ]
							= DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Pos( idx3 );
					}
				}
			}
			
			// Passive Object Part //
			
			// Zones Part //
			Map.ZoneInstanceInfo.clear();
			
			Map.ZoneInstanceInfo.resize( Zone.size() );

			for( size_t idx = 0; idx < Map.ZoneInstanceInfo.size(); ++idx )
			{
				Map.ZoneInstanceInfo[ idx ].BoundingRect = Zone[ idx ].BoundingRect;
				Map.ZoneInstanceInfo[ idx ].Id = Zone[ idx ].Id;
				Map.ZoneInstanceInfo[ idx ].Arg = Zone[ idx ].Argument;
			}
			
			Map.SaveBinary( MapBaseDirName + MapPath[ CurMap ] );
		}

		IsSaved = true;
		
		// Needed to refresh the map before we generate the minimap image //
		// Reason: when saving tiles it sorts before writing them //
		// However this breaks the Layering for the editor //
		LoadMap();
		
		CurMode = MINI_MAP_MODE;
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
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Reset()
{
	if( Button[ KEY_TAB ].Pressed() )
	{
		// Resets to default values //
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Global::HudZoom * Real( 4 );
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SaveScreenshot()
{
	std::string DirPrefix = "../Data/Maps/";
	
	std::string MiniMapName = DirPrefix + MapPath[ CurMap ];
	
	MiniMapName = MiniMapName.substr( 0, MiniMapName.size() - 4 ) + ".blackkey.quarter.tx";
	
	Log( LOG_HIGHEST_LEVEL, "Writing " << MiniMapName );
	
	std::ofstream outfile ( MiniMapName.c_str(), std::ofstream::binary );

	void* Pixels = Gfx::ScreenShot();

//	unsigned int PixelSize = 3;
	unsigned int PixelSize = 4;
	unsigned int Width = Global::ScreenW;
	unsigned int Height = Global::ScreenH;
	
	outfile.write( (char*)&PixelSize, sizeof( unsigned int ) );
	outfile.write( (char*)&Width, sizeof( unsigned int ) );
	outfile.write( (char*)&Height, sizeof( unsigned int ) );
	
	outfile.write( ( char* )Pixels, PixelSize * ( Width * Height ) );
	outfile.close();
	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
