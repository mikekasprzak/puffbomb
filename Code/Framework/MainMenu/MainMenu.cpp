// - ------------------------------------------------------------------------------------------ - //
#include "MainMenu.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
cMainMenu::cMainMenu()
{
	// Create Camera //
	Camera = new cCamera(
		Vector3D( 0.0, 0.0, Global::HudZoom ),			// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Global::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		Global::HudZoom,								// MinZoom
		Global::HudZoom,								// MaxZoom
		Global::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Global::ScreenW ),						// Width
		Real( Global::ScreenH )						// Height
	 );
	
	Form.Load( "2D/Menu/MainMenu.form" );

	Work();
}
// - ------------------------------------------------------------------------------------------ - //
cMainMenu::~cMainMenu()
{
	delete Camera;
}
// - ------------------------------------------------------------------------------------------ - //
void cMainMenu::ResetMenu()
{
	//Form.DialogBox[ 0 ].SuperFlowState = 1;
	//Work();
}
// - ------------------------------------------------------------------------------------------ - //
void cMainMenu::Draw()
{
	Camera->Update();

	Gfx::DisableDepth();
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	Form.Draw();	
	
	Gfx::EnableDepth();
	Gfx::DisableTex2D();
	Gfx::DisableBlend();	
}
// - ------------------------------------------------------------------------------------------ - //
void cMainMenu::Step()
{
	Form.Step();
	
	if( Form.DialogBox[ 0 ].SuperFlowState != 1 )
	{
		BreakLoop = true;	
	}
}
// - ------------------------------------------------------------------------------------------ - //
