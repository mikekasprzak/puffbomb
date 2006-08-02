// - ------------------------------------------------------------------------------------------ - //
// Impulse //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Impulse_H__
#define __Engine2D_Physics_Impulse_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cImpulse {
public:
	// Position of the impulse //
	Vector2D Pos;

public:
	// Class that describes a component of impulse //
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

public:
	// Inner Ring //
	cImpulseData Inner;
	// Outside Ring //
	cImpulseData Outer;
	
	// Difference between Forces and Radii //
	Real ForceDiff;
	Real RadiusDiff;
	Real InvRadiusDiff;
	
	// BoundingRectangle for grid searching //
	//Rect2D BoundingRect;
	
public:
	// Standard Constructor //
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

	// Get the force on you, given your position //
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
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Impulse_H__ //
// - ------------------------------------------------------------------------------------------ - //