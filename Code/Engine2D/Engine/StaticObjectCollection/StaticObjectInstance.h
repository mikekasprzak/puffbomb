// - ------------------------------------------------------------------------------------------ - //
// StaticObjectInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObjectCollection_StaticObjectInstance_H__
#define __Engine2D_Engine_StaticObjectCollection_StaticObjectInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/StaticObject/StaticObject.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectInstance {
public:
	// Position of this instance //
	Vector2D Pos;
	// Pointer to the contents of the instance inside the pool //
	cStatiObject* Instance;
	
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObjectCollection_StaticObjectInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
