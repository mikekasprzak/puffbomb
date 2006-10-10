#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Graphics/Gfx.h>
#include <Input/Input.h>
#include <Graphics/Mesh3dPool.h>
#include <Util/String.h>

// !!!! OPENGL !!!! //
#include <gl/gl.h>
#include <gl/glu.h>
// !!!! OPENGL !!!! //

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawSelModel()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		for( size_t i = 0; i < Model[CurSelected[idx]].Mesh3d->Data.size(); ++i )
		{
			cMesh3d& ThisMesh = *Model[CurSelected[idx]].Mesh3d;
				
			glBindTexture( GL_TEXTURE_2D, ThisMesh.Data[i].TextureID );
			
			glVertexPointer(3, GL_FLOAT, 0, &(*ThisMesh.Data[i].Vertex)[0]);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, &(*ThisMesh.Data[i].VertexColor)[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &(*ThisMesh.Data[i].TextureCoord)[0]);

			glPushMatrix();
			glTranslatef( Model[CurSelected[idx]].Offset.x, Model[CurSelected[idx]].Offset.y, Model[CurSelected[idx]].Offset.z );
			glDrawElements(
				GL_TRIANGLES, ThisMesh.Data[i].Indices->Size(),
				GL_UNSIGNED_INT, &(*ThisMesh.Data[i].Indices)[0]
			);
			glPopMatrix();
		}
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchModel()
{
	if ( Button[ KEY_LEFT ].Pressed() )
	{
		if( CurModel > 0 )
		{
			--CurModel;
		}
		else
		{
			CurModel = ModelNameList.size() - 1;
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( size_t( CurModel ) < ModelNameList.size() - 1 )
		{
			++CurModel;
		}
		else
		{
			CurModel = 0;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SelectModel()
{
	if( Button[ MOUSE_1 ].Released() )
	{
		int SceneTest = 0;
		
		Vector2D CurMousePos = CalcMousePos();
		if( Button[ KEY_LSHIFT ] )
		{
			for( size_t idx = 0; idx < ModelName.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
					
				RadiusRect2D Boundy = RadiusRect2D::Pair(
					Model[ idx ].Mesh3d->BoundingRect.P1().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y ),
					Model[ idx ].Mesh3d->BoundingRect.P2().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y ) );

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
						if( idx != size_t(SceneryIdx) )
						{
							SceneTest++;
							CurSelected.push_back( idx );
						}
					}
				}
			}
			if( SceneryIdx != -1 )
			{
				if( SceneTest == 0 )
				{
					CurSelected.push_back( SceneryIdx );
				}
			}
		
			
		}
		else if( Button[ KEY_LCTRL ] )
		{	
			for( size_t idx = 0; idx < ModelName.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
				
				RadiusRect2D Boundy = RadiusRect2D::Pair(
					Model[ idx ].Mesh3d->BoundingRect.P1().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y ),
					Model[ idx ].Mesh3d->BoundingRect.P2().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y ) );


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
			
			for( size_t idx = 0; idx < ModelName.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );

				RadiusRect2D Boundy = RadiusRect2D::Pair(
					Model[ idx ].Mesh3d->BoundingRect.P1().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y ),
					Model[ idx ].Mesh3d->BoundingRect.P2().ToVector2D() + Vector2D( Model[ idx ].Offset.x, Model[ idx ].Offset.y ) );

				if( Selection == Boundy )
				{
					if( idx != size_t(SceneryIdx) )
					{
						SceneTest++;
						CurSelected.push_back( idx );
					}
				}
			}
			if( SceneryIdx != -1 )
			{
				if( SceneTest == 0 )
				{
					CurSelected.push_back( SceneryIdx );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MoveModel()
{
	if( Button[ MOUSE_1 ].Pressed() )
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddModel()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		ModelName.push_back( ModelNameList[CurModel] );
		
		Vector2D PointA = ModelList[ CurModel ].Mesh3d->BoundingRect.P1().ToVector2D();
		Vector2D PointB = ModelList[ CurModel ].Mesh3d->BoundingRect.P2().ToVector2D();

		Vector2D TempPos = CalcMousePos() - ( ( PointB - PointA ) / 2 );
		CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );
		
		Model.push_back(
			cLevelData(
				TempPos.ToVector3D(),
				&Mesh3dPool.Load( ModelNameList[CurModel] )
			)
		);
				
		CurSelected.clear();
		CurSelected.push_back( Model.size() - 1 );
		
		std::string tempstr = String::PriorBaseName( ModelNameList[CurModel] );
		
		if( tempstr.size() > 2 )
		{
			if( tempstr == "Scene" )
			{
				SceneryIdx = ModelName.size() - 1;
			}
		}

		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeleteModel()
{
	if( !ModelName.empty() )
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
