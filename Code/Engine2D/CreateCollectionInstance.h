// - ------------------------------------------------------------------------------------------ - //
// CreateCollectionInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_CreateCollectionInstance_H__
#define __Engine2D_CreateCollectionInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include <Engine/DynamicObjectCollection.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// Create an instance of the requested object //
extern cDynamicObjectCollection* CreateCollectionInstance(
	unsigned int Id,
	Vector2D Pos = Vector2D::Zero,
	int Argument = 0
	);
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_CreateCollectionInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
