#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Edit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cEdit::cEdit() :
	IsHelp( false ),
	MiddleClick( false ),
	MiddleClickLast( false ),
	AutoGridDepth( true ),
	ScrollMouseX( 0 ),
	ScrollMouseY( 0 ),
	ScrollFrame( 10 ),
	ScrollSpeed( 3.0 ),
	GridSize( 16384.0 ),
//	GridSize( 256.0 ),
	CurrentGridDepth( 0 )
{
	// Create Camera //
	Camera = new cCamera(
		Vector3D( 0.0, 0.0, cGlobal::HudZoom ),
		Vector3D( 0.0, 0.0, 0.0 ),
		Vector3D( 0.0, 1.0, 0.0 ),
		45.0,
		Platform::AspectRatio,
		1.0,
		100000.0,
		cGlobal::HudZoom,
		cGlobal::HudZoom,
		cGlobal::HudZoom
	 );

	HudCamera = new cCamera(
		Vector3D( 0.0, 0.0, cGlobal::HudZoom ),
		Vector3D( 0.0, 0.0, 0.0 ),
		Vector3D( 0.0, 1.0, 0.0 ),
		45.0,
		Platform::AspectRatio,
		1.0,
		100000.0,
		cGlobal::HudZoom,
		cGlobal::HudZoom,
		cGlobal::HudZoom
	 );
	
	// Sets grid density values //
	Real GridDepthValue = 0.32;
	Real GridRangeValue = 32.0;
	
	Scale = Real::One;
	
	for( int idx = 0; idx < 13; ++idx )
	{
		GridDepth[idx] = GridDepthValue;
		
		GridDepthValue *= Real(2.0);
		
		GridRange[idx] = GridRangeValue;
		
		GridRangeValue *= Real(2.0);
	}


//	CurrentDir = "Content/PuffBOMB/";
	CurrentDir = "../../../../Content/PuffBOMB/";
	
	
	GridVertex.resize( GridSize * Real( 4 ) * Real( 2 ) );
	GridIndices.resize( GridSize * Real( 8 ) * Real( 2 ) );
	GridIndicesSize = 0;
	
	GridVertex2.resize( GridSize * Real( 2 ) );
	GridIndices2.resize( GridSize * Real( 2 ) * Real( 2 ) );
	GridIndicesSize2 = 0;
	
	LastCamera = Camera;
}

