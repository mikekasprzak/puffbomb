#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

#include <Animation/AnimationPool.h>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cAnimationEdit::cAnimationEdit() :
	UVWidth( 0.25 ),
	UVHeight( 0.4 )
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
		Vector3D( 0.0, 0.0, cGlobal::HudZoom ),			// Pos
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
	
	Animations.push_back( &AnimationPool.Load( "TestAnimation.anim" ) );
	
	Animator.Set( Animations[0], 0 );
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
	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::HudDraw()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::PreviewDraw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	Animator.DrawQuad( Vector2D( 0, 0 ) );
		
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::UVDraw()
{
	DrawGrid( UVCamera, CurrentGridDepth, 32.0, true, GridDepth );
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::Step()
{
	if( CheckViewOne() )
	{
		// Handles scrolling around the map
		Scroll( Camera );

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), Camera );
	}
	else if( CheckViewTwo( UVHeight ) )
	{
		// Handles scrolling around the map
		Scroll( PreviewCamera );

		// Handles the zooming in and out of the preview
		Zoom( Real( 32.0 ), PreviewCamera );
	}
	else if( CheckViewThree( UVHeight ) )
	{
		// Handles scrolling around the map
		Scroll( Camera );

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), Camera );
	}
	Animator.Step();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
