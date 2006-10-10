#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisAddNode()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() || isPaste == true )
	{
		Vector2D CurMousePos = CalcMousePos();
		
		int PivotIdx = 0;
		int HandleIdx = 1;
		Real Pivot = 100000.0;
		Real Handle = 100000.0;
		Real TestDistance = 100000.0;
	
		for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
		{
			TestDistance = ( Object[ CurrentObject ].Pos( idx ) - CurMousePos ).Magnitude();
		
			if( TestDistance < Pivot )
			{
				Pivot = TestDistance;
				PivotIdx = idx;
			}
		}
		
		for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
		{
			TestDistance = ( Object[ CurrentObject ].Pos( idx ) - CurMousePos ).Magnitude();
			
			if( int( idx ) != PivotIdx )
			{
				if( TestDistance < Handle )
				{
					Handle = TestDistance;
					HandleIdx = idx;
				}
			}
		}
		
		DisplayMesh[ CurrentObject ].DisplayNode.push_back(
			cDisplayMesh::cDisplayNode( CurMousePos, HandleIdx, PivotIdx ) );
		
		CalcSnapToGrid( DisplayMesh[ CurrentObject ].Pos(
			DisplayMesh[ CurrentObject ].size() - 1 ), CurrentGridDepth, GridDepth );
							
		if( !isPaste )
		{
			ActiveAction();
			CurrentNode = DisplayMesh[ CurrentObject ].size() - 1;
			CurSelected.clear();
			CurSelected.push_back( CurrentNode );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisSelectNode()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcMousePos();
	}
	
	if( Button[ MOUSE_1 ].Released() )
	{
		SphereCheck();
		Vector2D CurMousePos = CalcMousePos();
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( DisplayMesh[ CurrentObject ].Pos( idx ), CurMousePos,
					 OldMousePos ) )
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
			int temp = DisSingleSelect( CurMousePos );
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
			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( DisplayMesh[ CurrentObject ].Pos( idx ), CurMousePos,
					 OldMousePos ) )
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
			int temp = DisSingleSelect( CurMousePos );
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

			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( DisplayMesh[ CurrentObject ].Pos( idx ), CurMousePos, 
					OldMousePos ) )
				{
					CurSelected.push_back( idx );
				}
			}
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = DisSingleSelect( CurMousePos );
				if( temp != -1 )
				{
					CurSelected.push_back( temp );
				}
			}
		}
		
		if( !CurSelected.empty() )
		{
			CurrentNode = CurSelected[0];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawDisSelect()
{
	if( Button[ MOUSE_1 ] )
	{
		Vector2D CurMousePos = CalcMousePos();
		gfx::Rect( OldMousePos, CurMousePos, gfx::RGB( 255, 255, 255 ) );
		if( !Button[ KEY_LCTRL ] || !Button[ KEY_RCTRL ] )
		{
			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( DisplayMesh[ CurrentObject ].Pos( idx ), CurMousePos,
					 OldMousePos) )
				{
					gfx::Circle( 
						DisplayMesh[ CurrentObject ].Pos( idx ), 1, gfx::RGB( 0, 100, 50 ) );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
int cMesh2DEdit::DisSingleSelect( Vector2D &CurMousePos )
{
	int LastIdx = -1;
	Real LastDistance = 3.0;
	Real TestDistance = 3.0;
	
	for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
	{
		TestDistance = ( DisplayMesh[ CurrentObject ].Pos( idx ) - CurMousePos ).Magnitude();
		if( TestDistance < Real( 3.0 ) )
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
void cMesh2DEdit::DisMoveNode()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] || !Button[ KEY_RCTRL ] )
		{
			Vector2D CurMousePos = CalcMousePos();
			int temp = DisSingleSelect( CurMousePos );
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
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				CalcSnapToGrid( DisplayMesh[ CurrentObject ].Pos(
					CurSelected[idx] ), CurrentGridDepth, GridDepth );

			}
			SnapToGrid = false;
			ActiveAction();
		}
		else
		{
			ActiveAction();
		}
	}
	if( isGroupMove )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DisplayMesh[ CurrentObject ].Pos( CurSelected[idx] ).x -=
				( Mouse.Diff().x * Real( Global::HudW ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
			
			DisplayMesh[ CurrentObject ].Pos( CurSelected[idx] ).y +=
				( Mouse.Diff().y * Real( Global::HudH ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawDisSnapToGrid( size_t Node )
{	
	Vector2D SnapGhost( DisplayMesh[ CurrentObject ].Pos( Node ).x,
		DisplayMesh[ CurrentObject ].Pos( Node ).y );
	
	CalcSnapToGrid( SnapGhost, CurrentGridDepth, GridDepth );

	gfx::Circle( SnapGhost, 1, gfx::RGB( 80, 0, 0 ) );
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisDeleteNode()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			
			isDelete = true;
			DisDeleteFace();
			isDelete = false;
						
			std::vector< cDisplayMesh::cDisplayNode > tempDisNode;
			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
			{
				isDelete = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( idx == CurSelected[i] )
					{
						isDelete = true;	
					}
				}	
				if( !isDelete )
				{
					tempDisNode.push_back( DisplayMesh[ CurrentObject ].DisplayNode[idx] );
				}
			}
			DisplayMesh[ CurrentObject ].DisplayNode.clear();
			DisplayMesh[ CurrentObject ].DisplayNode.swap( tempDisNode );
			
			CurSelected.clear();
			CurrentNode = DisplayMesh[ CurrentObject ].size() - 1;
			CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisSetPivot()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		Vector2D CurMousePos = CalcMousePos();
		int temp = ColSingleSelect( CurMousePos );
		if( temp != -1 )
		{
			DisplayMesh[ CurrentObject ].DisplayNode[ CurrentNode ].Pivot = temp;
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisSetHandle()
{
	if( Button[ MOUSE_2 ].Pressed() )
	{
		Vector2D CurMousePos = CalcMousePos();
		int temp = ColSingleSelect( CurMousePos );
		if( temp != -1 )
		{
			DisplayMesh[ CurrentObject ].DisplayNode[ CurrentNode ].Handle = temp;
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
