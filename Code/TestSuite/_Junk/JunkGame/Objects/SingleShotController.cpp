// - ------------------------------------------------------------------------------------------ - //
#include "SingleShotController.h"

//#include <Util/Input.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cSingleShotController::cSingleShotController( cSphereObject* _Object, cSphereObject* _Shot, cNodeLink* _Link1, const std::string& File ) :
	cObjectController( _Object, File ),
	Shot( _Shot ),
	Link( _Link1 )
{
}
// - ------------------------------------------------------------------------------------------ - //	
void cSingleShotController::Step() {
//
//	// When you've shot your show, test to see if it's collided with anything //
//	if ( Shot->IsActive() ) {
//		// If it has not hit anything yet //
//		if ( !Shot->Hard[ 0 ].IsActive() ) {
//			// Hit Scenery //
//			if ( Shot->Sphere[ 0 ].Flags & cSphere::flScenery ) {
//				// Lock the shot to where it hit and activate the link at a length //
//				Link->Length = ( Shot->Pos( 0 ) - SphereObject->Pos( 0 ) ).Magnitude();
//				Link->SetActive();
//				Shot->Hard[ 0 ].Lock( *Shot );
//			}
//			// Hit Enemy (or something/self) //
//			else if ( Shot->Sphere[ 0 ].Flags & cSphere::flObject ) {
//				// Temporarily for now, remove it //
//				Shot->Hard[ 0 ].Unlock();
//				Shot->SetInactive();
//				Link->SetInactive();
//			}
//		}
//		// If it has hit something //
//		else {
//			// Decrease it's length if it has contracted //
//			Real Length = ( Shot->Pos( 0 ) - SphereObject->Pos( 0 ) ).Magnitude();
//			if ( Length < Link->Length )
//				Link->Length = Length;
//		}
//	}
//
//	// Pressing of the fire button //
//	if ( input::ButtonNew == bit0 ) {
//		Vector2D StickNormal = input::Stick.Normal();
//		if ( StickNormal.MagnitudeSquared() != Real::Zero ) {
//			Shot->Pos( 0 ) = SphereObject->Pos( 0 ) + (Real( 72 ) * StickNormal);
//			Shot->Old( 0 ) = Shot->Pos( 0 ) - (StickNormal * Real( 12 ));
//			
//			//Shot->AddForce( 0, StickNormal * Real( 2 ) );
//			
//			Shot->Hard[ 0 ].Unlock();
//			Shot->SetActive();
//			Link->SetInactive();
//		}
//	}
//	// Pressing of the Release button //
//	if ( input::ButtonNew == bit1 ) {
//		Shot->Hard[ 0 ].Unlock();
//		Shot->SetInactive();
//		Link->SetInactive();
//	}
//
//	// Torque Rotational Motion //
//	for ( int idx = 0; idx < 16; idx++ ) {	
//		SphereObject->AddForce(
//			1 + idx, 
//			(input::Stick.x * Real( 0.1 )) * 
//				(SphereObject->Pos( 1 + idx ) - SphereObject->Pos( 0 )).Tangent().Normal()
//			);
//	}
}	
// - ------------------------------------------------------------------------------------------ - //
