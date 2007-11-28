#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>

// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
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
				( Mouse.Diff().x * Real( Global::HudW ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
			
			CurFrame->Vertex[ CurSelected[idx] ].Pos.y +=
				( Mouse.Diff().y * Real( Global::HudH ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
		
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
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DeleteNode()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{	
			isDeleteNode = true;
			DeleteFaceFromNodes();
			isDeleteNode = false;

			std::vector< cFrame::cVertex > tempVertex;
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
					tempVertex.push_back( CurFrame->Vertex[idx] );
				}
			}
			CurFrame->Vertex.clear();
			CurFrame->Vertex.swap( tempVertex );
			
			CurSelected.clear();
			isDeleteNode = false;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::ScaleNode()
{
	if( Button[ KEY_L ].Pressed() )
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
//			CurFrame->Vertex[ CurSelected[idx] ].Pos.x *= Real( Real( 1 ) - Mouse.Diff().x );
//			CurFrame->Vertex[ CurSelected[idx] ].Pos.y *= Real( Real( 1 ) - Mouse.Diff().y );
		}	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::RotateNode()
{
/*	if( Button[ KEY_K ].Pressed() )
	{
		isRotateNode = !isRotateNode;	
	}
	if( Button[ MOUSE_1 ].Pressed() && isRotateNode )
	{
		isRotateNode = false;
		CurMousePos = CalcMousePos();
		OldMousePos = CurMousePos;
	}
	if( isRotateNode )
	{
		int MaxSteps = 16;
		
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
//			for( int i = 0; i <= MaxSteps; i++ )
			for( int i = 0; i <= MaxSteps; i++ )
			{
				Real StepAsRadian = (Real( 8 ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);
				
				Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
				
				Point *= Real( Mouse.Diff().x * Real( 2 ) );
				
				Real StepAsRadian2 = (Real( 9 ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);
				
				Vector2D Point2( sin( StepAsRadian2 ), cos( StepAsRadian2 ) );
				
				Point = Vector2D( Point2 - Point ).Magnitude() );
////				Point *= Real( 1 );
	
				//Point += Vector2D( CurFrame->Vertex[ CurSelected[idx] ].Pos.x, CurFrame->Vertex[ CurSelected[idx] ].Pos.y );
				
				CurFrame->Vertex[ CurSelected[idx] ].Pos += Point;
	//			CurFrame->Vertex[ CurSelected[idx] ].Pos += Point;
				
				//CurFrame->Vertex[ CurSelected[idx] ].Pos *= Real( Real( 1 ) - ( Mouse.Diff().x * Real( 2 ) ) );
			}
		}	
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
