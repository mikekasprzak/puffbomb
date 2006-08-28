#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
int cComponentEdit::MeshSingleSelectNode()
{
	int LastIdx = -1;
	Real LastDistance = NodeRadius;
	Real TestDistance = NodeRadius;
	
	for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
	{
		TestDistance = ( Pose->Node[ idx ].Pos - CurMousePos ).Magnitude();
		if( TestDistance < Real( NodeRadius ) )
		{
			if( TestDistance < LastDistance )
			{
				LastDistance = TestDistance;
				LastIdx = idx;
			}
		}
	}
	return LastIdx;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshSelectNode()
{
	if( Button[ MOUSE_1 ].Released() )
	{
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
			{
				if( WithinBox( Pose->Node[ idx ].Pos, CurMousePos, OldMousePos ) )
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
			// Single add-select //
			int temp = BodySingleSelectNode();
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
			for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
			{
				if( WithinBox( Pose->Node[ idx ].Pos, CurMousePos, OldMousePos ) )
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
			// Single de-select //
			int temp = BodySingleSelectNode();
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
		// Standard group select //
		else
		{
			CurSelected.clear();
			
			for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
			{
				if( WithinBox( Pose->Node[ idx ].Pos, CurMousePos, OldMousePos ) )
				{
					CurSelected.push_back( idx );
				}
			}
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = BodySingleSelectNode();
				if( temp != -1 )
				{
					CurSelected.push_back( temp );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshMoveNode()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] || !Button[ KEY_RCTRL ] )
		{
			int temp = BodySingleSelectNode();
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
		isGroupMove = false;
		
		if( SnapToGrid )
		{
			SetGridDepth( Camera, CurrentGridDepth, 32.0 );
			SetGridArray( CurrentGridDepth, UVGridDepth );

			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				Vector2D TempPos = Pose->Node[ CurSelected[idx] ].Pos;
				CalcSnapToGrid( TempPos, CurrentGridDepth, UVGridDepth );
				DynObj[ CurObj ].Body.SetPos( CurSelected[idx], TempPos );
				
			}
			SnapToGrid = false;
			DynObj[ CurObj ].Body.CalculateSpringLength();
			ActiveAction();
		}
		else
		{
			DynObj[ CurObj ].Body.CalculateSpringLength();
			ActiveAction();
		}
	}
	if( isGroupMove )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			
			Real TempX = Pose->Node[ CurSelected[idx] ].Pos.x;
			TempX -= OldMousePos.x - CurMousePos.x;
			
			Real TempY = Pose->Node[ CurSelected[idx] ].Pos.y;
			TempY -= OldMousePos.y - CurMousePos.y;
					
			DynObj[ CurObj ].Body.SetPos( CurSelected[idx], Vector2D( TempX, TempY ) );
		}
		OldMousePos = CurMousePos;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshAddNode()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /* || isPaste == true */ )
	{
		CurSelected.clear();
		
		Vector2D TempPos = CurMousePos;

		if( !Button[ KEY_LSHIFT ] )
		{
			SetGridDepth( Camera, CurrentGridDepth, 32.0 );
			SetGridArray( CurrentGridDepth, UVGridDepth );

			CalcSnapToGrid( TempPos, CurrentGridDepth, UVGridDepth );
		}
		DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node.push_back( Engine2D::cMeshPoseNode( TempPos, 0, 1 ) );

		CurSelected.push_back( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node.size() - 1 );
		
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshDeleteNode()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			sort( CurSelected.begin(), CurSelected.end() );
			for( int idx = CurSelected.size() - 1; idx > -1; --idx )
			{
				DynObj[ CurObj ].Body.DeleteNode( CurSelected[idx] );

			}
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshScaleNode()
{
	if( Button[ KEY_L ].Pressed() )
	{
		if( !( EditEventFlags & flScale ) )
		{
			EditEventFlags |= flScale;
		}
		else if( ( EditEventFlags & flScale ) )
		{
			EditEventFlags &= ~flScale;
			DynObj[ CurObj ].Body.CalculateSpringLength();
		}
	}
	if( Button[ MOUSE_1 ].Pressed() && EditEventFlags & flScale )
	{
		EditEventFlags &= ~flScale;
		CurMousePos = CalcMousePos();
		OldMousePos = CurMousePos;
		
		DynObj[ CurObj ].Body.CalculateSpringLength();		
	}
	if( EditEventFlags & flScale )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Vector2D TempPos = Pose->Node[ CurSelected[idx] ].Pos;
			TempPos *= Real( Real( 1 ) - ( Mouse.Diff().x * Real( 2 ) ) );
			
			DynObj[ CurObj ].Body.SetPos( CurSelected[idx], TempPos );
		}	
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
