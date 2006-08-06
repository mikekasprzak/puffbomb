#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

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
		Vector3D( 128.0, 128.0, 400.0 ),
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

	PreviewCamera = new cCamera(
		Vector3D( 0.0, 0.0, 500.0 ),
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
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
