#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Input/Input.h>

#include "CreateCollectionInstance.h"

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SelectDyn()
{
/*	if( Button[ MOUSE_1 ].Released() )
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
					if( Map.StaticObjectInstanceInfo[ idx ].Layer == CurLayer )
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
					if( Map.StaticObjectInstanceInfo[ idx ].Layer == CurLayer )
					{
						CurSelected.push_back( idx );
					}
				}
			}
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MoveDyn()
{
/*	if( Button[ MOUSE_1 ].Pressed() )
	{
		bool SceneMove = false;
		
		if( !Button[ KEY_LCTRL ] )
		{
			Vector2D CurMousePos = CalcMousePos();
			
			int temp = -1;
			
			for( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx )
			{
				Vector2D PointA = StaticObjectInstance[ idx ].Object->BoundingRect.P1().ToVector2D() + StaticObjectInstance[ idx ].Pos;
				Vector2D PointB = StaticObjectInstance[ idx ].Object->BoundingRect.P2().ToVector2D() + StaticObjectInstance[ idx ].Pos;
				
				if( WithinBox( CurMousePos, PointA, PointB ) )
				{
					temp = idx;
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
				Vector2D TempPos = StaticObjectInstance[ CurSelected[ idx ] ].Pos;
				CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );
				
				StaticObjectInstance[ CurSelected[ idx ] ].Pos = TempPos;
				Map.StaticObjectInstanceInfo[ CurSelected[ idx ] ].Pos = TempPos;

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
			StaticObjectInstance[ CurSelected[ idx ] ].Pos.x -= ( Mouse.Diff().x * Real( Global::HudW ) ) *
				Real( Camera->Pos.z / Global::HudZoom );

			StaticObjectInstance[ CurSelected[ idx ] ].Pos.y += ( Mouse.Diff().y * Real( Global::HudH ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
			
			Map.StaticObjectInstanceInfo[ CurSelected[ idx ] ].Pos = StaticObjectInstance[ CurSelected[ idx ] ].Pos;
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddDyn()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		DynamicCollection.push_back( Engine2D::CreateCollectionInstance( 2, Vector2D( -400, 400 ) ) );

		
		/*Map.DynamicObjectInstanceInfo.push_back(
			Engine2D::cDynamicObjectInstanceInfo( 
				Mesh3DName[ CurMesh3D ],
				CurMousePos
			)
		);*/
		
		/*Map.StaticObjectInstanceInfo.push_back(
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
		
		Map.StaticObjectInstanceInfo.back().Layer = CurLayer;
		
		CurSelected.clear();
		
		CurSelected.push_back( StaticObjectInstance.size() - 1 );
*/
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeleteDyn()
{
/*	if( !Mesh3DName.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			for( int idx = CurSelected.size() - 1; idx >= 0; --idx )
			{
				std::vector< Engine2D::cStaticObjectInstance > TempMesh3D;
				std::vector< Engine2D::cStaticObjectInstanceInfo > TempMesh3DInfo;
	
				for( size_t i = 0; i < StaticObjectInstance.size(); ++i )
				{
					if( CurSelected[idx] != i )
					{
						TempMesh3D.push_back( StaticObjectInstance[ i ] );
						TempMesh3DInfo.push_back( Map.StaticObjectInstanceInfo[ i ] );
					}
				}
				
				StaticObjectInstance.swap( TempMesh3D );
				Map.StaticObjectInstanceInfo.swap( TempMesh3DInfo );
			}
			CurSelected.clear();
			
			ActiveAction();
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::UpdateDynPreview()
{
	DynPreview.LoadBinary( DynBaseDirName + DynPath[ CurDyn ] );
	
	for( size_t idx = 0; idx < DynPreview.Component.size(); ++idx )
	{
		for( size_t idx2 = 0; idx2 < DynPreview.Component[ idx ].Body.Nodes.Size(); ++idx2 )
		{
			DynPreview.Component[ idx ].Body.Nodes.Pos( idx2 ) +=
				 Vector2D( Global::Left, Global::Bottom ) += Vector2D( 256, 256 );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchDyn()
{
	if ( Button[ KEY_LEFT ].Pressed() ) 
	{
		if( !DynPath.empty() )
		{
			if( CurDyn > 0 )
			{
				--CurDyn;
			}
			else
			{
				CurDyn = DynPath.size() - 1;
			}
			
			UpdateDynPreview();
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( !DynPath.empty() )
		{
			if( CurDyn < DynPath.size() - 1 )
			{
				++CurDyn;
			}
			else
			{
				CurDyn = 0;	
			}
				
			UpdateDynPreview();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
