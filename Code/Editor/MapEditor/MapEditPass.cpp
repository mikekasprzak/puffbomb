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
		PassiveObject.push_back( CreatePassiveInstance( ActivePass[ CurPass ], CurMousePos, 80 ) );
		
		CurSelected.clear();
		
		CurSelected.push_back( PassiveObject.size() - 1 );

		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeletePass()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		for( int idx = CurSelected.size() - 1; idx >= 0; --idx )
		{
			std::vector< Engine2D::cPassiveObject* > TempPass;

			for( size_t i = 0; i < PassiveObject.size(); ++i )
			{
				if( CurSelected[idx] != i )
				{
					TempPass.push_back( PassiveObject[ i ] );
				}
				else
				{
					delete PassiveObject[ i ];
				}
			}
			
			PassiveObject.swap( TempPass );
		}
		CurSelected.clear();
		
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchPass()
{
	if ( Button[ KEY_LEFT ].Pressed() ) 
	{
		if( !ActivePass.empty() )
		{
			if( CurPass > 0 )
			{
				--CurPass;
			}
			else
			{
				CurPass = ActivePass.size() - 1;
			}
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( !ActivePass.empty() )
		{
			if( CurPass < ActivePass.size() - 1 )
			{
				++CurPass;
			}
			else
			{
				CurPass = 0;	
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
