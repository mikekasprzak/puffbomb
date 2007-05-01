// - ------------------------------------------------------------------------------------------ - //
// AngleCross - A constraint that stops angles from breaking acute to obtuse, and vice versa //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_Constraints_AngleCross_H__
#define __Engine2D_Physics_Body2D_Constraints_AngleCross_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <DynamicComponent/Body2D/DynamicNodes/DynamicNodes.h>

//#include "AngleCrossFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cAngleCross {
public:	
	// Indices for our formulaic parts //
	size_t IndexA, IndexB, IndexP;

	// 2 types of angles we care about. Acute and Obtuse.  This is the type we are. //
	bool AngleType;


	// Flags //
	//cAngleCrossFlags Flags;
	
public:
	inline cAngleCross()
	{
	}
	
	inline cAngleCross( 
		const size_t _IndexA,
		const size_t _IndexB,
		const size_t _IndexP
		) :
		IndexA( _IndexA ),
		IndexB( _IndexB ),
		IndexP( _IndexP )
	{
	}
	
public:
	// Calculate the type of angle we are //
	inline bool CalcAngleType( cDynamicNodes& Node ) const {
		Vector2D PA = Node.Pos( IndexA ) - Node.Pos( IndexP );
		Vector2D PB = Node.Pos( IndexB ) - Node.Pos( IndexP );
		Real AngleType = PA.Tangent() * PB;
		
		// True if acute //
		if ( AngleType >= Real::Zero ) {
			return true;
		}
		// False if obtuse //
		return false;
	}
	
	inline void CalcMyAngleType( cDynamicNodes& Node ) {
		AngleType = CalcAngleType( Node );
	}

public:	
	inline void Step( cDynamicNodes& Node ) {
		
		return;
//		// Standard Verlet with masses //
//		Vector2D Ray = Node.Pos( IndexB ) - Node.Pos( IndexA );
//		Real RayLength = Ray.Magnitude();
//		
//		Real Dividend = (RayLength - Length);
//
//		// Disabling of Minimum and Maximum constraining //
//		if ( Flags.IgnoreMinimum() ) {
//			if ( Dividend <= Real::Zero ) {
//				return;
//			}
//		}	
//		if ( Flags.IgnoreMaximum() ) {
//			if ( Dividend > Real::Zero ) {
//				return;
//			}
//		}
//		
//		// Calculate the weighted push based on masses //
//		Real Divisor = (RayLength * (Node.InvMass( IndexA ) + Node.InvMass( IndexB )));
//		if ( Divisor.IsZero() )
//			return;
//		Real Diff = Dividend / Divisor;
//		
//		// Solve the AngleCross //
//		Node.Pos( IndexA ) += Node.InvMass( IndexA ) * Ray * Diff * Strength;
//		Node.Pos( IndexB ) -= Node.InvMass( IndexB ) * Ray * Diff * Strength;		
//
//
////		// Optimized Verlet with Square Root Approximation //
////		Vector2D Ray = Node.Pos( IndexB ) - Node.Pos( IndexA );
////		Real RadiusSumSquared = Length * Length;
////		
////		// That .5 is part of the square root approximation, not a scalar! //
////		Real Divisor = ( (Ray * Ray) + (RadiusSumSquared) );
////		Ray *= (RadiusSumSquared) / Divisor - Real( 0.5f );
////		
////		// A scalar here (or the line above) causes the segments to stretch more //
////		Node.Pos( IndexA ) -= Ray;// * Real( .16 );
////		Node.Pos( IndexB ) += Ray;// * Real( .16 );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_Constraints_AngleCross_H__ //
// - ------------------------------------------------------------------------------------------ - //
