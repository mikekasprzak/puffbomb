// - ------------------------------------------------------------------------------------------ - //
// CreateCollectionInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_CreateCollectionInstance_H__
#define __Engine2D_CreateCollectionInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include <DynamicCollection/DynamicCollection.h>
// - ------------------------------------------------------------------------------------------ - //
// Create an instance of the requested object //
extern Engine2D::cDynamicCollection* CreateCollectionInstance(
	const unsigned int Id,
	const Vector2D& Pos = Vector2D::Zero,
	const int Argument = 0
	);
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_CreateCollectionInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
