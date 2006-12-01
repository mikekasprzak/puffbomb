// - ------------------------------------------------------------------------------------------ - //
#include "ClassicCursor.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Graphics/Gfx.h>

#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cClassicCursor::cClassicCursor() :
	Selection( -1 )
{
}
// - ------------------------------------------------------------------------------------------ - //
cClassicCursor::~cClassicCursor() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cClassicCursor::Step() {
	// -- User Control -------------- //

	if ( Selection == -1 ) {
		// Update Cursor //
		Pos += Input::Pad[0].Stick1 * Real(16);
	}
	else {
		// Update Cursor //
		Pos += Input::Pad[0].Stick1 * Real(4);
			
		// Update Bomb Pos //
		Bomb[ Selection ].Pos = Pos;
	}
		
	// If Action Button Pressed (A) //
	if ( Input::Pad[0].Button[0].Pressed() ) {
		// If you have no selection //
		if ( Selection == -1 ) {
			// If there isn't a bomb alread here //
			if ( CanPlaceBombHere() ) {
				// Add a bomb //
				Bomb.push_back( cBombInfo( Pos ) );
			}
			// If there is //
			else {
				Selection = WhatBombIsHere();
				Pos = Bomb[ Selection ].Pos;
			}
		}
	}

	// If Back Button Pressed (B) //
	if ( Input::Pad[0].Button[1].Pressed() ) {
		Selection = -1;
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicCursor::Draw() {
	Gfx::DisableTex2D();
	Gfx::DisableDepth();

	// Draw the cursor //
	if ( Selection == -1 ) {
		Gfx::Circle( Pos, Real(10), CanPlaceBombHere() ? Gfx::RGBA( 255, 255, 255, 255 ) : Gfx::RGBA( 255, 0, 0, 255 ) );
		Gfx::Rect( Pos - Real(20), Pos + Real(20), Gfx::RGBA( 255, 255, 255, 255 ) );
	}
	else {
		Gfx::Rect( Bomb[ Selection ].Pos - Real(50), Bomb[ Selection ].Pos + Real(50), Gfx::RGBA( 0, 255, 0, 255 ) );
	}

	// Draw Bomb placeholders //
	for ( int idx = 0; idx < Bomb.size(); idx++ ) {
		Gfx::Circle( Bomb[ idx ].Pos, Real(32), Gfx::RGBA( 255, 0, 0, 255 ) );
		Gfx::Rect( Bomb[ idx ].Pos + Vector2D( -40, -40 ), Bomb[ idx ].Pos + Vector2D( -40 + (Bomb[ idx ].Time*4), -44 ), Gfx::RGBA( 255, 255, 0, 255 ) );
	}
	
	Gfx::EnableTex2D();
	Gfx::EnableDepth();
}
// - ------------------------------------------------------------------------------------------ - //
bool cClassicCursor::CanPlaceBombHere( const Vector2D& _Pos ) const {
	for ( int idx = 0; idx < Bomb.size(); idx++ ) {
		if ( (Bomb[ idx ].Pos - _Pos).MagnitudeSquared() < Real(64) * Real(64) )
			return false;
	}	
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
int cClassicCursor::WhatBombIsHere( const Vector2D& _Pos ) const {
	for ( int idx = 0; idx < Bomb.size(); idx++ ) {
		if ( (Bomb[ idx ].Pos - _Pos).MagnitudeSquared() < Real(64) * Real(64) )
			return idx;
	}	

	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
