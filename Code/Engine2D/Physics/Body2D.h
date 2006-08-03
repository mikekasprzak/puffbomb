// - ------------------------------------------------------------------------------------------ - //
// Body2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_H__
#define __Engine2D_Physics_Body2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/CollisionFlags.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cBody2D {
public:
	// Nodes //
	
	
	
	// Flags //
	cCollisionFlags Collision;

public:
	// Step the physics for all my parts //
	void Step();
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
