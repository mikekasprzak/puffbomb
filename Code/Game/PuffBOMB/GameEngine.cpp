// - ------------------------------------------------------------------------------------------ - //
#include "GameEngine.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cGameEngine::cGameEngine() {
	// Create Camera //
	HudCamera = new cCamera(
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
}
// - ------------------------------------------------------------------------------------------ - //
cGameEngine::~cGameEngine() {
	// Destroy my Custom Camera //
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGameEngine::Step() {
	// Stuff my engine does before //
	// ... //
	
	// Original Engine Step Stuff //
	cEngine2D::Step();
	
	// Stuff my engine does after //
	// ... //
}
// - ------------------------------------------------------------------------------------------ - //
void cGameEngine::Draw() {
	// Stuff my engine does before //
	// ... //
	
	// Original Engine Stuff //
	cEngine2D::Draw();
	
	// Stuff my engine does after //
	HudCamera->Update();
}
// - ------------------------------------------------------------------------------------------ - //
