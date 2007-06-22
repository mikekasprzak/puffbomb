// - ------------------------------------------------------------------------------------------ - //
// RopeConstraint - A constraint that stops angles from breaking acute to obtuse, and vice versa //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_Constraints_RopeConstraint_H__
#define __Engine2D_Physics_Body2D_Constraints_RopeConstraint_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <DynamicComponent/Body2D/DynamicNodes/DynamicNodes.h>

//#include "RopeConstraintFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cRopeConstraint {
public:	
	// Indices for our formulaic parts //
	std::vector< size_t > Index;

	Real Length;
	Real Balance;

	// Flags //
	//cRopeConstraintFlags Flags;
	
public:
	inline cRopeConstraint()
	{
	}
	
	inline cRopeConstraint( const Real& _Length ) :
		Length( _Length ),
		Balance( Real::Half )
	{
		// *NOTE*: The indices should to be correctly populated before you use step! //
	}
	
public:
	inline const Vector2D AVector( const cDynamicNodes& Node ) const {
		if ( Index.size() > 1 ) {
			return Node.Pos( 1 ) - Node.Pos( 0 );
		}
		return Vector2D::Zero;
	}
	
	inline const Vector2D BVector( const cDynamicNodes& Node ) const {
		if ( Index.size() > 1 ) {
			return Node.Pos( Index.size() - 2 ) - Node.Pos( Index.size() - 1 );
		}
		return Vector2D::Zero;
	}

	inline const Real CalcRopeLength( const cDynamicNodes& Node ) const {
		Real RopeSum;
		
		for ( size_t idx = 0; idx < Index.size() - 1; idx++ ) {
			RopeSum += (Node.Pos( idx+1 ) - Node.Pos( idx )).Magnitude();
		}
		
		return RopeSum;
	}
	
public:	
	inline void Step( cDynamicNodes& Node ) {
		Real ActualLength = CalcRopeLength( Node );
		Real RopeError = Length - ActualLength;
		
		// Calculate the length of each segment should be //
		Real SegmentLength = ActualLength;
		if ( Index.size() > 1 ) {
			SegmentLength /= Index.size();
		}
		
		// Balance the distance between each segment //
		// Optional with a flag? //
		
		// Constrain the ends //
		if ( Index.size() > 1 ) {
			// TODO: clip to segment length?
			
			Node.Pos( 0 ) -= AVector( Node ).Normal() * (RopeError * (Balance));
			Node.Pos( Index.size() - 1 ) -= BVector( Node ).Normal() * (RopeError * ((Real::One - Balance)));
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_Constraints_RopeConstraint_H__ //
// - ------------------------------------------------------------------------------------------ - //
