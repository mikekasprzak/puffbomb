// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include "SpiderController.h"

#include <Input/Input.h>
//#include <Util/Input.h>

#include <GL/gl.h>  // **Remove** //
#include <GL/glu.h> // **Remove** //

#include <Particle2D/ParticleFactory.h>
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cSpiderController::cSpiderController( 
	cSphereObject* _Object,
	cSphereObject* _Shot1,
	cNodeLink* _Link1,
	cSphereObject* _Shot2,
	cNodeLink* _Link2,
	const std::string& File
	) :
	cDisplayObjectController( _Object, File )
{
	Shot[0] = _Shot1;
	Shot[1] = _Shot2;
	Link[0] = _Link1;
	Link[1] = _Link2;
	RopeLength[0] = Real::One;
	RopeLength[1] = Real::One;
	
	CurrentShot = 0;
	
	// Scale and populate data //
	Scale = Real::One;

	// Copy default spring size //
	for ( size_t idx = 0; idx < _Object->Spring.size(); idx++ ) {
		SpringLength.push_back( _Object->Spring[ idx ].Length );
	}
	// Copy default Sphere Radius //
	for ( size_t idx = 0; idx < _Object->Sphere.size(); idx++ ) {
		SphereRadius.push_back( _Object->Sphere[ idx ].Radius );
	}
	// Copy and extrapolate Default Mass //
	for ( size_t idx = 0; idx < _Object->size(); idx++ ) {
		Mass.push_back( Real::One / _Object->InvMass( idx ) );
	}

	TextureId = TexturePool.Load( "SpiderTexture.tx" );
	
	MyPad = 0;
}
// - ------------------------------------------------------------------------------------------ - //	
void cSpiderController::Step() {
	if ( Input::Button[ KEY_1 ] ) {
		MyPad = 0;
	}
	if ( Input::Button[ KEY_2 ] ) {
		MyPad = 1;
	}
	if ( Input::Button[ KEY_3 ] ) {
		MyPad = 2;
	}
	if ( Input::Button[ KEY_4 ] ) {
		MyPad = 3;
	}
	
	// Cheesy Hacked in particle system that constanstly follows the player //
/*	ParticleFactory::Add(
		SphereObject->Pos( 0 ), 	// Pos //
		Vector2D( 5, 0 ),			// Velocity //
		Vector2D::Zero, 			// Acceleration //
		Vector2D::Zero, 			// Drift //
		90,	 						// Life //
		cAnimations::TestAni		// Animation //
	);
*/
	if ( Input::Pad[MyPad].Button[ GAMEPAD_BULGE ] )
		Scale = Real(1.5);
	else 
		Scale = Real::One;
	
	// Update sizes, masses and lengths //
	for ( size_t idx = 0; idx < SpringLength.size(); idx++ ) {
		SphereObject->Spring[ idx ].Length = SpringLength[ idx ] * Scale;
	}

	for ( size_t idx = 0; idx < SphereRadius.size(); idx++ ) {
		SphereObject->Sphere[ idx ].Radius = SphereRadius[ idx ] * Scale;
	}

	for ( size_t idx = 0; idx < Mass.size(); idx++ ) {
		SphereObject->InvMass( idx ) = Real::One / (Mass[ idx ] * Scale);
	}

	// Adjust Camera Zoom based on my size //
	//cGlobal::Zoom = Real( -800.0 ) - (Scale * Real(100) );
	//cGlobal::Zoom = Real( -800.0 ) - (Real::One * Real(100) );

	// When you've shot your show, test to see if it's collided with anything //
	if ( Shot[CurrentShot]->Flags.IsActive() ) {
		// If it has not hit anything yet //
		if ( !Shot[CurrentShot]->Hard[ 0 ].IsActive() ) {
			// Hit Scenery //
			if ( Shot[CurrentShot]->Sphere[ 0 ].Flags.Scenery() ) {

				// Calculate ray from center to shot //
				Vector2D Ray = ( Shot[CurrentShot]->Pos( 0 ) - SphereObject->Pos( 0 ) );
				
				// Old Rope Shrinking Trick //
				Ray *= Real( 0.9 );
				
				// Lock the shot to where it hit and activate the link at a length //
				RopeLength[CurrentShot] = Ray.NormalizeRet();
				
				// New Rope Shrinking Trick //
				//RopeLength[CurrentShot] -= SphereObject->Sphere[0].Radius * Real(2);

//				if ( RopeLength[CurrentShot] < Real( 32 ) )
//					RopeLength[CurrentShot] = Real( 32 );

				if ( RopeLength[CurrentShot] <= Real(32*16) ) {
					int NodeCount = Shot[CurrentShot]->size();
	
					Real SegmentLength = RopeLength[CurrentShot] / Real( NodeCount );
	
					for ( size_t idx = 1; idx < 16; idx++ ) {
						Shot[CurrentShot]->Pos( idx ) =
							Shot[CurrentShot]->Pos( 0 ) - (Ray * (SegmentLength * Real( idx )));
							
						Shot[CurrentShot]->Old( idx ) = Shot[CurrentShot]->Pos( idx );
					}
					for ( size_t idx = 0; idx < Shot[CurrentShot]->Spring.size(); idx++ ) {
						Shot[CurrentShot]->Spring[ idx ].Length = 
							RopeLength[CurrentShot] / Real( (NodeCount - 1) * 2 );
					}
	
	
	//				Link[CurrentShot]->Length = RopeLength[CurrentShot];
					Link[CurrentShot]->Length = Real( 32 ) * Scale;
					Link[CurrentShot]->SetActive();
					Shot[CurrentShot]->Hard[ 0 ].Lock( *Shot[CurrentShot] );
	
					// * - Advance the current shot //
					CurrentShot++;
					CurrentShot &= 1;
				}
			}
			// Hit Enemy (or something/self) //
			else if ( Shot[CurrentShot]->Sphere[ 0 ].Flags.Object() ) {
				// Temporarily for now, remove it //
				Shot[CurrentShot]->Hard[ 0 ].Unlock();
				Shot[CurrentShot]->Flags.SetInactive();
				Link[CurrentShot]->SetInactive();
			}
		}
	}
	
	// The Link length shrinking code //
//	for( int idx = 0; idx < 2; idx++ ) {
//		// If it has hit something //
//		if ( Shot[idx]->Hard[ 0 ].IsActive() ) {
//			// Decrease it's length if it has contracted //
//			Real Length = ( Shot[idx]->Pos( 0 ) - SphereObject->Pos( 0 ) ).Magnitude();
//			if ( Length < Link[idx]->Length )
//				Link[idx]->Length = Length;
//			if ( Link[CurrentShot]->Length < Real( 32 ) )
//				Link[CurrentShot]->Length = Real( 32 );
//		}
//	}

	// Variation with Joypad //
	{
		// Pressing of the fire button //
		//if ( input::ButtonNew == bitFire ) {
		if ( Input::Pad[MyPad].Button[ GAMEPAD_SHOOT ].Pressed() ) {
			//Vector2D StickNormal = input::Stick.Normal();
			Vector2D StickNormal = Input::Pad[MyPad].Stick1.Normal();
			if ( StickNormal.MagnitudeSquared() != Real::Zero ) {
				if ( !Shot[0]->Flags.IsActive() ) {
					CurrentShot = 0;
				}
				else if ( !Shot[1]->Flags.IsActive() ) {
					CurrentShot = 1;
				}
				
				Shot[CurrentShot]->Pos( 0 ) = SphereObject->Pos( 0 ) + (Real( 64 ) * StickNormal);
				Shot[CurrentShot]->Old( 0 ) = Shot[CurrentShot]->Pos( 0 ) - (StickNormal * (Real( 32 ) * Scale));
				
				for ( size_t idx = 1; idx < 16; idx++ ) {
					Shot[CurrentShot]->Pos( idx ) = Shot[CurrentShot]->Pos( 0 );
					Shot[CurrentShot]->Old( idx ) = Shot[CurrentShot]->Old( 0 );
				}
				for ( size_t idx = 0; idx < Shot[CurrentShot]->Spring.size(); idx++ ) {
					Shot[CurrentShot]->Spring[ idx ].Length = 0;
				}
				
				Shot[CurrentShot]->ResetFriction( 0 );
				Shot[CurrentShot]->Hard[ 0 ].Unlock();
				Shot[CurrentShot]->Flags.SetActive();
				Link[CurrentShot]->SetInactive();
			}
		}
		// Pressing of the Release button //
		//if ( input::ButtonNew == bitRelease ) {
		if ( Input::Pad[MyPad].Button[ GAMEPAD_RELEASE_NEXT ].Pressed() ) {
			//for( int idx = 0; idx < 2; idx++ )
			if ( !Shot[0]->Flags.IsActive() ) {
				CurrentShot = 1;
			}
			else if ( !Shot[1]->Flags.IsActive() ) {
				CurrentShot = 0;
			}
	
			int idx = CurrentShot;
			{
				Shot[idx]->Hard[ 0 ].Unlock();
				Shot[idx]->Flags.SetInactive();
				Link[idx]->SetInactive();
	
				// Advance the current shot //
				CurrentShot++;
				CurrentShot &= 1;
			}
		}

//		if ( input::Button == bitShrink ) {
//			Scale -= Real( 0.02 );
//		}
//		else if ( input::Button == bitGrow ) {
//			Scale += Real( 0.02 );
//		}
	}

//	// Varation with Mouse //
//	{
//		// Pressing of the fire button //
//		//if ( input::ButtonNew & bit24 ) {
//		//if ( Input::Mouse.Button[0].Pressed() ) {
//		if ( Input::Button[MOUSE_1].Pressed() ) {
//			//Vector2D StickNormal( Input::MouseDevice.Axis[0].Current() - Real::Half, -Input::MouseDevice.Axis[1].Current() + Real::Half);
//			//StickNormal.Normalize();
//			
////			Vector2D StickNormal = Input::Mouse.Normal();
//
//			Vector2D StickNormal( Input::Mouse.x - Real::Half, -Input::Mouse.y + Real::Half);
//			StickNormal.Normalize();
//			
//			if ( StickNormal.MagnitudeSquared() != Real::Zero ) {
//				if ( !Shot[0]->IsActive() ) {
//					CurrentShot = 0;
//				}
//				else if ( !Shot[1]->IsActive() ) {
//					CurrentShot = 1;
//				}
//				
//				Shot[CurrentShot]->Pos( 0 ) = SphereObject->Pos( 0 ) + (Real( 72 ) * StickNormal);
//				Shot[CurrentShot]->Old( 0 ) = Shot[CurrentShot]->Pos( 0 ) - (StickNormal * Real( 12 ));
//				
//				Shot[CurrentShot]->ResetFriction( 0 );
//				Shot[CurrentShot]->Hard[ 0 ].Unlock();
//				Shot[CurrentShot]->SetActive();
//				Link[CurrentShot]->SetInactive();
//			}
//		}
//		// Pressing of the Release button //
//		//if ( input::ButtonNew == bit25 ) {
//		if ( Input::Mouse.Button[1].Pressed() ) {
//			//for( int idx = 0; idx < 2; idx++ )
//			if ( !Shot[0]->IsActive() ) {
//				CurrentShot = 1;
//			}
//			else if ( !Shot[1]->IsActive() ) {
//				CurrentShot = 0;
//			}
//	
//			int idx = CurrentShot;
//			{
//				Shot[idx]->Hard[ 0 ].Unlock();
//				Shot[idx]->SetInactive();
//				Link[idx]->SetInactive();
//	
//				// Advance the current shot //
//				CurrentShot++;
//				CurrentShot &= 1;
//			}
//		}
//	}

/*
	// Variation with Joypad //
	{
		// Pressing of the fire button //
		if ( input::ButtonNew == bit0 ) {
			// A - This button does my sidemost shot //
			if ( Shot[0]->Pos( 0 ).x < Shot[1]->Pos( 0 ).x )
				CurrentShot = 0;
			else
				CurrentShot = 1;

			// B - Same shot belongs to same button //
//			CurrentShot = 0;
			Vector2D StickNormal = input::Stick.Normal();
			if ( StickNormal.MagnitudeSquared() != Real::Zero ) {
				Shot[CurrentShot]->Pos( 0 ) = SphereObject->Pos( 0 ) + (Real( 72 ) * StickNormal);
				Shot[CurrentShot]->Old( 0 ) = Shot[CurrentShot]->Pos( 0 ) - (StickNormal * Real( 12 ));
				
				Shot[CurrentShot]->ResetFriction( 0 );
				Shot[CurrentShot]->Hard[ 0 ].Unlock();
				Shot[CurrentShot]->SetActive();
				Link[CurrentShot]->SetInactive();
			}
		}

		// Pressing of the fire button //
		if ( input::ButtonNew == bit1 ) {
			// A - This button does my sidemost shot //
			if ( Shot[0]->Pos( 0 ).x < Shot[1]->Pos( 0 ).x )
				CurrentShot = 1;
			else
				CurrentShot = 0;

			// B - Same shot belongs to same button //
//			CurrentShot = 1;
			Vector2D StickNormal = input::Stick.Normal();
			if ( StickNormal.MagnitudeSquared() != Real::Zero ) {
				Shot[CurrentShot]->Pos( 0 ) = SphereObject->Pos( 0 ) + (Real( 72 ) * StickNormal);
				Shot[CurrentShot]->Old( 0 ) = Shot[CurrentShot]->Pos( 0 ) - (StickNormal * Real( 12 ));
				
				Shot[CurrentShot]->ResetFriction( 0 );
				Shot[CurrentShot]->Hard[ 0 ].Unlock();
				Shot[CurrentShot]->SetActive();
				Link[CurrentShot]->SetInactive();
			}
		}
	}

	// Varation with Mouse //
	{
		// Pressing of the fire button //
		if ( input::ButtonNew == bit24 ) {
			// A - This button does my sidemost shot //
			if ( Shot[0]->Pos( 0 ).x < Shot[1]->Pos( 0 ).x )
				CurrentShot = 0;
			else
				CurrentShot = 1;

			// B - Same shot belongs to same button //
//			CurrentShot = 0;
			Vector2D StickNormal = input::Mouse.Normal();
			if ( StickNormal.MagnitudeSquared() != Real::Zero ) {
				Shot[CurrentShot]->Pos( 0 ) = SphereObject->Pos( 0 ) + (Real( 72 ) * StickNormal);
				Shot[CurrentShot]->Old( 0 ) = Shot[CurrentShot]->Pos( 0 ) - (StickNormal * Real( 12 ));
				
				Shot[CurrentShot]->ResetFriction( 0 );
				Shot[CurrentShot]->Hard[ 0 ].Unlock();
				Shot[CurrentShot]->SetActive();
				Link[CurrentShot]->SetInactive();
			}
		}
		
		// Pressing of the fire button //
		if ( input::ButtonNew == bit25 ) {
			// A - This button does my sidemost shot //
			if ( Shot[0]->Pos( 0 ).x < Shot[1]->Pos( 0 ).x )
				CurrentShot = 1;
			else
				CurrentShot = 0;
			
			// B - Same shot belongs to same button //
//			CurrentShot = 1;
			Vector2D StickNormal = input::Mouse.Normal();
			if ( StickNormal.MagnitudeSquared() != Real::Zero ) {
				Shot[CurrentShot]->Pos( 0 ) = SphereObject->Pos( 0 ) + (Real( 72 ) * StickNormal);
				Shot[CurrentShot]->Old( 0 ) = Shot[CurrentShot]->Pos( 0 ) - (StickNormal * Real( 12 ));
				
				Shot[CurrentShot]->ResetFriction( 0 );
				Shot[CurrentShot]->Hard[ 0 ].Unlock();
				Shot[CurrentShot]->SetActive();
				Link[CurrentShot]->SetInactive();
			}
		}
	}

	// Releasing of button causes line to detach //
//	if ( !(input::Button & (bit0 | bit24)) ) {
//		int idx = 0;
//		Shot[idx]->Hard[ 0 ].Unlock();
//		Shot[idx]->SetInactive();
//		Link[idx]->SetInactive();
//	}
//	if ( !(input::Button & (bit1 | bit25)) ) {
//		int idx = 1;
//		Shot[idx]->Hard[ 0 ].Unlock();
//		Shot[idx]->SetInactive();
//		Link[idx]->SetInactive();
//	}
*/


//	// Update Rope Lengths (The tweak buttons) //
//	if ( input::Button & bit3 ) {
//		Link[0]->Length += (Real( 1.5 ) );// + input::TriggerL);
//		Link[1]->Length += (Real( 1.5 ) );// + input::TriggerR);
////		Link[0]->Length = RopeLength[0] * (Real( 0.8 ) );// + input::TriggerL);
////		Link[1]->Length = RopeLength[1] * (Real( 0.8 ) );// + input::TriggerR);
//	}
//	else if ( input::ButtonReleased & bit3 ) {
//		Link[0]->Length = ( Shot[0]->Pos( 0 ) - SphereObject->Pos( 0 ) ).Magnitude();
//		Link[1]->Length = ( Shot[1]->Pos( 0 ) - SphereObject->Pos( 0 ) ).Magnitude();
//	}
//
//	if ( input::Button & bit2 ) {
//		Link[0]->Length -= (Real( 1.5 ) );// + input::TriggerL);
//		Link[1]->Length -= (Real( 1.5 ) );// + input::TriggerR);
////		Link[0]->Length = RopeLength[0] * (Real( 0.8 ) );// + input::TriggerL);
////		Link[1]->Length = RopeLength[1] * (Real( 0.8 ) );// + input::TriggerR);
//	}
//	else if ( input::ButtonReleased & bit2 ) {
//		Link[0]->Length = ( Shot[0]->Pos( 0 ) - SphereObject->Pos( 0 ) ).Magnitude();
//		Link[1]->Length = ( Shot[1]->Pos( 0 ) - SphereObject->Pos( 0 ) ).Magnitude();
//	}


	// Torque Rotational Motion //
	for ( int idx = 0; idx < 16; idx++ ) {	
		SphereObject->AddForce(
			1 + idx, 
			(Input::Pad[MyPad].Stick1.x * Real( 0.2 )) * 
				(SphereObject->Pos( 1 + idx ) - SphereObject->Pos( 0 )).Tangent().Normal()
			);
	}
}	
// - ------------------------------------------------------------------------------------------ - //	
void cSpiderController::Draw() {
	
	// Draw Cursor //
	Gfx::Circle( SphereObject->Pos( 0 ) + (Input::Pad[MyPad].Stick1.Normal() * Real(64) ), Real( 10 ), Gfx::RGBA( 255, 255, 255, 255 ) );
	
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);	

	glBindTexture( GL_TEXTURE_2D, TextureId );
	
	Vector2D BlackBits( 1.0 / 32.0, 1.0 / 32.0 );
	Vector2D GreenBits( 5.0 / 32.0, 1.0 / 32.0 );
	
	Real Outline = Real(3);
	
	for( size_t idx = 0; idx != 15; ++idx )
	{
		Vector3D VertA = Vector3D(
			SphereObject->BoundingRect.Center().x,
			SphereObject->BoundingRect.Center().y,
			0.0
			);
		
		Vector3D VertB = Vector3D(
			SphereObject->Pos( SphereObject->Sphere[ idx + 1 ].Index ).x,
			SphereObject->Pos( SphereObject->Sphere[ idx + 1 ].Index ).y,
			0.0
			);
			
		Vector3D VertC = Vector3D(
			SphereObject->Pos( SphereObject->Sphere[ idx + 2 ].Index ).x,
			SphereObject->Pos( SphereObject->Sphere[ idx + 2 ].Index ).y,
			0.0
			);
			
		Vector3D RayA = VertB - VertA;
		RayA.Normalize();
		Vector3D VertB2 = VertB + (RayA * (SphereObject->Sphere[ idx + 1 ].Radius + Outline));
		VertB += RayA * SphereObject->Sphere[ idx + 1 ].Radius;
		
		Vector3D RayB = VertC - VertA;
		RayB.Normalize();
		Vector3D VertC2 = VertC + (RayB * (SphereObject->Sphere[ idx + 2 ].Radius + Outline));
		VertC += RayB * SphereObject->Sphere[ idx + 2 ].Radius;

		// Green //
		gfx::Face( 
			VertA,
			VertB,
			VertC,
			GreenBits,
			GreenBits,
			GreenBits
			);

		VertA.z = -Real::One;
		VertB2.z = -Real::One;
		VertC2.z = -Real::One;

		// Outline //
		gfx::Face( 
			VertA,
			VertB2,
			VertC2,
			BlackBits,
			BlackBits,
			BlackBits
			);

	}

	Vector3D VertA = Vector3D(
		SphereObject->BoundingRect.Center().x,
		SphereObject->BoundingRect.Center().y,
	 	0.0 
	 	);

	Vector3D VertB = Vector3D(
	 	SphereObject->Pos( SphereObject->Sphere[ 15 + 1 ].Index ).x,
	 	SphereObject->Pos( SphereObject->Sphere[ 15 + 1 ].Index ).y,
	  	0.0
	    );
	Vector3D VertC = Vector3D(
	 	SphereObject->Pos( SphereObject->Sphere[ 1 ].Index ).x,
	 	SphereObject->Pos( SphereObject->Sphere[ 1 ].Index ).y,
	  	0.0 
	  	);

	Vector3D RayA = VertB - VertA;
	RayA.Normalize();
	Vector3D VertB2 = VertB + (RayA * (SphereObject->Sphere[ 15 + 1 ].Radius + Outline));
	VertB += RayA * SphereObject->Sphere[ 15 + 1 ].Radius;
	
	Vector3D RayB = VertC - VertA;
	RayB.Normalize();
	Vector3D VertC2 = VertC + (RayB * (SphereObject->Sphere[ 1 ].Radius + Outline));
	VertC += RayB * SphereObject->Sphere[ 1 ].Radius;
			

	// Green //
	gfx::Face( 
		VertA,
		VertB,
		VertC,
		GreenBits,
		GreenBits,
		GreenBits
		);

	VertA.z = -Real::One;
	VertB2.z = -Real::One;
	VertC2.z = -Real::One;

	// Outline //
	gfx::Face( 
		VertA,
		VertB2,
		VertC2,
		BlackBits,
		BlackBits,
		BlackBits
		);

