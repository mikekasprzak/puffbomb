#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <algorithm>
#include <functional>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
int cComponentEdit::BodySingleSelectNode()
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
void cComponentEdit::BodySelectNode()
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
void cComponentEdit::BodyMoveNode()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] && !Button[ KEY_RCTRL ] )
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
				DynObj->Body.SetPos( CurSelected[idx], TempPos );
				
			}
			SnapToGrid = false;
			DynObj->Body.CalculateInternalConstraints();
			ActiveAction();
		}
		else
		{
			DynObj->Body.CalculateInternalConstraints();
			ActiveAction();
		}
	}
	if( isGroupMove )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
/*			Real TempX = Pose->Node[ CurSelected[idx] ].Pos.x;
			TempX -=
				( Mouse.Diff().x * Real( Global::HudW ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
			
			Real TempY = Pose->Node[ CurSelected[idx] ].Pos.y;
			TempY +=
				( Mouse.Diff().y * Real( Global::HudH ) ) *
				Real( Camera->Pos.z / Global::HudZoom );
					
			DynObj->Body.SetPos( CurSelected[idx], Vector2D( TempX, TempY ) );*/
			
			Real TempX = Pose->Node[ CurSelected[idx] ].Pos.x;
			TempX -= OldMousePos.x - CurMousePos.x;
			
			Real TempY = Pose->Node[ CurSelected[idx] ].Pos.y;
			TempY -= OldMousePos.y - CurMousePos.y;
					
			DynObj->Body.SetPos( CurSelected[idx], Vector2D( TempX, TempY ) );
		}
		OldMousePos = CurMousePos;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddNode()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /* || isPaste == true */ )
	{
		CurSelected.clear();
		
		size_t TempIdx = DynObj->Body.AddNode();

		Vector2D TempPos = CurMousePos;
		
		if( !Button[ KEY_LSHIFT ] )
		{
			SetGridDepth( Camera, CurrentGridDepth, 32.0 );
			SetGridArray( CurrentGridDepth, UVGridDepth );

			CalcSnapToGrid( TempPos, CurrentGridDepth, UVGridDepth );
		}
		DynObj->Body.SetPos( TempIdx, TempPos );
		
		CurSelected.push_back( TempIdx );
		
		DynObj->Body.SetMass( TempIdx, Real( 1 ) );
	
		BodyCalcTotalMass();
		
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
				DynObj->Body.DeleteNode( CurSelected[idx] );
			}
			
			BodyCalcTotalMass();
			
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
/*void cComponentEdit::BodyScaleNode()
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
			DynObj->Body.CalculateInternalConstraints();
		}
	}
	if( Button[ MOUSE_1 ].Pressed() && EditEventFlags & flScale )
	{
		EditEventFlags &= ~flScale;
		CurMousePos = CalcMousePos();
		OldMousePos = CurMousePos;
		
		DynObj->Body.CalculateInternalConstraints();		
	}
	if( EditEventFlags & flScale )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Vector2D TempPos = Pose->Node[ CurSelected[idx] ].Pos;
			TempPos *= Real( Real( 1 ) - ( Mouse.Diff().x * Real( 2 ) ) );
			
			DynObj->Body.SetPos( CurSelected[idx], TempPos );
		}	
	}
}*/
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyMass( const Real MassDiff )
{
	if( Button[ KEY_LCTRL ] )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			if( Pose->Node[ CurSelected[idx] ].Mass > Real( 1.0 ) )
			{
				if( ( Button[ KEY_MINUS ] ) || ( Mouse.Wheel.Diff() < 0 ) )
				{
					DynObj->Body.SetMass( CurSelected[idx], Pose->Node[ CurSelected[idx] ].Mass - MassDiff );
					BodyCalcTotalMass();
				}
			}
			if( ( Button[ KEY_EQUALS ] ) || ( Mouse.Wheel.Diff() > 0 ) )
			{
				DynObj->Body.SetMass( CurSelected[idx], Pose->Node[ CurSelected[idx] ].Mass + MassDiff );
				BodyCalcTotalMass();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyCalcTotalMass()
{
	Real TempMass = Real( 0 );
	
	for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
	{
		TempMass += Pose->Node[ idx ].Mass;
	}
	
	DynObj->Body.SetTotalMass( TempMass );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
