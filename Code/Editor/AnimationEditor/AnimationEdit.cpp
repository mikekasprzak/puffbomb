#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

#include <Animation/AnimationPool.h>

#include <Graphics/Gfx.h>
#include <Input/Input.h>

// For FPS test //
#include <Platform/Global.h>
#include <Font/Fonts.h>
#include <sstream>
// ------------ //

// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cAnimationEdit::cAnimationEdit() :
	UVWidth( 0.25 ),
	UVHeight( 0.4 ),
	UVScale( 256.0 ),
	UVZoomOffsetX( 144.5 ),
	UVZoomOffsetY( 232 ),
	UVCurGridDepth( 0 ),
	SnapToGrid( false ),
	isGroupMove( false ),
	FrameIdx( 0 ),
	NodeRadius( 6.0 ),
	OldMousePos( Real(0.0), Real(0.0) ),
	CurMousePos( Real(0.0), Real(0.0) )
{
	// Create Cameras //
	UVCamera = new cCamera(
		Vector3D( 128.0, 128.0, 400.0 ),				// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Platform::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		cGlobal::HudZoom,								// MinZoom
		cGlobal::HudZoom,								// MaxZoom
		cGlobal::HudZoom								// HudZoom
	);
	
	Real PreviewHeight = UVHeight;

	if( Platform::AspectRatio < Real( 0.79 ) )
	{
	//	Real( 1.66 )
		PreviewHeight = 0.75;
	}
	
	PreviewCamera = new cCamera(
		Vector3D( 0.0, 0.0, cGlobal::HudZoom * ( Real( 1 ) - PreviewHeight ) ),		// Pos
		Vector3D( 0.0, 0.0, 0.0 ),					// View
		Vector3D( 0.0, 1.0, 0.0 ),					// Up
		45.0,										// Field of View
		Platform::AspectRatio,						// Aspect Ratio
		1.0,										// NearClip
		100000.0,									// FarClip
		cGlobal::HudZoom,							// MinZoom
		cGlobal::HudZoom,							// MaxZoom
		cGlobal::HudZoom							// HudZoom
	);
	
	Camera->Pos.z = Real( 800.0 );
//	Camera->Pos.z = Real( cGlobal::HudZoom );
		
	Animations.push_back( &AnimationPool.Load( "TestAnimation.anim" ) );
	
	Animator.Set( Animations[0], 0 );
	
	CurFrame = &Animator.Animation->Frame[ FrameIdx ].GetFrame();

	TexVertex.a = Vector3D( 0.0, 0.0, 0.0 );
	TexVertex.b = Vector3D( UVScale, 0.0, 0.0 );
	TexVertex.c = Vector3D( UVScale, UVScale, 0.0 );
	TexVertex.d = Vector3D( 0.0, UVScale, 0.0 );
	TexUV.b = Vector2D( 1.0, 1.0 );
	TexUV.a = Vector2D( 0.0, 1.0 );
	TexUV.c = Vector2D( 1.0, 0.0 );
	TexUV.d = Vector2D( 0.0, 0.0 );
	TexIndices[0] = 0;
	TexIndices[1] = 1;
	TexIndices[2] = 2;
	TexIndices[3] = 3;

	GridSize = 2048.0;

	CalcUVZoomOffset();
	
	CurMode = NODE_MODE;

}
// - ------------------------------------------------------------------------------------------ - //
cAnimationEdit::~cAnimationEdit()
{
	delete UVCamera;
	delete PreviewCamera;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::Draw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	DrawFrame();
	
	DrawSelected();

	Gfx::DisableBlend();
	Gfx::DisableTex2D();
	
	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::HudDraw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
	DisplayText();
	
//	//  DISPLAYS FPS  //
//	std::stringstream Temp;
//	Temp << Platform::FPS;
//	std::string TempString = Temp.str();
//	
//	Vector3D TempPos = Vector3D( cGlobal::Left, cGlobal::Top - Real( 45 ), 0.0 );
//
//	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 184, 0, 0, 255 ) );
//	// -------------- //
	Gfx::DisableBlend();
	Gfx::DisableTex2D();
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::PreviewDraw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
	Gfx::ResetColor();
	
//	Animator.DrawQuad( Vector2D( 0, 0 ) );
	Animator.Draw( Vector2D( 0, 0 ) );
		
	Gfx::DisableBlend();
	Gfx::DisableTex2D();
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::UVDraw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
	Gfx::DrawQuads(
		&TexVertex,
		&TexUV,
		TexIndices,
		4,
		CurFrame->TextureID,
		Gfx::White()
	);
	
	Gfx::DisableBlend();
	Gfx::DisableTex2D();
	
	DrawGrid( UVCamera, CurrentGridDepth, 40.0, true, GridDepth );

}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::Step()
{
	if( CheckViewOne() )
	{
		CurView = 1;
		CurMousePos = CalcMousePos();

		// Handles scrolling around the map
		Scroll( Camera );

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), Camera );
		
		if( CurMode == NODE_MODE )
		{
			if( !isGroupMove )
			{
				SelectNode();
			
				AddNode();
			}
			MoveNode();
		}
		else if( CurMode == FACE_MODE )
		{	
			SelectNode();
			
			AddFace();
		}
		else if( CurMode == TEXTURE_MODE )
		{	
			SelectFace();
		}
	}
	else if( CheckViewTwo( UVHeight ) )
	{
		CurView = 2;
		CurMousePos = CalcMousePos();

		// Handles scrolling around the map
		//Scroll( PreviewCamera );
		
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			Scroll( PreviewCamera, Real( 0.325 ), Real( 0.25 ), Vector2D( UVZoomOffsetX, UVZoomOffsetY ) );
		}
		else
		{
			Scroll(
				PreviewCamera,
				Real( UVWidth * Real( Real( 1 ) + UVWidth ) / Real( 2 ) ),
				Real( UVHeight * Real( Real( 1 ) + UVHeight ) / Real( 2 ) ),
				Vector2D( UVZoomOffsetX, UVZoomOffsetY )
			);
		}
		// Handles the zooming in and out of the preview
		Zoom( Real( 32.0 ), PreviewCamera );
	}
	else if( CheckViewThree( UVHeight ) )
	{
		CurView = 3;
		CurMousePos = CalcUVMousePos();

		// Handles scrolling around the map
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			Scroll( UVCamera, Real( 0.33 ), Real( 0.25 ), Vector2D( UVZoomOffsetX, UVZoomOffsetY ) );
		}
		else
		{
			Scroll( UVCamera, UVWidth, UVHeight, Vector2D( UVZoomOffsetX, UVZoomOffsetY ) );
		}

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), UVCamera );
	}
	Animator.Step();
	
	Undo();

	SwitchMode();

	SwitchFrame();
	
	LastView = CurView;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::Undo()
{
	// Resets the zoom
	if ( Button[ KEY_TAB ].Pressed() )
	{
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Real( 800.0 );
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;

		UVCamera->Pos.x = 128.0;
		UVCamera->Pos.y = 128.0;
		UVCamera->Pos.z = 400.0;
		
		UVCamera->View.x = UVCamera->Pos.x;
		UVCamera->View.y = UVCamera->Pos.y;
		UVCamera->View.z = 0.0;

		PreviewCamera->Pos.x = 0.0;
		PreviewCamera->Pos.y = 0.0;
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			PreviewCamera->Pos.z = cGlobal::HudZoom * ( Real( 1 ) - Real( 0.25 ) );
		}
		else
		{
			PreviewCamera->Pos.z = cGlobal::HudZoom * ( Real( 1 ) - UVHeight );
		}	
		
		PreviewCamera->View.x = PreviewCamera->Pos.x;
		PreviewCamera->View.y = PreviewCamera->Pos.y;
		PreviewCamera->View.z = 0.0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::ActiveAction()
{

}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::CalcUVZoomOffset()
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
Vector2D cAnimationEdit::CalcMousePos()
{
	Vector2D tempMousPos;
	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		tempMousPos = Vector2D(
				Real( ( int( Mouse.x * Real( cGlobal::HudW ) ) )
				- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				- ( ( Real(cGlobal::HudW) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom ),
				Real( ( int( -Mouse.y * Real( cGlobal::HudH ) ) )
				+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				+ ( ( Real(cGlobal::HudH) * Real( 0.25 ) ) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom )
		);
	}
	else
	{
		tempMousPos = Vector2D(
				Real( ( int( Mouse.x * Real( cGlobal::HudW ) ) )
				- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				- ( ( Real(cGlobal::HudW) * Real( 0.75 ) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom ),
				Real( ( int( -Mouse.y * Real( cGlobal::HudH ) ) )
				+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom  ) )
				+ ( cGlobal::HudH >> 1 ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom )
		);
	}
	
	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cAnimationEdit::CalcUVMousePos()
{
	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		return Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW * Real( 0.33 ) ) ) )
			- ( -UVCamera->Pos.x / Real( UVCamera->Pos.z / UVZoomOffsetX ) )
			- ( ( Real(cGlobal::HudW) * Real( 0.33 ) ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetX ) / UVScale + Real( 1 )
			+ ( ( UVCamera->Pos.z - Real( 612 ) ) / Real( 612 ) ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) * Real( 0.25 ) )
			+ ( UVCamera->Pos.y / Real( UVCamera->Pos.z / UVZoomOffsetY ) )
			+ ( ( cGlobal::HudH * Real( 0.25 ) ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetY ) ) / UVScale - Real( 1 )
			- ( ( UVCamera->Pos.z - Real( 612 ) ) / Real( 612 ) )
		);
	}
	else
	{
		return Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW * UVWidth ) ) )
			- ( -UVCamera->Pos.x / Real( UVCamera->Pos.z / UVZoomOffsetX ) )
			- ( ( Real(cGlobal::HudW) * UVWidth ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetX ) / UVScale + Real( 1 )
			+ ( ( UVCamera->Pos.z - Real( 612 ) ) / Real( 612 ) ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) * UVHeight )
			+ ( UVCamera->Pos.y / Real( UVCamera->Pos.z / UVZoomOffsetY ) )
			+ ( ( cGlobal::HudH * UVHeight ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetY ) ) / UVScale - Real( 1 )
			- ( ( UVCamera->Pos.z - Real( 612 ) ) / Real( 612 ) )
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DrawFrame()
{
	glLineWidth( 1.0 );
		
	ABCSet< Vector3D > PolyVertex[ CurFrame->Face.size() ];
	ABCSet< Vector2D > PolyTexCoord[ CurFrame->Face.size() ];
	unsigned int PolyIndicesSize = CurFrame->Face.size() * 3;
	unsigned int PolyIndices[ PolyIndicesSize ];

	ABSet< Vector3D > LineVertex[ CurFrame->Face.size() * 3 ];
	unsigned int LineIndicesSize = CurFrame->Face.size() * 6;
	unsigned int LineIndices[ LineIndicesSize ];

	for( size_t idx = 0; idx < CurFrame->Face.size(); ++idx )
	{
		PolyVertex[ idx ].a = CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.a ].Pos.ToVector3D();
		PolyVertex[ idx ].b = CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.b ].Pos.ToVector3D();
		PolyVertex[ idx ].c = CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.c ].Pos.ToVector3D();
		
		LineVertex[ idx ].a = PolyVertex[ idx ].a;
		LineVertex[ idx ].b = PolyVertex[ idx ].b;

		LineVertex[ idx + CurFrame->Face.size() ].a = PolyVertex[ idx ].b;
		LineVertex[ idx + CurFrame->Face.size() ].b = PolyVertex[ idx ].c;

		LineVertex[ idx + ( CurFrame->Face.size() * 2 ) ].a = PolyVertex[ idx ].a;
		LineVertex[ idx + ( CurFrame->Face.size() * 2 ) ].b = PolyVertex[ idx ].c;

		PolyTexCoord[ idx ].a = CurFrame->Face[ idx ].UV.a;
		PolyTexCoord[ idx ].b = CurFrame->Face[ idx ].UV.b;
		PolyTexCoord[ idx ].c = CurFrame->Face[ idx ].UV.c;
		
		PolyIndices[ idx ] = idx;
		LineIndices[ idx ] = idx;
	}
	
	for( size_t idx = CurFrame->Face.size(); idx < PolyIndicesSize; ++idx )
	{
		PolyIndices[ idx ] = idx;
	}
	for( size_t idx = CurFrame->Face.size(); idx < LineIndicesSize; ++idx )
	{
		LineIndices[ idx ] = idx;
	}
	// Draw textured faces //
	Gfx::DrawPolygons( PolyVertex, PolyTexCoord, PolyIndices, PolyIndicesSize, CurFrame->TextureID, Gfx::White() );

	Gfx::DisableTex2D();
	// Draw lines showing faces //
	Gfx::DrawLines( LineVertex, LineIndices, LineIndicesSize, Gfx::RGBA( 0, 200, 0, 255 ) );
	
	// Draw circles representing vertex's //
	for( size_t idx = 0; idx < CurFrame->Vertex.size(); ++idx )
	{
		Gfx::Circle( CurFrame->Vertex[ idx ].Pos, NodeRadius, Gfx::White() );
	}
	
	Gfx::EnableTex2D();
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DrawSelected()
{
	Gfx::DisableTex2D();
 
 	if( !isGroupMove )
	{
		DrawSelBox();
	}
		
	if( CurSelected.size() > 0 )
	{
		glLineWidth( 4.0 );
	
		if( CurMode == NODE_MODE || CurMode == FACE_MODE )
		{
			// Draw circles representing vertex's //
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				Gfx::Circle( CurFrame->Vertex[ CurSelected[ idx ] ].Pos, NodeRadius, Gfx::RGBA( 0, 150, 255, 255 ) );
			}
		}
		else if( CurMode == TEXTURE_MODE )
		{
			ABSet< Vector3D > LineVertex[ CurSelected.size() * 3 ];
			unsigned int LineIndicesSize = CurSelected.size() * 6;
			unsigned int LineIndices[ LineIndicesSize ];
			
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				LineVertex[ idx ].a = CurFrame->Vertex[ CurFrame->Face[ CurSelected[ idx ] ].VertexIdx.a ].Pos.ToVector3D();
				LineVertex[ idx ].b = CurFrame->Vertex[ CurFrame->Face[ CurSelected[ idx ] ].VertexIdx.b ].Pos.ToVector3D();
		
				LineVertex[ idx + CurSelected.size() ].a = LineVertex[ idx ].b;
				LineVertex[ idx + CurSelected.size() ].b = CurFrame->Vertex[ CurFrame->Face[ CurSelected[ idx ] ].VertexIdx.c ].Pos.ToVector3D();
		
				LineVertex[ idx + ( CurSelected.size() * 2 ) ].a = LineVertex[ idx ].a;
				LineVertex[ idx + ( CurSelected.size() * 2 ) ].b = LineVertex[ idx + CurSelected.size() ].b;
	
				LineIndices[ idx ] = idx;
			}
			for( size_t idx = CurSelected.size(); idx < LineIndicesSize; ++idx )
			{
				LineIndices[ idx ] = idx;
			}
			
			// Draw lines showing faces //
			Gfx::DrawLines( LineVertex, LineIndices, LineIndicesSize, Gfx::RGBA( 255, 0, 0, 255 ) );
		}
	}
	Gfx::EnableTex2D();
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DrawSelBox()
{
	if( Button[ MOUSE_1 ] )
	{	
		glLineWidth( 1.0 );
		
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
void cAnimationEdit::SwitchMode()
{	
	unsigned int LastMode = CurMode;
	
	if ( Button[ KEY_1 ].Pressed() )
	{
		CurMode = NODE_MODE;
	}
	else if ( Button[ KEY_2 ].Pressed() )
	{
		CurMode = FACE_MODE;
	}
	else if ( Button[ KEY_3 ].Pressed() )
	{
		CurMode = TEXTURE_MODE;
	}
	
	if( LastMode != CurMode )
	{
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::SwitchFrame()
{	
	if ( Button[ KEY_LEFT ].Pressed() )
	{
		if( FrameIdx > 0 )
		{
			--FrameIdx;
		}
		else
		{
			FrameIdx = Animator.Animation->Frame.size() - 1;
		}
		CurFrame = &Animator.Animation->Frame[ FrameIdx ].GetFrame();
		CurSelected.clear();
	}
	if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( FrameIdx < Animator.Animation->Frame.size() - 1 )
		{
			++FrameIdx;
		}
		else
		{
			FrameIdx = 0;
		}
		CurFrame = &Animator.Animation->Frame[ FrameIdx ].GetFrame();
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
