// - ------------------------------------------------------------------------------------------ - //
// Distortion //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include "Distortion.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
//void cDistortion::Action( cDynamicComponent& _Vs ) {
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
//}
// - ------------------------------------------------------------------------------------------ - //
bool cDistortion::Work() {
	// Step pulse rate timer //
	
	// On pulse match, impulse //
	
	Engine2D::cEngine2D::Current->Impulse.push_back( 
		Engine2D::cImpulse(
			Pos,
			// Inner Radius, Intensity, Tangent //
			Real( 0 ), Real( -2 ), Real( 0.2 ),
			// Outer Radius, Intensity, Tangent //
			Real( 1312 ), Real( 0 ), Real( 0.2 )
			)
		);
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
