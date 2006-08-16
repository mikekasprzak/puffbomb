// - ------------------------------------------------------------------------------------------ - //
// DynamicObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicObjectCollection_DynamicObject_H__
#define __Engine2D_Engine_DynamicObjectCollection_DynamicObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>
#include <Graphics/Mesh2D.h>

#include "StateFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObject {
public:
	// Parts of a component //
	cBody2D Body;
	cMesh2D Mesh;
	
	// Who our parent is //
	class cDynamicObject* Parent;
	
	// Flags //
	cStateFlags State;

public:
	cDynamicObject();
	cDynamicObject( class cDynamicObject* _Parent );

public:
	// Do physics as a self sustaining object. //
	void Step();
	
	// Draw Myself //
	void Draw();

public:
	// Query the state to know if component is active //
	inline bool IsActive() {
		return State.Active();
	}

public:
	// Solve Collisions/Actions //
	void Solve( cDynamicObject& _Vs );
	void Solve( class cStaticObject& _Vs );
	void Solve( class cPassiveObject& _Vs );
	void Solve( class cZone& _Vs );
	void Solve( class cImpulse& _Vs );
	
	// Messanging //
	// * needs to be here to relay the message back to the parent ** //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicObjectCollection_DynamicObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
