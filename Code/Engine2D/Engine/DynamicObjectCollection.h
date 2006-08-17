// - ------------------------------------------------------------------------------------------ - //
// DynamicObjectCollection - A collection of Components //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicObjectCollection_H__
#define __Engine2D_Engine_DynamicObjectCollection_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include <Physics/Linkage.h>
#include "DynamicObjectCollection/DynamicObject.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObjectCollection {
public:
	// Components of this object //
	std::vector< cDynamicObject > Component;
	
	// Node Linkage in this object //
	std::vector< cNodeLink > NodeLink;
	// Anchoring (locking) points in this object //
	std::vector< cNodeAnchor > NodeAnchor;

public:
	cDynamicObjectCollection() {
	}
	
	virtual ~cDynamicObjectCollection() {
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
#endif // __Engine2D_Engine_DynamicObjectCollection_H__ //
// - ------------------------------------------------------------------------------------------ - //
