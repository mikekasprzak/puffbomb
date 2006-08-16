// - ------------------------------------------------------------------------------------------ - //
// StaticObjectComponentInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObject_StaticObjectComponentInstance_H__
#define __Engine2D_Engine_StaticObject_StaticObjectComponentInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/StaticObject/StaticObjectComponent.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectComponentInstance {
public:
	// Position of this instance //
	Vector2D Pos;
	// Pointer to the contents of the instance inside the pool //
	cStatiObjectComponent* Instance;
	
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObject_StaticObjectComponentInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
