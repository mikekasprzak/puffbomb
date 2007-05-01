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
		// If the angle type has changed, then project on to the plane between Points A and B //
		if ( AngleType != CalcAngleType( Node ) ) {
			Vector2D PA = Node.Pos( IndexA ) - Node.Pos( IndexP );
			Vector2D AB = Node.Pos( IndexB ) - Node.Pos( IndexA );
			
			Vector2D ABTanNorm = AB.Tangent().Normal();
			
			Node.Pos( IndexP ) += (ABTanNorm * PA) * ABTanNorm;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_Constraints_AngleCross_H__ //
// - ------------------------------------------------------------------------------------------ - //
