// - ------------------------------------------------------------------------------------------ - //
// BasicBomb //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include "BasicBomb.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
//void cBasicBomb::Action( cDynamicComponent& _Vs ) {
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
void cBasicBomb::Work() {
	// Count down timer //
	
	// On timer zero, impulse //
	
	Engine2D::cEngine2D::Current->Impulse.push_back( 
		Engine2D::cImpulse(
			Pos,
			// Inner Radius, Intensity, Tangent //
			Real( 0 ), Real( 2 ), Real( 0 ),
			// Outer Radius, Intensity, Tangent //
			Real( 512 ), Real( 0 ), Real( 0 )
			)
		);
		
	// Make sure we don't accidentially impulse again //
}
// - ------------------------------------------------------------------------------------------ - //
