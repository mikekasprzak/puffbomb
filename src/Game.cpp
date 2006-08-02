// - ------------------------------------------------------------------------------------------ - //
// Remove SDL from here
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <sstream>
#include <map>
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include <Font/Fonts.h>

#include <Input/Input.h>

#include <Platform/Global.h>

#include <Graphics/TexturePool.h>

#include <Animation/AnimationPool.h>
#include <Particle2D/FXLibrary.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/String.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
cGame* cGame::Current;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cGame::cGame( int _ScreenW, int _ScreenH ) :
	Global( _ScreenW, _ScreenH ),
	Focus1( 0 ), Focus2( 0 )
{
	Current = this;

	Real HudZoom = SetHudData();
	
	// Create Camera //
	Camera = new cCamera(
		Vector3D( 0.0, 0.0, HudZoom ),
		Vector3D( 0.0, 0.0, 0.0 ),
		Vector3D( 0.0, 1.0, 0.0 ),
		45.0,
		Platform::AspectRatio,
		1.0,
		100000.0,
		HudZoom,
		HudZoom + Real( 8000 ),
		HudZoom
	 );

	HudCamera = new cCamera(
		Vector3D( 0.0, 0.0, HudZoom ),
		Vector3D( 0.0, 0.0, 0.0 ),
		Vector3D( 0.0, 1.0, 0.0 ),
		45.0,
		Platform::AspectRatio,
		1.0,
		100000.0,
		HudZoom,
		HudZoom,
		HudZoom
	 );
	
	
	Log( LOG_HIGHEST_LEVEL, "****** Loading Map ******" );
	//LoadMap( "Content/PuffBOMB/Maps/Level00.map" );
	LoadMap( "Maps/Level00.map" );
	Log( LOG_HIGHEST_LEVEL, "****** Finished Loading Map ******" );
	
	Log( LOG_HIGHEST_LEVEL, "****** Loading Fonts ******" );
	cFonts::LoadFonts();
	Log( LOG_HIGHEST_LEVEL, "****** Finished Loading Fonts ******" );
	
	Log( LOG_HIGHEST_LEVEL, "****** Generating Collision ******" );
	GenerateCollision();
	Log( LOG_HIGHEST_LEVEL, "****** Finished Generating Collision ******" );
		 
	Camera->NewTarget( Focus1 );

	// Create a Dialog box and populate it //
	//Form.Load( "Content/PuffBOMB/2D/Menu/Test.form" );
	Form.Load( "2D/Menu/Test.form" );

}
// - ------------------------------------------------------------------------------------------ - //
cGame::~cGame() {
	delete Camera;
	delete HudCamera;
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Reset() {
	// Send all objects back to their home points //
	for ( size_t idx = 0; idx < SphereObject.size(); ++idx ) {
		SphereObject[ idx ]->Reset();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Reload() {
	// Reload the objects //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::Input() {
	// Cheesy hack to reset all objects //
	if ( Input::Button[ KEY_TAB ] ) {
		Reset();
	}

	if( Input::Button[ KEY_8 ].Pressed() ) {
		BackgroundOn = !BackgroundOn;
	}

	// Cheesy hack to toggle more info display (normals, springs, bounding boxes, etc) //
	if( Input::Button[ KEY_0 ].Pressed() ) {
		cGlobal::ToggleExtraDisplayInfo();
	}

	// Cheesy hack to toggle more info display (normals, springs, bounding boxes, etc) //
	if( Input::Button[ KEY_9 ].Pressed() ) {
		cGlobal::ToggleCollisionDisplay();
	}
	
	if( Input::Button[ KEY_T ].Pressed() )
	{
		Camera->NewTarget( Focus2 );
	}
	if( Input::Button[ KEY_Y ].Pressed() )
	{
		Camera->NewTarget( Focus1 );
	}
	
	if ( Input::Button[ KEY_BACKSPACE ].Pressed() ) {
		Impulse.push_back( 
			cImpulse(
				Vector2D( 0, 0 ),
				Real( 30 ), Real( 10 ),
				Real( 90 ), Real( 0 )
				)
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Step() {
	// Physics Stage 1 -------------------------------------- //
	// Step all the physics for all objects //
	for ( size_t idx = 0; idx < SphereObject.size(); ++idx ) {
		if ( SphereObject[ idx ]->Flags.IsActive() ) { 
			SphereObject[ idx ]->ClearFlags();
			SphereObject[ idx ]->Step();
			
			// Apply Impulses //
			for ( size_t idx2 = 0; idx2 < Impulse.size(); idx2++ ) {
				SphereObject[ idx ]->Solve( Impulse[ idx2 ] );
			}
		}
	}
	
	// Clear Impulses //
	Impulse.clear();	

	// Physics Stage 2 -------------------------------------- //
	// Run all contacts and springs twice, for cleaner results //
	for ( int ContactsAndSprings = 0; ContactsAndSprings < 2; ContactsAndSprings++ ) {
		// Step Physics for NodeLink's (i.e. global springs that connect several objects) //
		for ( size_t idx = 0; idx < NodeLink.size(); ++idx ) {
			if ( NodeLink[ idx ]->IsActive() ) { 
				NodeLink[ idx ]->Step();
			}
		}		
	
		// Solve collisions for all objects //
		for ( size_t idx = 0; idx < SphereObject.size(); ++idx ) {
			if ( SphereObject[ idx ]->Flags.IsActive() ) { 
				// Test and act versus zones //
				for ( size_t idx2 = 0; idx2 < Zone.size(); ++idx2 ) {
					SphereObject[ idx ]->Solve( Zone[ idx2 ] );
				}

				// No reason to repeat any //
				for ( size_t idx2 = idx + 1; idx2 < SphereObject.size(); ++idx2 ) {
					if ( SphereObject[ idx2 ]->Flags.IsActive() ) { 
						// (Test and) Solve collisions between these 2 objects //
						SphereObject[ idx ]->Solve( *SphereObject[ idx2 ] );
					}
				}
				
				// Test versus static collision only if you're awake //
				if ( SphereObject[ idx ]->IsAwake() ) {
					// Their statics, not part of our family.  So we sadly needs to do them all every time //
					for ( size_t idx2 = 0; idx2 < StaticObject.size(); ++idx2 ) {
						SphereObject[ idx ]->Solve( *StaticObject[ idx2 ] );
					}
				}
			}
		}
	}

	// Physics Stage 3 -------------------------------------- //	
	// All objects have now moved.  Now to have them do and interpret what they've learned //
	for ( size_t idx = 0; idx < ObjectController.size(); ++idx ) {
		if ( ObjectController[ idx ]->SphereObject->Flags.IsActive() ) {
			ObjectController[ idx ]->Step();
		}
	}
	
	// - -------------------------------------------------------------------------------------- - //
	// Particle Systems //
	FlatParticle.Step();
	AdditiveParticle.Step();

	// - -------------------------------------------------------------------------------------- - //
	// Other //
	Form.Step();

	// Particle Explosion Hack //	
	if( Input::Button[ KEY_BACKSPACE ] )
	{
		FXLibrary::OutlineTest( Vector2D( 0, 0 ) );	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Draw() {


	// Draw Scenery 3D Model //
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	if ( BackgroundOn )
	{
		//void* ObjectTest = 0;
		for( size_t idx = 0; idx < Mesh3d.size(); ++idx )
		{
			Gfx::DrawMesh3d( &Mesh3d[idx] );

		}

	}
	glDisable(GL_BLEND);
	glDisable( GL_TEXTURE_2D );
	glDisable(GL_DEPTH_TEST);
	
	// Draw our dense particle system //
	//DenseParticleSystem.Draw();

	// Draw Objects //
	// Sets the color of the objects to white before being drawn.
	// otherwise they depend on the last thing drawn to have the correct colour.
	
	
	glColor4ub( 255, 255, 255, 255 );
	for ( size_t idx = 0; idx < ObjectController.size(); ++idx ) {
		ObjectController[ idx ]->Draw();
	}

	// Draw Debug Information //
	glDisable(GL_DEPTH_TEST);
	{		
		// Draw scenery collision information //
		for ( size_t idx = 0; idx < StaticObject.size(); ++idx ) {
			StaticObject[ idx ]->DebugDraw( );
		}
	
		// Draw Objects //
		for ( size_t idx = 0; idx < SphereObject.size(); ++idx ) {
			if ( SphereObject[ idx ]->Flags.IsActive() ) { 
				SphereObject[ idx ]->DebugDraw( );
			}
		}
	
//		// Draw PolyObjects //
//		for ( size_t idx = 0; idx < PolyObject.size(); ++idx ) {
//			if ( PolyObject[ idx ]->Flags.IsActive() ) { 
//				PolyObject[ idx ]->DebugDraw( );
//			}
//		}
	
		// Draw Node Links //
		for ( size_t idx = 0; idx < NodeLink.size(); ++idx ) {
			if ( NodeLink[ idx ]->IsActive() ) { 
				NodeLink[ idx ]->DebugDraw( );
			}
		}
	}

		// Draw Collision Line results //
//		for ( int idx = 0; idx < CollisionLine.size(); idx++ ) {
//			gfx::Line( CollisionLine[idx].a, CollisionLine[idx].b, gfx::RGB( 255, 0, 0 ), gfx::RGB( 0, 255, 0 ) );
//			Vector2D Center = CollisionLine[idx].b - CollisionLine[idx].a;
//			Real Mag = Center.NormalizeRet();
//			Center = (Center * (Mag * Real::Half)) + CollisionLine[idx].a;
//			gfx::Line( Center, Center + (CollisionLine[idx].Normal * Real( 10 )), gfx::RGB( 255, 255, 255 ) );
//		}

		// Draw Found Polygons //
//		for ( int idx = 0; idx < Polygon.size(); idx++ ) {
//			for ( int idx2 = 0; idx2 < Polygon[idx].size(); idx2++ ) {
//				gfx::Line( Polygon[idx][idx2].a, Polygon[idx][idx2].b, gfx::RGB( (idx*64) + 192, idx2*64, idx2*64 ), gfx::RGB( (idx*64) + 192, idx2*64, idx2*64 ) );
//				Vector2D Center = Polygon[idx][idx2].b - Polygon[idx][idx2].a;
//				Real Mag = Center.NormalizeRet();
//				Center = (Center * (Mag * Real::Half)) + Polygon[idx][idx2].a;
//				gfx::Line( Center, Center + (Polygon[idx][idx2].Normal * Real( 10 )), gfx::RGB( 255, 255, 255 ) );
//			}
//		}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	FlatParticle.Draw();
	
	// Enables additive blending //
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	AdditiveParticle.Draw();

	// Disables additive blending //
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::HudDraw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glDisable( GL_DEPTH_TEST );

	std::stringstream Temp;
	Temp << Platform::FPS;
	std::string TempString = Temp.str();
	
	Vector3D TempPos = Vector3D( cGlobal::Left, cGlobal::Top - Real( 45 ), 0.0 );

	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), gfx::RGBA( 184, 0, 0, 255 ) );

	Form.Draw();

	glEnable( GL_DEPTH_TEST );

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
bool cGame::BackgroundOn = true;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
Real cGame::SetHudData()
{
	// Default is 16:9 Aspect Ratio
	Real HudZoom = 1302.5;
	
	// 16:9
	if( Platform::AspectRatio > Real( 1.75 ) && Platform::AspectRatio < Real( 1.81 ) )
	{
		HudZoom = 1302.5;

		cGlobal::Top = Real( 540.0 );
		cGlobal::Bottom = Real( -540.0 );
		cGlobal::Left = Real( -960.0 );
		cGlobal::Right = Real( 960.0 );
	}
	// 16:10
	else if( Platform::AspectRatio > Real( 1.57 ) && Platform::AspectRatio < Real( 1.63 ) )
	{
		HudZoom = 1447.0;
		
		cGlobal::Top = Real( 600.0 );
		cGlobal::Bottom = Real( -600.0 );
		cGlobal::Left = Real( -960.0 );
		cGlobal::Right = Real( 960.0 );

	}
	// 4:3
	else if( Platform::AspectRatio > Real( 1.30 ) && Platform::AspectRatio < Real( 1.36 ) )
	{
		HudZoom = 1266.0;
		
		cGlobal::Top = Real( 525.0 );
		cGlobal::Bottom = Real( -525.0 );
		cGlobal::Left = Real( -700.0 );
		cGlobal::Right = Real( 700.0 );

	}
	
	// 5:4
	else if( Platform::AspectRatio > Real( 1.22 ) && Platform::AspectRatio < Real( 1.28 ) )
	{
		HudZoom = 1234.0;
		
		cGlobal::Top = Real( 512.0 );
		cGlobal::Bottom = Real( -512.0 );
		cGlobal::Left = Real( -640.0 );
		cGlobal::Right = Real( 640.0 );

	}
	
	cGlobal::HudH = Real( cGlobal::Top * Real( 2.0 ) );
	cGlobal::HudW = Real( cGlobal::Right * Real( 2.0 ) );
	
	cGlobal::HudZoom = HudZoom;

	return HudZoom;
}
// - ------------------------------------------------------------------------------------------ - //
