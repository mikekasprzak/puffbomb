#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cComponentEdit::cComponentEdit() :
	PreviewWidth( 0.25 ),
	PreviewHeight( 0.4 )
{
	// Create Preview Camera
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
cComponentEdit::~cComponentEdit()
{
	delete PreviewCamera;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Draw()
{
	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::HudDraw()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::PreviewDraw()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Step()
{
	if( CheckViewOne() )
	{
		// Handles scrolling around the map
		Scroll( Camera );

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), Camera );
	}
	else if( CheckViewTwo( PreviewHeight ) )
	{
		// Handles scrolling around the map
		Scroll( PreviewCamera );

		// Handles the zooming in and out of the preview
		Zoom( Real( 32.0 ), PreviewCamera );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
