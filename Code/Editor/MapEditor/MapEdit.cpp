#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <iostream>
#include <iomanip>

// !!!! OPENGL !!!! //
#include <SDL/SDL.h>
#include <gl/gl.h>
#include <gl/glu.h>
// !!!! OPENGL !!!! //

// For FPS test //
#include <Global.h>
#include <Font/Fonts.h>
#include <sstream>
// ------------ //

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
//cMapEdit::cMapEdit( cGame& _Game, cMesh2DEdit& _Mesh2DEdit ) :
//	Game( &_Game ),
//	Mesh2DEdit( &_Mesh2DEdit ),
//cMapEdit::cMapEdit( cGame& _Game ) : // Removed because of game dependency //
//	Game( &_Game ),
cMapEdit::cMapEdit() :
	GameZoom( 0.0 ),
	CurMesh( 0 ),
	SceneryIdx( -1 ),
	CurrentObject( 0 ),
	Focus1( 0 ),
	Focus2( 0 ),
	isPaste( false ),
	CurZone( 0 ),
	CurMode( 1 ),
	CornerSize( 128 ),
	ResizeCorner( 0 )
{
	Focus = Vector2D( Real(0.0), Real(0.0) );
	Log( LOG_HIGHEST_LEVEL, "MapEdit Constructor (Editor) " );
	
	ListModels();
	Log( LOG_HIGHEST_LEVEL, "ListModels Complete " );

	MapName = "Level00.map";
//	DirMapName = CurrentDir + "Maps/" + MapName;
	DirMapName = "Maps/" + MapName;
	LoadMap( DirMapName );
	Log( LOG_HIGHEST_LEVEL, "LoadMap Complete " );
		
	ActiveAction();
	isSaved = true;

	LoadZoneDesc();

}	
// - ------------------------------------------------------------------------------------------ - //	
cMapEdit::~cMapEdit()
{
	Log( LOG_HIGHEST_LEVEL, "~cMapEdit()" );

}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Step()
{
	// Handles scrolling around the map
	Scroll( Camera );
	
	// Handles the zooming in and out of a map
	Zoom( Real( 256.0 ), Camera );
	
	// Toggles the physics 
	Physics();

	if( CurMode == OBJECT_MODE )
	{
		
		AddObject();
		PasteObject();
		
		SwitchMesh();
	
		Undo();

		if( !MapObject.empty() )
		{
			if( !isGroupMove )
			{
				SelectObject();
			}
			CopyObject();
			
			MoveObject();
			
			DeleteObject();
		}

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
	else if( CurMode == TILE_MODE )
	{
		SwitchModel();
		
		AddModel();
		DeleteModel();
		
		if( !isGroupMove )
		{
			SelectModel();
		}
		MoveModel();

	}
	SaveMap( DirMapName.c_str() );
	
	if( !isGroupMove )
	{
		SwitchMode();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Draw()
{
	Gfx::EnableTex2D();
	Gfx::EnableDepth();
	Gfx::EnableBlend();
	
	// Draw Scenery 3D Model //
	for( size_t idx = 0; idx < Model.size(); ++idx )
	{
		// REMOVED TEMORARILY AS MICHAEL CHANGED DRAWMESH3D //
//		Gfx::DrawMesh3d( &Model[idx] );

	}
	Gfx::DisableDepth();
	Gfx::DisableTex2D();
	
	// Draws all the 2D information in the map
	Draw2D();
	
	if( CurMode == OBJECT_MODE )
	{
		DrawSelBox();
		
		// Draws the currently selected Object or Objects
		DrawSelected();
		// Displays any text in the map editor

		DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
	}	
//	else if( CurMode == ZONE_MODE && !Game->Zone.empty() )
	else if( CurMode == ZONE_MODE )
	{
		DrawZones();
	}
	else if( CurMode == TILE_MODE )
	{
		Gfx::EnableTex2D();

		// Enables additive blending //
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		
		DrawSelModel();
		
		// Disables additive blending //
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Gfx::DisableTex2D();	
		
		DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );

		DrawSelBox();
	}
	Gfx::DisableBlend();
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::HudDraw()
{
/*	if( CurMode == OBJECT_MODE )
	{
		Mesh2DEdit->Object[CurMesh].CalcBoundingRect();
		Vector2D Point1 = Mesh2DEdit->Object[CurMesh].BoundingRect.P1();
		Vector2D Point2 = Mesh2DEdit->Object[CurMesh].BoundingRect.P2();
	
		Point1.x = ( ( Global::HudW >> 1 ) - Point2.x );
		Point1.y = ( -( Global::HudH >> 1 ) - Point1.y );

		DrawMesh( CurMesh, Point1 );
	}*/
	if( CurMode == TILE_MODE )
	{
		glEnable( GL_TEXTURE_2D );
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		for( size_t i = 0; i < ModelList[CurModel].Mesh3d->Data.size(); ++i )
		{
			cMesh3d& ThisMesh = *ModelList[CurModel].Mesh3d;
				
			glBindTexture( GL_TEXTURE_2D, ThisMesh.Data[i].TextureID );
			
			glVertexPointer(3, GL_FLOAT, 0, &(*ThisMesh.Data[i].Vertex)[0]);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, &(*ThisMesh.Data[i].VertexColor)[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &(*ThisMesh.Data[i].TextureCoord)[0]);
	
			glPushMatrix();
			glTranslatef( ModelList[CurModel].Offset.x, ModelList[CurModel].Offset.y, ModelList[CurModel].Offset.z );
			glDrawElements(
				GL_TRIANGLES, ThisMesh.Data[i].Indices->Size(),
				GL_UNSIGNED_INT, &(*ThisMesh.Data[i].Indices)[0]
			);
			glPopMatrix();
		}
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisable( GL_TEXTURE_2D );

	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glDisable( GL_DEPTH_TEST );

	DisplayText();
	
//  DISPLAYS FPS  //
//	std::stringstream Temp;
//	Temp << Global::FPS;
//	std::string TempString = Temp.str();
//	
//	Vector3D TempPos = Vector3D( Global::Left, Global::Top - Real( 45 ), 0.0 );
//
//	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), gfx::RGBA( 184, 0, 0, 255 ) );
// -------------- //

	glEnable( GL_DEPTH_TEST );

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Draw2D()
{
//	// Draw scenery collision information //
//	for ( size_t idx = 0; idx < Game->StaticObject.size(); ++idx ) {
//		Game->StaticObject[ idx ]->DebugDraw( );
//	}
//
//	for ( size_t idx = 0; idx < MapObject.size(); ++idx )
//	{
//		DrawMesh( MapObject[idx].MeshIdx, MapObject[idx].Pos );
//	}
//
///*	// Draw PolyObjects //
//	for ( size_t idx = 0; idx < Game->PolyObject.size(); ++idx ) {
//		Game->PolyObject[ idx ]->DebugDraw( );
//	}*/
//
//	// Draw Node Links //
//	for ( size_t idx = 0; idx < Game->NodeLink.size(); ++idx ) {
//		if ( Game->NodeLink[ idx ]->IsActive() ) { 
//			Game->NodeLink[ idx ]->DebugDraw( );
//		}
//	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawMesh( int idx, Vector2D MapPos )
{
/*	Mesh2DEdit->Object[idx].DebugDraw(
		Gfx::RGBA( 0, 255, 0, 255 ), Gfx::RGBA( 255, 0, 0, 255 ), MapPos );

//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
	Gfx::EnableTex2D();
	
	if( Mesh2DEdit->DisplayMesh[idx].TextureIdx != -1 )
	{
		glBindTexture( GL_TEXTURE_2D,
			Mesh2DEdit->TextureID[ Mesh2DEdit->DisplayMesh[idx].TextureIdx ] );
	}
	
//	for( int ii = Mesh2DEdit->CheckLow( idx ); ii <= Mesh2DEdit->CheckHigh( idx ); ++ii )
	{
		for( size_t i = 0; i < Mesh2DEdit->DisplayMesh[ idx ].Face.size(); ++i )
		{
			glColor3ub( 255, 255, 255 );
			
	//		if( Mesh2DEdit->DisplayMesh[ idx ].Face[i].Layer == ii )
			{
				gfx::Face( 
					Mesh2DEdit->DisplayMesh[ idx ].Pos(
						Mesh2DEdit->DisplayMesh[ idx ].Face[i].Vertex.a )
						+ MapPos,
					Mesh2DEdit->DisplayMesh[ idx ].Pos(
						Mesh2DEdit->DisplayMesh[ idx ].Face[i].Vertex.b )
						+ MapPos,
					Mesh2DEdit->DisplayMesh[ idx ].Pos(
						Mesh2DEdit->DisplayMesh[ idx ].Face[i].Vertex.c )
						+ MapPos,
					Mesh2DEdit->DisplayMesh[ idx ].Face[i].UV.a,
					Mesh2DEdit->DisplayMesh[ idx ].Face[i].UV.b,
					Mesh2DEdit->DisplayMesh[ idx ].Face[i].UV.c
				);
			}
		}
	}
	Gfx::DisableTex2D();

//	glDisable(GL_BLEND);
//	glDisable(GL_TEXTURE_2D);*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ToggleEdit()
{
//	Global::Origin = Focus;
	
	if( Global::DebugDraw & Global::flExtraInfo )
	{
		Global::DebugDraw ^= Global::flExtraInfo;
	}
	if( Global::DebugDraw & Global::flCollision )
	{
		Global::DebugDraw ^= Global::flCollision;
	}
	//Global::DebugDraw |= Global::flExtraInfo;
	//Global::DebugDraw |= Global::flCollision;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ToggleGame()
{
//	Focus = Global::Origin;
 	
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Physics()
{
	if ( Button[ KEY_TAB ].Pressed() ) {
//		for ( size_t idx = 0; idx < Game->SphereObject.size(); ++idx ) {
//			Game->SphereObject[ idx ]->Reset();
//		}
/*		for ( size_t idx = 0; idx < Game->PolyObject.size(); ++idx ) {
			Game->PolyObject[ idx ]->Reset();
		}*/
		// Resets the zoom
		Scale = Real::One;
//		Global::Origin.x = 0;
//		Global::Origin.y = 0;
			
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Global::HudZoom;
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;
	}
	// Step Physics
//	if( Button[ KEY_RCTRL ] )
//	{
//		Game->Step();
//	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawSelected()
{
/*	if( !MapObject.empty() )
	{
		glLineWidth( 4 );
		
		Mesh2DEdit->Object[MapObject[CurrentObject].MeshIdx].DebugDraw(
			Gfx::RGBA( 0, 192, 0, 255 ), Gfx::RGBA( 0, 128, 255, 255 ), MapObject[CurrentObject].Pos );

		glLineWidth( 1.5 );

		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Mesh2DEdit->Object[MapObject[CurSelected[idx]].MeshIdx].DebugDraw(
				Gfx::RGBA( 0, 192, 0, 255 ), Gfx::RGBA( 0, 255, 128, 255 ), MapObject[CurSelected[idx]].Pos );
		}
	}
	*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawSelBox()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcMousePos();
	}

	if( Button[ MOUSE_1 ] )
	{
		if( !isGroupMove )
		{
			Vector2D CurMousePos = CalcMousePos();
			Gfx::Rect( OldMousePos, CurMousePos, Gfx::RGBA( 255, 255, 255, 255 ) );
		}
		else if( SnapToGrid )
		{
			if( CurMode != TILE_MODE )
			{
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					DrawSnapToGrid( idx );
				}
			}
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
void cMapEdit::SelectObject()
{
/*	if( Button[ MOUSE_1 ].Released() )
	{	
		Vector2D CurMousePos = CalcMousePos();
		if( Button[ KEY_LSHIFT ] )
		{
			for( size_t idx = 0; idx < MapObject.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
				Vector2D PointA =
					Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P1() + MapObject[idx].Pos;
				Vector2D PointB =
					Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P2() + MapObject[idx].Pos;
				
				RadiusRect2D Boundy = RadiusRect2D::Pair( PointA, PointB );

				if( Selection == Boundy )
				{
					bool CurSelectedTest = false;
					for( size_t i = 0; i < CurSelected.size(); ++i )
					{
						if( CurSelected[i] == idx )
						{
							CurSelectedTest = true;
						}
					}
					if( !CurSelectedTest )
					{
						CurrentObject = idx;
						CurSelected.push_back( idx );
					}
				}
			}
		}
		else if( Button[ KEY_LCTRL ] )
		{			
			for( size_t idx = 0; idx < MapObject.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
				Vector2D PointA =
					Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P1() + MapObject[idx].Pos;
				Vector2D PointB =
					Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P2() + MapObject[idx].Pos;
				
				RadiusRect2D Boundy = RadiusRect2D::Pair( PointA, PointB );

				if( Selection == Boundy )
				{
					for( size_t i = 0; i < CurSelected.size(); ++i )
					{
						if( CurSelected[i] == idx )
						{
							std::vector <size_t> tempVec;
							for( size_t vec = 0; vec < CurSelected.size(); ++vec )
							{
								if( CurSelected[vec] != idx )
								{
									tempVec.push_back( CurSelected[vec] );
								}
							}
							CurSelected.swap( tempVec );
						}
					}
				}
			}
		}
		else
		{
			CurSelected.clear();
			
			for( size_t idx = 0; idx < MapObject.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
				Vector2D PointA =
					Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P1() + MapObject[idx].Pos;
				Vector2D PointB =
					Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P2() + MapObject[idx].Pos;
				
				RadiusRect2D Boundy = RadiusRect2D::Pair( PointA, PointB );

				if( Selection == Boundy )
				{
					CurrentObject = idx;
					CurSelected.push_back( idx );
				}
			}
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
int cMapEdit::SingleSelect( Vector2D &CurMousePos )
{
/*	for ( size_t idx = 0; idx < MapObject.size(); ++idx )
	{
		Vector2D PointA =
			Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P1() + MapObject[idx].Pos;
		Vector2D PointB =
			Mesh2DEdit->Object[MapObject[idx].MeshIdx].BoundingRect.P2() + MapObject[idx].Pos;
		
		if( WithinBox( CurMousePos, PointA, PointB ) )
		{
			return idx;
		}
	}
	*/
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MoveObject()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] )
		{
			Vector2D CurMousePos = CalcMousePos();
			int temp = SingleSelect( CurMousePos );
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				if( temp == int(CurSelected[idx]) )
				{
					isGroupMove = true;
				}
			}
		}
		// Snaps to grid
		if( !Button[ KEY_LSHIFT ] && isGroupMove )
		{
			SnapToGrid = true;
		}
		else
		{
			SnapToGrid = false;
		}
	}
	if( Button[ MOUSE_1 ].Released() )
	{
		if( SnapToGrid )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				CalcSnapToGrid( MapObject[CurSelected[idx]].Pos, CurrentGridDepth, GridDepth );
				SnapToGrid = false;
			}
			ActiveAction();
		}
		else
		{
			if( isGroupMove )
			{
				ActiveAction();
			}
		}
		isGroupMove = false;
	}
	if( isGroupMove )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			MapObject[CurSelected[idx]].Pos.x -= ( Mouse.Diff().x * Real( Global::HudW ) ) *
				Real( Camera->Pos.z / Global::HudZoom );

			MapObject[CurSelected[idx]].Pos.y += ( Mouse.Diff().y * Real( Global::HudH ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawSnapToGrid( size_t idx )
{
/*	Vector2D SnapGhost( MapObject[CurSelected[idx]].Pos.x, MapObject[CurSelected[idx]].Pos.y );
	
	CalcSnapToGrid( SnapGhost, CurrentGridDepth, GridDepth );

	Mesh2DEdit->Object[MapObject[CurSelected[idx]].MeshIdx].DebugDraw(
		Gfx::RGBA( 0, 128, 0, 255 ), Gfx::RGBA( 128, 0, 0, 255 ), SnapGhost );*/

}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddObject()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() || isPaste == true )
	{
		cMapObject tempMapObject;
		
		tempMapObject.MeshIdx = CurMesh;
		tempMapObject.Pos = CalcMousePos();
		
		CalcSnapToGrid( tempMapObject.Pos, CurrentGridDepth, GridDepth );
		
		MapObject.push_back( tempMapObject );

		if( !isPaste )
		{
			ActiveAction();
			CurSelected.clear();
			CurSelected.push_back( MapObject.size() - 1 );
			CurrentObject = MapObject.size() - 1;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeleteObject()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			for( int idx = CurSelected.size() - 1; idx >= 0; --idx )
			{
				if( Focus1 > int( CurSelected[idx] ) )
				{
					--Focus1;
				}
				if( Focus2 > int( CurSelected[idx] ) )
				{
					--Focus2;
				}
				
				std::vector <cMapObject> tempVec;
				for( size_t vec = 0; vec < MapObject.size(); ++vec )
				{
					if( CurSelected[idx] != vec )
					{
						tempVec.push_back( MapObject[vec] );
					}
				}
				MapObject.swap( tempVec );
			}
						
			CurSelected.clear();
		
			ActiveAction();
			if( MapObject.size() != 0 )
			{
				CurrentObject = MapObject.size() - 1;
			}
			else
			{
				CurrentObject = 0;
			}			
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchMesh()
{	
/*	if ( Button[ KEY_LEFT ].Pressed() )
	{
		if( CurMesh > 0 )
		{
			--CurMesh;
		}
		else
		{
			CurMesh = Mesh2DEdit->Object.size() - 1;	
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( size_t(CurMesh) < Mesh2DEdit->Object.size() - 1 )
		{
			++CurMesh;
		}
		else
		{
			CurMesh = 0;	
		}
	}	*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::CopyObject()
{
	if( Button[ KEY_LCTRL ] )
	{
		if( Button[ KEY_C ].Pressed() || Button[ KEY_INSERT ].Pressed() )
		{
			CopyStorage.clear();
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				CopyStorage.push_back( MapObject[CurSelected[idx]] );	
			}			
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::PasteObject()
{
	if( Button[ KEY_LCTRL ] && Button[ KEY_V ].Pressed() ||
	Button[ KEY_LSHIFT ] && Button[ KEY_INSERT ].Pressed() )
	{
		CurSelected.clear();
		Vector2D CurMousePos = CalcMousePos();
		for( size_t idx = 0; idx < CopyStorage.size(); ++idx )
		{
			MapObject.push_back( CopyStorage[idx] );
			
			MapObject[ MapObject.size() - 1 ].Pos
				= CurMousePos + CopyStorage[idx].Pos - CopyStorage[0].Pos;
			
			CurSelected.push_back( MapObject.size() - 1 );
		}
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ActiveAction()
{
	cUndoObject tempUndoObj;
	
	tempUndoObj.Focus1 = Focus1;
	tempUndoObj.Focus2 = Focus2;
		
	tempUndoObj.MapObject = MapObject;

	UndoObject.push_back( tempUndoObj );
	
	RedoObject.clear();
	
	isSaved = false;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::Undo()
{
	if( Button[ KEY_LCTRL ] )
	{
		// Undo the last action //
		if( Button[ KEY_Z ].Pressed() )
		{
			if( UndoObject.size() > 1 )
			{
				RedoObject.push_back( UndoObject.back() );
				UndoObject.pop_back();
				
				if( !UndoObject.empty() )
				{
					Focus1 = UndoObject.back().Focus1;
					Focus2 = UndoObject.back().Focus2;
					
					MapObject = UndoObject.back().MapObject;
				}
				CurSelected.clear();
				CurrentObject = MapObject.size() - 1;
			}
		}
		// Redo the undo action //
		if( Button[ KEY_Y ].Pressed() )
		{
			
			if( !RedoObject.empty() )
			{
				UndoObject.push_back( RedoObject.back() );
				RedoObject.pop_back();
				
				Focus1 = UndoObject.back().Focus1;
				Focus2 = UndoObject.back().Focus2;

				MapObject = UndoObject.back().MapObject;

				CurSelected.clear();
				CurrentObject = MapObject.size() - 1;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SetFocus()
{
/*	if( Button[ KEY_F ] )
	{
		if( Button[ KEY_1 ].Pressed() )
		{
			Vector2D CurMousePos = CalcMousePos();
			
			CurrentObject = SingleSelect( CurMousePos );
			
			Focus1 = CurrentObject;
			CurSelected.clear();
			ActiveAction();
		}
		if( Button[ KEY_2 ].Pressed() )
		{
			Vector2D CurMousePos = CalcMousePos();
			
			CurrentObject = SingleSelect( CurMousePos );
			
			Focus2 = CurrentObject;
			CurSelected.clear();
			ActiveAction();
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchMode()
{
	if( Button[ KEY_1 ].Pressed() )
	{
		CurMode = OBJECT_MODE;
		CurSelected.clear();
	}
	else if( Button[ KEY_2 ].Pressed() )
	{
		CurMode = ZONE_MODE;
		CurSelected.clear();
	}
	else if( Button[ KEY_3 ].Pressed() )
	{
		CurMode = TILE_MODE;
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
