// - ------------------------------------------------------------------------------------------ - //
#include "Flow.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cFlow::cFlow()
{

}
// - ------------------------------------------------------------------------------------------ - //
Real cFlow::SetHudData()
{
	// Default is 16:9 Aspect Ratio
	Real HudZoom = 1302.5;
	
	// 16:9
	if( Platform::AspectRatio > Real( 1.75 ) && Platform::AspectRatio < Real( 1.81 ) )
	{
		HudZoom = 1302.5;

		cGlobal::Top = Real( 540.0 );
		cGlobal::Bottom = Real( -540.0 );
		cGlobal::Left = Real( -960.0 );
		cGlobal::Right = Real( 960.0 );
	}
	// 16:10
	else if( Platform::AspectRatio > Real( 1.57 ) && Platform::AspectRatio < Real( 1.63 ) )
	{
		HudZoom = 1447.0;
		
		cGlobal::Top = Real( 600.0 );
		cGlobal::Bottom = Real( -600.0 );
		cGlobal::Left = Real( -960.0 );
		cGlobal::Right = Real( 960.0 );

	}
	// 4:3
	else if( Platform::AspectRatio > Real( 1.30 ) && Platform::AspectRatio < Real( 1.36 ) )
	{
		HudZoom = 1266.0;
		
		cGlobal::Top = Real( 525.0 );
		cGlobal::Bottom = Real( -525.0 );
		cGlobal::Left = Real( -700.0 );
		cGlobal::Right = Real( 700.0 );

	}
	
	// 5:4
	else if( Platform::AspectRatio > Real( 1.22 ) && Platform::AspectRatio < Real( 1.28 ) )
	{
		HudZoom = 1234.0;
		
		cGlobal::Top = Real( 512.0 );
		cGlobal::Bottom = Real( -512.0 );
		cGlobal::Left = Real( -640.0 );
		cGlobal::Right = Real( 640.0 );

	}
	// 3:4 // Tablet pc res //
	else if( Platform::AspectRatio > Real( 0.70 ) && Platform::AspectRatio < Real( 0.79 ) )
	{
		HudZoom = 1690.5;
		
		cGlobal::Top = Real( 700.0 );
		cGlobal::Bottom = Real( -700.0 );
		cGlobal::Left = Real( -525.0 );
		cGlobal::Right = Real( 525.0 );
	}
	
	
	cGlobal::HudH = Real( cGlobal::Top * Real( 2.0 ) );
	cGlobal::HudW = Real( cGlobal::Right * Real( 2.0 ) );
	
	cGlobal::HudZoom = HudZoom;

	return HudZoom;
}
// - ------------------------------------------------------------------------------------------ - //
