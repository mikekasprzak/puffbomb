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
	
	Real PreviewHeight = UVHeight;

	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		PreviewHeight = 0.75;
		
		UVWidth = 0.33;
		UVHeight = 0.25;
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

	GridSize = 2048.0;
}
// - ------------------------------------------------------------------------------------------ - //
cComponentEdit::~cComponentEdit()
{
	delete UVCamera;
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
void cComponentEdit::UVDraw()
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
	else if( CheckViewTwo( UVHeight ) )
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
