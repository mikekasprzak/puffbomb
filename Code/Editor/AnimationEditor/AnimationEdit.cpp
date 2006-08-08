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
	CurFrame( 0 )
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

	PreviewCamera = new cCamera(
		Vector3D( 0.0, 240.0, cGlobal::HudZoom ),		// Pos
		Vector3D( 0.0, 240.0, 0.0 ),					// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Platform::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		cGlobal::HudZoom,								// MinZoom
		cGlobal::HudZoom,								// MaxZoom
		cGlobal::HudZoom								// HudZoom
	);
	
	Camera->Pos.z = Real( 800.0 );
	
	Animations.push_back( &AnimationPool.Load( "TestAnimation.anim" ) );
	
	Animator.Set( Animations[0], 0 );

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
	Gfx::Circle( Vector3D( Real( 0.0 ), Real( 0.0 ), Real( 0.0 ) ), Real( 20.0 ), Gfx::White() );
	
	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::HudDraw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
//	//  DISPLAYS FPS  //
//	std::stringstream Temp;
//	Temp << Platform::FPS;
//	std::string TempString = Temp.str();
//	
//	Vector3D TempPos = Vector3D( cGlobal::Left, cGlobal::Top - Real( 45 ), 0.0 );
//
//	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), gfx::RGBA( 184, 0, 0, 255 ) );
//	// -------------- //
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::PreviewDraw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	Gfx::ResetColor();
	
//	Animator.DrawQuad( Vector2D( 0, 0 ) );
	Animator.Draw( Vector2D( 0, 0 ) );
		
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::UVDraw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	Gfx::DrawQuads(
		&TexVertex,
		&TexUV,
		TexIndices,
		4,
		Animator.Animation->Frame[ CurFrame ].GetFrame().TextureID,
		Gfx::White()
	);
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	
	DrawGrid( UVCamera, CurrentGridDepth, 40.0, true, GridDepth );

}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::Step()
{
	if( CheckViewOne() )
	{
		CurView = 1;
		// Handles scrolling around the map
		Scroll( Camera );

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), Camera );
	}
	else if( CheckViewTwo( UVHeight ) )
	{
		CurView = 2;
		// Handles scrolling around the map
		Scroll( PreviewCamera );

		// Handles the zooming in and out of the preview
		Zoom( Real( 32.0 ), PreviewCamera );
	}
	else if( CheckViewThree( UVHeight ) )
	{
		CurView = 3;
		// Handles scrolling around the map
		ScrollUV();

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), UVCamera );
	}
	Animator.Step();
	
	Undo();
	
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
		PreviewCamera->Pos.y = 240.0;
		PreviewCamera->Pos.z = cGlobal::HudZoom;
		
		PreviewCamera->View.x = PreviewCamera->Pos.x;
		PreviewCamera->View.y = PreviewCamera->Pos.y;
		PreviewCamera->View.z = 0.0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::ScrollUV()
{
	// Scroll Mouse Button
	// Pans the Hud	
	if( Button[ MOUSE_3 ] && MiddleClick == false || LastView != CurView )
	{
		//UVMiddleClick = true;
		MiddleClick = true;
		ScrollMouseX = int( Mouse.x * ( Real( cGlobal::HudW ) * UVWidth ) );
		ScrollMouseY = int( -Mouse.y * ( Real( cGlobal::HudH ) * UVHeight ) );
			
	}
	else if( !( Button[ MOUSE_3 ] ) && MiddleClick )
	{
		MiddleClickLast = MiddleClick;
		MiddleClick = false;
	}
	if( MiddleClick )
	{
		UVCamera->Pos.x += ( int( Mouse.x * ( Real( cGlobal::HudW ) * ( UVWidth ) ) ) - ScrollMouseX )
			* Real( -UVCamera->Pos.z / UVZoomOffsetX );
		UVCamera->Pos.y += ( int( -Mouse.y * ( Real( cGlobal::HudH ) ) * UVHeight ) - ScrollMouseY )
			* Real( -UVCamera->Pos.z / UVZoomOffsetY );
		ScrollMouseX = int( Mouse.x * ( Real( cGlobal::HudW ) * UVWidth ) );
		ScrollMouseY = int( -Mouse.y * ( Real( cGlobal::HudH ) * UVHeight ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cAnimationEdit::CalcUVMousePos()
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
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::CalcUVZoomOffset()
{
	UVZoomOffsetX = ( Real( cGlobal::HudW ) * UVZoomOffsetX ) / Real( 1920.0 );
	UVZoomOffsetY = ( Real( cGlobal::HudH ) * UVZoomOffsetY ) / Real( 1200.0 );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
