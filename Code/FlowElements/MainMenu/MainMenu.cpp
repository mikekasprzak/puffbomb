// - ------------------------------------------------------------------------------------------ - //
#include "MainMenu.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Platform/Global.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
cMainMenu::cMainMenu()
{
	// Create Camera //
	Camera = new cCamera(
		Vector3D( 0.0, 0.0, cGlobal::HudZoom ),			// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Platform::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		cGlobal::HudZoom,								// MinZoom
		cGlobal::HudZoom,								// MaxZoom
		cGlobal::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Platform::ScreenW ),						// Width
		Real( Platform::ScreenH )						// Height
	 );
	
	Form.Load( "2D/Menu/MainMenu.form" );
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	Work();
	
	Gfx::DisableTex2D();
	Gfx::DisableBlend();
}
// - ------------------------------------------------------------------------------------------ - //
cMainMenu::~cMainMenu()
{
	delete Camera;
}
// - ------------------------------------------------------------------------------------------ - //
void cMainMenu::Draw()
{
	Camera->Update();

	Form.Draw();	
}
// - ------------------------------------------------------------------------------------------ - //
void cMainMenu::Step()
{
	Form.Step();
}
// - ------------------------------------------------------------------------------------------ - //
