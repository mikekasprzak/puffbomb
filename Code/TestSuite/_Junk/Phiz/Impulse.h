// - ------------------------------------------------------------------------------------------ - //
// Impulse //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_Impulse_H__
#define __Phiz_Impulse_H__
// - ------------------------------------------------------------------------------------------ - //

#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <Geometry/Rect.h>

// - ------------------------------------------------------------------------------------------ - //
class cImpulse {
public:
	Vector2D Pos;
	
	class cImpulseData {
	public:
		Real Radius;
		Real Force;
		
		Real RadiusSquared;
		
		cImpulseData( const Real& _Radius, const Real& _Force ) :
			Radius( _Radius),
			Force( _Force ),
			RadiusSquared( _Radius * _Radius )
		{
		}
				
	};
	
	// Inner Ring //
	cImpulseData Inner;
	// Outside Ring //
	cImpulseData Outer;
	
	// Difference between Forces and Radii //
	Real ForceDiff;
	Real RadiusDiff;
	Real InvRadiusDiff;
	
	// BoundingRectangle for grid searching //
	//cRect2D BoundingRect;
	
public:
	inline cImpulse(
		const Vector2D& _Pos,
		const Real& _InnerRadius, const Real& _InnerForce,
		const Real& _OuterRadius, const Real& _OuterForce
		) :
		Pos( _Pos ),
		Inner( _InnerRadius, _InnerForce ),
		Outer( _OuterRadius, _OuterForce ),
		ForceDiff( _InnerForce - _OuterForce ),
		RadiusDiff( _OuterRadius - _InnerRadius ),
		InvRadiusDiff( Real::One / RadiusDiff )
	{
	}

	inline Vector2D GetForce( const Vector2D& _Pos ) {
		Vector2D Line = _Pos - Pos;
		
		if ( Line.MagnitudeSquared() > Outer.RadiusSquared ) {
			return Vector2D::Zero;
		}
		else if ( Line.MagnitudeSquared() <= Inner.RadiusSquared ) {
			return Line.Normal() * Inner.Force;
		}
		else {
			// Linear Impulses //
			Real Mag = Line.NormalizeRet();
			Real ForceScalar = (RadiusDiff - ( Mag - Inner.Radius )) * InvRadiusDiff;
			return Line * (ForceDiff * ForceScalar);
			
			// Exponential Impulses //
//			Real Mag = Line.NormalizeRet();
//			Mag -= Inner.Radius;
//			Real ForceScalar = Mag*Mag / (RadiusDiff*RadiusDiff); // * InvRadiusDiff;
//			return Line * (ForceDiff * (Real::One - ForceScalar));
		}
	}		
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_Impulse_H__ //
// - ------------------------------------------------------------------------------------------ - //
