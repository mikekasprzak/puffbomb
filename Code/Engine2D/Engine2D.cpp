// - ------------------------------------------------------------------------------------------ - //
#include "Engine2D.h"

#include <Graphics/Gfx.h>
#include <Global.h>

#include <Input/Input.h>

#include "CreateCollectionInstance.h"
#include "CreatePassiveInstance.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// Static instance to know who's active is inside "Engine2D_Current.cpp" //
// - ------------------------------------------------------------------------------------------ - //
cEngine2D::cEngine2D() :
	ShowCollectionDebug( false ),
	ShowStaticDebug( false ),
	ShowPassiveDebug( false ),
	ShowZoneDebug( false )
{
	// Create Camera //
	Camera = new cCamera(
		Vector3D( 0.0, 0.0, Global::HudZoom * Real( 2.5 ) ),			// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Global::AspectRatio,							// Aspect Ratio
		1000.0,											// NearClip
		100000.0,										// FarClip
		Global::HudZoom * Real( 2.5 ),					// MinZoom
		Global::HudZoom * Real( 8 ),					// MaxZoom
		Global::HudZoom,								// HudZoom
		Real( 0 ),										// X
		Real( 0 ),										// Y
		Real( Global::ScreenW ),						// Width
		Real( Global::ScreenH )							// Height
	 );
	
	// Set this Engine to be the active engine //
	SetActive();
	
 //	Gfx::SaturateBlend();
	Gfx::StandardBlend();
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
	
	Current = 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cEngine2D::Message( int, cDynamicCollection* ) {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
int cEngine2D::Message( int, cPassiveObject* ) {
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::PhysicsStart() {
}
// - ------------------------------------------------------------------------------------------ - //	
void cEngine2D::PhysicsEnd() {
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::StepPhysics() {	
	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();
	
	// Overloaded code that occurs no matter how many times we step //
	PhysicsStart();

	// Physics Stage 1 -------------------------------------- //
	// Step all the physics for all objects //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		// If object is active //
		if ( DynamicComponent[ idx ]->IsActive() ) {
			// Step Object //
			DynamicComponent[ idx ]->Body.Step();
			
			// Step it's internal Animation system //
			//DynamicComponent[ idx ]->StepAnimation();
			
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
				DynamicCollection[ idx ]->Component[ idx2 ].Body.StepInternalConstraints();
			}
		}

		// Physics Stage 2 B -------------------------------- //
		// For every component //
		for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
			// If object is active //
			if ( DynamicComponent[ idx ]->IsActive() ) {
				// If "IgnoreObjects" is set, don't test versus components //
				if ( !DynamicComponent[ idx ]->Flags.IgnoreObjects() ) {
					// For every after object //
					for ( size_t idx2 = idx + 1; idx2 < DynamicComponent.size(); ++idx2 ) {
						// If either object has IgnoreFamily enabled //
						if ( DynamicComponent[ idx ]->Flags.IgnoreFamily() ||
							DynamicComponent[ idx2 ]->Flags.IgnoreFamily() )
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
				if ( !DynamicComponent[ idx ]->Flags.IgnoreScenery() ) {
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
		if ( DynamicCollection[ idx ]->IsActive() ) {
			// If work returns false, then destroy object //
			if ( !DynamicCollection[ idx ]->Work() ) {
				
			}
		}
	}

	// Do the job of passives //
	for ( size_t idx = 0; idx < PassiveObject.size(); ++idx ) {
		if ( PassiveObject[ idx ]->IsActive() ) {
			// If work returns false, then destroy object //
			if ( !PassiveObject[ idx ]->Work() ) {
				
			}
		}
	}
	
	// Overloaded code that occurs no matter how many times we step //
	PhysicsEnd();	
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::StepAnimation() {
	// Step static object animations //
	//for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
	//	StaticObjectInstance[ idx ].StepAnimation();
	//}

	// Step Component animations //
	for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
		if ( DynamicComponent[ idx ]->IsActive() ) {
			// Step it's internal Animation system //
			DynamicComponent[ idx ]->StepAnimation();
		}
	}
	
	// Step Passive Object Animations //
	for ( size_t idx = 0; idx < PassiveObject.size(); ++idx ) {
		if ( PassiveObject[ idx ]->IsActive() ) { 
			// Step it's internal Animation system //
			PassiveObject[ idx ]->StepAnimation();
		}
	}
	
	// - -------------------------------------------------------------------------------------- - //
	// Debug Info //
	if ( Input::Button[ KEY_0 ].Pressed() ) {
		ShowCollectionDebug = !ShowCollectionDebug;
		ShowPassiveDebug = ShowCollectionDebug;
		ShowZoneDebug = ShowCollectionDebug;
		ShowStaticDebug = ShowCollectionDebug;
	}
	
	if ( Input::Button[ KEY_9 ].Pressed() ) {
		ShowCollectionDebug = !ShowCollectionDebug;
	}

	if ( Input::Button[ KEY_8 ].Pressed() ) {
		ShowStaticDebug = !ShowStaticDebug;
	}

	if ( Input::Button[ KEY_7 ].Pressed() ) {
		ShowPassiveDebug = !ShowPassiveDebug;
	}

	if ( Input::Button[ KEY_6 ].Pressed() ) {
		ShowZoneDebug = !ShowZoneDebug;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::Step() {
	// Physics and General Engine //
	for ( int idx = 0; idx < 2; idx++ ) {
		StepPhysics();
	}
	
	// Animation system stepping //
	StepAnimation();
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::Draw() {
	// --------------- Engine ------------------------- //
	Camera->Update();
	// - -------------------------------------------------------------------------------------- - //
//	// Richard's Rotate effect (Initially set to 90) //
//	if( RotateCounter != 0 ) {
//		Gfx::Rotate( Real( RotateCounter ), -Real( 1.0 ), Real( 1.0 ), Real( 1.0 ) );
//			
//		RotateCounter -= 9;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Set my Engine and Physics instance to be the active ones //
	SetActive();
	Physics.SetActive();

	// Graphics settings to correctly render everything //
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	Gfx::EnableDepth();
	
	// First Pass Back StaticObject Draw //
	{
		// Draw Tiles (First, 'cause the objects as flat sprites clip 3D things funny) //
		for ( size_t idx = 0; idx < BackStaticObject.size(); ++idx ) {
			BackStaticObject[ idx ]->Draw();
		}
	}
	
//	// Static outlines //
//	{
//		Gfx::DisableDepth();
//		Gfx::DisableTex2D();
//		
//		for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
//			StaticObjectInstance[ idx ].DrawThickEdges();
//		}
//		
//		Gfx::EnableTex2D();
//		Gfx::EnableDepth();		
//	}

	// First Pass Component Draw (White) //
//	{
//		Gfx::PushMatrix();
//		Gfx::Translate( Real::Zero, Real::Zero, -Real( 2.05 ) );
//		// Draw Objects //
//		for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
//			if ( DynamicComponent[ idx ]->IsActive() ) {
//				DynamicComponent[ idx ]->Draw( 0 );
//			}
//		}
//		Gfx::PopMatrix();
//	}

	// Second Pass Component Draw //
	{
		// Draw Objects //
		for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
			if ( DynamicComponent[ idx ]->IsActive() ) { 
				DynamicComponent[ idx ]->Draw( 1 );
			}
		}
	}

//	Gfx::DisableDepth();
	
//	// First Pass Passive Object Draw //
//	{
//		// Draw Passive Objects //
//		for ( size_t idx = 0; idx < PassiveObject.size(); ++idx ) {
//			if ( PassiveObject[ idx ]->IsActive() ) { 
//				PassiveObject[ idx ]->Draw();
//			}
//		}
//	}

	Gfx::EnableDepth();
	Gfx::EnableTex2D();
		
	// First Pass Front StaticObject Draw //
	{
		// Draw Tiles (First, 'cause the objects as flat sprites clip 3D things funny) //
		for ( size_t idx = 0; idx < FrontStaticObject.size(); ++idx ) {
			FrontStaticObject[ idx ]->Draw();
		}
	}
	
	Gfx::DisableDepth();
	
	// First Pass Passive Object Draw //
	{
		// Draw Passive Objects //
		for ( size_t idx = 0; idx < PassiveObject.size(); ++idx ) {
			if ( PassiveObject[ idx ]->IsActive() ) { 
				PassiveObject[ idx ]->Draw();
			}
		}
	}
	
	Gfx::EnableDepth();
	Gfx::EnableTex2D();
		
	// - -------------------------------------------------------------------------------------- - //
	Gfx::DisableDepth();
	Gfx::DisableTex2D();
		
	// Draw Debug Information //
	{
		Gfx::DisableTex2D();
		Gfx::DisableDepth();
		//Gfx::DisableBlend();
	
		// Draw Objects //
		if ( ShowCollectionDebug ) {
			for ( size_t idx = 0; idx < DynamicComponent.size(); ++idx ) {
				DynamicComponent[ idx ]->DrawBody();
			}
		}
	
		// Draw Tiles //
		if ( ShowStaticDebug ) {
			for ( size_t idx = 0; idx < StaticObjectInstance.size(); ++idx ) {
				StaticObjectInstance[ idx ].DrawBody();
			}
		}
	
		// Draw Passive Object //
		if ( ShowPassiveDebug ) {
			for ( size_t idx = 0; idx < PassiveObject.size(); ++idx ) {
				PassiveObject[ idx ]->DebugDraw();
			}
		}
	
		// Draw Zone //
		if ( ShowZoneDebug ) {
			for ( size_t idx = 0; idx < Zone.size(); ++idx ) {
				Zone[ idx ].DebugDraw();
			}
		}
	}
	
	Gfx::EnableDepth();
	Gfx::EnableTex2D();	
	// - -------------------------------------------------------------------------------------- - //		
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
		
		// Sort static objects in to fronts and backs //
		for ( int idx = 0; idx < StaticObjectInstance.size(); idx++ ) {
			if ( StaticObjectInstance[ idx ].GetFrontPolygonZ() >= Real::Zero ) {
				FrontStaticObject.push_back( &StaticObjectInstance[ idx ] );
			}
			else {
				BackStaticObject.push_back( &StaticObjectInstance[ idx ] );				
			}
		}
	}
	
	
	// Zones part //
	{
		Zone.clear();
	
		for( size_t idx = 0; idx < Map.ZoneInstanceInfo.size(); ++idx )
		{
			if ( Map.ZoneInstanceInfo[ idx ].Id == 1 ) {
				Camera->CameraBounds = Map.ZoneInstanceInfo[ idx ].BoundingRect.ToPairRect();
			}
			else {
				Zone.push_back(
					Engine2D::cZone( 
						Map.ZoneInstanceInfo[ idx ].BoundingRect,
						Map.ZoneInstanceInfo[ idx ].Id,
						Map.ZoneInstanceInfo[ idx ].Arg
						)
					);
			}
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
			
			DynamicCollection.back()->CalcBoundingRect();
		}
	}
	// Passive Object Part //
	{
		// Delete the collections //
		for ( size_t idx = 0; idx < PassiveObject.size(); idx++ ) {
			delete PassiveObject[ idx ];
		}
		
		PassiveObject.clear();
	
		for( size_t idx = 0; idx < Map.PassiveObjectInstanceInfo.size(); ++idx )
		{
			PassiveObject.push_back( CreatePassiveInstance( 
				Map.PassiveObjectInstanceInfo[ idx ].Id,
				Map.PassiveObjectInstanceInfo[ idx ].Pos,
				Map.PassiveObjectInstanceInfo[ idx ].Arg
				)
			);
		}
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
void cEngine2D::AddCollection( cDynamicCollection* _Col ) {
	// Add the collection //
	DynamicCollection.push_back( _Col );

	// Add it's parts to the component list //
	for ( size_t idx2 = 0; idx2 < _Col->Component.size(); idx2++ ) {
		DynamicComponent.push_back( &_Col->Component[ idx2 ] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cEngine2D::ElementTracker( cAnimator& ElementAnim, const Rect2D& MyRect, const bool Rotate, const Real Scaler )
{
	Real ZoomOffset = Real( Camera->Pos.z / Camera->HudZoom );
	
	Real ImageWidth = 0;
	Real ImageHeight = 0;

	if( !ElementAnim.Animation->Frame.empty() )
	{
		if( ElementAnim.Animation->Frame[ 0 ].MyFrame.Vertex.size() > 3 )
		{
			ImageWidth = ElementAnim.Animation->Frame[ 0 ].MyFrame.Vertex[ 3 ].Pos.x;
			ImageHeight = ElementAnim.Animation->Frame[ 0 ].MyFrame.Vertex[ 3 ].Pos.y;

		}
	}
	
	//ImageWidth += Offset.x;
	//ImageHeight += Offset.y;
	
	Real YPlayerTest = ( ( MyRect.Center().y - Camera->Pos.y ) / ZoomOffset );
	Real XPlayerTest = ( ( MyRect.Center().x - Camera->Pos.x ) / ZoomOffset );
	
	Vector2D DrawPos = Vector2D( 0, 0 );
	
	if( MyRect != Camera->ViewArea.ToRect() + Camera->Pos.ToVector2D() )
	{
		if( YPlayerTest > Global::Bottom + ImageHeight &&
			YPlayerTest < Global::Top - ImageHeight )
		{
			if( MyRect.Center().x < Camera->Pos.x )
			{
				DrawPos =
					Vector2D(
						Global::Left + ImageWidth,
						YPlayerTest
				);
			}
			else if( MyRect.Center().x > Camera->Pos.x )
			{
				DrawPos = 
					Vector2D(
						Global::Right - ImageWidth,
						YPlayerTest
				);
			}
		
		}
		else if( XPlayerTest > Global::Left + ImageWidth &&
				 XPlayerTest < Global::Right - ImageWidth )
		{
			if( MyRect.Center().y < Camera->Pos.y )
			{
				DrawPos =
					Vector2D( 
						XPlayerTest,
						Global::Bottom + ImageHeight
				);
			}
			else if( MyRect.Center().y > Camera->Pos.y )
			{
				DrawPos =
					Vector2D( 
						XPlayerTest,
						Global::Top - ImageHeight
				);
			}
		}
		else
		{
			if( YPlayerTest <= Global::Bottom + ImageHeight )
			{
				if( XPlayerTest <= Global::Left + ImageWidth )
				{
					DrawPos =
						Vector2D(
							Global::Left + ImageWidth,
							Global::Bottom + ImageHeight
					);
				}
				else
				{
					DrawPos =
						Vector2D(
							Global::Right - ImageWidth,
							Global::Bottom + ImageHeight
					);	
				}
			}
			else if( YPlayerTest >= Global::Top - ImageHeight )
			{
				if( XPlayerTest <= Global::Left + ImageWidth )
				{
					DrawPos =
						Vector2D(
							Global::Left + ImageWidth,
							Global::Top - ImageHeight
					);
				}
				else
				{
					DrawPos =
						Vector2D(
							Global::Right - ImageWidth,
							Global::Top - ImageHeight
					);
				}
			}
		}

		Vector2D Scaley = ( MyRect.Center() - ( Camera->Pos.ToVector2D() + ( DrawPos * ZoomOffset ) ) ).Normal() * Scaler;	
		
		if( Rotate )
		{
			Matrix2x2 MyMatrix;
			
			Vector2D Direction = ( MyRect.Center() - ( Camera->Pos.ToVector2D() + ( DrawPos * ZoomOffset ) ) ).Normal();
			
			MyMatrix( 1, 0 ) = Direction.Tangent().y;
			MyMatrix( 1, 1 ) = Direction.Tangent().x;
	
			MyMatrix( 0, 0 ) = Direction.y;
			MyMatrix( 0, 1 ) = Direction.x;
		
			ElementAnim.DrawQuad( DrawPos - Scaley, MyMatrix );
		}
		else
		{
			ElementAnim.DrawQuad( DrawPos - Scaley );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