/*
	// Eyes //
	{
		Vector3D Center(
			SphereObject->BoundingRect.Center().x,
			SphereObject->BoundingRect.Center().y - Real( 8 ),
		 	0.0 
		 	);
		 	
		Vector3D Left(
			-32,
			0.0,
		 	0.0 
		 	);
		 	
		Vector2D P1( 0.0 / 32.0, 24.0 / 32.0 );
		Vector2D P2( 8.0 / 32.0, 24.0 / 32.0 );
		Vector2D P3( 0.0 / 32.0, 32.0 / 32.1 );
		Vector2D P4( 8.0 / 32.0, 32.0 / 32.1 );
		
		Real Size(32);

		// Left //		 	
		gfx::Face( 
			Center + Left + Vector3D( -Size, Size, 0 ),
			Center + Left + Vector3D( Size, Size, 0 ),
			Center + Left + Vector3D( -Size, -Size, 0 ),
			P1,
			P3,
			P2
			);		 

		gfx::Face( 
			Center + Left + Vector3D( -Size, -Size, 0 ),
			Center + Left + Vector3D( Size, Size, 0 ),
			Center + Left + Vector3D( Size, -Size, 0 ),
			P3,
			P4,
			P2
			);

		// Right //		 	
		gfx::Face( 
			Center - Left + Vector3D( -Size, Size, 0 ),
			Center - Left + Vector3D( Size, Size, 0 ),
			Center - Left + Vector3D( -Size, -Size, 0 ),
			P2,
			P4,
			P1
			);		 

		gfx::Face( 
			Center - Left + Vector3D( -Size, -Size, 0 ),
			Center - Left + Vector3D( Size, Size, 0 ),
			Center - Left + Vector3D( Size, -Size, 0 ),
			P4,
			P3,
			P1
			);

		 	
	}
*/

	glDisable(GL_BLEND);	
	glDisable(GL_TEXTURE_2D);		
}
// - ------------------------------------------------------------------------------------------ - //
