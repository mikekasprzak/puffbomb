// - ------------------------------------------------------------------------------------------ - //
#include "Engine2D.h"

#include <Graphics/Gfx.h>
#include <Global.h>

#include <Input/Input.h>

#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"
#include "CreateZoneInstance.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// Static instance to know who's active is inside "Engine2D_Current.cpp" //
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::cEngine2D() {
	// Create Camera //
	Camera = new cCamera(
		Vector3D( 0.0, 0.0, Global::HudZoom * Real( 2 ) ),			// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Global::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		Global::HudZoom * Real( 2 ),					// MinZoom
		Global::HudZoom * Real( 8 ),					// MaxZoom
		Global::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Global::ScreenW ),						// Width
		Real( Global::ScreenH )							// Height
	 );
}
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::~cEngine2D() {
	// Delete the collections //
	for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ ) {
		delete DynamicCollection[ idx ];
	}

	// Delete PassiveObject's //
	for ( size_t idx = 0; idx < PassiveObject.size(); idx++ ) {
		delete PassiveObject[ idx ];
	}

	// Delete Zones //
/*	for ( size_t idx = 0; idx < Zone.size(); idx++ ) {
		delete Zone[ idx ];
	}*/
	
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
			
			// Step it's internal Animation system //
			DynamicComponent[ idx ]->StepAnimation();
			
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
				// If "IgnoreObjects" is set, don't test versus components //
				if ( !DynamicComponent[ idx ]->State.IgnoreObjects() ) {
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
				
				// if "IgnoreScenery" is set, don't test versus static objects //
				if ( !DynamicComponent[ idx ]->State.IgnoreScenery() ) {
					// For every piece of static collision //
					for ( size_t idx2 = 0; idx2 < StaticObjectInstance.size(); ++idx2 ) {
						DynamicComponent[ idx ]->Solve( StaticObjectInstance[ idx2 ] );
					}
				}
				
			}
		}
	}

	// Physics Stage 3 -------------------------------------- //	
	// Components Interact with Zones and Passives once, since previous is a relaxation loop //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		// If object is active //
		if ( DynamicComponent[ idx ]->IsActive() ) {
			// Solve Versus Zones //
			for ( size_t idx2 = 0; idx2 < Zone.size(); ++idx2 ) {
				DynamicComponent[ idx ]->Solve( Zone[ idx2 ] );
			}

			// Solve Versus Passive Objects //
			for ( size_t idx2 = 0; idx2 < PassiveObject.size(); ++idx2 ) {
				DynamicComponent[ idx ]->Solve( *PassiveObject[ idx2 ] );
			}
		}
	}
	
	// Physics Stage 4 -------------------------------------- //	
	// All objects have now moved.  Now to have them do and interpret what they've learned //
	for ( size_t idx = 0; idx < DynamicCollection.size(); ++idx ) {
		//if ( DynamicCollection[ idx ].IsActive() ) {
			DynamicCollection[ idx ]->Work();
		//}
	}

	// Do the job of passives //
	for ( size_t idx = 0; idx < PassiveObject.size(); ++idx ) {
		//if ( PassiveObject[ idx ].IsActive() ) {
		PassiveObject[ idx ]->Work();
		//}
	}
	
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

	// Draw Tiles (First, 'cause the objects as flat sprites clip 3D things funny) //
	for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
		StaticObjectInstance[ idx ].Draw();
	}

	// Draw Objects //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		if ( DynamicComponent[ idx ]->IsActive() ) { 
			DynamicComponent[ idx ]->Draw();
		}
	}
/*
	Gfx::DisableTex2D();
	Gfx::DisableDepth();
	Gfx::DisableBlend();

	// Draw Objects //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		DynamicComponent[ idx ]->DrawBody();
	}

	// Draw Tiles //
	for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
		StaticObjectInstance[ idx ].DrawBody();
	}
*/
	Gfx::EnableDepth();
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::LoadMap( const std::string MapName )
{
	Map.LoadBinary( MapName );
	
	Log( LOG_HIGHEST_LEVEL, "Static Object part " );

	// Static Object part //
	{
		StaticObjectInstance.clear();
		
		for ( size_t idx = 0; idx < Map.StaticObjectInstanceInfo.size(); idx++ )
		{
			StaticObjectInstance.push_back(
				Engine2D::cStaticObjectInstance(
					Map.StaticObjectInstanceInfo[ idx ].FileName,
					Map.StaticObjectInstanceInfo[ idx ].Pos //,
//					Map.StaticObjectInstanceInfo[ idx ].Arg
				)
			);
		}
	}
	
	
	// Zones part //
	{
		Zone.clear();
	
		for( size_t idx = 0; idx < Map.ZoneInstanceInfo.size(); ++idx )
		{
			Zone.push_back( Engine2D::cZone( 
				Map.ZoneInstanceInfo[ idx ].BoundingRect,
				Map.ZoneInstanceInfo[ idx ].Id,
				Map.ZoneInstanceInfo[ idx ].Arg
				)
			);
		}
	}

	ResetMap();
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::ResetMap()
{
	Log( LOG_HIGHEST_LEVEL, "Dynamic Object part " );
	
	// Dynamic Object part //
	{
		// Delete the collections //
		for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ ) {
			delete DynamicCollection[ idx ];
		}

		DynamicCollection.clear();
		
		for ( size_t idx = 0; idx < Map.DynamicObjectInstanceInfo.size(); idx++ )
		{
			DynamicCollection.push_back(
				CreateCollectionInstance(
					Map.DynamicObjectInstanceInfo[ idx ].Id,
					Map.DynamicObjectInstanceInfo[ idx ].Pos,
					Map.DynamicObjectInstanceInfo[ idx ].Arg
				)
			);
			
			for ( size_t idx2 = 0; idx2 < Map.DynamicObjectInstanceInfo[ idx ].Component.size(); idx2++ )
			{
				for ( size_t idx3 = 0; idx3 < Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos.size(); idx3++ )
				{
					DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Pos( idx3 ) =
						Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ];
						
					DynamicCollection[ idx ]->Component[ idx2 ].Body.Nodes.Old( idx3 ) =
						Map.DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ];					
				}
			}
		}
		
		PassiveObject.clear();
		
		Zone.clear();
	}
	//Log( LOG_HIGHEST_LEVEL, "Finished LoadMap() " );

	DynamicComponent.clear();

	// Populate component list with all components //
	for ( size_t idx = 0; idx < DynamicCollection.size(); idx++ ) {
		for ( size_t idx2 = 0; idx2 < DynamicCollection[ idx ]->Component.size(); idx2++ ) {
			DynamicComponent.push_back( &DynamicCollection[ idx ]->Component[ idx2 ] );
		}
		DynamicCollection[ idx ]->UpdateAnchors();
	}

	// Wake up all components //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		DynamicComponent[ idx ]->Body.Nodes.WakeUp();
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
