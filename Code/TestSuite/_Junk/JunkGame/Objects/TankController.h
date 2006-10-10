// - ------------------------------------------------------------------------------------------ - //
// TankController //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_TankController_H__
#define __Game_TankController_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/SphereObject.h>
#include <Phiz/NodeLink.h>

#include <DisplayObjectController.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cTankController: public cDisplayObjectController {
public:
	// Construct, and require an associated SphereObject //
	cTankController(
		cSphereObject* _Object,
		cSphereObject* _Shot1,
		const std::string& File
		);
	
	virtual ~cTankController() {
	}
	
	enum {
		bitFire = bit0,
		//bitRelease = bit1,
		
		bitLeftThrust = bit4,
		bitRightThrust = bit5
	};

	// My Shot //	
	cSphereObject* Shot;
	
	// My Gamepad //
	int MyPad;
	
	// Turret Angles //
	Real Angle;
	Real Power;
	Vector2D AngleVector;
	
		
public:	
	// Your chance to do something //
	virtual void Step();
	
	// Draw him //
	virtual void Draw();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_TankController_H__ //
// - ------------------------------------------------------------------------------------------ - //
