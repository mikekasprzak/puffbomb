// - ------------------------------------------------------------------------------------------ - //
// DynamicObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicObject_H__
#define __Engine2D_Engine_DynamicObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include <Physics/NodeLink.h>
#include "DynamicObject/DynamicObjectComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObject {
public:
	// Components of this object //
	std::vector< cDynamicObjectComponent > Component;
	// Linkage in this object //
	std::vector< cNodeLink > NodeLink;

public:
	cDynamicObject() {
	}
	
	virtual ~cDynamicObject() {
	}
	
public:
	// Do physics, as a self sustaining object //
	void Step();
	// Step the node links //
	void StepNodeLinks();
	
	// Do any work (control/AI) I may have.  This is commonly overloaded to provide control. //
	virtual void Work();
	// Draw Myself. This is uncommonly overloaded, unless you want a different display method. //
	virtual void Draw();

public:
	// Query if this object is, at all, enabled //
	inline bool IsActive() {
		return true;
	}

public:
	// Solve Collisions/Actions //
	void Solve( cDynamicObject& _Vs );
	void Solve( class cStaticObject& _Vs );
	void Solve( class cPassiveObject& _Vs );
	void Solve( class cZone& _Vs );
	void Solve( class cImpulse& _Vs );
	
	// Messanging //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
