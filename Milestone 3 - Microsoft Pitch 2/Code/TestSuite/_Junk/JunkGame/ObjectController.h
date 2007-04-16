// - ------------------------------------------------------------------------------------------ - //
// ObjectController //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_ObjectController_H__
#define __Phiz_ObjectController_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <string>

#include <Phiz/SphereObject.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cObjectController {
public:
	cSphereObject* SphereObject;
	
public:
	// Construct, and require an associated SphereObject //
	cObjectController( cSphereObject* _Object, const std::string& /*File*/ ) :
		SphereObject( _Object )
	{
	}

	virtual ~cObjectController() {
	}
	
public:	
	// Your chance to do something //
	virtual void Step() {
		// Do something! Overload Me! //
	}	

	virtual void Draw() {
		// Draw something! Overload Me! //
	}	

	virtual void Message( cSphereObject* /*Obj*/, int /*Info*/ ) {
		// Tell me something //
	}
	virtual void Message( cPolyObject* /*Obj*/, int /*Info*/ ) {
		// Tell me something //
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_ObjectController_H__ //
// - ------------------------------------------------------------------------------------------ - //
