// - ------------------------------------------------------------------------------------------ - //
// Impulse //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Impulse_H__
#define __Engine2D_Physics_Impulse_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <Physics/Physics.h>
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
		Real Tangent;
		
		Real RadiusSquared;
		
		cImpulseData( const Real& _Radius, const Real& _Force, const Real& _Tangent = Real::Zero ) :
			Radius( _Radius),
			Force( _Force ),
			Tangent( _Tangent ),
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
	
	// Bounding rectangle, for early out test, and partitioning //
	cPhysics::BoundingRectType BoundingRect;
	
public:
	// Standard Constructor //
	inline cImpulse(
		const Vector2D& _Pos,
		const Real& _InnerRadius, const Real& _InnerForce, const Real& _InnerTangent,
		const Real& _OuterRadius, const Real& _OuterForce, const Real& _OuterTangent
		) :
		Pos( _Pos ),
		Inner( _InnerRadius, _InnerForce, _InnerTangent ),
		Outer( _OuterRadius, _OuterForce, _OuterTangent ),
		ForceDiff( _InnerForce - _OuterForce ),
		RadiusDiff( _OuterRadius - _InnerRadius ),
		InvRadiusDiff( Real::One / RadiusDiff )
	{
		CalcBoundingRect();
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
	
	// Calculate the bounding rectangle for the impulse, mainly used by partitioning //
	inline void CalcBoundingRect() {
		BoundingRect = cPhysics::BoundingRectType::Pair( Pos - Outer.Radius, Pos + Outer.Radius );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Impulse_H__ //
// - ------------------------------------------------------------------------------------------ - //
