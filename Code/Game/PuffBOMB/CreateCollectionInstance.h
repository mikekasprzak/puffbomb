// - ------------------------------------------------------------------------------------------ - //
// CreateCollectionInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_CreateCollectionInstance_H__
#define __Engine2D_CreateCollectionInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include <DynamicCollection/DynamicCollection.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// Create an instance of the requested object //
extern cDynamicCollection* CreateCollectionInstance(
	const unsigned int Id,
	const Vector2D& Pos = Vector2D::Zero,
	const int Argument = 0
	);
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_CreateCollectionInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
