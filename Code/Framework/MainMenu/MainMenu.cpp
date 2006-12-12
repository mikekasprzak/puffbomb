// - ------------------------------------------------------------------------------------------ - //
#include "MainMenu.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
// DELETE THIS WHEN YOU GET SICK OF THE RANDOM PARTICLE SHIT //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>

#include <stdlib.h>
#include <time.h>
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
#ifdef EDITOR
// For FPS test //
#include <Font/Fonts.h>
#include <sstream>
// ------------ //
#endif // EDITOR //
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
		1000.0,											// NearClip
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
	
	LastTime = GetTime();
	
	//srand ( time(NULL) );
	
	Gfx::DisableSmoothPolygon();
	
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

	Gfx::EnableTex2D();
	Gfx::EnableBlend();
		
	DenseParticle.Draw();
//	SolidParticle.Draw();

	Gfx::StandardBlend();

	Form.Draw();
	
#ifdef EDITOR
	//	//  DISPLAYS FPS  //
	std::stringstream Temp;
	Temp << Global::FPS;
	std::string TempString = Temp.str();
	
	Vector3D TempPos = Vector3D( Global::Left, Global::Top - Real( 45 ), 0.0 );

	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 0, 200, 0, 255 ) );
	// -------------- //
#endif // EDITOR //
	
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
	
	
/*	if( LastTime < GetTime() )
	{
		for( size_t idx = 0; idx < 200; ++idx )
		{
			int XPos = rand() % int( Global::HudW ) - int( Global::Right );
			int YPos = rand() % int( Global::HudH ) - int( Global::Top );
			
			FXLibrary::CrazyTest( Vector2D( XPos, YPos ) );
			
		}
		LastTime = GetTime() + 400;
	}*/

	if( LastTime < GetTime() )
	{
		int XPos = rand() % int( Global::HudW ) - int( Global::Right );
		int YPos = rand() % int( Global::HudH ) - int( Global::Top );
		
//		FXLibrary::Bomb( Vector2D( XPos, YPos ) );
		FXLibrary::CrazyTest( Vector2D( XPos, YPos ) );
		
		LastTime = GetTime() + 30;
	}
	
	DenseParticle.Step();
//	SolidParticle.Step();
}
// - ------------------------------------------------------------------------------------------ - //
