// - ------------------------------------------------------------------------------------------ - //
// CreatePassiveInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_CreatePassiveInstance_H__
#define __Engine2D_CreatePassiveInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
// Create an instance of the requested object //
extern Engine2D::cPassiveObject* CreatePassiveInstance(
	const unsigned int Id,
	const Vector2D& Pos = Vector2D::Zero,
	const int Argument = 0
	);
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_CreatePassiveInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
