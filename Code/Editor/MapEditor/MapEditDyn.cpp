#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Input/Input.h>

#include "CreateCollectionInstance.h"

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
int cMapEdit::SingleSelectDyn()
{
	int LastIdx = -1;
	Real LastDistance = Real( 100 );

	for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
	{
		for( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); ++idx2 )
		{
			for( size_t idx3 = 0; idx3 < DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Size(); ++idx3 )
			{
				Real TestDistance = ( DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Pos( idx3 ) - CurMousePos ).Magnitude();
				
				if( TestDistance < Real( 100 ) )
				{
					if( TestDistance < LastDistance )
					{
						LastDistance = TestDistance;

						LastIdx = idx;
					}
				}
			}
		}
	}
		
	return LastIdx;
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SelectDyn()
{
	if( Button[ MOUSE_1 ].Released() )
	{
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); ++idx2 )
				{
					for( size_t idx3 = 0; idx3 < DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Size(); ++idx3 )
					{
						if( WithinBox( DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Pos( idx3 ), CurMousePos, OldMousePos ) )
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
			// Single add-select //
			int temp = SingleSelectDyn();
			if( temp != -1 )
			{
				bool CurSelectedTest = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( int( CurSelected[i] ) == temp )
					{
						CurSelectedTest = true;
					}					
				}
				if( !CurSelectedTest )
				{
					CurSelected.push_back( temp );	
				}
			}
		}
		// Group de-select //
		else if( Button[ KEY_LCTRL ] || Button[ KEY_RCTRL ] )
		{
			for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); ++idx2 )
				{
					for( size_t idx3 = 0; idx3 < DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Size(); ++idx3 )
					{
						if( WithinBox( DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Pos( idx3 ), CurMousePos, OldMousePos ) )
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
			}
			// Single de-select //
			int temp = SingleSelectDyn();
			if( temp != -1 )
			{
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( int(CurSelected[i]) == temp )
					{			
						std::vector <size_t> tempVec;
						for( size_t vec = 0; vec < CurSelected.size(); ++vec )
						{
							if( int(CurSelected[vec]) != temp )
							{
								tempVec.push_back( CurSelected[vec] );
							}
						}
						CurSelected.swap( tempVec );
					}
				}
			}
		}
		else
		{
			CurSelected.clear();
			
			for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); ++idx2 )
				{
					for( size_t idx3 = 0; idx3 < DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Size(); ++idx3 )
					{
						if( WithinBox( DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Pos( idx3 ), CurMousePos, OldMousePos ) )
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
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = SingleSelectDyn();
				if( temp != -1 )
				{
					CurSelected.push_back( temp );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MoveDyn()
{
	
	if( Button[ MOUSE_1 ].Pressed() )
	{
		bool SceneMove = false;
		
		if( !Button[ KEY_LCTRL ] && !Button[ KEY_RCTRL ] && !Button[ KEY_LSHIFT ]  )
		{
			Vector2D CurMousePos = CalcMousePos();
			
			int temp = SingleSelectDyn();
			
/*			for( size_t idx = 0; idx < DynamicCollection.size(); ++idx )
			{
				
				
				Vector2D PointA = StaticObjectInstance[ idx ].Object->BoundingRect.P1().ToVector2D() + StaticObjectInstance[ idx ].Pos;
				Vector2D PointB = StaticObjectInstance[ idx ].Object->BoundingRect.P2().ToVector2D() + StaticObjectInstance[ idx ].Pos;
				
				if( WithinBox( CurMousePos, PointA, PointB ) )
				{
					temp = idx;
				}
			}*/
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
				for( size_t i2 = 0; i2 < DynamicCollection[ CurSelected[ idx ] ]->Component.size(); ++i2 )
				{
					for( size_t i3 = 0; i3 < DynamicCollection[ CurSelected[ idx ] ]->Component[ i2 ].Body.Nodes.Size(); ++i3 )
					{
						//CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );
						
						Real TempX = ( Mouse.Diff().x * Real( Global::HudW ) )
							* Real( Camera->Pos.z / Global::HudZoom );
						
						Real TempY = ( Mouse.Diff().y * Real( Global::HudH ) )
							* Real( Camera->Pos.z / Global::HudZoom );
						
						DynamicCollection[ CurSelected[ idx ] ]->Component[ i2 ].Body.Nodes.Pos( i3 ).x -= TempX;
						DynamicCollection[ CurSelected[ idx ] ]->Component[ i2 ].Body.Nodes.Pos( i3 ).y += TempY;
						
						Map.DynamicObjectInstanceInfo[ CurSelected[ idx ] ].Pos.x -= TempX;
						Map.DynamicObjectInstanceInfo[ CurSelected[ idx ] ].Pos.x += TempY;
						
					}
				}

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
			for( size_t i2 = 0; i2 < DynamicCollection[ CurSelected[ idx ] ]->Component.size(); ++i2 )
			{
				for( size_t i3 = 0; i3 < DynamicCollection[ CurSelected[ idx ] ]->Component[ i2 ].Body.Nodes.Size(); ++i3 )
				{
					Real TempX = ( Mouse.Diff().x * Real( Global::HudW ) )
						* Real( Camera->Pos.z / Global::HudZoom );
					
					Real TempY = ( Mouse.Diff().y * Real( Global::HudH ) )
						* Real( Camera->Pos.z / Global::HudZoom );
					
					DynamicCollection[ CurSelected[ idx ] ]->Component[ i2 ].Body.Nodes.Pos( i3 ).x -= TempX;
					DynamicCollection[ CurSelected[ idx ] ]->Component[ i2 ].Body.Nodes.Pos( i3 ).y += TempY;
					
					Map.DynamicObjectInstanceInfo[ CurSelected[ idx ] ].Pos.x -= TempX;
					Map.DynamicObjectInstanceInfo[ CurSelected[ idx ] ].Pos.x += TempY;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddDyn()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		Vector2D TempPos = CurMousePos;

		CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );
		
		DynamicCollection.push_back( Engine2D::CreateCollectionInstance( ActiveDyns[ CurDyn ], TempPos ) );
		
		Map.DynamicObjectInstanceInfo.push_back(
			Engine2D::cDynamicObjectInstanceInfo( 
				ActiveDyns[ CurDyn ],
				TempPos
			)
		);
		
		CurSelected.clear();
		
		CurSelected.push_back( DynamicCollection.size() - 1 );

		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeleteDyn()
{
	if( !ActiveDyns.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			for( int idx = CurSelected.size() - 1; idx >= 0; --idx )
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
			}
			CurSelected.clear();
			
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::UpdateDynPreview()
{
	if( DynPreview != 0 )
	{
		delete DynPreview;
	}
	
	if( !ActiveDyns.empty() )
	{
		DynPreview = Engine2D::CreateCollectionInstance( ActiveDyns[ CurDyn ], Vector2D( Global::Left, Global::Bottom ) + Vector2D( 256, 256 ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchDyn()
{
	if ( Button[ KEY_LEFT ].Pressed() ) 
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
