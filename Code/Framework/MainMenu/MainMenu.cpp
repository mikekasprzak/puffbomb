// - ------------------------------------------------------------------------------------------ - //
#include "MainMenu.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
// DELETE THIS WHEN YOU GET SICK OF THE RANDOM PARTICLE //
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
	
	SolidParticle.Clear();
	DenseParticle.Clear();
	
#ifdef EDITOR
//	Window.Load( "2D/Menu/MainMenuEditor.form" );
	Window.Load( "2D/Menu/Test.form" );
#else
	Window.Load( "2D/Menu/MainMenu.form" );
#endif // EDITOR //
	
	LastTime = GetTime();
	
	Gfx::DisableSmoothPolygon();
	
	//Window.Form[ 0 ].GroupVisible( 1, 1, false );
	//Window.Form[ 0 ].GroupColor( 1, 1, Gfx::RGBA( 255, 255, 0, 255 ) );
	//Window.Form[ 0 ].GroupPos( 1, Vector2D( 100, 0 ) );
/*	int bob = 5;
	if( Window.Form[ 0 ].Labels[ bob ]->AniLabel() )
	{
		Window.Form[ 0 ].Labels[ bob ]->AniLabel()->PassiveAni = Window.Form[ 0 ].Labels[ bob ]->AniLabel()->SelectAni;
		//Log( 10, "Window.Form[ 0 ].Labels[ bob ]->AniLabel()" );
	}*/
		
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
	//Window.Form[ 0 ].SuperFlowState = 1;
	//Work();
}
// - ------------------------------------------------------------------------------------------ - //
void cMainMenu::Draw()
{
	Camera->Update();

	Gfx::EnableTex2D();
	Gfx::EnableBlend();
		
	DenseParticle.Draw();
	SolidParticle.Draw();

	Gfx::StandardBlend();

	Window.Draw();
	
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
	Window.Step();
	
	if( Window.Form[ 0 ].SuperFlowState != 1 )
	{
		BreakLoop = true;	
	}
	
	if( LastTime < GetTime() )
	{
		int XPos = rand() % int( Global::HudW ) - int( Global::Right );
		int YPos = rand() % int( Global::HudH ) - int( Global::Top );

		FXLibrary::CrazyTest( Vector2D( XPos, YPos ) );

		LastTime = GetTime() + 80;
	}
	
	DenseParticle.Step();
	SolidParticle.Step();
}
// - ------------------------------------------------------------------------------------------ - //
