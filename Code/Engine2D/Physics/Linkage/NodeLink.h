// - ------------------------------------------------------------------------------------------ - //
// NodeLink //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_NodeLink_H__
#define __Engine2D_Physics_NodeLink_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>

#include <Engine/DynamicObjectCollection/DynamicObject.h>

#include "LinkageFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cNodeLink {
public:
	// Length of the Spring //
	Real Length;	
	// How well to solve the spring.  1.0 is a normal stiff spring.  Less than .5 gets gooey. //
	Real Strength;
	// When to detach the spring (if enabled) //
	Real BreakPoint;

	// Flags for controlling the function of the NodeLink //
	cLinkageFlags Flags;


	// Object number and Index numbers used //
	unsigned int ObjectA, IndexA;
	unsigned int ObjectB, IndexB;
	
public:
	void Step( std::vector< cDynamicObject >& Component ) {
		cBody2D& BodyA = Component[ ObjectA ].Body;
		cBody2D& BodyB = Component[ ObjectB ].Body;

		Vector2D& PointA = BodyA.Nodes.Pos( IndexA );
		Vector2D& PointB = BodyB.Nodes.Pos( IndexB );
		const Real& InvMassA = BodyA.Nodes.InvMass( IndexA );
		const Real& InvMassB = BodyB.Nodes.InvMass( IndexB );
		
		// Do spring thing //
		Vector2D Ray = PointB - PointA;
		Real RayLength = Ray.Magnitude();
		
		Real Dividend = (RayLength - Length);

		// Early out for all flag tests //
//		if ( Flags & (flIgnoreMinimum | flIgnoreMaximum )) {
//			if ( Flags & flIgnoreMinimum ) {
//				if ( Dividend <= Real::Zero )
//					return;
//			}
//			else if ( Flags & flIgnoreMaximum ) {
//				if ( Dividend > Real::Zero )
//					return;
//			}
//		}

		Real Divisor = RayLength * (InvMassA + InvMassB);
		if ( Divisor.IsZero() )
			return;
		Real Diff = Dividend / Divisor;
		
		PointA += InvMassA * Ray * Diff * Strength;
		PointB -= InvMassB * Ray * Diff * Strength;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_NodeLink_H__ //
// - ------------------------------------------------------------------------------------------ - //
