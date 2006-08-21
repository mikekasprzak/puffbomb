#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <algorithm>
#include <functional>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
int cComponentEdit::BodySingleSelectNode()
{
	int LastIdx = -1;
	Real LastDistance = NodeRadius;
	Real TestDistance = NodeRadius;
	
//	for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
	for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
	{
//		TestDistance = ( Body2D[ CurBody ].Nodes.Pos( idx ) - CurMousePos ).Magnitude();
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
void cComponentEdit::BodySelectNode()
{
	if( Button[ MOUSE_1 ].Released() )
	{
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
//			for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
			for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
			{
//				if( WithinBox( Body2D[ CurBody ].Nodes.Pos( idx ), CurMousePos, OldMousePos ) )
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
//			for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
			for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
			{
//				if( WithinBox( Body2D[ CurBody ].Nodes.Pos( idx ), CurMousePos, OldMousePos ) )
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
			
//			for( size_t idx = 0; idx < Body2D[ CurBody ].Nodes.Size(); ++idx )
			for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
			{
//				if( WithinBox( Body2D[ CurBody ].Nodes.Pos( idx ), CurMousePos, OldMousePos ) )
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
void cComponentEdit::BodyMoveNode()
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
			SetGridDepth( Camera, CurrentGridDepth, 40.0 );
			SetGridArray( CurrentGridDepth, GridDepth );

			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				//Pose->Node[ idx ].Pos
				//Body2D[ 0 ].SetPos(
//				CalcSnapToGrid( Body2D[ CurBody ].Nodes.Pos( CurSelected[idx] ), CurrentGridDepth, GridDepth );
				Vector2D TempPos = Pose->Node[ CurSelected[idx] ].Pos;
				CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );
				DynObj[ CurObj ].Body.SetPos( CurSelected[idx], TempPos );
				
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
			
			
			Real TempX = Pose->Node[ CurSelected[idx] ].Pos.x;
			TempX -=
				( Mouse.Diff().x * Real( cGlobal::HudW ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
			
			Real TempY = Pose->Node[ CurSelected[idx] ].Pos.y;
			TempY +=
				( Mouse.Diff().y * Real( cGlobal::HudH ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
					
			DynObj[ CurObj ].Body.SetPos( CurSelected[idx], Vector2D( TempX, TempY ) );
/*
			Body2D[ CurBody ].Nodes.Pos( CurSelected[idx] ).x -=
				( Mouse.Diff().x * Real( cGlobal::HudW ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
			
			Body2D[ CurBody ].Nodes.Pos( CurSelected[idx] ).y +=
				( Mouse.Diff().y * Real( cGlobal::HudH ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
*/		
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddNode()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /* || isPaste == true */ )
	{
		CurSelected.clear();
		
//		size_t tempIdx = Body2D[ CurBody ].AddNode();
		size_t TempIdx = DynObj[ CurObj ].Body.AddNode();

		//Body2D[ CurBody ].Nodes.Pos( tempIdx ) = CurMousePos;
		Vector2D TempPos = CurMousePos;
		
		SetGridDepth( Camera, CurrentGridDepth, 40.0 );
		SetGridArray( CurrentGridDepth, GridDepth );

		if( !Button[ KEY_LCTRL ].Pressed() )
		{
			CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );
		}
		DynObj[ CurObj ].Body.SetPos( TempIdx, TempPos );

		//CalcSnapToGrid( Body2D[ CurBody ].Nodes.Pos( tempIdx ), CurrentGridDepth, GridDepth );
		
		CurSelected.push_back( TempIdx );
		
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeleteNode()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			sort( CurSelected.begin(), CurSelected.end() );
			for( int idx = CurSelected.size() - 1; idx > -1; --idx )
			{
				DynObj[ CurObj ].Body.DeleteNode( CurSelected[idx] );
				
//				Log( LOG_HIGHEST_LEVEL, "CurSelected[idx]  " << CurSelected[idx] );
			}
			
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyScaleNode()
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
void cComponentEdit::BodyMass( const Real MassDiff )
{
	if( Button[ KEY_LCTRL ] )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
		//	if( Body2D[ CurBody ].Nodes.Mass[ CurSelected[idx] ] > Real( 1.0 ) )
			if( Pose->Node[ CurSelected[idx] ].Mass > Real( 1.0 ) )
			{
				if ( Button[ KEY_MINUS ] )
				{
					DynObj[ CurObj ].Body.SetMass( CurSelected[idx], Pose->Node[ CurSelected[idx] ].Mass - MassDiff );
					
				//	Body2D[ CurBody ].Nodes.Mass[ CurSelected[idx] ] -= MassDiff;
				}
				
				if( Mouse.Wheel.Diff() < 0 )
				{
					DynObj[ CurObj ].Body.SetMass( CurSelected[idx], Pose->Node[ CurSelected[idx] ].Mass - MassDiff );
	
//					Body2D[ CurBody ].Nodes.Mass[ CurSelected[idx] ] -= MassDiff;
				}		
			}
			// - ---------------------------------------------------------------------- - //
			if( Button[ KEY_EQUALS ] )
			{
				DynObj[ CurObj ].Body.SetMass( CurSelected[idx], Pose->Node[ CurSelected[idx] ].Mass + MassDiff );
				//Body2D[ CurBody ].Nodes.Mass[ CurSelected[idx] ] += MassDiff;
			}
			if( Mouse.Wheel.Diff() > 0 )
			{
				DynObj[ CurObj ].Body.SetMass( CurSelected[idx], Pose->Node[ CurSelected[idx] ].Mass + MassDiff );
				//Body2D[ CurBody ].Nodes.Mass[ CurSelected[idx] ] += MassDiff;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
