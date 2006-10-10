#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Edit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/String.h>
#include <Util/DirectoryCache.h>
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
const fl cEdit::flDelete			= bit4;
const fl cEdit::flMove				= bit5;
const fl cEdit::flScale	 			= bit6;
const fl cEdit::flHelp	 			= bit7;
const fl cEdit::flMiddleClick	 	= bit8;
const fl cEdit::flAutoGridDepth		= bit9;
const fl cEdit::flSnapToGrid		= bit10;
const fl cEdit::flisGroupMove		= bit11;
const fl cEdit::flGlobalIncrease 	= bit12;
const fl cEdit::flGlobalDecrease 	= bit13;
// - ------------------------------------------------------------------------------------------ - //
cEdit::cEdit() :
	EditEventFlags( 0 ),
	IsHelp( false ),
//	MiddleClick( false ),
//	MiddleClickLast( false ),
//	AutoGridDepth( true ),
	ScrollMouseX( 0 ),
	ScrollMouseY( 0 ),
	ScrollFrame( 10 ),
	CurView( 1 ),
	LastView( 1 ),
	ScrollSpeed( 3.0 ),
	GridSize( 16384.0 ),
	CurrentGridDepth( 0 ),
	UVWidth( 0.25 ),
	UVHeight( 0.4 ),
	UVScale( 256.0 ),
	UVZoomOffsetX( 144.5 ),
	UVZoomOffsetY( 232 ),
	SnapToGrid( false ),
	isGroupMove( false ),
	OldMousePos( Real(0.0), Real(0.0) ),
	CurMousePos( Real(0.0), Real(0.0) )
{
	EditEventFlags |= flAutoGridDepth;
	
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
		cGlobal::HudZoom,
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Platform::ScreenW ),						// Width
		Real( Platform::ScreenH )						// Height
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
		cGlobal::HudZoom,
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Platform::ScreenW ),						// Width
		Real( Platform::ScreenH )						// Height
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
	CurrentDir = "../../../../Content/PuffBOMB/";
	
	
	GridVertex.resize( GridSize * Real( 4 ) * Real( 2 ) );
	GridIndices.resize( GridSize * Real( 8 ) * Real( 2 ) );
	GridIndicesSize = 0;
	
	GridVertex2.resize( GridSize * Real( 2 ) );
	GridIndices2.resize( GridSize * Real( 2 ) * Real( 2 ) );
	GridIndicesSize2 = 0;
	
	LastCamera = Camera;
	
	LoadTextures();
	
	TexVertex[0] = Vector3D( 0.0, 0.0, 0.0 );
	TexVertex[1] = Vector3D( UVScale, 0.0, 0.0 );
	TexVertex[2] = Vector3D( UVScale, UVScale, 0.0 );
	TexVertex[3] = Vector3D( 0.0, UVScale, 0.0 );
	TexUV[1] = Vector2D( 1.0, 1.0 );
	TexUV[0] = Vector2D( 0.0, 1.0 );
	TexUV[2] = Vector2D( 1.0, 0.0 );
	TexUV[3] = Vector2D( 0.0, 0.0 );
	TexIndices[0] = 0;
	TexIndices[1] = 1;
	TexIndices[2] = 2;
	TexIndices[3] = 3;

	CalcUVZoomOffset();
	
}

