// - ------------------------------------------------------------------------------------------ - //
// DenseLink //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_DenseLink_H__
#define __Phiz_DenseLink_H__
// - ------------------------------------------------------------------------------------------ - //

#include <Geometry/Real.h>
#include "DenseParticle.h"

// - ------------------------------------------------------------------------------------------ - //
class cDenseLink {
public:
	cDenseParticle* a;
	cDenseParticle* b;
	
	Real Length;
	Real BreakPointSquared;

public:
	cDenseLink( cDenseParticle* _a, cDenseParticle* _b, Real BreakScalar ) :
		a( _a ),
		b( _b ),
		Length( (b->Pos - a->Pos).Magnitude() ),
		BreakPointSquared( (Length * BreakScalar) * (Length * BreakScalar) )
	{
	}
	
public:
	inline const bool Step() const {
		Vector2D Line = b->Pos - a->Pos;
		if ( Line.MagnitudeSquared() >= BreakPointSquared ) {
			// We Broke :( //
			return true;
		}
		
		// Calculate the spring push //
		Real Mag = Line.NormalizeRet();
//		Real Mag = Line.Manhattan();
//		Line /= Mag;
		Real Diff = (Length - Mag) * Real::Half;
		Vector2D Push = Diff * Line;
		
		// Move the positions //
		a->Pos -= Push;
		b->Pos += Push;
		
		// All is well :) //
		return false;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_DenseLink_H__ //
// - ------------------------------------------------------------------------------------------ - //
