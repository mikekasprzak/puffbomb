// - ------------------------------------------------------------------------------------------ - //
// Spring //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_Constraints_Spring_H__
#define __Engine2D_Physics_Body2D_Constraints_Spring_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <Physics/Body2D/DynamicNodes.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cSpring {
public:	
	// Length of the Spring //
	Real Length;
	// How well to solve the spring.  1.0 is a normal stiff spring.  Less than .5 gets gooey. //
	Real Strength;


	enum {
		flMinConstrain = bit0,
		flMaxConstrain = bit1
	};
	int Flags;

	// Indices at the end for consistency //
	size_t IndexA, IndexB;
	
public:
	inline cSpring() :
		Flags( flMinConstrain | flMaxConstrain )
	{
	}
	
	inline cSpring( size_t _IndexA, size_t _IndexB ) :
		Length( Real::One ),
		Strength( Real::One ),
		Flags( flMinConstrain | flMaxConstrain ),
		IndexA( _IndexA ),
		IndexB( _IndexB )
	{
	}

	// Get the current length of the spring //
	inline Real CurrentLength( cDynamicNodes& Node ) {
		Vector2D Line = Node.Pos( IndexB ) - Node.Pos( IndexA );
		return Line.Magnitude();
	}

	// Calculate the length of the spring given these positions //
	inline void CalcLength( cDynamicNodes& Node ) {
		Vector2D Line = Node.Pos( IndexB ) - Node.Pos( IndexA );
		Length = Line.Magnitude();
	}
	
	// 
	inline void Step( cDynamicNodes& Node ) {
//		// Optimized Verlet with Square Root Approximation //
//		Vector2D Ray = Node.Pos( IndexB ) - Node.Pos( IndexA );
//		Real RadiusSumSquared = Length * Length;
//		
//		// That .5 is part of the square root approximation, not a scalar! //
//		Real Divisor = ( (Ray * Ray) + (RadiusSumSquared) );
//		Ray *= (RadiusSumSquared) / Divisor - Real( 0.5f );
//		
//		// A scalar here (or the line above) causes the segments to stretch more //
//		Node.Pos( IndexA ) -= Ray;// * Real( .16 );
//		Node.Pos( IndexB ) += Ray;// * Real( .16 );
		

		Vector2D Ray = Node.Pos( IndexB ) - Node.Pos( IndexA );
		Real RayLength = Ray.Magnitude();
		Real Divisor = (RayLength * (Node.InvMass( IndexA ) + Node.InvMass( IndexB )));
		if ( Divisor.IsZero() )
			return;
		Real Diff = (RayLength - Length) / Divisor;
		
		// Verify this works //
		if ( !(Flags & flMinConstrain) )
			if ( Diff >= Real::Zero )
				return;
		if ( !(Flags & flMaxConstrain) )
			if ( Diff < Real::Zero )
				return;
		
		Node.Pos( IndexA ) += Node.InvMass( IndexA ) * Ray * Diff * Strength;
		Node.Pos( IndexB ) -= Node.InvMass( IndexB ) * Ray * Diff * Strength;		
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_Constraints_Spring_H__ //
// - ------------------------------------------------------------------------------------------ - //
