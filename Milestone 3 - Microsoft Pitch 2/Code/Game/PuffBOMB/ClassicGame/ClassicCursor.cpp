// - ------------------------------------------------------------------------------------------ - //
#include "ClassicCursor.h"
// - ------------------------------------------------------------------------------------------ - //
#include "ClassicGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Graphics/Gfx.h>

#include <Util/Debug.h>

#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cClassicCursor::cClassicCursor() :
	Engine( dynamic_cast<cClassicGameEngine*>(Engine2D::cEngine2D::Current) ),
	Selection( -1 ),
	BombLimit( 5 ),
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
	// Camera control //
	{
		// Zoom the camera //
		if( Input::Pad[ 0 ].Button[ PAD_Y ] ) { 
			Engine->Camera->MinZoom = Global::HudZoom * Real( 3.5 );
		}
		// Don't Zoom the camera //
		else {
			Engine->Camera->MinZoom = Global::HudZoom * Real( 2.5 );
		}
	}


	// Cursor/Bomb Motion (Left Stick and DPad) //
	{
		// With no bomb selection //
		if ( Selection == -1 ) {
			// Update Cursor //
			if ( Input::Pad[0].Button[ PAD_R ] ) {
				Pos += Input::Pad[0].Stick1 * Real(64);
			}
			else {
				Pos += Input::Pad[0].Stick1 * Real(16);
			}
			
			Pos += Input::Pad[0].DPad.KeyRepeat() * Real(1);
		}
		// With a bomb selected //
		else {
			// Update Bomb Pos //
			if ( Input::Pad[0].Button[ PAD_R ] ) {
				Bomb[ Selection ].Pos += Input::Pad[0].Stick1 * Real(16);
			}
			else {
				Bomb[ Selection ].Pos += Input::Pad[0].Stick1 * Real(4);
			}
			Bomb[ Selection ].Pos += Input::Pad[0].DPad.KeyRepeat() * Real(1);
			
			PushMeOutOfOtherBombs( Selection );
						
			// Update Cursor //
			Pos = Bomb[ Selection ].Pos;
		}
	}	
	
	
	// Bomb Timers //
	{
		if ( Selection != -1 ) {
			// Adjust timer based on pressing of the L/P triggers //
			Bomb[ Selection ].Time += (int)Input::Pad[0].Trigger.KeyRepeat();
				
			if ( Bomb[ Selection ].Time < 0 )
				Bomb[ Selection ].Time = 0;
	
			if ( Bomb[ Selection ].Time > 47 )
				Bomb[ Selection ].Time = 47;
		}
	}
	

	// Bomb selection and removal buttons //
	{
		// If Action/Select Button Pressed (A) //
		if ( Input::Pad[0].Button[ PAD_A ].Pressed() ) {
			// If you have no selection //
			if ( Selection == -1 ) {
				// If there isn't a bomb alread here //
				if ( CanPlaceBombHere() ) {
					// As long as we have less than the maximum number of bombs for this level //
					if ( BombLimit > (int)Bomb.size() ) {
						// Add a bomb //
						Bomb.push_back( cBombInfo( Pos ) );
						Selection = Bomb.size() - 1;
						
						// Remove a Bomb from the hud //
						Engine->ClockHud.RemoveBomb();
					}
				}
				// If there is //
				else {
					Selection = WhatBombIsHere();
					if ( Selection != -1 ) {
						Pos = Bomb[ Selection ].Pos;
					}
				}
			}
			else {
				Selection = -1;
			}
		}
	
		// If Delete Button Pressed //
		if ( Input::Pad[0].Button[ PAD_B ].Pressed() ) {
			// If you have a selection //
			if ( Selection != -1 ) {
				// Remove this bomb //
				Bomb.erase( Bomb.begin() + Selection );
				Selection = -1;
				
				// Add a Bomb to the hud //
				Engine->ClockHud.AddBomb();				
			}
			// Or make a selection if there's a bomb that can be selected here //
			else {
				Selection = WhatBombIsHere();
				if ( Selection != -1 ) {
					Pos = Bomb[ Selection ].Pos;
				}
			}
		}
	}


	// Bomb selection hotkeys //
	{
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
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicCursor::Draw() {
	Gfx::EnableTex2D();
	
	// Draw Bomb Graphics //
	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
		//Gfx::Circle( Bomb[ idx ].Pos, Real(48), Gfx::RGBA( 255, 0, 0, 255 ) );
		//BombGraphic.Step();
		
		Real MeterSize = Real( 0.7 );
		if ( Selection != -1 ) {
			if ( Selection == (int)idx ) {
				MeterSize = Real( 1.5 );
			}
		}
		
		
		BombGraphic.DrawQuad( Bomb[ idx ].Pos );
		

		Gfx::Color OverColor = 0;
		Gfx::Color UnderColor = 0;
			
		switch ( Bomb[ idx ].Time >> 4 ) {
			case 0: {
				OverColor = Gfx::RGBA( 0, 0, 255, 142 );
				UnderColor = Gfx::RGBA( 0, 0, 0, 0 );
				break;
			}
			case 1: {
				OverColor = Gfx::RGBA( 255, 255, 0, 142 );
				UnderColor = Gfx::RGBA( 0, 0, 255, 142 );
				break;
			}
			case 2: {
				OverColor = Gfx::RGBA( 0, 255, 0, 142 );
				UnderColor = Gfx::RGBA( 255, 255, 0, 142 );
				break;
			}
		};
			

		if ( UnderColor != 0 ) {
			BombTimer.SetFrame( 15 );
			BombTimer.DrawQuad( Bomb[ idx ].Pos, UnderColor, MeterSize );
		}
		
		BombTimer.SetFrame( (Bomb[ idx ].Time) & 15 );
		BombTimer.DrawQuad( Bomb[ idx ].Pos, OverColor, MeterSize );
		
		//BombTab.DrawQuad( Bomb[ idx ].Pos, Gfx::White(), MeterSize );
	}
	
	Gfx::DisableTex2D();
	Gfx::DisableDepth();
	
	Gfx::SetLineWidth( 2 );

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

		// Thick Black outline //
		Gfx::SetLineWidth( 4 );	
		Gfx::Rect( Pos - Real(20), Pos + Real(20), Gfx::RGBA( 0, 0, 0, 255 ) );

		Gfx::SetLineWidth( 2 );		
		Gfx::Rect( Pos - Real(20), Pos + Real(20), Gfx::RGBA( 255, 255, 255, 255 ) );
	}
	else {
		Gfx::SetLineWidth( 4 );
		Gfx::Rect( Bomb[ Selection ].Pos - Real(50), Bomb[ Selection ].Pos + Real(50), Gfx::RGBA( 0, 0, 0, 255 ) );


		Gfx::SetLineWidth( 2 );
		Gfx::Rect( Bomb[ Selection ].Pos - Real(50), Bomb[ Selection ].Pos + Real(50), Gfx::RGBA( 0, 255, 0, 255 ) );
	}

	Gfx::SetLineWidth( 1 );

	// Draw Bomb Timers //
