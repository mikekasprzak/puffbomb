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
int cComponentEdit::SingleSelectNode()
{
	int LastIdx = -1;
	Real LastDistance = NodeRadius;
	Real TestDistance = NodeRadius;
	
	for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
	{
		TestDistance = ( Body2D[ CurBody ].Nodes.Pos( idx ) - CurMousePos ).Magnitude();
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
void cComponentEdit::SelectNode()
{
	if( Button[ MOUSE_1 ].Released() )
	{
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
			{
				if( WithinBox( Body2D[ CurBody ].Nodes.Pos( idx ), CurMousePos, OldMousePos ) )
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
			int temp = SingleSelectNode();
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
			for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
			{
				if( WithinBox( Body2D[ CurBody ].Nodes.Pos( idx ), CurMousePos, OldMousePos ) )
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
			int temp = SingleSelectNode();
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
			
			for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
			{
				if( WithinBox( Body2D[ CurBody ].Nodes.Pos( idx ), CurMousePos, OldMousePos ) )
				{
					CurSelected.push_back( idx );
				}
			}
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = SingleSelectNode();
				if( temp != -1 )
				{
					CurSelected.push_back( temp );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MoveNode()
{
	/*if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] || !Button[ KEY_RCTRL ] )
		{
			int temp = SingleSelectNode();
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
			SetGridDepth( Camera, CurrentGridDepth, 40.0 );
			SetGridArray( CurrentGridDepth, GridDepth );

			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
			
				CalcSnapToGrid( CurFrame->Vertex[ CurSelected[idx] ].Pos, CurrentGridDepth, GridDepth );
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
			CurFrame->Vertex[ CurSelected[idx] ].Pos.x -=
				( Mouse.Diff().x * Real( cGlobal::HudW ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
			
			CurFrame->Vertex[ CurSelected[idx] ].Pos.y +=
				( Mouse.Diff().y * Real( cGlobal::HudH ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
		
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::AddNode()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /* || isPaste == true */ )
	{
		CurSelected.clear();
		
		size_t tempIdx = Body2D[ CurBody ].Nodes.Size() - 1;
		
		Body2D[ CurBody ].AddNode();
		
		Body2D[ CurBody ].Nodes.Pos( tempIdx ) = CurMousePos;

		SetGridDepth( Camera, CurrentGridDepth, 40.0 );
		SetGridArray( CurrentGridDepth, GridDepth );
		
		CalcSnapToGrid( Body2D[ CurBody ].Nodes.Pos( tempIdx ), CurrentGridDepth, GridDepth );
		
		CurSelected.push_back( tempIdx );
		
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DeleteNode()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{	
			/*isDeleteNode = true;
			//DeleteFaceFromNodes();
			isDeleteNode = false;

			std::vector< Engine2D::cBody2D > tempBody2D;
			for( size_t idx = 0; idx < CurFrame->Vertex.size(); ++idx )
			{
				isDeleteNode = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( idx == CurSelected[i] )
					{
						isDeleteNode = true;	
					}
				}	
				if( !isDeleteNode )
				{
					tempBody2D.push_back( CurFrame->Vertex[idx] );
				}
			}
			CurFrame->Vertex.clear();
			CurFrame->Vertex.swap( tempBody2D );
			
			CurSelected.clear();
			isDeleteNode = false;*/
			
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				Body2D[ CurBody ].DeleteNode( CurSelected[idx] );
			}
			//Body2D[ CurBody ].DeleteNode( 2 );
			
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::ScaleNode()
{
	/*if( Button[ KEY_L ].Pressed() )
	{
		isScaleNode = !isScaleNode;	
	}
	if( Button[ MOUSE_1 ].Pressed() && isScaleNode )
	{
		isScaleNode = false;
		CurMousePos = CalcMousePos();
		OldMousePos = CurMousePos;
	}
	if( isScaleNode )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			CurFrame->Vertex[ CurSelected[idx] ].Pos *= Real( Real( 1 ) - ( Mouse.Diff().x * Real( 2 ) ) );
		}	
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
