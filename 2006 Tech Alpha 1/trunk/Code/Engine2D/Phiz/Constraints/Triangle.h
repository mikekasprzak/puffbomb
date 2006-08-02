// - ------------------------------------------------------------------------------------------ - //
// Triangle //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_Constraint_Triangle_H__
#define __Phiz_Constraint_Triangle_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include "../DynamicNodes.h"
#include "../StaticNodes.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cTriangle {
public:
	size_t IndexA, IndexB, IndexC;
	
	Vector2D NormalA, NormalB, NormalC;

public:
	inline void CalculateNormals( cStaticNodes& Node ) {
		Vector2D RayA = Node.Pos( IndexB ) - Node.Pos( IndexA );
		NormalA = (-RayA.Tangent()).Normal();

		Vector2D RayB = Node.Pos( IndexC ) - Node.Pos( IndexB );
		NormalB = (-RayB.Tangent()).Normal();

		Vector2D RayC = Node.Pos( IndexA ) - Node.Pos( IndexC );
		NormalC = (-RayC.Tangent()).Normal();
	}

	inline void CalculateNormals( cDynamicNodes& Node ) {
		Vector2D RayA = Node.Pos( IndexB ) - Node.Pos( IndexA );
		NormalA = (-RayA.Tangent()).Normal();

		Vector2D RayB = Node.Pos( IndexC ) - Node.Pos( IndexB );
		NormalB = (-RayB.Tangent()).Normal();

		Vector2D RayC = Node.Pos( IndexA ) - Node.Pos( IndexC );
		NormalC = (-RayC.Tangent()).Normal();
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_Constraint_Triangle_H__ //
// - ------------------------------------------------------------------------------------------ - //
