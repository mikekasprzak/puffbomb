// - ------------------------------------------------------------------------------------------ - //
#include "ClassicLevelEnd.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>

#include <stdlib.h>
#include <time.h>
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cClassicLevelEnd::cClassicLevelEnd( cClassicGameEngine* _MyEngine ) :
	MyEngine( _MyEngine )
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
	
	Form.Load( "2D/Menu/ClassicLevelEnd.form" );

	Gfx::DisableSmoothPolygon();
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //
cClassicLevelEnd::~cClassicLevelEnd()
{
	delete Camera;
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicLevelEnd::ResetMenu()
{

}
// - ------------------------------------------------------------------------------------------ - //
void cClassicLevelEnd::Draw()
{
	MyEngine->Camera->Update();
	
	MyEngine->Draw();

	Camera->Update();

	Gfx::EnableTex2D();
	Gfx::EnableBlend();
		
//	DenseParticle.Draw();
//	SolidParticle.Draw();

	Gfx::StandardBlend();

	Form.Draw();
	
	Gfx::DisableTex2D();
	Gfx::DisableBlend();	
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicLevelEnd::Step()
{
	if( Input::Pad[ 0 ].Button[ PAD_A ].Pressed() || Input::Pad[0].Button[ PAD_START ].Pressed() )
	{
		cMessageEntity::Current->BreakLoop = true;	
	}
	
	Form.Step();
	
/*	if( LastTime < GetTime() )
	{
		int XPos = rand() % int( Global::HudW ) - int( Global::Right );
		int YPos = rand() % int( Global::HudH ) - int( Global::Top );

		FXLibrary::CrazyTest( Vector2D( XPos, YPos ) );

		LastTime = GetTime() + 80;
	}
	
	DenseParticle.Step();
	SolidParticle.Step();*/
}
// - ------------------------------------------------------------------------------------------ - //
