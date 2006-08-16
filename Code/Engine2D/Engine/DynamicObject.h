// - ------------------------------------------------------------------------------------------ - //
// DynamicObject - A collection of Components //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicObject_H__
#define __Engine2D_Engine_DynamicObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include <Physics/NodeLink.h>
#include <Physics/NodeAnchor.h>
#include "DynamicObject/DynamicObjectComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObject {
public:
	// Components of this object //
	std::vector< cDynamicObjectComponent > Component;
	
	// Node Linkage in this object //
	std::vector< cNodeLink > NodeLink;
	// Anchoring (locking) points in this object //
	std::vector< cNodeAnchor > NodeAnchor;

public:
	cDynamicObject() {
	}
	
	virtual ~cDynamicObject() {
	}
	
public:
	// Do physics, as a self sustaining object //
	void Step();
	// Step the mass body linkage (node links and anchors) //
	void StepLinkage();
	
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
	// Messanging //
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
