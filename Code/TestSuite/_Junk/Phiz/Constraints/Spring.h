// - ------------------------------------------------------------------------------------------ - //
// Spring //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_Constraint_Spring_H__
#define __Phiz_Constraint_Spring_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cSpring {
public:	
	Real Length;
	
	// How well to solve the spring.  1.0 is a normal stiff spring.  Less than .5 starts to give //
	//   you a gooey look. //
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

	inline Real CurrentLength( cDynamicNodes& Node ) {
		Vector2D Line = Node.Pos( IndexB ) - Node.Pos( IndexA );
		return Line.Magnitude();
	}
	
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

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_Constraint_Spring_H__ //
// - ------------------------------------------------------------------------------------------ - //
