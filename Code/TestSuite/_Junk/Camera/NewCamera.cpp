// - ------------------------------------------------------------------------------------------ - //
#include <gl/gl.h>
#include <gl/glu.h>

#include "NewCamera.h"

#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cCamera::cCamera(
	const Vector3D _Pos,
	const Vector3D _View,
	const Vector3D _Up,
	const Real _FovY,
	const Real _Aspect,
	const Real _NearClip,
	const Real _FarClip,
	const Real _MinZoom,
	const Real _MaxZoom,
	const Real _HudZoom
 ) :
		Pos( _Pos ),
		View( _View ),
		Up( _Up ),
		FovY( _FovY ),
		Aspect( _Aspect ),
		NearClip( _NearClip ),
		FarClip( _FarClip ),
		MinZoom( _MinZoom ),
		MaxZoom( _MaxZoom ),
		HudZoom( _HudZoom ),
//		Delay( 0 ),
//		Low( Vector2D( 0, 0 ) ),
//		High( Vector2D( 0, 0 ) ),
		CameraBounds( Vector2D( -1792, -1792 ), Vector2D( 6656, 1280 ) )
{
	glViewport( 0, 0, Global::ScreenW, Global::ScreenH );
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( FovY, Aspect, NearClip, FarClip ); 
	glMatrixMode(GL_MODELVIEW);

}
// - ------------------------------------------------------------------------------------------ - //
//Vector2D cCamera::GetPos()
//{
//	if( Delay > 0 )
//	{
//		if( Delay == 1 )
//		{
//			RemoveTarget( RemoveFocus );
//		}
//		--Delay;
//	}
//	
//	// Gets the position of the tracker //
//	Low = ( *Focus.begin() )->BoundingRect.P1();
//	High = ( *Focus.begin() )->BoundingRect.P2();
//
//	std::list< cSphereObject* >::iterator iter;
//	
//	Vector2D TempPos = Vector2D::Zero;
//	
//	for ( iter = Focus.begin(); iter != Focus.end(); iter++ )
//	{
//		TempPos = (*iter)->BoundingRect.Center();
//		TempPos -= Tracker;
//		
//		TempPos *= Real( 0.05 );
//		Tracker += TempPos;
//		
//		// Set the low and high extremes //
//		Vector2D TempLow = (*iter)->BoundingRect.P1();
//		Vector2D TempHigh = (*iter)->BoundingRect.P2();
//		
//		if( Low.x > TempLow.x )
//		{
//			Low.x = TempLow.x;
//		}
//		if( Low.y > TempLow.y )
//		{
//			Low.y = TempLow.y;
//		}
//
//		if( High.x < TempHigh.x )
//		{
//			High.x = TempHigh.x;
//		}
//		if( High.y < TempHigh.y )
//		{
//			High.y = TempHigh.y;
//		}
//	}
//	Real TempZoom = ( Low - High ).Manhattan();
//	
//	// Checks against the Zoom Bounds //
//	if( TempZoom < MinZoom )
//	{
//		TempZoom = MinZoom;
//	}
//	if( TempZoom > MaxZoom )
//	{
//		TempZoom = MaxZoom;
//	}
//	
//	// Bad Attempt to zoom the camera while moving fast
///*	Real TestValue = 5;
//	
//	if( TempPos.x > TestValue || TempPos.x < -TestValue
//	||  TempPos.y > TestValue || TempPos.y < -TestValue )
//	{
//		TempZoom *= Real( 2.0 );
//	}
//*/
//	TempZoom -= Pos.z;
//	
//	TempZoom *= Real( 0.1 );
//	 
//	Pos.z += TempZoom;
//
//	// Bounds the Camera //
//	Real ZoomOffset = Real( Pos.z / HudZoom );
//	
//	Real CheckValue = ( Global::Left * ZoomOffset );
//	
//	Vector2D P2Value = CameraBounds.P2();// - CameraBounds.P1();
//	
//	if( Tracker.x < ( CameraBounds.P1().x - CheckValue ) )
//	{
//		Tracker.x = ( CameraBounds.P1().x - CheckValue );
//	}
//	CheckValue = ( Global::Right * ZoomOffset );
//	if( Tracker.x > ( P2Value.x - CheckValue ) )
//	{
//		Tracker.x = ( P2Value.x - CheckValue );
//	}
//	CheckValue = ( Global::Bottom * ZoomOffset );
//	if( Tracker.y < ( CameraBounds.P1().y - CheckValue ) )
//	{
//		Tracker.y = ( CameraBounds.P1().y - CheckValue );
//	}
//	CheckValue = ( Global::Top * ZoomOffset );
//	if( Tracker.y > ( P2Value.y - CheckValue ) )
//	{
//		Tracker.y = ( P2Value.y - CheckValue );
//	}
//
//	// Sets the position of the camera to the tracker //
//	Pos.x = Tracker.x;
//	Pos.y = Tracker.y;
//	
//	View.x = Tracker.x;
//	View.y = Tracker.y;
//
//	return Tracker;
//
//}
//// - ------------------------------------------------------------------------------------------ - //
//void cCamera::NewTarget( cSphereObject* _Focus )
//{
//	bool IsNewFocus = true;
//	
//	std::list< cSphereObject* >::iterator iter;
//		
//	for ( iter = Focus.begin(); iter != Focus.end(); iter++ )
//	{
//		if( _Focus == (*iter) )
//		{
//			IsNewFocus = false;	
//		}
//	}
//	
//	if( IsNewFocus )
//	{
//		Focus.push_back( _Focus );
//	}
//	
//	Delay = 0;
//	Low = _Focus->BoundingRect.P1();
//	High = _Focus->BoundingRect.P2();
//}
//// - ------------------------------------------------------------------------------------------ - //
//void cCamera::RemoveTarget( cSphereObject* _Focus )
//{
//	bool IsFocus = false;
//
//	std::list< cSphereObject* >::iterator iter;
//		
//	for ( iter = Focus.begin(); iter != Focus.end(); iter++ )
//	{
//		if( _Focus == (*iter) )
//		{
//			IsFocus = true;
//			break;	
//		}
//	}
//	
//	if( IsFocus )
//	{
//		Focus.erase( iter );
//		Delay = 0;
//		
//		if( !Focus.empty() )
//		{
//			Low = ( *Focus.begin() )->BoundingRect.P1();
//			High = ( *Focus.begin() )->BoundingRect.P2();
//		}
//	}
//}
//// - ------------------------------------------------------------------------------------------ - //
//void cCamera::RemoveTarget( cSphereObject* _Focus, const int _Delay )
//{
//	RemoveFocus = _Focus;
//	Delay = _Delay;
//}
//// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //