#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Input/Input.h>

#include "CreatePassiveInstance.h"

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SelectPass()
{
	if( Button[ MOUSE_1 ].Released() )
	{
		if( Button[ KEY_LSHIFT ] )
		{
			for( size_t idx = 0; idx < PassiveObject.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
					
				RadiusRect2D Boundy = RadiusRect2D::Pair(
					PassiveObject[ idx ]->BoundingRect.P1(),
					PassiveObject[ idx ]->BoundingRect.P2() );	
					
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
			for( size_t idx = 0; idx < PassiveObject.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
				
				RadiusRect2D Boundy = RadiusRect2D::Pair(
					PassiveObject[ idx ]->BoundingRect.P1(),
					PassiveObject[ idx ]->BoundingRect.P2() );	
					
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
			
			for( size_t idx = 0; idx < PassiveObject.size(); ++idx )
			{
				RadiusRect2D Selection = RadiusRect2D::Pair( OldMousePos, CurMousePos );
				
				Real TempValue = PassiveObject[ idx ]->BoundingRect.P2().x;
				
				RadiusRect2D Boundy = RadiusRect2D::Pair(
					PassiveObject[ idx ]->BoundingRect.P1(),
					PassiveObject[ idx ]->BoundingRect.P2() );

				if( Selection == Boundy )
				{
					CurSelected.push_back( idx );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MovePass()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		bool SceneMove = false;
		
		if( !Button[ KEY_LCTRL ] )
		{
			Vector2D CurMousePos = CalcMousePos();
			
			int temp = -1;
			
			for( size_t idx = 0; idx < PassiveObject.size(); ++idx )
			{
				Vector2D PointA = PassiveObject[ idx ]->BoundingRect.P1();
				Vector2D PointB = PassiveObject[ idx ]->BoundingRect.P2();
				
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
		if( isGroupMove )
		{
			ActiveAction();
		}
		
		isGroupMove = false;
	}
	if( isGroupMove )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			PassiveObject[ CurSelected[ idx ] ]->Pos.x -= ( Mouse.Diff().x * Real( Global::HudW ) ) *
				Real( Camera->Pos.z / Global::HudZoom );

			PassiveObject[ CurSelected[ idx ] ]->Pos.y += ( Mouse.Diff().y * Real( Global::HudH ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
					
			PassiveObject[ CurSelected[ idx ] ]->BoundingRect =
				Engine2D::cPhysics::BoundingRectType::Pair(
					PassiveObject[ CurSelected[ idx ] ]->Pos - Vector2D( 32, 32 ), PassiveObject[ CurSelected[ idx ] ]->Pos + Vector2D( 32, 32 ) );	
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddPass()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		PassiveObject.push_back( CreatePassiveInstance( 32, CurMousePos, 80 ) );
		
		CurSelected.clear();
		
		CurSelected.push_back( PassiveObject.size() - 1 );

		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeletePass()
{
	if( !ActiveDyns.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			/*for( int idx = CurSelected.size() - 1; idx >= 0; --idx )
			{
				std::vector< Engine2D::cDynamicCollection* > TempDyn;
				std::vector< Engine2D::cDynamicObjectInstanceInfo > TempDynInfo;
	
				for( size_t i = 0; i < DynamicCollection.size(); ++i )
				{
					if( CurSelected[idx] != i )
					{
						TempDyn.push_back( DynamicCollection[ i ] );
						TempDynInfo.push_back( Map.DynamicObjectInstanceInfo[ i ] );
					}
					else
					{
						delete DynamicCollection[ i ];
					}
				}
				
				DynamicCollection.swap( TempDyn );
				Map.DynamicObjectInstanceInfo.swap( TempDynInfo );
			}*/
			CurSelected.clear();
			
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::UpdatePassPreview()
{
	/*if( DynPreview != 0 )
	{
		delete DynPreview;
	}
	
	if( !ActiveDyns.empty() )
	{
		DynPreview = Engine2D::CreateCollectionInstance( ActiveDyns[ CurDyn ], Vector2D( Global::Left, Global::Bottom ) + Vector2D( 256, 256 ) );
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchPass()
{
	/*if ( Button[ KEY_LEFT ].Pressed() ) 
	{
		if( !ActiveDyns.empty() )
		{
			if( CurDyn > 0 )
			{
				--CurDyn;
			}
			else
			{
				CurDyn = ActiveDyns.size() - 1;
			}
			
			UpdateDynPreview();
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( !ActiveDyns.empty() )
		{
			if( CurDyn < ActiveDyns.size() - 1 )
			{
				++CurDyn;
			}
			else
			{
				CurDyn = 0;	
			}
				
			UpdateDynPreview();
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
