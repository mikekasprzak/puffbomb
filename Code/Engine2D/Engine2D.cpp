// - ------------------------------------------------------------------------------------------ - //
#include "Engine2D.h"

#include <Graphics/Gfx.h>
#include <Global.h>

#include "DynamicComponent/ComponentAnimationSet/ComponentAnimationSetPool.h"
#include "StaticObject/StaticObjectPool.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// Static instance to know who's active //
cEngine2D* cEngine2D::Current;
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::cEngine2D() {
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
		Global::HudZoom + Real( 8000 ),				// MaxZoom
		Global::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Global::ScreenW ),						// Width
		Real( Global::ScreenH )						// Height
	 );
	
	// Add a dummy object for testing //
	cDynamicCollection* Dummy = new cDynamicCollection();
	Vector2D MyOffset( 200, 0 );
	DynamicCollection.push_back( Dummy );
	Dummy->Component.push_back( cDynamicComponent( Dummy, "Hamster/Body/HamsterBody.comp", MyOffset ) );


	Dummy = new cDynamicCollection();
	DynamicCollection.push_back( Dummy );
	//Dummy->Component.push_back( cDynamicComponent( Dummy, "Hamster/Body/HamsterBody.comp", Vector2D::Zero ) );
	Dummy->LoadBinary( "2D/HighFive/HighFive.coll" );
	
	StaticObjectInstance.push_back( cStaticObjectInstance() );
	StaticObjectInstance.back().Object = StaticObjectPool.Load( "Tile_Brickter.blend.mesh3d" );

	StaticObjectInstance.push_back( cStaticObjectInstance() );
	StaticObjectInstance.back().Object = StaticObjectPool.Load( "Tile_BrickterPaste.blend.mesh3d" );
	StaticObjectInstance.back().Pos = Vector2D( 200, 0 );

	StaticObjectInstance.push_back( cStaticObjectInstance() );
	StaticObjectInstance.back().Object = StaticObjectPool.Load( "Tile_BrickterPaste.blend.mesh3d" );
	StaticObjectInstance.back().Pos = Vector2D( 400, 0 );
	
	
	// Populate component list with all components //
	for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ ) {
		for ( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); idx2++ ) {
			DynamicComponent.push_back( &DynamicCollection[ idx ]->Component[ idx2 ] );
		}
	}
	
	// Wake up all components //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		DynamicComponent[ idx ]->Body.Nodes.WakeUp();
	}
}
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::~cEngine2D() {
	// Delete the collections //
	for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ ) {
		delete DynamicCollection[ idx ];
	}
	
	// Toast our Camera //
	delete Camera;
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::Step() {
	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();

	// Physics Stage 1 -------------------------------------- //
	// Step all the physics for all objects //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		// If object is active //
		if ( DynamicComponent[ idx ]->IsActive() ) {
			// Step Object //
			DynamicComponent[ idx ]->Body.Step();
			
			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				DynamicComponent[ idx ]->Solve( Impulse[ idx2 ] );
			}
		}
	}

	// Clear Impulses //
	Impulse.clear();

	// Physics Stage 2 -------------------------------------- //
	// Run all contacts and springs twice, for cleaner results //
	for ( int ContactsAndSprings = 0; ContactsAndSprings < 2; ContactsAndSprings++ ) {
		// Physics Stage 2 A -------------------------------- //
		// For every collection //
		for ( size_t idx = 0; idx < DynamicCollection.size(); ++idx ) {
			// Update nodes via NodeLink springs and Anchors //
			DynamicCollection[ idx ]->StepLinkage();
			
			// Update all Springs //
			for ( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); idx2++ ) {
				DynamicCollection[ idx ]->Component[ idx2 ].Body.StepSprings();
			}
		}

		// Physics Stage 2 B -------------------------------- //
		// For every component //
		for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
			// If object is active //
			if ( DynamicComponent[ idx ]->IsActive() ) {
				// If "IgnoreObjects" is set, move on to the next component //
				if ( DynamicComponent[ idx ]->State.IgnoreObjects() )
					continue;
					
				// For every after object //
				for ( size_t idx2 = idx + 1; idx2 < DynamicComponent.size(); ++idx2 ) {
					// If either object has IgnoreFamily enabled //
					if ( DynamicComponent[ idx ]->State.IgnoreFamily() ||
						DynamicComponent[ idx2 ]->State.IgnoreFamily() )
					{
						// Bail if they do share a common parent //
						if ( DynamicComponent[ idx ]->Parent == DynamicComponent[ idx2 ]->Parent )
							continue;
					}
					
					// If the other object is active //
					if ( DynamicComponent[ idx2 ]->IsActive() ) {
						// Solve the collision between them //
						DynamicComponent[ idx ]->Solve( *DynamicComponent[ idx2 ] );
					}
				}
			}
		}
	}
//		// Step Physics for all Springs inside each component inside this object //
//
//
//		// Step Physics for NodeLink's (i.e. global springs that connect several components) //
////		for ( size_t idx = 0; idx < NodeLink.size(); ++idx ) {
////			if ( NodeLink[ idx ]->IsActive() ) { 
////				NodeLink[ idx ]->Step();
////			}
////		}		
//	
//		// ** this solving step shold solve for all components, not all objects ** //
//	
//		// Solve collisions for all objects //
//		for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
//			if ( DynamicComponent[ idx ]->IsActive() ) { 
//				// Test and act versus zones //
//				for ( size_t idx2 = 0; idx2 < Zone.size(); ++idx2 ) {
//					DynamicComponent[ idx ].Solve( Zone[ idx2 ] );
//				}
//
//				// No reason to repeat any //
//				for ( size_t idx2 = idx + 1; idx2 < DynamicComponent.size(); ++idx2 ) {
//					if ( DynamicComponent[ idx2 ].IsActive() ) { 
//						// (Test and) Solve collisions between these 2 objects //
//						DynamicComponent[ idx ].Solve( SphereObject[ idx2 ] );
//					}
//				}
//				
//				// Test versus static collision only if you're awake //
//				if ( DynamicComponent[ idx ].IsAwake() ) {
//					// Their statics, not part of our family.  So we sadly needs to do them all every time //
//					for ( size_t idx2 = 0; idx2 < StaticObject.size(); ++idx2 ) {
//						DynamicComponent[ idx ].Solve( StaticObject[ idx2 ] );
//					}
//				}
//			}
//		}
//	}

//	// Physics Stage 3 -------------------------------------- //	
//	// All objects have now moved.  Now to have them do and interpret what they've learned //
//	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
//		if ( DynamicComponent[ idx ].IsActive() ) {
//			DynamicComponent[ idx ].Work();
//		}
//	}
	
	// - -------------------------------------------------------------------------------------- - //
	// Particle Systems //
//	FlatParticle.Step();
//	AdditiveParticle.Step();

	// - -------------------------------------------------------------------------------------- - //
	// Other //
//	Form.Step();


}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::Draw() {
	// --------------- Engine ------------------------- //
	Camera->Update();

	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();

	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	// Draw Objects //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		if ( DynamicComponent[ idx ]->IsActive() ) { 
			DynamicComponent[ idx ]->Draw();
		}
	}

	// Draw Tiles //
	for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
		StaticObjectInstance[ idx ].Draw();
	}
	
	Gfx::DisableTex2D();
	Gfx::DisableBlend();

	Gfx::Circle( Vector2D::Zero, Real( 25 ), Gfx::RGB( 255, 255, 255 ) );
	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
