#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Graphics/Gfx.h>
#include <Input/Input.h>
#include <Util/String.h>

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SelectMesh3D()
{
	if( Button[ MOUSE_1 ].Released() )
	{
		if( Button[ KEY_LSHIFT ] )
		{
			for( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
					
				RadiusRect2D Boundy = RadiusRect2D::Pair(
					StaticObjectInstance[ idx ].Object->BoundingRect.P1().ToVector2D() + StaticObjectInstance[ idx ].Pos,
					StaticObjectInstance[ idx ].Object->BoundingRect.P2().ToVector2D() + StaticObjectInstance[ idx ].Pos );

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
						CurSelected.push_back( idx );
					}
				}
			}
		}
		else if( Button[ KEY_LCTRL ] )
		{	
			for( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
				
				RadiusRect2D Boundy = RadiusRect2D::Pair(
					StaticObjectInstance[ idx ].Object->BoundingRect.P1().ToVector2D() + StaticObjectInstance[ idx ].Pos,
					StaticObjectInstance[ idx ].Object->BoundingRect.P2().ToVector2D() + StaticObjectInstance[ idx ].Pos );

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
			
			for( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );

				RadiusRect2D Boundy = RadiusRect2D::Pair(
					StaticObjectInstance[ idx ].Object->BoundingRect.P1().ToVector2D() + StaticObjectInstance[ idx ].Pos,
					StaticObjectInstance[ idx ].Object->BoundingRect.P2().ToVector2D() + StaticObjectInstance[ idx ].Pos );

				if( Selection == Boundy )
				{
					CurSelected.push_back( idx );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MoveMesh3D()
{
/*	if( Button[ MOUSE_1 ].Pressed() )
	{
		int SceneTest = 0;
		
		bool SceneMove = false;
		
		if( !Button[ KEY_LCTRL ] )
		{
			Vector2D CurMousePos = CalcMousePos();
			
			int temp = -1;
			
			for( size_t idx = 0; idx < Model.size(); ++idx )
			{
				Vector2D PointA = Model[ idx ].Mesh3d->BoundingRect.P1().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y );
				Vector2D PointB = Model[ idx ].Mesh3d->BoundingRect.P2().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y );
				
				if( WithinBox( CurMousePos, PointA, PointB ) )
				{
					if( idx != size_t(SceneryIdx) )
					{						
						SceneTest++;
						temp = idx;
					}
					else
					{
						SceneMove = true;	
					}
				}
			}
			if( SceneTest == 0 )
			{
				if( SceneMove )
				{
					temp = SceneryIdx;
				}
			}
			if( temp != -1 )
			{
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( temp == int(CurSelected[idx]) )
					{
						isGroupMove = true;
					}
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
				Vector2D TempOffset = Vector2D( Model[CurSelected[idx]].Offset.x, Model[CurSelected[idx]].Offset.y );
				Model[CurSelected[idx]].Offset = CalcSnapToGrid( TempOffset, CurrentGridDepth, GridDepth ).ToVector3D();
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
			Model[CurSelected[idx]].Offset.x -= ( Mouse.Diff().x * Real( Global::HudW ) ) *
				Real( Camera->Pos.z / Global::HudZoom );

			Model[CurSelected[idx]].Offset.y += ( Mouse.Diff().y * Real( Global::HudH ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddMesh3D()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		Map.StaticObjectInstanceInfo.push_back(
			Engine2D::cStaticObjectInstanceInfo( 
				Mesh3DName[ CurMesh3D ],
				CurMousePos
			)
		);
				
		StaticObjectInstance.push_back(
			Engine2D::cStaticObjectInstance(
				Map.StaticObjectInstanceInfo.back().FileName,
				Map.StaticObjectInstanceInfo.back().Pos
			)
		);
		
		StaticObjectInstance.back().Object->CalcBoundingRect();

		Vector2D PointA = StaticObjectInstance.back().Object->BoundingRect.P1().ToVector2D();
		Vector2D PointB = StaticObjectInstance.back().Object->BoundingRect.P2().ToVector2D();

		Vector2D TempPos = CurMousePos - ( ( PointB - PointA ) / 2 );
		CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );

		StaticObjectInstance.back().Pos = TempPos;
		Map.StaticObjectInstanceInfo.back().Pos = TempPos;
		
		CurSelected.clear();
		
		CurSelected.push_back( StaticObjectInstance.size() - 1 );

		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeleteMesh3D()
{
/*	if( !ModelName.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			for( int idx = CurSelected.size() - 1; idx >= 0; --idx )
			{
				std::vector< cLevelData > TempModel;
				std::vector< std::string > TempModelName;
	
				for( size_t i = 0; i < ModelName.size(); ++i )
				{
					if( CurSelected[idx] != i )
					{
						TempModel.push_back( Model[ i ] );
						TempModelName.push_back( ModelName[ i ] );
					}
				}
				
				if( int( CurSelected[idx] ) == SceneryIdx )
				{
					SceneryIdx = -1;
				}
				else if( int( CurSelected[idx] ) < SceneryIdx )
				{
					SceneryIdx--;
				}
				
				Model.swap( TempModel );
				ModelName.swap( TempModelName );
			}
			CurSelected.clear();
			
			ActiveAction();
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::UpdateMesh3DPreview()
{
	Mesh3DPreview = Engine2D::cStaticObjectInstance(
		Mesh3DName[ CurMesh3D ],
		Vector2D( Global::Left, Global::Bottom )
	);
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchMesh3D()
{
	if ( Button[ KEY_LEFT ].Pressed() ) 
	{
		if( !Mesh3DName.empty() )
		{
			if( CurMesh3D > 0 )
			{
				--CurMesh3D;
			}
			else
			{
				CurMesh3D = Mesh3DName.size() - 1;
			}
			
			UpdateMesh3DPreview();
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( !Mesh3DName.empty() )
		{
			if( CurMesh3D < Mesh3DName.size() - 1 )
			{
				++CurMesh3D;
			}
			else
			{
				CurMesh3D = 0;	
			}
				
			UpdateMesh3DPreview();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
