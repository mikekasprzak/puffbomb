// - ------------------------------------------------------------------------------------------ - //
// Spring //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_Constraints_Spring_H__
#define __Engine2D_Physics_Body2D_Constraints_Spring_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <DynamicComponent/Body2D/DynamicNodes/DynamicNodes.h>

#include "SpringFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cSpring {
public:	
	// Indices at the end for consistency //
	size_t IndexA, IndexB;

	// Length of the Spring //
	Real Length;
	// How well to solve the spring.  1.0 is a normal stiff spring.  Less than .5 gets gooey. //
	Real Strength;

	// Flags //
	cSpringFlags Flags;
	
public:
	inline cSpring()
	{
	}
	
	inline cSpring( 
		const size_t _IndexA,
		const size_t _IndexB,
		const Real _Length = Real::One,
		const Real _Strength = Real::One
		) :
		IndexA( _IndexA ),
		IndexB( _IndexB ),
		Length( _Length ),
		Strength( _Strength )
	{
	}
	
public:
	// Get the current length of the spring //
	inline Real CurrentLength( cDynamicNodes& Node ) {
		Vector2D Line = Node.Pos( IndexB ) - Node.Pos( IndexA );
		return Line.Magnitude();
	}

	// Calculate the length of the spring given these positions //
	inline void CalcLength( cDynamicNodes& Node ) {
		Length = CurrentLength( Node );
	}

public:	
	inline void Step( cDynamicNodes& Node ) {
		// Standard Verlet with masses //
		Vector2D Ray = Node.Pos( IndexB ) - Node.Pos( IndexA );
		Real RayLength = Ray.Magnitude();
		
		Real Dividend = (RayLength - Length);

		// Disabling of Minimum and Maximum constraining //
		if ( Flags.IgnoreMinimum() ) {
			if ( Dividend <= Real::Zero ) {
				return;
			}
		}	
		if ( Flags.IgnoreMaximum() ) {
			if ( Dividend > Real::Zero ) {
				return;
			}
		}
		
		// Calculate the weighted push based on masses //
		Real Divisor = (RayLength * (Node.InvMass( IndexA ) + Node.InvMass( IndexB )));
		if ( Divisor.IsZero() )
			return;
		Real Diff = Dividend / Divisor;
		
		// Solve the Spring //
		Node.Pos( IndexA ) += Node.InvMass( IndexA ) * Ray * Diff * Strength;
		Node.Pos( IndexB ) -= Node.InvMass( IndexB ) * Ray * Diff * Strength;		


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
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_Constraints_Spring_H__ //
// - ------------------------------------------------------------------------------------------ - //
