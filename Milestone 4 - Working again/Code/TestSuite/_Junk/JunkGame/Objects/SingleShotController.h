// - ------------------------------------------------------------------------------------------ - //
// SingleShotController //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_SingleShotController_H__
#define __Game_SingleShotController_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/SphereObject.h>
#include <Phiz/NodeLink.h>

#include <ObjectController.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cSingleShotController: public cObjectController {
public:
	// Construct, and require an associated SphereObject //
	cSingleShotController( cSphereObject* _Object, cSphereObject* _Shot1, cNodeLink* _Link1, const std::string& File );
	
	cSphereObject* Shot;
	cNodeLink* Link;
	
public:	
	// Your chance to do something //
	virtual void Step();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_SingleShotController_H__ //
// - ------------------------------------------------------------------------------------------ - //
