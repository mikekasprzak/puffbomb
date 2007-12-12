// - ------------------------------------------------------------------------------------------ - //
// ExitVortex //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Math/Matrix.h>

#include "ExitVortex.h"
#include <Engine2D.h>

#include <Particle2D/FXLibrary.h>
// - ------------------------------------------------------------------------------------------ - //
int cExitVortex::Message( int Msg, Engine2D::cDynamicComponent* const Sender ) {
	switch ( Msg ) {
		// Impact //
		case 1: {
			// Check who it is //
			switch( int SubMsg = Sender->Parent->Message( 2, (Engine2D::cPassiveObject*)this ) ) {
				// An object that is collectable //
				case 21: {
					Sender->SetInactive();
					FXLibrary::EnterVortex( Sender->Body.BoundingRect.Center(), 0 );
					break;
				};
				// An object that is a collectable requirement //
				case 22: {
					Sender->SetInactive();
					Engine2D::cEngine2D::Current->Message( 2, this );
					FXLibrary::EnterVortex( Sender->Body.BoundingRect.Center(), 1 );
					break;
				};
				// The object will clean itself up //
				case 23: {
					break;
				};
			};
			break;
		};
		// Who am I? //
		case 2: {
			
			return 20;
			break;
		};
	};
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cExitVortex::StepAnimation() {
	if( Animator.Animation ) {
		Animator.Step();
	}
	
	if( Face.Animation ) {
		Face.Step();
	}	
}
// - ------------------------------------------------------------------------------------------ - //
bool cExitVortex::Work() {
	// Step pulse rate timer //
	
	// On pulse match, impulse //
	
	Engine2D::cEngine2D::Current->Impulse.push_back( 
		Engine2D::cImpulse(
			Pos,
			// Inner Radius, Intensity, Tangent //
			Real( 0 ), Real( -0.4 ), Real( -0.0 ),
			// Outer Radius, Intensity, Tangent //
			Real( 512+64 ), Real( 0 ), Real( -0.0 )
			)
		);
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
void cExitVortex::Draw() {
	// Draw the animation //
	if( Animator.Animation ) {
		Animator.DrawQuad( Pos, Matrix2x2::Rotate( CommonClock ) );
		Animator.DrawQuad( Pos, Matrix2x2::RotateScale( (CommonClock + Real( 0.0625 )), Real( 0.8 ) ) );
		Animator.DrawQuad( Pos, Matrix2x2::RotateScale( (CommonClock + Real( 0.0625 )) * Real( 2 ), Real( 0.7 ) ) );
		if ( Face.Animation ) {
			Face.DrawQuad( Pos );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
