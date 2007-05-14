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
	size_t IndexPivot, IndexA, IndexB;

	// 2 types of angles we care about. Acute and Obtuse.  This is the type we are. //
	bool AngleType;

	// Flags //
	//cAngleCrossFlags Flags;
	
public:
	inline cAngleCross()
	{
	}
	
	inline cAngleCross( 
		const size_t _IndexPivot,
		const size_t _IndexA,
		const size_t _IndexB
		) :
		IndexPivot( _IndexPivot ),
		IndexA( _IndexA ),
		IndexB( _IndexB ),
		AngleType( false )
	{
		// *NOTE*: The Angle Type needs to be correctly populated before you use step! //
	}
	
public:
	// Calculate the type of angle we are //
	inline bool CalcAngleType( const cDynamicNodes& Node ) const {
		Vector2D PA = Node.Pos( IndexA ) - Node.Pos( IndexPivot );
		Vector2D PB = Node.Pos( IndexB ) - Node.Pos( IndexPivot );
		Real Angle = PA.Tangent() * PB;
		
		// True if acute, False if obtuse //
		return Angle >= Real::Zero;
	}
	
	inline void CalcMyAngleType( const cDynamicNodes& Node ) {
		AngleType = CalcAngleType( Node );
	}

	// Calculate the type of angle we are //
	inline bool CalcAngleType( const std::vector< cBodyPoseNode >& Node ) const {
		Vector2D PA = Node[ IndexA ].Pos - Node[ IndexPivot ].Pos;
		Vector2D PB = Node[ IndexB ].Pos - Node[ IndexPivot ].Pos;
		Real Angle = PA.Tangent() * PB;
		
		// True if acute, False if obtuse //
		return Angle >= Real::Zero;
	}
	
	inline void CalcMyAngleType( const std::vector< cBodyPoseNode >& Node ) {
		AngleType = CalcAngleType( Node );
	}
	
public:	
	inline void Step( cDynamicNodes& Node ) {
		// If the angle type has changed, then project on to the plane between Points A and B //
		if ( AngleType != CalcAngleType( Node ) ) {
			Vector2D PA = Node.Pos( IndexA ) - Node.Pos( IndexPivot );
			Vector2D AB = Node.Pos( IndexB ) - Node.Pos( IndexA );
			
			Vector2D ABTanNorm = AB.Tangent().Normal();
			
			Node.Pos( IndexPivot ) += (ABTanNorm * PA) * ABTanNorm;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_Constraints_AngleCross_H__ //
// - ------------------------------------------------------------------------------------------ - //
