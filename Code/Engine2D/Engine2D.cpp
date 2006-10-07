// - ------------------------------------------------------------------------------------------ - //
#include "Engine2D.h"

#include <Platform/Global.h>
#include <Global.h>

// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// Static instance to know who's active //
cEngine2D* cEngine2D::Current;
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::cEngine2D() {
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
		cGlobal::HudZoom + Real( 8000 ),				// MaxZoom
		cGlobal::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Platform::ScreenW ),						// Width
		Real( Platform::ScreenH )						// Height
	 );

	// Create Camera //
	HudCamera = new cCamera(
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
	 
}
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::~cEngine2D() {
	delete Camera;
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::Step() {
	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();

/*
	// Physics Stage 1 -------------------------------------- //
	// Step all the physics for all objects //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		if ( DynamicComponent[ idx ].IsActive() ) { 
			DynamicComponent[ idx ].Step();
			
			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				DynamicComponent[ idx ].Solve( Impulse[ idx2 ] );
			}
		}
	}
	
	// Clear Impulses //
	Impulse.clear();	

	// Physics Stage 2 -------------------------------------- //
	// Run all contacts and springs twice, for cleaner results //
	for ( int ContactsAndSprings = 0; ContactsAndSprings < 2; ContactsAndSprings++ ) {
		// Step Physics for all Springs inside each component inside this object //


		// Step Physics for NodeLink's (i.e. global springs that connect several components) //
		for ( size_t idx = 0; idx < NodeLink.size(); ++idx ) {
			if ( NodeLink[ idx ]->IsActive() ) { 
				NodeLink[ idx ]->Step();
			}
		}		
	
		// ** this solving step shold solve for all components, not all objects ** //
	
		// Solve collisions for all objects //
		for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
			if ( DynamicComponent[ idx ].IsActive() ) { 
				// Test and act versus zones //
				for ( size_t idx2 = 0; idx2 < Zone.size(); ++idx2 ) {
					DynamicComponent[ idx ].Solve( Zone[ idx2 ] );
				}

				// No reason to repeat any //
				for ( size_t idx2 = idx + 1; idx2 < DynamicComponent.size(); ++idx2 ) {
					if ( DynamicComponent[ idx2 ].IsActive() ) { 
						// (Test and) Solve collisions between these 2 objects //
						DynamicComponent[ idx ].Solve( SphereObject[ idx2 ] );
					}
				}
				
				// Test versus static collision only if you're awake //
				if ( DynamicComponent[ idx ].IsAwake() ) {
					// Their statics, not part of our family.  So we sadly needs to do them all every time //
					for ( size_t idx2 = 0; idx2 < StaticObject.size(); ++idx2 ) {
						DynamicComponent[ idx ].Solve( StaticObject[ idx2 ] );
					}
				}
			}
		}
	}

	// Physics Stage 3 -------------------------------------- //	
	// All objects have now moved.  Now to have them do and interpret what they've learned //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		if ( DynamicComponent[ idx ].IsActive() ) {
			DynamicComponent[ idx ].Work();
		}
	}
	
	// - -------------------------------------------------------------------------------------- - //
	// Particle Systems //
//	FlatParticle.Step();
//	AdditiveParticle.Step();

	// - -------------------------------------------------------------------------------------- - //
	// Other //
//	Form.Step();

*/
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::Draw() {
	Camera->Update();

	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();

/*
	// Draw Objects //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		DynamicComponent[ idx ].Draw();
	}
*/

	Gfx::Circle( Vector2D::Zero, Real( 25 ), Gfx::RGB( 255, 255, 255 ) );
	
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::HudDraw() {
	HudCamera->Update();

}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