cEdit::~cEdit()
{
	delete Camera;
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::Scroll( cCamera* MyCamera )
{
	Scroll( MyCamera, Real( 1.0 ), Real( 1.0 ), Vector2D( cGlobal::HudZoom, cGlobal::HudZoom ) );
}
void cEdit::Scroll( cCamera* MyCamera, const Real PercentW, const Real PercentH, const Vector2D ZoomInfo )
{
	// Pans the screen	
	if( ( Button[ MOUSE_3 ] ) && ( !( EditEventFlags & flMiddleClick ) ) || ( LastView != CurView ) )
	{
		EditEventFlags |= flMiddleClick;
		//MiddleClick = true;
		ScrollMouseX = int( Mouse.x * Real( cGlobal::HudW ) * PercentW );
		ScrollMouseY = int( -Mouse.y * Real( cGlobal::HudH ) * PercentH );
	}
	else if( ( !( Button[ MOUSE_3 ] ) ) && ( EditEventFlags & flMiddleClick ) )
	{
		EditEventFlags &= ~flMiddleClick;
		//MiddleClick = false;
	}
	else if( EditEventFlags & flMiddleClick )
	{
		MyCamera->Pos.x += ( int( Mouse.x * Real( cGlobal::HudW ) * PercentW ) - ScrollMouseX )
			* Real( -MyCamera->Pos.z / ZoomInfo.x );
		MyCamera->Pos.y += ( int( -Mouse.y * Real( cGlobal::HudH ) * PercentH ) - ScrollMouseY )
			* Real( -MyCamera->Pos.z / ZoomInfo.y );
		ScrollMouseX = int( Mouse.x * Real( cGlobal::HudW ) * PercentW );
		ScrollMouseY = int( -Mouse.y * Real( cGlobal::HudH ) * PercentH );
	
		MyCamera->View.x = MyCamera->Pos.x;
		MyCamera->View.y = MyCamera->Pos.y;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::DrawGrid( cCamera* MyCamera, size_t &CurGridDepth, Real GridChange, bool DrawOrig, Real* MyGridDepth )
{
	Gfx::SetLineWidth( 1.0 );
	
	if( Button[ KEY_END ].Pressed() )
	{
		EditEventFlags &= ~flAutoGridDepth;
	}
	else if( Button[ KEY_HOME ].Pressed() )
	{
		EditEventFlags |= flAutoGridDepth;
	}

	int colour = 40;
	
	size_t LastGridDepth = CurGridDepth;
	
	SetGridDepth( MyCamera, CurGridDepth, GridChange );

	if( LastGridDepth != CurGridDepth )
	{
		SetGridArray( CurGridDepth, MyGridDepth );
	}
	
	Gfx::DrawLines(
		&GridVertex[0],
		&GridIndices[0],
		GridIndicesSize,
		Gfx::RGBA( colour, colour, colour, 128 )
	);
	
	colour = 65;
	
	Gfx::DrawLines(
		&GridVertex2[0],
		&GridIndices2[0],
		GridIndicesSize2,
		Gfx::RGBA( colour, colour, colour, 128 )
	);
		
	if( DrawOrig )
	{	
		DrawOrigin();
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::SetGridDepth( cCamera* MyCamera, size_t &CurGridDepth, Real GridChange )
{
//	if( AutoGridDepth )
	if( ( EditEventFlags & flAutoGridDepth ) )
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
		Gfx::RGBA( 192, 192, 192, 128 )
	);
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
bool cEdit::CheckViewOne()
{
 	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		if( Mouse.y * Real( cGlobal::HudH ) < Real(cGlobal::HudH * 0.75) )
		{
			return true;	
		}
	}
	else
	{
		if( Mouse.x * Real( cGlobal::HudW ) < Real(cGlobal::HudW * 0.75) )
		{
			return true;	
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool cEdit::CheckViewTwo( const Real ViewHeight )
{
 	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		if( Mouse.y * Real( cGlobal::HudH ) > Real(cGlobal::HudH * 0.75) )
		{
			if( Mouse.x * Real( cGlobal::HudW ) > Real(cGlobal::HudW * ( 0.33 ) ) )
			{
				return true;
			}
		}	
	}
	else
	{
		if( Mouse.x * Real( cGlobal::HudW ) > Real(cGlobal::HudW * 0.75) )
		{
			if( Mouse.y * Real( cGlobal::HudH ) < Real(cGlobal::HudH * ( 1 - ViewHeight ) ) )
			{
				return true;
			}
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool cEdit::CheckViewThree( const Real ViewHeight )
{
 	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		if( Mouse.y * Real( cGlobal::HudH ) > Real(cGlobal::HudH * 0.75) )
		{
			if( Mouse.x * Real( cGlobal::HudW ) < Real(cGlobal::HudW * ( 0.33 ) ) )
			{
				return true;
			}
		}	
	}
	else
	{
		if( Mouse.x * Real( cGlobal::HudW ) > Real(cGlobal::HudW * 0.75) )
		{
			if( Mouse.y * Real( cGlobal::HudH ) > Real(cGlobal::HudH * ( 1 - ViewHeight ) ) )
			{
				return true;
			}
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::LoadTextures()
{
	Log( LOG_HIGHEST_LEVEL, "LoadTextures" );
	std::string DirPrefix = "Textures/";

	cDirectoryCache cDirCache( DirPrefix );
	
	for( size_t idx = 0; idx < cDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( cDirCache.File[idx] ) == ".tx" )
		{
			std::string NoDir = String::BaseName( cDirCache.File[idx] ) + String::LastExtension( cDirCache.File[idx] );
			
			TextureID.push_back( TexturePool.Load( NoDir ) );
			
			std::string NoPack = String::BaseName( NoDir ) + String::LastExtension( NoDir );
			
			TextureName.push_back( NoPack );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
int cEdit::FindTexture( const unsigned int& TempTextureID )
{
	for( size_t idx = 0; idx < TextureID.size(); ++idx )
	{
		if( TempTextureID == TextureID[ idx ] )
		{
			return idx;
			break;	
		}
	}
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::DrawSelBox()
{
	if( Button[ MOUSE_1 ] )
	{	
		Gfx::SetLineWidth( 1.0 );
		
			SelBoxVertex[ 0 ] = Vector3D( CurMousePos.x, CurMousePos.y, Real::Zero );
			SelBoxVertex[ 1 ] = Vector3D( CurMousePos.x, OldMousePos.y, Real::Zero );
			SelBoxVertex[ 2 ] = Vector3D( OldMousePos.x, OldMousePos.y, Real::Zero );
			SelBoxVertex[ 3 ] = Vector3D( OldMousePos.x, CurMousePos.y, Real::Zero );
				
		for( size_t idx = 0; idx < 4; ++idx )
		{
			SelBoxIndices[ idx ] = idx;
		}
		SelBoxIndices[ 4 ] = 0;
	
		Gfx::DrawLineStrip( SelBoxVertex, SelBoxIndices, 5, Gfx::White() );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cEdit::CalcUVZoomOffset()
{
	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		UVZoomOffsetX = Real( 138.0 );
		UVZoomOffsetY = Real( 105.5 );
	}
	else
	{
		UVZoomOffsetX = ( Real( cGlobal::HudW ) * UVZoomOffsetX ) / Real( 1920.0 );
		UVZoomOffsetY = ( Real( cGlobal::HudH ) * UVZoomOffsetY ) / Real( 1200.0 );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
