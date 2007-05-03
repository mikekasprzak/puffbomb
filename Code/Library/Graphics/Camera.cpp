// - ------------------------------------------------------------------------------------------ - //
#include "Camera.h"

#include <Graphics/Gfx.h>
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
		const Real _HudZoom,
		const Real _XPos,
		const Real _YPos,
		const Real _Width,
		const Real _Height
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
		XPos( _XPos ),
		YPos( _YPos ),
		Width( _Width ),
		Height( _Height ),
		Focus( Vector2D( 0, 0 ) ),
		Delay( 0 ),
		Low( Vector2D( 0, 0 ) ),
		High( Vector2D( 0, 0 ) ),
		CameraBounds( Vector2D( -10000, -10000 ), Vector2D( 20000, 20000 ) ),
		ViewArea( Vector2D( -10, -10 ), Vector2D( 20, 20 ) ),
		IsZoomedOut( false )
{

	Gfx::Viewport( XPos, YPos, Width, Height );
	Gfx::ProjMatrixMode();
	Gfx::LoadIdentity();
	Gfx::Perspective( FovY, Aspect, NearClip, FarClip );
	Gfx::ModelMatrixMode();
	
	GetPos();
	
	DefaultXViewArea = Real( ViewArea._P2.x - ViewArea._P1.x );
	DefaultYViewArea = Real( ViewArea._P2.y - ViewArea._P1.y );
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cCamera::GetPos()
{
	MinZoom = Real( 2.5 ) * HudZoom;

	if( IsZoomedOut )
	{
		// Do the Calculation for Y as well as X !! //
//		Log( LOG_HIGHEST_LEVEL, "Real( ViewArea._P2.x - ViewArea._P1.x ): " << Real( ViewArea._P2.x - ViewArea._P1.x ) );
//		Log( LOG_HIGHEST_LEVEL, "DefaultXViewArea: " << DefaultXViewArea );

		Real TempMinZoomX = ( ( CameraBounds.P2().x - CameraBounds.P1().x ) / DefaultXViewArea ) * MinZoom;

		Real TempMinZoomY = ( ( CameraBounds.P2().y - CameraBounds.P1().y ) / DefaultYViewArea ) * MinZoom;
		
		if( TempMinZoomX < TempMinZoomY )
		{
			MinZoom = TempMinZoomX;
		}
		else
		{
			MinZoom = TempMinZoomY;
		}
		
		
//		MinZoom = ( ( CameraBounds.P2().x - CameraBounds.P1().x ) / Real( 4800 ) ) * MinZoom;
		
		// To Limit the Max Zoom out //
		/*if( MinZoom > HudZoom * Real( 3.5 ) )
		{
			MinZoom = Real( 3.5 ) * HudZoom;
		}*/
	}

	// Gets the position of the tracker //
	Low = Focus;
	High = Focus;

	Vector2D TempPos = Vector2D::Zero;

	TempPos = Focus;
	TempPos -= Tracker;
	
	TempPos *= Real( 0.05 );
	Tracker += TempPos;

	Real TempZoom = ( Low - High ).Manhattan();
	
	// Checks against the Zoom Bounds //
	if( TempZoom < MinZoom )
	{
		TempZoom = MinZoom;
	}
	if( TempZoom > MaxZoom )
	{
		TempZoom = MaxZoom;
	}

	TempZoom -= Pos.z;
	
	TempZoom *= Real( 0.1 );
	 
	Pos.z += TempZoom;

	// Bounds the Camera //
	Real ZoomOffset = Real( Pos.z / HudZoom );
	
	Vector2D P1Value = CameraBounds.P1();
	Vector2D P2Value = CameraBounds.P2();

	Real CheckValue = ( Global::Left * ZoomOffset );
	if( Tracker.x < ( P1Value.x - CheckValue ) )
	{
		Tracker.x = ( P1Value.x - CheckValue );
	}
	ViewArea._P1.x = CheckValue; // Update the ViewArea //
	CheckValue = ( Global::Right * ZoomOffset );
	if( Tracker.x > ( P2Value.x - CheckValue ) )
	{
		Tracker.x = ( P2Value.x - CheckValue );
	}
	ViewArea._P2.x = CheckValue; // Update the ViewArea //
	CheckValue = ( Global::Bottom * ZoomOffset );
	if( Tracker.y < ( P1Value.y - CheckValue ) )
	{
		Tracker.y = ( P1Value.y - CheckValue );
	}
	ViewArea._P1.y = CheckValue; // Update the ViewArea //
	CheckValue = ( Global::Top * ZoomOffset );
	if( Tracker.y > ( P2Value.y - CheckValue ) )
	{
		Tracker.y = ( P2Value.y - CheckValue );
	}
	ViewArea._P2.y = CheckValue; // Update the ViewArea //

	// Sets the position of the camera to the tracker //
	Pos.x = Tracker.x;
	Pos.y = Tracker.y;
	
	View.x = Tracker.x;
	View.y = Tracker.y;

	return Tracker;

}
// - ------------------------------------------------------------------------------------------ - //
void cCamera::UpdateTarget( const Vector2D& _Focus )
{
	Focus = _Focus;

	GetPos();
}
// - ------------------------------------------------------------------------------------------ - //
void cCamera::Update()
{
	Gfx::Viewport( XPos, YPos, Width, Height );
	Gfx::ProjMatrixMode();
	Gfx::LoadIdentity();
	Gfx::Perspective( FovY, Aspect, NearClip, FarClip );
	Gfx::ModelMatrixMode();

	Gfx::LoadIdentity();
	Gfx::Translate( -Pos.x, -Pos.y, -Pos.z );
		
}
// - ------------------------------------------------------------------------------------------ - //
