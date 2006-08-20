// - ------------------------------------------------------------------------------------------ - //
#include "Engine2D.h"

#include <Platform/Global.h>

// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// Static instance to know who's active //
cEngine2D* cEngine2D::Current;
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::cEngine2D() {
	Real HudZoom = 1302.5;
	
	// Create Camera //
	Camera = Engine2D::cCamera(
		Vector3D( 0.0, 0.0, HudZoom ),					// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Platform::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		HudZoom,										// MinZoom
		HudZoom + Real( 8000 ),							// MaxZoom
		HudZoom											// HudZoom
	 );	
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::Step() {
	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();

/*
	// Physics Stage 1 -------------------------------------- //
	// Step all the physics for all objects //
	for ( size_t idx = 0; idx < DynamicObject.size(); ++idx ) {
		if ( DynamicObject[ idx ].IsActive() ) { 
			DynamicObject[ idx ].Step();
			
			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				DynamicObject[ idx ].Solve( Impulse[ idx2 ] );
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
		for ( size_t idx = 0; idx < DynamicObject.size(); ++idx ) {
			if ( DynamicObject[ idx ].IsActive() ) { 
				// Test and act versus zones //
				for ( size_t idx2 = 0; idx2 < Zone.size(); ++idx2 ) {
					DynamicObject[ idx ].Solve( Zone[ idx2 ] );
				}

				// No reason to repeat any //
				for ( size_t idx2 = idx + 1; idx2 < DynamicObject.size(); ++idx2 ) {
					if ( DynamicObject[ idx2 ].IsActive() ) { 
						// (Test and) Solve collisions between these 2 objects //
						DynamicObject[ idx ].Solve( SphereObject[ idx2 ] );
					}
				}
				
				// Test versus static collision only if you're awake //
				if ( DynamicObject[ idx ].IsAwake() ) {
					// Their statics, not part of our family.  So we sadly needs to do them all every time //
					for ( size_t idx2 = 0; idx2 < StaticObject.size(); ++idx2 ) {
						DynamicObject[ idx ].Solve( StaticObject[ idx2 ] );
					}
				}
			}
		}
	}

	// Physics Stage 3 -------------------------------------- //	
	// All objects have now moved.  Now to have them do and interpret what they've learned //
	for ( size_t idx = 0; idx < DynamicObject.size(); ++idx ) {
		if ( DynamicObject[ idx ].IsActive() ) {
			DynamicObject[ idx ].Work();
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
	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();

/*
	// Draw Objects //
	for ( size_t idx = 0; idx < DynamicObject.size(); ++idx ) {
		DynamicObject[ idx ].Draw();
	}
*/
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
