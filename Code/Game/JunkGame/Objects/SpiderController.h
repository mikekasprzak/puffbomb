// - ------------------------------------------------------------------------------------------ - //
// SpiderController //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_SpiderController_H__
#define __Game_SpiderController_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/SphereObject.h>
#include <Phiz/NodeLink.h>

#include <Game/DisplayObjectController.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cSpiderController: public cDisplayObjectController {
public:
	// Construct, and require an associated SphereObject //
	cSpiderController(
		cSphereObject* _Object,
		cSphereObject* _Shot1,
		cNodeLink* _Link1,
		cSphereObject* _Shot2,
		cNodeLink* _Link2,
		const std::string& File
		);
	
	virtual ~cSpiderController() {
	}
	
	enum {
		bitFire = bit0,
		bitRelease = bit1,
		
		bitShrink = bit4,
		bitGrow = bit5
	};
	
	cSphereObject* Shot[2];
	cNodeLink* Link[2];
	Real RopeLength[2];
	
	int CurrentShot;
	int MyPad;
	
public:	
	Real Scale;
	
	std::vector< Real > SpringLength;
	std::vector< Real > SphereRadius;
	std::vector< Real > Mass;
		
public:	
	// Your chance to do something //
	virtual void Step();
	
	// Draw him //
	virtual void Draw();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_SpiderController_H__ //
// - ------------------------------------------------------------------------------------------ - //
