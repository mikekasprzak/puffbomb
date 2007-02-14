// - ------------------------------------------------------------------------------------------ - //
#include "MenuFlowEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Framework/MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Font/Fonts.h>
#include <Graphics/Gfx.h>
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
cMenuFlowEngine::cMenuFlowEngine( const std::string& FileName )
{
	// Create Camera //
	HudCamera = new cCamera(
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
	 
 	LoadMap( FileName );
 
	#ifdef EDITOR
		Form.Load( "2D/Menu/MainMenuEditor.form" );
	//	Form.Load( "2D/Menu/Test2.form" );
	#else
		Form.Load( "2D/Menu/MainMenu.form" );
	#endif // EDITOR //
 
	DenseParticle.Clear();
 	SolidParticle.Clear();
 	
 	Gfx::DisableMouseDraw();
}
// - ------------------------------------------------------------------------------------------ - //
cMenuFlowEngine::~cMenuFlowEngine() {
	// Destroy my Custom Camera //
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cMenuFlowEngine::Step() {
	// Original Engine Step Stuff //
	cEngine2D::Step();
	
	// Step Particle Systems //
	SolidParticle.Step();
	DenseParticle.Step();

	// Form //
	Form.Step();
	
	if( Form.SuperFlowState != 1 )
	{
//		BreakLoop = true;	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuFlowEngine::Draw() {
	// Stuff my engine does before //
	// ... //
	
	// Original Engine Stuff //
	cEngine2D::Draw();
	
	// Stuff my engine does after //

	Gfx::DisableDepth();
	
	SolidParticle.Draw();
	DenseParticle.Draw();

	Gfx::EnableDepth();

	HudCamera->Update();

	Gfx::DisableDepth();
		
	// Draw MiniMap and draw the view box //
	Gfx::PushMatrix();
	{
//		Gfx::Translate( Vector2D( Global::Right, Global::Bottom ) );

//		Gfx::DisableTex2D();
		
//		Gfx::SetLineWidth( 1.0 );
		
		Gfx::EnableTex2D();

		Form.Draw();
		
		Gfx::DisableTex2D();
	}
	Gfx::PopMatrix();
	
}
// - ------------------------------------------------------------------------------------------ - //
