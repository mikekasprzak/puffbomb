// - ------------------------------------------------------------------------------------------ - //
// ExitVortex //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Geometry/Matrix.h>

#include "ExitVortex.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
//int cExitVortex::Message( int Msg, cDynamicComponent* const Sender ) {
//	switch ( Id ) {
//		// Camera Boundary //
//		case 1: {
//			
//		}
//
//		// Level Boundary //
//		case 2: {
//			
//		}
//		
//		// ??? //
//		case 3: {
//			if ( _Vs.Body.Pose->Sphere.size() ) {
//				// Uhh //	
//			}
//		}
//	};
//	return 0;
//}
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
			Real( 512 ), Real( 0 ), Real( -0.0 )
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
