#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>

// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
int cAnimationEdit::SingleSelectNode()
{
	int LastIdx = -1;
	Real LastDistance = NodeRadius;
	Real TestDistance = NodeRadius;
	
	for( size_t idx = 0; idx < CurFrame->Vertex.size(); ++idx )
	{
		TestDistance = ( CurFrame->Vertex[ idx ].Pos - CurMousePos ).Magnitude();
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
void cAnimationEdit::SelectNode()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CurMousePos;
	}
	
	if( Button[ MOUSE_1 ].Released() )
	{
		//Vector2D CurMousePos = CalcMousePos();
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			for( size_t idx = 0; idx < CurFrame->Vertex.size(); ++idx )
			{
				if( WithinBox( CurFrame->Vertex[ idx ].Pos, CurMousePos, OldMousePos ) )
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
			for( size_t idx = 0; idx < CurFrame->Vertex.size(); ++idx )
			{
				if( WithinBox( CurFrame->Vertex[ idx ].Pos, CurMousePos, OldMousePos ) )
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

			for( size_t idx = 0; idx < CurFrame->Vertex.size(); ++idx )
			{
				if( WithinBox( CurFrame->Vertex[ idx ].Pos, CurMousePos, OldMousePos ) )
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
void cAnimationEdit::MoveNode()
{
	if( Button[ MOUSE_1 ].Pressed() )
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::AddNode()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /* || isPaste == true */ )
	{
		CurSelected.clear();
		
		CurFrame->Vertex.push_back( cFrame::cVertex( CurMousePos ) );

		SetGridDepth( Camera, CurrentGridDepth, 40.0 );
		SetGridArray( CurrentGridDepth, GridDepth );
		
		CalcSnapToGrid( CurFrame->Vertex[CurFrame->Vertex.size() - 1].Pos, CurrentGridDepth, GridDepth );
		
		CurSelected.push_back( CurFrame->Vertex.size() - 1 );
		
		ActiveAction();
	}
}
void cAnimationEdit::DeleteNode()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
		/*	
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
			CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;*/
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
