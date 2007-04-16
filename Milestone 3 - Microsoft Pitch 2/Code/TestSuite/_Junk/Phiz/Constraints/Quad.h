// - ------------------------------------------------------------------------------------------ - //
// Quad //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_Constraint_Quad_H__
#define __Phiz_Constraint_Quad_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include "../DynamicNodes.h"
#include "../StaticNodes.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cQuad {
public:
	size_t IndexA, IndexB, IndexC, IndexD;
	
	Vector2D NormalA, NormalB, NormalC, NormalD;

public:
	inline void CalculateNormals( cStaticNodes& Node ) {
		Vector2D RayA = Node.Pos( IndexB ) - Node.Pos( IndexA );
		NormalA = (-RayA.Tangent()).Normal();

		Vector2D RayB = Node.Pos( IndexC ) - Node.Pos( IndexB );
		NormalB = (-RayB.Tangent()).Normal();

		Vector2D RayC = Node.Pos( IndexD ) - Node.Pos( IndexC );
		NormalC = (-RayC.Tangent()).Normal();

		Vector2D RayD = Node.Pos( IndexA ) - Node.Pos( IndexD );
		NormalD = (-RayD.Tangent()).Normal();		
	}

	inline void CalculateNormals( cDynamicNodes& Node ) {
		Vector2D RayA = Node.Pos( IndexB ) - Node.Pos( IndexA );
		NormalA = (-RayA.Tangent()).Normal();

		Vector2D RayB = Node.Pos( IndexC ) - Node.Pos( IndexB );
		NormalB = (-RayB.Tangent()).Normal();

		Vector2D RayC = Node.Pos( IndexD ) - Node.Pos( IndexC );
		NormalC = (-RayC.Tangent()).Normal();

		Vector2D RayD = Node.Pos( IndexA ) - Node.Pos( IndexD );
		NormalD = (-RayD.Tangent()).Normal();		
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_Constraint_Quad_H__ //
// - ------------------------------------------------------------------------------------------ - //
