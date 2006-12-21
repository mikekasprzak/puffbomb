// - ------------------------------------------------------------------------------------------ - //
#include "ClassicCursor.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Graphics/Gfx.h>

#include <Util/Debug.h>

#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cClassicCursor::cClassicCursor() :
	Selection( -1 ),
	TimeMode( false ),
	BombGraphic( "BlueBomb.anim" ),
	BombTimer( "BombTimer.anim" ),
	BombTab( "BombTimer_CoverTab.anim" )
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
		Engine2D::cEngine2D::Current->Camera->MinZoom = Global::HudZoom * Real( 2 );
		
		// Update Cursor //
		Pos += Input::Pad[0].Stick1 * Real(16);
	}
	else {
		Engine2D::cEngine2D::Current->Camera->MinZoom = (Global::HudZoom * Real( 2 )) - Real( 500 );
		
		if ( TimeMode ) {
			Bomb[ Selection ].Time += ((int)Input::Pad[0].Stick1.x);
				
			if ( Bomb[ Selection ].Time < 0 )
				Bomb[ Selection ].Time = 0;

			if ( Bomb[ Selection ].Time > 47 )
				Bomb[ Selection ].Time = 47;
		}
		else {
			// Update Bomb Pos //
			Bomb[ Selection ].Pos += Input::Pad[0].Stick1 * Real(4);
			PushMeOutOfOtherBombs( Selection );
						
			// Update Cursor //
			Pos = Bomb[ Selection ].Pos;
		}
	}
		
	// If Action Button Pressed (A) //
	if ( Input::Pad[0].Button[ PAD_A ].Pressed() ) {
		// If you have no selection //
		if ( Selection == -1 ) {
			// If there isn't a bomb alread here //
			if ( CanPlaceBombHere() ) {
				// Add a bomb //
				Bomb.push_back( cBombInfo( Pos ) );
				Selection = Bomb.size() - 1;
				TimeMode = false;
			}
			// If there is //
			else {
				Selection = WhatBombIsHere();
				TimeMode = false;
				if ( Selection != -1 ) {
					Pos = Bomb[ Selection ].Pos;
				}
			}
		}
		else {
			TimeMode = false;
			
//			if ( !TimeMode ) {
//				TimeMode = true;
//			}
//			else {
//				Selection = -1;
//			}
		}
	}

	// If Timer Button Pressed (X) //
	if ( Input::Pad[0].Button[ PAD_X ].Pressed() ) {
		// If you have no selection //
		if ( Selection == -1 ) {
			// If there isn't a bomb alread here //
			if ( CanPlaceBombHere() ) {
//				// Add a bomb //
//				Bomb.push_back( cBombInfo( Pos ) );
//				Selection = Bomb.size() - 1;
//				TimeMode = true;
			}
			// If there is //
			else {
				Selection = WhatBombIsHere();
				TimeMode = true;
				if ( Selection != -1 ) {
					Pos = Bomb[ Selection ].Pos;
				}
			}
		}
		else {
			TimeMode = true;

//			if ( !TimeMode ) {
//				TimeMode = true;
//			}
//			else {
//				Selection = -1;
//			}
		}
	}
	// If Back Button Pressed (B) //
	if ( Input::Pad[0].Button[ PAD_B ].Pressed() ) {
		// Deselect, if you had a selection //
		Selection = -1;
	}

	// If Delete Button Pressed (Y) //
	if ( Input::Pad[0].Button[ PAD_Y ].Pressed() ) {
		// If you have a selection //
		if ( Selection != -1 ) {
			// Remove this bomb //
			Bomb.erase( Bomb.begin() + Selection );
			Selection = -1;
		}
		// Or make a selection if there's a bomb that can be selected here //
		else {
			Selection = WhatBombIsHere();
			TimeMode = false;
			if ( Selection != -1 ) {
				Pos = Bomb[ Selection ].Pos;
			}
		}
	}
	
	// If there are bombs to select //
	if ( Bomb.size() > 0 ) {
		// Quick select Previous/Last Bomb //
		if ( Input::Pad[0].Button[ PAD_L ].Pressed() ) {
			// If no selection //
			if ( Selection == -1 ) {
				Selection = Bomb.size() - 1;
			}
			// If a selection //
			else {
				Selection--;
				// If this puts us under, loop around //
				if ( Selection < 0 ) {
					Selection = Bomb.size() - 1;
				}
			}
			
			// Pull the cursor position from the now currently selected bomb //
			Pos = Bomb[ Selection ].Pos;
		}

		// Quick select Next/First Bomb //
		if ( Input::Pad[0].Button[ PAD_R ].Pressed() ) {
			// If no selection //
			if ( Selection == -1 ) {
				Selection = 0;
			}
			// If a selection //
			else {
				Selection++;
				// If this puts us under, loop around //
				if ( Selection > (int)Bomb.size() - 1 ) {
					Selection = 0;
				}
			}
			
			// Pull the cursor position from the now currently selected bomb //
			Pos = Bomb[ Selection ].Pos;
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicCursor::Draw() {
	Gfx::DisableTex2D();
//	Gfx::DisableDepth();

	// Draw the cursor //
	if ( Selection == -1 ) {
		if ( WhatBombIsHere() == -1 ) {
			// A bomb is or isn't too close //
			Gfx::Circle( Pos, Real(10), CanPlaceBombHere() ? Gfx::RGBA( 255, 255, 255, 255 ) : Gfx::RGBA( 255, 0, 0, 255 ) );
		}
		else {
			// A bomb I can select //
			Gfx::Circle( Pos, Real(10), Gfx::RGBA( 0, 255, 0, 255 ) );
		}
		
		Gfx::Rect( Pos - Real(20), Pos + Real(20), Gfx::RGBA( 255, 255, 255, 255 ) );
	}
	else {
		Gfx::Rect( Bomb[ Selection ].Pos - Real(50), Bomb[ Selection ].Pos + Real(50), TimeMode ? Gfx::RGBA( 0, 64, 255, 255 ) : Gfx::RGBA( 0, 255, 0, 255 ) );
	}


	Gfx::EnableTex2D();
	
	// Draw Bomb Graphics //
	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
		//Gfx::Circle( Bomb[ idx ].Pos, Real(48), Gfx::RGBA( 255, 0, 0, 255 ) );
		//BombGraphic.Step();
		BombGraphic.DrawQuad( Bomb[ idx ].Pos );
		

		Gfx::Color OverColor;
		Gfx::Color UnderColor;
			
		switch ( Bomb[ idx ].Time >> 4 ) {
			case 0: {
				OverColor = Gfx::RGB( 255, 0, 0 );
				UnderColor = Gfx::RGBA( 0, 0, 0, 0 );
				break;				
			}
			case 1: {
				OverColor = Gfx::RGB( 255, 255, 0 );
				UnderColor = Gfx::RGB( 255, 0, 0 );
				break;				
			}
			case 2: {
				OverColor = Gfx::RGB( 0, 255, 0 );
				UnderColor = Gfx::RGB( 255, 255, 0 );
				break;				
			}
		};
			

		if ( UnderColor != 0 ) {
			BombTimer.SetFrame( 15 );
			BombTimer.DrawQuad( Bomb[ idx ].Pos, UnderColor );
		}
		
		BombTimer.SetFrame( (Bomb[ idx ].Time) & 15 );
		BombTimer.DrawQuad( Bomb[ idx ].Pos, OverColor );
		
		BombTab.DrawQuad( Bomb[ idx ].Pos );
	}
	
	Gfx::DisableTex2D();

	// Draw Bomb Timers //
//	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
//		Gfx::Rect( Bomb[ idx ].Pos + Vector2D( -60, -60 ), Bomb[ idx ].Pos + Vector2D( -60 + (Bomb[ idx ].Time*4), -44 ), Gfx::RGBA( 255, 255, 0, 255 ) );
//	}
	
	Gfx::EnableTex2D();
//	Gfx::EnableDepth();
}
// - ------------------------------------------------------------------------------------------ - //
bool cClassicCursor::CanPlaceBombHere( const Vector2D& _Pos ) const {
	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
		if ( (Bomb[ idx ].Pos - _Pos).MagnitudeSquared() < Real(48+48) * Real(48+48) )
			return false;
	}	
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
int cClassicCursor::WhatBombIsHere( const Vector2D& _Pos ) const {
	int NearestBomb = -1;
	Real BestDistance( 48*48 );
	
	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
		Real DistanceToBomb = (Bomb[ idx ].Pos - _Pos).MagnitudeSquared();
		if ( DistanceToBomb < BestDistance ) {
			NearestBomb = idx;
			BestDistance = DistanceToBomb;
		}
	}	

	return NearestBomb;
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicCursor::PushMeOutOfOtherBombs( const int _Selection ) {
	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
		if ( idx == _Selection )
			continue;
			
		Vector2D BombDiff = Bomb[ idx ].Pos - Bomb[ _Selection ].Pos;
		
		Real RadiusSum = Real(48) + Real(48);
		Real RadiusSumSquared = RadiusSum * RadiusSum;
		
		if ( BombDiff.MagnitudeSquared() < RadiusSumSquared ) {
			Bomb[ _Selection ].Pos -= BombDiff.Normal() * (RadiusSum - BombDiff.Magnitude());
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