cEdit::~cEdit()
{
	delete Camera;
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::Scroll( cCamera* MyCamera )
{
//	cGlobal::HudH;
	
	// Scroll Mouse Button
	// Pans the screen	
	if( Button[ MOUSE_3 ] && MiddleClick == false )
	{
		MiddleClick = true;
		ScrollMouseX = int( Mouse.x * Real( cGlobal::HudW ) );
		ScrollMouseY = int( -Mouse.y * Real( cGlobal::HudH ) );
	}
	else if( !( Button[ MOUSE_3 ] ) && MiddleClick )
	{
		MiddleClickLast = MiddleClick;
		MiddleClick = false;
	}
	else if( MiddleClick )
	{
		MyCamera->Pos.x += ( int( Mouse.x * Real( cGlobal::HudW ) ) - ScrollMouseX )
			* Real( -MyCamera->Pos.z / cGlobal::HudZoom );
		MyCamera->Pos.y += ( int( -Mouse.y * Real( cGlobal::HudH ) ) - ScrollMouseY )
			* Real( -MyCamera->Pos.z / cGlobal::HudZoom );
		ScrollMouseX = int( Mouse.x * Real( cGlobal::HudW ) );
		ScrollMouseY = int( -Mouse.y * Real( cGlobal::HudH ) );
	
		MyCamera->View.x = MyCamera->Pos.x;
		MyCamera->View.y = MyCamera->Pos.y;

	}
/*	
	// Scroll Mouse Button
	// Pans the screen	
	if( Button[ MOUSE_3 ] && MiddleClick == false )
	{
		MiddleClick = true;
		ScrollMouseX = int( Mouse.x * Real( cGlobal::ScreenW ) );
		ScrollMouseY = int( -Mouse.y * Real( cGlobal::ScreenH ) );
	}
	else if( !( Button[ MOUSE_3 ] ) && MiddleClick )
	{
		MiddleClickLast = MiddleClick;
		MiddleClick = false;
	}
	else if( MiddleClick )
	{
		MyCamera->Pos.x += ( int( Mouse.x * Real( cGlobal::ScreenW ) ) - ScrollMouseX )
			* Real( -MyCamera->Pos.z / cGlobal::HudZoom );
		MyCamera->Pos.y += ( int( -Mouse.y * Real( cGlobal::ScreenH ) ) - ScrollMouseY )
			* Real( -MyCamera->Pos.z / cGlobal::HudZoom );
		ScrollMouseX = int( Mouse.x * Real( cGlobal::ScreenW ) );
		ScrollMouseY = int( -Mouse.y * Real( cGlobal::ScreenH ) );
	
		MyCamera->View.x = MyCamera->Pos.x;
		MyCamera->View.y = MyCamera->Pos.y;
		
//		Log( LOG_HIGHEST_LEVEL, "HUDZOOM " << cGlobal::HudZoom );

	}*/	
	
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::DrawGrid( cCamera* MyCamera, size_t &CurGridDepth, Real GridChange, bool DrawOrig, Real* MyGridDepth )
{
	if ( Button[ KEY_END ].Pressed() )
	{
		AutoGridDepth = !AutoGridDepth;
	}

	int colour = 40;
	
	size_t LastGridDepth = CurGridDepth;
	
	if( AutoGridDepth )
	{
		for( int idx = 1; idx < 13; ++idx )
		{
			if( MyCamera->Pos.z < GridChange )
			{
				CurGridDepth = idx;
				break;
			}	
			GridChange *= Real(2.0);
		}
	}
	else
	{
		if ( Button[ KEY_PGDN ].Pressed() )
		{
			if( CurGridDepth >= 12 )
			{
				CurGridDepth = 1;
			}
			else
			{
				++CurGridDepth;	
			}
				
		}
		else if ( Button[ KEY_PGUP ].Pressed() )
		{
			if( CurGridDepth <= 1 )
			{
				CurGridDepth = 12;
			}
			else
			{
				--CurGridDepth;	
			}
		}
	}
	if( LastGridDepth != CurGridDepth )
	{
		SetGridArray( CurGridDepth, MyGridDepth );
			
	}
	
	glEnable(GL_BLEND);

	Gfx::DrawLines(
		&GridVertex[0],
		&GridIndices[0],
		GridIndicesSize,
		gfx::RGBA( colour, colour, colour, 128 )
	);
	
	colour = 65;
	
	Gfx::DrawLines(
		&GridVertex2[0],
		&GridIndices2[0],
		GridIndicesSize2,
		gfx::RGBA( colour, colour, colour, 128 )
	);
	
	glDisable(GL_BLEND);
	
	if( DrawOrig )
	{	
		DrawOrigin();
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::SetGridArray( size_t CurGridDepth, Real* MyGridDepth )
{
	GridIndicesSize = 0;
	
	for( Real idx = 0; idx < GridSize; idx += MyGridDepth[CurGridDepth] )
	{
		GridVertex[ GridIndicesSize ] =
			ABSet< Vector3D >( 
				Vector3D(
					Real( idx ),
					Real( -GridSize ),
					Real( 0 )
				),
				Vector3D(
					Real( idx ),
					Real( GridSize ),
					Real( 0 )
				)
			);
		GridIndices[GridIndicesSize] = GridIndicesSize;
		GridIndicesSize++;
		
		GridVertex[ GridIndicesSize ] =
			ABSet< Vector3D >( 
				Vector3D(
					Real( -GridSize ),
					Real( idx ),
					Real( 0 )
				),
				Vector3D(
					Real( GridSize ),
					Real( idx ),
					Real( 0 )
				)
			);
		GridIndices[GridIndicesSize] = GridIndicesSize;
		GridIndicesSize++;
		
		GridVertex[ GridIndicesSize ] =
			ABSet< Vector3D >( 
				Vector3D(
					Real( -idx ),
					Real( -GridSize ),
					Real( 0 )
				),
				Vector3D(
					Real( -idx ),
					Real( GridSize ),
					Real( 0 )
				)
			);
		GridIndices[GridIndicesSize] = GridIndicesSize;
		GridIndicesSize++;
		
		GridVertex[ GridIndicesSize ] =
			ABSet< Vector3D >( 
				Vector3D(
					Real( -GridSize ),
					Real( -idx ),
					Real( 0 )
				),
				Vector3D(
					Real( GridSize ),
					Real( -idx ),
					Real( 0 )
				)
			);
		GridIndices[GridIndicesSize] = GridIndicesSize;
		GridIndicesSize++;
	}
	
	size_t VertexSize = GridIndicesSize;
	GridIndicesSize *= 2;
	for( size_t idx = VertexSize; idx < GridIndicesSize; ++idx )
	{
		GridIndices[idx] = idx;
	}

	if( CurGridDepth < 11 )
	{
		GridIndicesSize2 = 0;
	
		for( Real idx = 0; idx < GridSize; idx += MyGridDepth[CurGridDepth + 2] )
		{
			GridVertex2[ GridIndicesSize2 ] =
				ABSet< Vector3D >( 
					Vector3D(
						Real( idx ),
						Real( -GridSize ),
						Real( 0 )
					),
					Vector3D(
						Real( idx ),
						Real( GridSize ),
						Real( 0 )
					)
				);
			GridIndices2[GridIndicesSize2] = GridIndicesSize2;
			GridIndicesSize2++;
			
			GridVertex2[ GridIndicesSize2 ] =
				ABSet< Vector3D >( 
					Vector3D(
						Real( -GridSize ),
						Real( idx ),
						Real( 0 )
					),
					Vector3D(
						Real( GridSize ),
						Real( idx ),
						Real( 0 )
					)
				);
			GridIndices2[GridIndicesSize2] = GridIndicesSize2;
			GridIndicesSize2++;
			
			GridVertex2[ GridIndicesSize2 ] =
				ABSet< Vector3D >( 
					Vector3D(
						Real( -idx ),
						Real( -GridSize ),
						Real( 0 )
					),
					Vector3D(
						Real( -idx ),
						Real( GridSize ),
						Real( 0 )
					)
				);
			GridIndices2[GridIndicesSize2] = GridIndicesSize2;
			GridIndicesSize2++;
			
			GridVertex2[ GridIndicesSize2 ] =
				ABSet< Vector3D >( 
					Vector3D(
						Real( -GridSize ),
						Real( -idx ),
						Real( 0 )
					),
					Vector3D(
						Real( GridSize ),
						Real( -idx ),
						Real( 0 )
					)
				);
			GridIndices2[GridIndicesSize2] = GridIndicesSize2;
			GridIndicesSize2++;
		}
		
		size_t VertexSize2 = GridIndicesSize2;
		GridIndicesSize2 *= 2;
		for( size_t idx = VertexSize2; idx < GridIndicesSize2; ++idx )
		{
			GridIndices2[idx] = idx;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::DrawOrigin()
{
	ABSet< Vector3D > OriginVertex[ 2 ];
	unsigned int OriginIndices[ 4 ];
	
	OriginVertex[ 0 ] =
		ABSet< Vector3D >(
			Vector3D(
				Real( 0 ),
				Real( -GridSize ),
				Real( 0 )
			),
			Vector3D(
				Real( 0 ),
				Real( GridSize ),
				Real( 0 )
			)
		);
	OriginVertex[ 1 ] =
		ABSet< Vector3D >(
			Vector3D(
				Real( -GridSize ),
				Real( 0 ),
				Real( 0 )
			),
			Vector3D(
				Real( GridSize ),
				Real( 0 ),
				Real( 0 )
			)
		);
	for( size_t idx = 0; idx < 4; ++idx )
	{
		OriginIndices[idx] = idx;
	}
	
	Gfx::DrawLines(
		OriginVertex,
		OriginIndices,
		4,
		gfx::RGBA( 255, 255, 255, 128 )
	);

	/*
	gfx::Line(
		Real( 0 ),
		Real( -GridSize ),
		Real( 0 ),
		Real( 0 ),
		Real( GridSize ),
		Real( 0 ),
		gfx::RGBA( 255, 255, 255, 128 )
	);
	gfx::Line(
		Real( -GridSize ),
		Real( 0 ),
		Real( 0 ),
		Real( GridSize ),
		Real( 0 ),
		Real( 0 ),
		gfx::RGBA( 255, 255, 255, 128 )
	);*/
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::Zoom( Real ScaleAmount, cCamera* MyCamera )
{
	if ( Button[ KEY_EQUALS ] )
	{
		MyCamera->Pos.z -= Real( 5 );
	}
	else if ( Button[ KEY_MINUS ] )
	{
		MyCamera->Pos.z += Real( 5 );
	}
	// - -------------------------------------------------------------------------------------- - //
	if( Mouse.Wheel.Diff() > 0 )
	{
		MyCamera->Pos.z -= Real( ScaleAmount );
	}		
	else if( Mouse.Wheel.Diff() < 0 )
	{
		MyCamera->Pos.z += Real( ScaleAmount );
	}
}
// - ------------------------------------------------------------------------------------------ - //
bool cEdit::WithinBox( Vector2D &TestPoint, Vector2D &PointA, Vector2D &PointB )
{
	bool InXBox = false;
	bool InYBox = false;
	
	// Check X //
	if( PointB.x < PointA.x )
	{
		if( TestPoint.x > PointB.x &&
			TestPoint.x < PointA.x )
		{
			InXBox = true;
		}
	}
	else
	{
		if( TestPoint.x < PointB.x &&
			TestPoint.x > PointA.x )
		{
			InXBox = true;
		}
	}
	// Check Y //
	if( PointB.y < PointA.y )
	{
		if( TestPoint.y > PointB.y &&
			TestPoint.y < PointA.y )
		{
			InYBox = true;
		}
	}
	else
	{
		if( TestPoint.y < PointB.y &&
			TestPoint.y > PointA.y )
		{
			InYBox = true;
		}
	}
	if( InXBox && InYBox )
	{
		return true;	
	}
		
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cEdit::CalcSnapToGrid( Vector2D &TempVec2D, size_t CurGridDepth, Real* MyGridDepth )
{
	if( TempVec2D.x > 0 )
	{
		TempVec2D.x = int( ( TempVec2D.x
			+ Real(MyGridDepth[CurGridDepth ] / Real( 2.0 ) ) )
			/ MyGridDepth[CurGridDepth ] ) 
			* Real(MyGridDepth[CurGridDepth ]);
	}
	else
	{
		TempVec2D.x = int( ( TempVec2D.x
			- Real(MyGridDepth[CurGridDepth] / Real( 2.0 ) ) )
			/ MyGridDepth[CurGridDepth ] ) 
			* Real(MyGridDepth[CurGridDepth ]);
	}
	if( TempVec2D.y > 0 )
	{
		TempVec2D.y = int( ( TempVec2D.y
			+ Real(MyGridDepth[CurGridDepth ] / Real( 2.0 ) ) )
			/ MyGridDepth[CurGridDepth ] ) 
			* Real(MyGridDepth[CurGridDepth ]);
	}
	else
	{
		TempVec2D.y = int( ( TempVec2D.y
			- Real(MyGridDepth[CurGridDepth ] / Real( 2.0 ) ) )
			/ MyGridDepth[CurGridDepth ] ) 
			* Real(MyGridDepth[CurGridDepth ]);
	}
	return TempVec2D;
}
// - ------------------------------------------------------------------------------------------ - //
int cEdit::ArraySize( char * array )
{
	int Idx = 0;
	char TempChar = array[Idx];
	while( TempChar != 0 )
	{
		++Idx;
		TempChar = array[Idx];
	}
	return Idx;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //