// - ------------------------------------------------------------------------------------------ - //
// Input //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Input_Input_H__
#define __Input_Input_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Input/Keys.h>
#include "UserKeys.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Button.h"
#include "Axis.h"
#include "Wheel.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "KeyboardDevice.h"
#include "MouseDevice.h"
#include "PadDevice.h"
// - ------------------------------------------------------------------------------------------ - //

namespace Input {
	// - -------------------------------------------------------------------------------------- - //
	// A platform dependant function for initializing input capabilities of the system //
	extern void Init();
	
	// A platform dependant function for populating the contents of the Keyboard, Mouse and Pad's //
	extern void Update();
	// - -------------------------------------------------------------------------------------- - //
	extern cKeyboardDevice Keyboard;
	extern cMouseDevice Mouse;
	extern cPadDevice Pad[15];
	// - -------------------------------------------------------------------------------------- - //
};

// - ------------------------------------------------------------------------------------------ - //
#include "ButtonLayer.h"
// - ------------------------------------------------------------------------------------------ - //

namespace Input {
	extern cButtonLayer Button;
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Input_Input_H__ //
// - ------------------------------------------------------------------------------------------ - //
