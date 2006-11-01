// - ------------------------------------------------------------------------------------------ - //
// Distortion //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include "Distortion.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
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
void cDistortion::Work() {
	// Step pulse rate timer //
	
	// On pulse match, impulse //
	
	cEngine2D::Current->Impulse.push_back( 
		cImpulse(
			Pos,
			// Inner Radius, Intensity, Tangent //
			Real( 0 ), Real( -4 ), Real( 1 ),
			// Outer Radius, Intensity, Tangent //
			Real( 1512 ), Real( 1 ), Real( 1 )
			)
		);	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