//	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
//		Gfx::Rect( Bomb[ idx ].Pos + Vector2D( -60, -60 ), Bomb[ idx ].Pos + Vector2D( -60 + (Bomb[ idx ].Time*4), -44 ), Gfx::RGBA( 255, 255, 0, 255 ) );
//	}
	
	Gfx::EnableTex2D();
	Gfx::EnableDepth();
}
// - ------------------------------------------------------------------------------------------ - //
bool cClassicCursor::CanPlaceBombHere( const Vector2D& _Pos ) const {
	for ( size_t idx = 0; idx < Bomb.size(); idx++ ) {
		if ( (Bomb[ idx ].Pos - _Pos).MagnitudeSquared() < Real(64+64) * Real(64+64) )
			return false;
	}	
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
int cClassicCursor::WhatBombIsHere( const Vector2D& _Pos ) const {
	int NearestBomb = -1;
	Real BestDistance( 64*64 );
	
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
		if ( _Selection == (int)idx )
			continue;
			
		Vector2D BombDiff = Bomb[ idx ].Pos - Bomb[ _Selection ].Pos;
		
		Real RadiusSum = Real(64) + Real(64);
		Real RadiusSumSquared = RadiusSum * RadiusSum;
		
		if ( BombDiff.MagnitudeSquared() < RadiusSumSquared ) {
			Bomb[ _Selection ].Pos -= BombDiff.Normal() * (RadiusSum - BombDiff.Magnitude());
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
