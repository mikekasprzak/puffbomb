// - ------------------------------------------------------------------------------------------ - //
#include "LevelEnd.h"
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
cLevelEnd::cLevelEnd( cGolfGameEngine* _MyEngine ) :
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
	
	Form.Load( "2D/Menu/LevelEnd.form" );
	
	for( size_t idx = 0; idx < MyEngine->Player.size(); ++idx )
	{
		std::stringstream Temp;
		Temp << MyEngine->Player[ idx ]->Score;
		std::string TempString = Temp.str();

		Form.DialogBox[ 0 ].TextLabel.push_back(
			cTextLabel(
				Vector2D( 160 + Form.DialogBox[ 0 ].Pos.x, Form.DialogBox[ 0 ].TextLabel[ idx ].Pos.y ),
				true,
				0, 
				TempString,
				0.5,
				Gfx::White()
			)
		);
	}
	
	if( MyEngine->Player.size() < 4 )
	{
		for( size_t idx = MyEngine->Player.size(); idx < 4; ++idx )
		{
			Form.DialogBox[ 0 ].TextLabel[ idx ].Text.clear();
		}
	}
	
	
	
	LastTime = GetTime();
	
	Gfx::DisableSmoothPolygon();
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //
cLevelEnd::~cLevelEnd()
{
	delete Camera;
}
// - ------------------------------------------------------------------------------------------ - //
void cLevelEnd::ResetMenu()
{

}
// - ------------------------------------------------------------------------------------------ - //
void cLevelEnd::Draw()
{
	MyEngine->Camera->Update();
	
	MyEngine->Draw();
	
	Camera->Update();

	Gfx::EnableTex2D();
	Gfx::EnableBlend();
		
	DenseParticle.Draw();
	SolidParticle.Draw();

	Gfx::StandardBlend();

	Form.Draw();
	
	Gfx::DisableTex2D();
	Gfx::DisableBlend();	
}
// - ------------------------------------------------------------------------------------------ - //
void cLevelEnd::Step()
{
	if( Input::Pad[ 0 ].Button[ PAD_A ].Pressed() || Input::Pad[0].Button[ PAD_START ].Pressed() )
	{
		cMessageEntity::Current->BreakLoop = true;	
	}
	
	Form.Step();
	
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
