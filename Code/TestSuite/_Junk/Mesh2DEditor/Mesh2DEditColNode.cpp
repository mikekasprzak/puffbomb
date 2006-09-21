#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawNode( int Color, int Node )
{	
	gfx::Circle( Object[ CurrentObject ].Pos( Node ), 1, Color );
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawColSnapToGrid( size_t Node )
{	
	Vector2D SnapGhost( Object[ CurrentObject ].Pos( Node ).x,
		Object[ CurrentObject ].Pos( Node ).y );
	
	CalcSnapToGrid( SnapGhost, CurrentGridDepth, GridDepth );

	gfx::Circle( SnapGhost, 1, gfx::RGB( 80, 0, 0 ) );
	
	if( HasSphere[ Node ] )
	{
		for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ )
		{
			if ( Object[ CurrentObject ].Sphere[ idx ].Index == Node )
			{
				gfx::Circle(
					SnapGhost,
					Object[ CurrentObject ].Sphere[ idx ].Radius,
					gfx::RGB( 80, 0, 0 )
				);
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SwitchNode()
{	
	if ( Button[ KEY_UP ].Pressed() )
	{
		if( CurrentNode > 0 )
		{
			--CurrentNode;
		}
		else
		{
			CurrentNode = Object[ CurrentObject ].size() - 1;
		}
	}
	else if ( Button[ KEY_DOWN ].Pressed() )
	{

		if( CurrentNode < Object[ CurrentObject ].size() - 1 )
		{
			++CurrentNode;	
		}
		else
		{
			CurrentNode = 0;	
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColAddNode()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() || isPaste == true )
	{

		CurrentNode = Object[ CurrentObject ].AddNode();
		Object[ CurrentObject ].Set(
			CurrentNode,
			CalcMousePos()
		);
		
		CalcSnapToGrid( Object[ CurrentObject ].HomePos( CurrentNode ), CurrentGridDepth, GridDepth );
							
		Object[ CurrentObject ].Pos( CurrentNode ) =
			Object[ CurrentObject ].HomePos( CurrentNode );
		Object[ CurrentObject ].Old( CurrentNode ) =
			Object[ CurrentObject ].HomePos( CurrentNode );
		Object[ CurrentObject ].HomeOld( CurrentNode ) =
			Object[ CurrentObject ].Old( CurrentNode );

		SphereCheck();
		if( !isPaste )
		{
			ActiveAction();
			SphereCheck();
			CurSelected.clear();
			CurSelected.push_back( Object[ CurrentObject ].size() - 1 );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SetMass( Real MassDiff, int Node )
{
	if( Button[ KEY_LCTRL ] )
	{
		if( Object[ CurrentObject ].Mass[ Node ] > MassDiff )
		{
			if ( Button[ KEY_MINUS ] )
			{
				Object[ CurrentObject ].Mass[ Node ] -= MassDiff;
			}
			
			if( Mouse.Wheel.Diff() < 0 )
			{
				Object[ CurrentObject ].Mass[ Node ] -= MassDiff;
			}		
		}
		// - ------------------------------------------------------------------------------ - //
		if( Button[ KEY_EQUALS ] )
		{
			Object[ CurrentObject ].Mass[ Node ] += MassDiff;
		}
		if( Mouse.Wheel.Diff() > 0 )
		{
			Object[ CurrentObject ].Mass[ Node ] += MassDiff;
		}
	}
	else
	{
		if( !Mesh2DInfo[ CurrentObject ].UndoObject.empty() )
		{
			if( Object[ CurrentObject ].Mass[ Node ] !=
				Mesh2DInfo[ CurrentObject ].UndoObject.back().SphereObject.Mass[ Node ] )
			{				
				ActiveAction();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColSelectNode()
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
			for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( Object[ CurrentObject ].Pos( idx ), CurMousePos, OldMousePos ) )
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
			int temp = ColSingleSelect( CurMousePos );
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
			for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( Object[ CurrentObject ].Pos( idx ), CurMousePos, OldMousePos ) )
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
			int temp = ColSingleSelect( CurMousePos );
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

			for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( Object[ CurrentObject ].Pos( idx ), CurMousePos, OldMousePos ) )
				{
					CurSelected.push_back( idx );
				}
			}
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = ColSingleSelect( CurMousePos );
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
int cMesh2DEdit::ColSingleSelect( Vector2D &CurMousePos )
{
	int LastIdx = -1;
	Real LastDistance = 3.0;
	Real TestDistance = 3.0;

	for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
	{
		TestDistance = ( Object[ CurrentObject ].Pos( idx ) - CurMousePos ).Magnitude();
		if( HasSphere[ idx ] && EditMode == SPHERE_MODE )
		{
			if( TestDistance < Object[ CurrentObject ].Sphere[ idx ].Radius )
			{
				if( TestDistance < LastDistance )
				{
					LastDistance = TestDistance;
					LastIdx = idx;
				}
			}
		}
		else if( TestDistance < Real( 3.0 ) )
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
void cMesh2DEdit::ColMoveNode()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] || !Button[ KEY_RCTRL ] )
		{
			//Vector2D MousePos = CalcMousePos();
		
			Vector2D CurMousePos = CalcMousePos();
			int temp = ColSingleSelect( CurMousePos );
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
				CalcSnapToGrid( Object[ CurrentObject ].HomePos( CurSelected[idx] )
					, CurrentGridDepth, GridDepth );
						
				Object[ CurrentObject ].Pos( CurSelected[idx] ) =
					Object[ CurrentObject ].HomePos( CurSelected[idx] );
				Object[ CurrentObject ].Old( CurSelected[idx] ) =
					Object[ CurrentObject ].HomePos( CurSelected[idx] );
				Object[ CurrentObject ].HomeOld( CurSelected[idx] ) =
					Object[ CurrentObject ].Old( CurSelected[idx] );
				
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
			Object[ CurrentObject ].HomePos( CurSelected[idx] ).x -=
				( Mouse.Diff().x * Real( cGlobal::HudW ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
			
			Object[ CurrentObject ].HomePos( CurSelected[idx] ).y +=
				( Mouse.Diff().y * Real( cGlobal::HudH ) ) *
				Real( Camera->Pos.z / cGlobal::HudZoom );
						
			Object[ CurrentObject ].Pos( CurSelected[idx] ) =
				Object[ CurrentObject ].HomePos( CurSelected[idx] );
			Object[ CurrentObject ].Old( CurSelected[idx] ) =
				Object[ CurrentObject ].HomePos( CurSelected[idx] );
			Object[ CurrentObject ].HomeOld( CurSelected[idx] ) =
				Object[ CurrentObject ].Old( CurSelected[idx] );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColCopy()
{
	if( Button[ KEY_LCTRL ] || Button[ KEY_RCTRL ] )
	{
		// Copy the current Node and Sphere //
		if( Button[ KEY_C ].Pressed() || Button[ KEY_INSERT ].Pressed() )
		{
			cStoreMesh tempStoreMesh;
			StoreMesh.clear();
			SphereCheck();
			for( size_t i = 0; i < CurSelected.size(); ++i )
			{
				if( HasSphere[ CurSelected[i] ] )
				{
					for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
						if ( Object[ CurrentObject ].Sphere[ idx ].Index == CurSelected[i] ) {
	
							tempStoreMesh.Radius = Object[ CurrentObject ].Sphere[ idx ].Radius;
							tempStoreMesh.Mass = Object[ CurrentObject ].Mass[ CurSelected[i] ];
							tempStoreMesh.Pos = Object[ CurrentObject ].Pos( CurSelected[i] );
						}
					}
				}
				else
				{
					tempStoreMesh.Radius = Real( 0.0 );
					tempStoreMesh.Mass = Object[ CurrentObject ].Mass[ CurSelected[i] ];
					tempStoreMesh.Pos = Object[ CurrentObject ].Pos( CurSelected[i] );
					
				}
				StoreMesh.push_back( tempStoreMesh );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColPaste()
{
	if( Button[ KEY_LCTRL ] && Button[ KEY_V ].Pressed() ||
		Button[ KEY_RCTRL ] && Button[ KEY_V ].Pressed() ||
	Button[ KEY_LSHIFT ] && Button[ KEY_INSERT ].Pressed() ||
	Button[ KEY_RSHIFT ] && Button[ KEY_INSERT ].Pressed() )
	{
		for( size_t idx = 0; idx < StoreMesh.size(); ++idx )
		{
			if( StoreMesh[idx].Mass != Real( 0.0 ) )
			{
				isPaste = true;
				ColAddNode();
				if( StoreMesh[idx].Radius != Real( 0.0 ) )
				{
					AddSphere();
					Object[ CurrentObject ].Sphere[
						Object[ CurrentObject ].Sphere.size() - 1 ].Radius = StoreMesh[idx].Radius;
				}
				Object[ CurrentObject ].Mass[ Object[ CurrentObject ].size() - 1 ]
					= StoreMesh[idx].Mass;

				Object[ CurrentObject ].Set(
					CurrentNode,
					Vector2D( CalcMousePos().x + StoreMesh[idx].Pos.x,
						CalcMousePos().y + StoreMesh[idx].Pos.y )
				);
				isPaste = false;
			} 
		}
		int tempSelect = Object[ CurrentObject ].size() - 1;
		CurSelected.clear();
		for( size_t i = 0; i < StoreMesh.size(); ++i )
		{
			CurSelected.push_back( tempSelect );
			--tempSelect;
		}
		ActiveAction();
		SphereCheck();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColDeleteNode()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			for( int idx = CurSelected.size() - 1; idx >= 0; --idx )
			{ 
				Object[ CurrentObject ].DeleteNode( CurSelected[idx] );
			}
			CurSelected.clear();
			SphereCheck();
		
			ActiveAction();
			if( CurrentNode != 0 )
			{
				CurrentNode--;
			}
			else
			{
				CurrentNode = 0;
			}			
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColMass( Real MassDiff )
{
	if( !CurSelected.empty() )
	{
		for( size_t i = 0; i < CurSelected.size(); ++i )
		{
			SetMass( MassDiff, CurSelected[i] );
		}	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawColSelect()
{
	if( Button[ MOUSE_1 ] )
	{
		Vector2D CurMousePos = CalcMousePos();
		gfx::Rect( OldMousePos, CurMousePos, gfx::RGB( 255, 255, 255 ) );
		if( !Button[ KEY_LCTRL ] )
		{
			for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( Object[ CurrentObject ].Pos( idx ), CurMousePos, OldMousePos ) )
				{
					if( EditMode == NODE_MODE || EditMode == SPRING_MODE )
					{	
						DrawNode( gfx::RGB( 0, 200, 100 ), idx );
					}
					else if( EditMode == SPHERE_MODE )
					{
						DrawNode( gfx::RGB( 0, 100, 50 ), idx );
					}
					if( HasSphere[ idx ] )
					{
						for( size_t sphere = 0; sphere < Object[ CurrentObject ].size(); ++sphere )
						{
							if ( Object[ CurrentObject ].Sphere[ sphere ].Index == idx )
							{
								if( EditMode == NODE_MODE || EditMode == SPRING_MODE )
								{
									DrawSphere( gfx::RGB( 0, 100, 50 ), sphere );
								}
								else if( EditMode == SPHERE_MODE )
								{
									DrawSphere( gfx::RGB( 0, 200, 100 ), sphere );
								}
							}
						}
					}
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColLockNode()
{
	if( Button[ KEY_L ].Pressed() )
	{
		if( ColIsLocked( CurrentNode ) )
		{
			Object[ CurrentObject ].DeleteHard( CurrentNode );			
		}
		else
		{
			Object[ CurrentObject ].AddHard( CurrentNode );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
bool cMesh2DEdit::ColIsLocked( size_t Idx )
{
	for( size_t i = 0; i < Object[ CurrentObject ].Hard.size(); ++i )
	{
		if( Object[ CurrentObject ].Hard[i].Index == Idx )
		{
			if( Object[ CurrentObject ].Hard[i].Enabled )
			{
				return true;
			}
		}
	}
	
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
