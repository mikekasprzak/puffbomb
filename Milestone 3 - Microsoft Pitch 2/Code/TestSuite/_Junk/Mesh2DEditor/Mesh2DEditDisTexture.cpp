#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <algorithm>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisChangeTexture()
{
	if( Button[ KEY_F5 ].Pressed() )
	{
		if( DisplayMesh[ CurrentObject ].TextureIdx > 0 )
		{
			--DisplayMesh[ CurrentObject ].TextureIdx;
			ActiveAction();
		}
	}
	else if( Button[ KEY_F6 ].Pressed() )
	{
		if( size_t( DisplayMesh[ CurrentObject ].TextureIdx ) < TextureID.size() - 1 )
		{
			++DisplayMesh[ CurrentObject ].TextureIdx;
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisAddTexture()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		if( DisplayMesh[ CurrentObject ].TextureIdx < 0 )
		{
			DisplayMesh[ CurrentObject ].TextureIdx = 0;
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisDeleteTexture()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		if( DisplayMesh[ CurrentObject ].TextureIdx != -1 )
		{
			DisplayMesh[ CurrentObject ].TextureIdx = -1;
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisDrawUV()
{
	glLineWidth( 4 );

	//Real Size = 0.01 * UVScale;
	Real Size = 4;
	
	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		// Draws the lines between UV coords //
		Vector2D Inverta = 
			Vector2D( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.a.x,
				( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.a.y - Real(1.0) )
				 * Real(-1.0) );
		Vector2D Invertb = 
			Vector2D( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.b.x,
				( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.b.y - Real(1.0) )
				 * Real(-1.0) );
		Vector2D Invertc = 
			Vector2D( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.c.x,
				( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.c.y - Real(1.0) )
				 * Real(-1.0) );
	
		Inverta.x *= Real( UVScale );
		Inverta.y *= Real( UVScale );

		Invertb.x *= Real( UVScale );
		Invertb.y *= Real( UVScale );

		Invertc.x *= Real( UVScale );
		Invertc.y *= Real( UVScale );
		
		gfx::Line( 
			Inverta,
			Invertb,
			gfx::RGB( 177, 177, 177 )
		);
		gfx::Line( 
			Invertb,
			Invertc,
			gfx::RGB( 177, 177, 177 )
		);
		gfx::Line( 
			Invertc,
			Inverta,
			gfx::RGB( 177, 177, 177 )
		);
		// Draws a red green and blue circle indicating the first second and third UV coord //
		
		gfx::Circle( 
			Inverta,
			Size,
			gfx::RGB( 150, 0, 0 ) );
		gfx::Circle( 
			Invertb,
			Size,
			gfx::RGB( 0, 150, 0 ) );
		gfx::Circle( 
			Invertc,
			Size,
			gfx::RGB( 0, 0, 150 ) );
	}
	
	// Draws the currently selected UV //
	for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
	{
		int VertexNum = CurSelUV[idx] % 3;
		int i = ( CurSelUV[idx] / 3 );
				
		if( VertexNum == 0 )
		{
			Vector2D Inverta = 
				Vector2D( DisplayMesh[ CurrentObject ].Face[ i ].UV.a.x * UVScale,
					( ( DisplayMesh[ CurrentObject ].Face[ i ].UV.a.y - Real(1.0) )
					 * Real(-1.0) ) * UVScale );

			gfx::Circle( 
				Inverta,
				Size,
				gfx::RGB( 0, 250, 100 ) );
		}
		else if( VertexNum == 1 )
		{
			Vector2D Invertb = 
				Vector2D( DisplayMesh[ CurrentObject ].Face[ i ].UV.b.x * UVScale,
					( ( DisplayMesh[ CurrentObject ].Face[ i ].UV.b.y - Real(1.0) )
					 * Real(-1.0) ) * UVScale );

			gfx::Circle( 
				Invertb,
				Size,
				gfx::RGB( 0, 250, 100 ) );
		}
		else if( VertexNum == 2 )
		{
			Vector2D Invertc = 
				Vector2D( DisplayMesh[ CurrentObject ].Face[ i ].UV.c.x * UVScale,
					( ( DisplayMesh[ CurrentObject ].Face[ i ].UV.c.y - Real(1.0) )
					 * Real(-1.0) ) * UVScale );

			gfx::Circle( 
				Invertc,
				Size,
				gfx::RGB( 0, 250, 100 ) );
		}
	}
	glLineWidth( 1.5 );
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisSelectUV()
{
	if( Button[ MOUSE_1 ].Released() && !CurSelected.empty() )
	{
		OldMousePos.x /= UVScale;
		OldMousePos.y /= UVScale;
		
		OldMousePos.y = ( OldMousePos.y - Real(1.0) ) * Real(-1.0);
		
		Vector2D CurMousePos = CalcUVMousePos();
		
		CurMousePos.y = ( CurMousePos.y - Real(1.0) ) * Real(-1.0);

		// Group de-select //
		if( Button[ KEY_LCTRL ] || Button[ KEY_RCTRL ] )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				if( WithinBox( 
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.a, CurMousePos,
					 OldMousePos ) )
				{	
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) )
						{
							IsNewUV = false;
						}
					}
					if( !IsNewUV )
					{
						std::vector <size_t> tempVec;
						
						for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
						{
							if( CurSelUV[vec] != CurSelected[ idx ] * 3 )
							{
								tempVec.push_back( CurSelUV[vec] );
							}
						}
						CurSelUV.swap( tempVec );
					}	
				}
				if( WithinBox( 
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.b, CurMousePos,
					 OldMousePos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 1 )
						{
							IsNewUV = false;
						}
					}
					if( !IsNewUV )
					{
						std::vector <size_t> tempVec;
						
						for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
						{
							if( CurSelUV[vec] != ( CurSelected[ idx ] * 3 ) + 1 )
							{
								tempVec.push_back( CurSelUV[vec] );
							}
						}
						CurSelUV.swap( tempVec );
					}	
				}
				if( WithinBox( 
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.c, CurMousePos,
					 OldMousePos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 2 )
						{
							IsNewUV = false;
						}
					}
					if( !IsNewUV )
					{
						std::vector <size_t> tempVec;
						
						for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
						{
							if( CurSelUV[vec] != ( CurSelected[ idx ] * 3 ) + 2 )
							{
								tempVec.push_back( CurSelUV[vec] );
							}
						}
						CurSelUV.swap( tempVec );
					}	
				}
			}
			int TestUV = -1;
			TestUV = DisSingleSelectUV( CurMousePos );
			if( TestUV != -1 )
			{
				bool IsNewUV = true;
				for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
				{
					if( int( CurSelUV[idx] ) == TestUV )
					{
						IsNewUV = false;
					}
				}
				if( !IsNewUV )
				{
					std::vector <size_t> tempVec;
					
					for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
					{
						if( int(CurSelUV[vec]) != TestUV )
						{
							tempVec.push_back( CurSelUV[vec] );
						}
					}
					CurSelUV.swap( tempVec );
				}	
			}
		}
		else
		{		
			// Group add-select //	
			if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
			{
					
			}
			// Standard group select //
			else
			{
				CurSelUV.clear();
			}
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				if( WithinBox( 
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.a, CurMousePos,
					 OldMousePos ) )
				{	
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) )
						{
							IsNewUV = false;
						}
					}
					if( IsNewUV )
					{
						CurSelUV.push_back( ( CurSelected[ idx ] * 3 ) );
					}
				}
				if( WithinBox( 
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.b, CurMousePos,
					 OldMousePos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 1 )
						{
							IsNewUV = false;
						}
					}
					if( IsNewUV )
					{
						CurSelUV.push_back( ( CurSelected[ idx ] * 3 ) + 1 );
					}
				}
				if( WithinBox( 
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.c, CurMousePos,
					 OldMousePos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 2 )
						{
							IsNewUV = false;
						}
					}
					if( IsNewUV )
					{
						CurSelUV.push_back( ( CurSelected[ idx ] * 3 ) + 2 );
					}	
				}
			}
			int TestUV = -1;
			
			TestUV = DisSingleSelectUV( CurMousePos );
			
			if( TestUV != -1 )
			{
				bool IsNewUV = true;
				for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
				{
					if( int( CurSelUV[idx] ) == TestUV )
					{
						IsNewUV = false;
					}
				}
				if( IsNewUV )
				{
					CurSelUV.push_back( TestUV );
				}	
			}
			
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ZoomUV()
{
	if ( Button[ KEY_EQUALS ] )
	{
		UVCamera->Pos.z -= Real( 10 );
	}
	else if ( Button[ KEY_MINUS ] )
	{
		UVCamera->Pos.z += Real( 10 );
	}
	// - -------------------------------------------------------------------------------------- - //
	if( Mouse.Wheel.Diff() > 0 )
	{
		UVCamera->Pos.z -= Real( 64 );
	}		
	else if( Mouse.Wheel.Diff() < 0 )
	{
		UVCamera->Pos.z += Real( 64 );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ScrollUV()
{
	// Scroll Mouse Button
	// Pans the Hud	
	if( Button[ MOUSE_3 ] && UVMiddleClick == false )
	{
		UVMiddleClick = true;
		UVScrollMouseX = int( Mouse.x * ( Real( Global::HudW ) * UVWidth ) );
		UVScrollMouseY = int( -Mouse.y * ( Real( Global::HudH ) * UVHeight ) );
	}
	else if( !( Button[ MOUSE_3 ] ) && UVMiddleClick )
	{
		UVMiddleClickLast = UVMiddleClick;
		UVMiddleClick = false;
	}
	else if( UVMiddleClick )
	{
		UVCamera->Pos.x += ( int( Mouse.x * ( Real( Global::HudW ) * ( UVWidth ) ) ) - UVScrollMouseX )
			* Real( -UVCamera->Pos.z / UVZoomOffsetX );
		UVCamera->Pos.y += ( int( -Mouse.y * ( Real( Global::HudH ) ) * UVHeight ) - UVScrollMouseY )
			* Real( -UVCamera->Pos.z / UVZoomOffsetY );
		UVScrollMouseX = int( Mouse.x * ( Real( Global::HudW ) * UVWidth ) );
		UVScrollMouseY = int( -Mouse.y * ( Real( Global::HudH ) * UVHeight ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cMesh2DEdit::CalcUVMousePos()
{
	// 612
	// 244.8
	// 550.8
	// 0.000265625
	//UVZoomOffsetX( 144.5 ),
	//UVZoomOffsetY( 232 ),

	return Vector2D(
		Real( ( int( Mouse.x * Real( Global::HudW * UVWidth ) ) )
		- ( -UVCamera->Pos.x / Real( UVCamera->Pos.z / UVZoomOffsetX ) )
		- ( ( Real(Global::HudW) * UVWidth ) ) )
		* Real( UVCamera->Pos.z / UVZoomOffsetX ) / UVScale + Real( 1 )
		+ ( ( UVCamera->Pos.z - Real( 612 ) ) / Real( 612 ) ),
		Real( ( int( -Mouse.y * Real( Global::HudH ) * UVHeight )
		+ ( UVCamera->Pos.y / Real( UVCamera->Pos.z / UVZoomOffsetY ) )
		+ ( ( Global::HudH * UVHeight ) ) )
		* Real( UVCamera->Pos.z / UVZoomOffsetY ) ) / UVScale - Real( 1 )
		- ( ( UVCamera->Pos.z - Real( 612 ) ) / Real( 612 ) )
	);
	
	
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawDisSelectUV()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcUVMousePos();
		OldMousePos.x *= UVScale;
		OldMousePos.y *= UVScale;
	}
	
	if( Button[ MOUSE_1 ] )
	{
		Vector2D CurMousePos = CalcUVMousePos();
		CurMousePos.x *= UVScale;
		CurMousePos.y *= UVScale;
		
		gfx::Rect( OldMousePos, CurMousePos, gfx::RGB( 255, 255, 255 ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
int cMesh2DEdit::DisSingleSelectUV( Vector2D &CurMousePos )
{
	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		if( ( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.a
			- CurMousePos ).Magnitude() < Real( 0.03 ) )
		{
			return CurSelected[ idx ] * 3;
		}
		if( ( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.b
			- CurMousePos ).Magnitude() < Real( 0.03 ) )
		{
			return CurSelected[ idx ] * 3 + 1;
		}
		if( ( DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].UV.c
			- CurMousePos ).Magnitude() < Real( 0.03 ) )
		{
			return CurSelected[ idx ] * 3 + 2;
		}
	}
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisMoveUV()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] )
		{
			Vector2D CurMousePos = CalcUVMousePos();
			CurMousePos.y = ( CurMousePos.y - Real(1.0) ) * Real(-1.0);

			int temp = DisSingleSelectUV( CurMousePos );
			for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
			{
				if( temp == int(CurSelUV[idx]) )
				{
					isUVGroupMove = true;
				}
			}
		}
		// Snaps to grid
		if( !Button[ KEY_LSHIFT ] && isUVGroupMove )
		{
			SnapToUVGrid = true;
		}
		else
		{
			SnapToUVGrid = false;
		}
	}
	if( Button[ MOUSE_1 ].Released() )
	{
		isUVGroupMove = false;
		
		if( SnapToUVGrid )
		{
			for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
			{
				int VertexNum = CurSelUV[idx] % 3;
				int i = ( CurSelUV[idx] / 3 );
				
				if( VertexNum == 0 )
				{
					DisplayMesh[ CurrentObject ].Face[ i ].UV.a.x *= UVScale;
					DisplayMesh[ CurrentObject ].Face[ i ].UV.a.y *= UVScale;
					
					CalcSnapToGrid( DisplayMesh[ CurrentObject ].Face[ i ].UV.a
						, CurUVGridDepth, UVGridDepth );
					
					DisplayMesh[ CurrentObject ].Face[ i ].UV.a.x /= UVScale;
					DisplayMesh[ CurrentObject ].Face[ i ].UV.a.y /= UVScale;
				}
				else if( VertexNum == 1 )
				{
					DisplayMesh[ CurrentObject ].Face[ i ].UV.b.x *= UVScale;
					DisplayMesh[ CurrentObject ].Face[ i ].UV.b.y *= UVScale;
					
					CalcSnapToGrid( DisplayMesh[ CurrentObject ].Face[ i ].UV.b
						, CurUVGridDepth, UVGridDepth );
					
					DisplayMesh[ CurrentObject ].Face[ i ].UV.b.x /= UVScale;
					DisplayMesh[ CurrentObject ].Face[ i ].UV.b.y /= UVScale;
				}
				else if( VertexNum == 2 )
				{
					DisplayMesh[ CurrentObject ].Face[ i ].UV.c.x *= UVScale;
					DisplayMesh[ CurrentObject ].Face[ i ].UV.c.y *= UVScale;
					
					CalcSnapToGrid( DisplayMesh[ CurrentObject ].Face[ i ].UV.c
						, CurUVGridDepth, UVGridDepth );
					
					DisplayMesh[ CurrentObject ].Face[ i ].UV.c.x /= UVScale;
					DisplayMesh[ CurrentObject ].Face[ i ].UV.c.y /= UVScale;
				}
			}
			SnapToUVGrid = false;
			ActiveAction();
		}
		else
		{
			//ActiveAction();
		}
	}
	if( isUVGroupMove )
	{
		for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
		{
			int VertexNum = CurSelUV[idx] % 3;
			int i = ( CurSelUV[idx] / 3 );
				
			if( VertexNum == 0 )
			{
				DisplayMesh[ CurrentObject ].Face[ i ].UV.a.x -=
				( Mouse.Diff().x * ( Real( Global::HudW ) * ( UVWidth ) ) ) *
				Real( UVCamera->Pos.z / UVZoomOffsetX ) / ( UVScale * Real( 2 ) );
				
				DisplayMesh[ CurrentObject ].Face[ i ].UV.a.y +=
				( -Mouse.Diff().y * Real( Global::HudH ) * ( UVHeight ) ) *
				Real( -UVCamera->Pos.z / UVZoomOffsetY ) / ( UVScale * Real( 2 ) ) * Real(-1.0);
			}
			else if( VertexNum == 1 )
			{
				DisplayMesh[ CurrentObject ].Face[ i ].UV.b.x -=
				( Mouse.Diff().x * ( Real( Global::HudW ) * ( UVWidth ) ) ) *
				Real( UVCamera->Pos.z / UVZoomOffsetX ) / ( UVScale * Real( 2 ) );
				
				DisplayMesh[ CurrentObject ].Face[ i ].UV.b.y +=
				( -Mouse.Diff().y * Real( Global::HudH ) * ( UVHeight ) ) *
				Real( -UVCamera->Pos.z / UVZoomOffsetY ) / ( UVScale * Real( 2 ) ) * Real(-1.0);
			}
			else if( VertexNum == 2 )
			{
				DisplayMesh[ CurrentObject ].Face[ i ].UV.c.x -=
				( Mouse.Diff().x * ( Real( Global::HudW ) * ( UVWidth ) ) ) *
				Real( UVCamera->Pos.z / UVZoomOffsetX ) / ( UVScale * Real( 2 ) );
				
				DisplayMesh[ CurrentObject ].Face[ i ].UV.c.y +=
				( -Mouse.Diff().y * Real( Global::HudH ) * ( UVHeight ) ) *
				Real( -UVCamera->Pos.z / UVZoomOffsetY ) / ( UVScale * Real( 2 ) ) * Real(-1.0);
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisRotateUV()
{
	if( Button[ KEY_T ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a.x =
			( DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a.x - Real(1.0) )
			* Real(-1.0);
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a.y = 
			( DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a.y - Real(1.0) )
			* Real(-1.0);
			
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b.x =
			( DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b.x - Real(1.0) )
			* Real(-1.0);
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b.y = 
			( DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b.y - Real(1.0) )
			* Real(-1.0);

			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.c.x =
			( DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.c.x - Real(1.0) )
			* Real(-1.0);
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.c.y = 
			( DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.c.y - Real(1.0) )
			* Real(-1.0);

		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisRotateUVRGB()
{
	if( Button[ KEY_R ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Vector2D temp = DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a;

			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a = 
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.c;

			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.c = 
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b;

			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b = temp;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisInvertUV()
{
	if( Button[ KEY_I ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Vector2D temp = DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a;

			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.a = 
			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b;

			DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].UV.b = temp;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisChangeLayer()
{
	if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
	{
		// Changes the selected faces layer //
		if( Button[ KEY_MINUS_PAD ].Pressed() )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				--DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].Layer;
			}
			--CurLayer;
			LayerCheck();
			ActiveAction();
		}
		else if( Button[ KEY_PLUS_PAD ].Pressed() )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				++DisplayMesh[ CurrentObject ].Face[CurSelected[idx]].Layer;
			}
			++CurLayer;
			LayerCheck();
			ActiveAction();
		}
	}
	else
	{
		// Changes the current layer //
		if( Button[ KEY_MINUS_PAD ].Pressed() )
		{
			--CurLayer;
			CurSelected.clear();
		}
		else if( Button[ KEY_PLUS_PAD ].Pressed() )
		{
			++CurLayer;
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::LayerCheck()
{
	DrawLayers.clear();
	for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
	{
		bool HasLayer = false;
		for( size_t i = 0; i < DrawLayers.size(); ++i )
		{
			if( DrawLayers[i] == DisplayMesh[ CurrentObject ].Face[idx].Layer )
			{
				HasLayer = true;
			}
		}
		if( !HasLayer )
		{
			DrawLayers.push_back( DisplayMesh[ CurrentObject ].Face[idx].Layer );
		}
	}
	sort( DrawLayers.begin(), DrawLayers.end() );
}
// - ------------------------------------------------------------------------------------------ - //
int cMesh2DEdit::CheckLow( int ObjectIdx )
{
	int TempLow = 0;
	for( size_t idx = 0; idx < DisplayMesh[ ObjectIdx ].Face.size(); ++idx )
	{
		if( DisplayMesh[ ObjectIdx ].Face[idx].Layer < TempLow )
		{
			TempLow = DisplayMesh[ ObjectIdx ].Face[idx].Layer;
		}
	}
	return TempLow;
}
// - ------------------------------------------------------------------------------------------ - //
int cMesh2DEdit::CheckHigh( int ObjectIdx )
{
	int TempHigh = 0;
	for( size_t idx = 0; idx < DisplayMesh[ ObjectIdx ].Face.size(); ++idx )
	{
		if( DisplayMesh[ ObjectIdx ].Face[idx].Layer > TempHigh )
		{
			TempHigh = DisplayMesh[ ObjectIdx ].Face[idx].Layer;
		}
	}
	return TempHigh;
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::CalcUVZoomOffset()
{
	UVZoomOffsetX = ( Real( Global::HudW ) * UVZoomOffsetX ) / Real( 1920.0 );
	UVZoomOffsetY = ( Real( Global::HudH ) * UVZoomOffsetY ) / Real( 1200.0 );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
