// - ------------------------------------------------------------------------------------------ - //
// Distortion //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include "Distortion.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
//int cDistortion::Message( int Msg, cDynamicComponent* const Sender ) {
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
bool cDistortion::Work() {
	// Step pulse rate timer //
	
	// On pulse match, impulse //
	
	Engine2D::cEngine2D::Current->Impulse.push_back( 
		Engine2D::cImpulse(
			Pos,
			// Inner Radius, Intensity, Tangent //
			Real( 0 ), Real( -2 ), Real( 0.5 ),
			// Outer Radius, Intensity, Tangent //
			Real( 512 ), Real( 0 ), Real( 0.1 )
			)
		);
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
