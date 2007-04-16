// - ------------------------------------------------------------------------------------------ - //
// HamsterController //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_HamsterController_H__
#define __Game_HamsterController_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/SphereObject.h>
#include <Phiz/NodeLink.h>

#include <DisplayObjectController.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cHamsterController: public cDisplayObjectController {
public:
	// Construct, and require an associated SphereObject //
	cHamsterController(
		cSphereObject* _Object,
		const std::string& File
		);
	
	virtual ~cHamsterController() {
	}
	
	enum {
		bitFire = bit0,
		//bitRelease = bit1,
		
		bitLeftThrust = bit4,
		bitRightThrust = bit5
	};

	unsigned int AimerTextureId;
	unsigned int ElementTextureId;
		
	Vector2D Cursor;
	
	// My Gamepad //
	int MyPad;	
		
public:	
	// Your chance to do something //
	virtual void Step();
	
	// Draw him //
	virtual void Draw();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_HamsterController_H__ //
// - ------------------------------------------------------------------------------------------ - //
