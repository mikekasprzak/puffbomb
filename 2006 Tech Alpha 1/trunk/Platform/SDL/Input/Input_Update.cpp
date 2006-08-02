// - ------------------------------------------------------------------------------------------ - //
#include <string>

// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
#include <Util/Debug.h>

#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
namespace Input {
	// - -------------------------------------------------------------------------------------- - //
	SDL_Joystick *SystemJoystick[MAX_SYSTEM_JOYSTICKS];

	// - -------------------------------------------------------------------------------------- - //
	void Init() {
		int JoysticksUsed = 0;
		
		// Zero out our array //
		for( int idx = 0; idx < MAX_SYSTEM_JOYSTICKS; idx++ ) {
			SystemJoystick[ idx ] = 0;
		}
		
		// Use all the XBOX 360 Joysticks first //		
		for( int idx = 0; idx < SDL_NumJoysticks(); idx++ ) {
			// Bail if all our joystick slots are taken //
			if ( JoysticksUsed >= MAX_SYSTEM_JOYSTICKS )
				break;
			
			string StickName = SDL_JoystickName( idx );
			
			if ( StickName.find("XBOX 360") != string::npos ) {
				SystemJoystick[ JoysticksUsed++ ] = SDL_JoystickOpen( idx );
				Log( LOG_HIGHEST_LEVEL,
					"Pad " << (JoysticksUsed - 1) << " is a \"" << SDL_JoystickName( idx ) << "\" **" );
			}
		}
		
		// Use the remaining Joysticks //
		for( int idx = 0; idx < SDL_NumJoysticks(); idx++ ) {
			// Bail if all our joystick slots are taken //
			if ( JoysticksUsed >= MAX_SYSTEM_JOYSTICKS )
				break;

			string StickName = SDL_JoystickName( idx );
			
			if ( StickName.find("XBOX 360") == string::npos ) {
				SystemJoystick[ JoysticksUsed++ ] = SDL_JoystickOpen( idx );
				Log( LOG_HIGHEST_LEVEL,
					"Pad " << (JoysticksUsed - 1) << " is a \"" << SDL_JoystickName( idx ) << "\"" );
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void UnInit() {
	}
	// - -------------------------------------------------------------------------------------- - //
	void Update() {
		// Joypads //
		{
			SDL_JoystickUpdate();
			
			Sint16 Axis[PAD_AXIS_COUNT];
			Uint8 Button[PAD_BUTTON_COUNT];
			Uint8 Hat[2];
				
			// Now, populate our structures //
			for ( int idx = 0; idx < MAX_SYSTEM_JOYSTICKS; idx++ ) {
				if ( SystemJoystick[ idx ] ) {
					// ------------------------------------------ //
					// Clear our Axis //
					for ( int idx2 = 0; idx2 < PAD_AXIS_COUNT; idx2++ ) {
						Axis[ idx2 ] = 0;
					}
					// Clear our Buttons //
					for ( int idx2 = 0; idx2 < PAD_BUTTON_COUNT; idx2++ ) {
						Button[ idx2 ] = 0;
					}
					// Clear our Hats //
					for ( int idx2 = 0; idx2 < 2; idx2++ ) {
						Hat[ idx2 ] = 0;
					}
					// ------------------------------------------ //
					// Get Axis Information //
					for( int idx2 = 0; idx2 < SDL_JoystickNumAxes( SystemJoystick[ idx ] ); idx2++ ) {
						// Bail if too many axis //
						if ( idx2 >= PAD_AXIS_COUNT )
							break;

						Axis[ idx2 ] = SDL_JoystickGetAxis( SystemJoystick[ idx ], idx2 );
						//Log( 10, Axis[ idx2 ] );
					}
					// Get Button Information //
					for( int idx2 = 0; idx2 < SDL_JoystickNumButtons( SystemJoystick[ idx ] ); idx2++ ) {
						// Bail if too many buttons //
						if ( idx2 >= PAD_BUTTON_COUNT )
							break;

						Button[ idx2 ] = SDL_JoystickGetButton( SystemJoystick[ idx ], idx2 );
					}
					// Get HatInformation //
					for( int idx2 = 0; idx2 < SDL_JoystickNumHats( SystemJoystick[ idx ] ); idx2++ ) {
						// Bail if too many hats //
						if ( idx2 >= 2 )
							break;

						Hat[ idx2 ] = SDL_JoystickGetHat( SystemJoystick[ idx ], idx2 );
					}
					// ------------------------------------------ //
					// Do range clamping //
					for ( int idx2 = 0; idx2 < PAD_AXIS_COUNT; idx2++ ) {
						// Fix the limit discontinuity between negative and positive //
						if ( Axis[ idx2 ] == -32768 )
							Axis[ idx2 ] = -32767;
							
//						// Account for error when the pad is centered //
//						if ( abs( Axis[ idx2 ] ) < (1 << 13) )
//							Axis[ idx2 ] = 0;
					}

					// ------------------------------------------ //
					// Write it //
					// ------------------------------------------ //
					// Calculate //
					Vector2D Stick1( Real(Axis[0]) / Real(32767), Real(-Axis[1]) / Real(32767) );
					// Clamp //
					if ( Stick1.Magnitude() < Real( 0.25 ) )
						Stick1 = Vector2D::Zero;
					// Write //
					Pad[ idx ].Stick1.Update( Stick1 );

					// Calculate //
					Vector2D Stick2( Real(Axis[3]) / Real(32767), Real(-Axis[4]) / Real(32767) );
					// Clamp //
					if ( Stick2.Magnitude() < Real( 0.25 ) )
						Stick2 = Vector2D::Zero;
					// Write //
					Pad[ idx ].Stick2.Update( Stick2 );


					int DPadX = 0;
					int DPadY = 0;
					
					if ( Hat[0] & SDL_HAT_UP )
						DPadY = 1;
					else if ( Hat[0] & SDL_HAT_DOWN )
						DPadY = -1;
					
					if ( Hat[0] & SDL_HAT_RIGHT )
						DPadX = 1;
					else if ( Hat[0] & SDL_HAT_LEFT )
						DPadX = -1;

					Pad[ idx ].DPad.Update(
						Vector2D( Real( DPadX ), Real( DPadY ) )
						);

					Pad[ idx ].Trigger.Update( Real(Axis[2]) / Real(32767) );
					
					for( int idx2 = 0; idx2 < PAD_BUTTON_COUNT; idx2++ ) {
						Pad[ idx ].Button[ idx2 ].Update( Button[ idx2 ] == 1 );
					}
					// ------------------------------------------ //
				}
			}
			
		}
		
		// Mouse //
		{
			int x, y;
			int Button = SDL_GetMouseState( &x, &y );
			
			Mouse.Update(
				Vector2D(
					Real( x ) / Real( Platform::ScreenW ),
					Real( y ) / Real( Platform::ScreenH )
					)
				);
				
			Mouse.Wheel.Update();
					
			Mouse.Button[0].Update( Button & SDL_BUTTON(1) );
			Mouse.Button[1].Update( Button & SDL_BUTTON(3) );
			Mouse.Button[2].Update( Button & SDL_BUTTON(2) );
		}
		
		// Keyboard //
		{
			int NumKeys = 0;
			unsigned char* KeyState = SDL_GetKeyState( &NumKeys );
			
			for ( int idx = 0; idx < NumKeys; idx++ ) {
				Keyboard.Button[ idx ].Update( KeyState[ idx ] != 0 );
			}
		}
		
		// Populate Virtual Joysticks //
		{
			
		}
	}
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
