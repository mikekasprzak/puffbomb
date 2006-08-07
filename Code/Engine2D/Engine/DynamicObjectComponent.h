// - ------------------------------------------------------------------------------------------ - //
// DynamicObjectComponent //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicObjectComponent_H__
#define __Engine2D_Engine_DynamicObjectComponent_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D.h>
#include <Graphics/Mesh2D.h>

#include <Physics/StateFlags.h>
#include <Physics/CollisionFlags.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObjectComponent {
public:
	// Parts of a component //
	cBody2D Body;
	cMesh2D Mesh;
	
	// Flags //
	cStateFlags State;
	cCollisionFlags Collision;

public:
	// Do physics //
	inline void Step() {
		// Clear Collision Flags //
		Body.Collision.Clear();
		// Step physics of object //
		Body.Nodes.Step();
	}

	// Draw Myself //
	inline void Draw() {
	}

public:
	inline bool IsActive() {
		return true;
	}

public:
	
	// Messanging //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicObjectComponent_H__ //
// - ------------------------------------------------------------------------------------------ - //
