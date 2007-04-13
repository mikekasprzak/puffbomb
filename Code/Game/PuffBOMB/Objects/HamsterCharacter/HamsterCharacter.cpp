// - ------------------------------------------------------------------------------------------ - //
// HamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
//#include <Particle2D/SolidParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "HamsterCharacter.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
int cHamsterCharacter::Message( int Msg, Engine2D::cPassiveObject* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			// Check who it is //
			switch( int SubMsg = Sender->Message( 2, (Engine2D::cDynamicComponent*)this ) ) {
				// Pickup //
				case 10 ... 14: {
					Sender->Message( 3, (Engine2D::cDynamicComponent*)this );
					Engine2D::cEngine2D::Current->Message( SubMsg, this );
					break;
				};
//				// Exit Vortex //
//				case 20: {
//					// Disappear //
//					SetInactive();
//					// Increment victory scoring //
//					
//					// Create some sort of disappearing effect //
//					FXLibrary::EnterVortex( Component[ 0 ].Body.BoundingRect.Center(), 1 );
//					
//					break;
//				};
			};
			
			break;
		}
		// Who Are You? //
		case 2: {
			// Check who is asking //
			switch( int SubMsg = Sender->Message( 2, (Engine2D::cDynamicComponent*)this ) ) {
				// Exit Vortex //
				case 20: {
					// I am a collectable character //
					return 22;
					break;
				};
			};
			return 0;
			break;
		}
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
int cHamsterCharacter::Message( int Msg, Engine2D::cDynamicCollection* const /*Sender*/ ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			//Log( 10, "Cowabunga!" );
			break;
		}
		// Who Are You? //
		case 2: {
			return 0;
			break;
		}
	};
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Message( const Engine2D::cImpulse& /*Sender*/ ) {
	// Set a bomb shock animation (30-37) //
	Component[ 0 ].SetAnimation( 30 );
	HasBeenBlownUp = true;
}
// - ------------------------------------------------------------------------------------------ - //
void cHamsterCharacter::Message( const Engine2D::cZone& Sender ) {
	switch ( Sender.Id ) {
		// Win Zone!! //
		case 9: {
			Engine2D::cEngine2D::Current->Message( 2, this );
			
			break;
		}		
		// Fall out, send back to last position //
		case 4: {
			Engine2D::cEngine2D::Current->Message( 4, this );
			
			break;
		}		
		// Fall out, send back to drop point //
		case 5: {
			Engine2D::cEngine2D::Current->Message( 5, this );
			
			break;
		}		
	};
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool cHamsterCharacter::Work() {
	Engine2D::cDynamicComponent& Comp = Component[ 0 ];
	Engine2D::cBody2D& Body = Comp.Body;
	
	// This it a hack that takes advantage of the engine, so to allow me to spawn safely in multi //
	// If I have became an Object Sensor //
	if ( Body.Flags.ObjectSensor() ) {
		// If I have no contact with other objects //
		if ( !Body.CollisionFlags.Object() ) {
			// I no longer need to be an Object Sensor //
			Body.Flags.ResetObjectSensor();
		}
	}
	
	// - -------------------------------------------------------------------------------------- - //
	// Process animation changes based on situations! //
	// - -------------------------------------------------------------------------------------- - //
	// Animation changes that occur after an animation has looped //
	if ( Comp.Animator.AnimationFlags.Looped() ) {
		// If we were in a shock animation, and it's now ended, switch to an in flight //
		if ( Comp.Animator.CurrentAnimation >= 30 ) {
			if ( Comp.Animator.CurrentAnimation <= 37 ) {
				Comp.SetAnimation( 10 );
			}
		}
		
		// If we were in a hit animation, and it's now ended, switch back to in flight //
		if ( Comp.Animator.CurrentAnimation >= 14 ) {
			if ( Comp.Animator.CurrentAnimation <= 21 ) {
				Comp.SetAnimation( 10 );
			}
		}		
	}
	
	
	// Poll Impact potential //
	int ImpactMask = 0;
	
	// Animations as they affect me when *I AM* an ObjectSensor (I.e. ignore object reactions) //
	if ( Body.Flags.ObjectSensor() ) {
		if ( Body.SphereFlags[ TopLeftIndex ].Object() ) {
			ImpactMask |= bit0;
		}
		if ( Body.SphereFlags[ TopRightIndex ].Object() ) {
			ImpactMask |= bit1;
		}
		if ( Body.SphereFlags[ BottomLeftIndex ].Object() ) {
			ImpactMask |= bit2;
		}
		if ( Body.SphereFlags[ BottomRightIndex ].Object() ) {
			ImpactMask |= bit3;
		}
		if ( Body.SphereFlags[ MiddleIndex ].Object() ) {
			ImpactMask |= bit4;
		}
	}
	
	{
		if ( Body.SphereFlags[ TopLeftIndex ].Scenery() ) {
			ImpactMask |= bit0;
		}
		if ( Body.SphereFlags[ TopRightIndex ].Scenery() ) {
			ImpactMask |= bit1;
		}
		if ( Body.SphereFlags[ BottomLeftIndex ].Scenery() ) {
			ImpactMask |= bit2;
		}
		if ( Body.SphereFlags[ BottomRightIndex ].Scenery() ) {
			ImpactMask |= bit3;
		}
		if ( Body.SphereFlags[ MiddleIndex ].Scenery() ) {
			ImpactMask |= bit4;
		}
	}
	
	
	// Animations that activate when the body impacts something //
	{
		// Center and any of the sides dictates a reaction animation //
		if ( ImpactMask & bit4 ) {
			switch ( ImpactMask & (bit0|bit1|bit2|bit3) ) {
				// Corners Only //
				case (bit0): {
					Comp.SetAnimation( 14 );
					break;
				};
				case (bit1): {
					Comp.SetAnimation( 14 );
					break;
				};
				case (bit2): {
					Comp.SetAnimation( 18 );
					break;
				};
				case (bit3): {
					Comp.SetAnimation( 18 );
					break;
				};
			};
		};
		
		if ( HasBeenBlownUp ) {
			switch ( ImpactMask & (bit0|bit1|bit2|bit3) ) {
				// Top //
				case (bit0|bit1): {
					Comp.SetAnimation( 6 );
					break;
				};
				// Left //
				case (bit0|bit2): {
					Comp.SetAnimation( 4 );
					break;
				};					
				// Bottom //
				case (bit2|bit3): {
					Comp.SetAnimation( 2 );
					break;
				};
				// Right //
				case (bit1|bit3): {
					Comp.SetAnimation( 8 );
					break;
				};							
			};
		}
	}
			
	// - -------------------------------------------------------------------------------------- - //
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
