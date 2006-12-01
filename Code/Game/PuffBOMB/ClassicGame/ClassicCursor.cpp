// - ------------------------------------------------------------------------------------------ - //
#include "ClassicCursor.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Graphics/Gfx.h>

#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cClassicCursor::cClassicCursor() :
	Selected( -1 )
{
}
// - ------------------------------------------------------------------------------------------ - //
cClassicCursor::~cClassicCursor() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicCursor::Step() {
	// -- User Control -------------- //

	// Update Cursor //
	Pos += Input::Pad[0].Stick1 * Real(16);
		
	// If button pressed //
	if ( CanPlaceBombHere() ) {
		if ( Input::Pad[0].Button[0].Pressed() ) {
			Log( 10, "Placed!" );
			// Add a bomb //
			Bomb.push_back( cBombInfo( Pos ) );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicCursor::Draw() {
	Gfx::DisableTex2D();
	Gfx::DisableDepth();

	// Draw the cursor //
	Gfx::Circle( Pos, Real(10), CanPlaceBombHere() ? Gfx::RGBA( 255, 255, 255, 255 ) : Gfx::RGBA( 255, 0, 0, 255 ) );
	Gfx::Rect( Pos - Real(20), Pos + Real(20), Gfx::RGBA( 255, 255, 255, 255 ) );

	// Draw Bomb placeholders //
	for ( int idx = 0; idx < Bomb.size(); idx++ ) {
		if ( Bomb[ idx ].Placed ) {
			Gfx::Circle( Bomb[ idx ].Pos, Real(32), Gfx::RGBA( 255, 0, 0, 255 ) );
			Gfx::Rect( Bomb[ idx ].Pos + Vector2D( -40, -40 ), Bomb[ idx ].Pos + Vector2D( -40 + (Bomb[ idx ].Time*4), -44 ), Gfx::RGBA( 255, 255, 0, 255 ) );
		}	
	}
	
	Gfx::EnableTex2D();
	Gfx::EnableDepth();
}
// - ------------------------------------------------------------------------------------------ - //
bool cClassicCursor::CanPlaceBombHere( const Vector2D& _Pos ) {
	for ( int idx = 0; idx < Bomb.size(); idx++ ) {
		if ( Bomb[ idx ].Placed ) {
			if ( (Bomb[ idx ].Pos - _Pos).MagnitudeSquared() < Real(64) * Real(64) )
				return false;
		}	
	}	
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
