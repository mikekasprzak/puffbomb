// - ------------------------------------------------------------------------------------------ - //
// NodeAnchor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_NodeAnchor_H__
#define __Engine2D_Physics_NodeAnchor_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <Engine/DynamicObjectCollection/DynamicObject.h>

#include "LinkageFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cNodeAnchor {
public:
	// Where to pull the anchored point towards //
	Vector2D Pos;	

	// How well to solve the spring.  1.0 is a normal stiff spring.  Less than .5 gets gooey. //
	Real Strength;
	// When to detach the spring (if enabled) //
	Real BreakPoint;

	// Flags for controlling the function of the Anchor //
	cLinkageFlags Flags;
	

	// Object number and Index numbers used //
	unsigned int Object, Index;
		
public:
	inline void Step( std::vector< cDynamicObject >& Component ) {
		// Bail if inactive //
		if ( !Flags.Active() )
			return;

		// Create some nice easier to use references //
		cBody2D& Body = Component[ Object ].Body;

		Vector2D& PointA = Body.Nodes.Pos( Index );
		const Vector2D& PointB = Pos;
		
		const Real& InvMass = Body.Nodes.InvMass( Index );
		
		// Do spring thing //
		Vector2D Ray = PointB - PointA;
		Real RayLength = Ray.Magnitude();
		
		Real Dividend = (RayLength - Real::Zero);

		// Flag Tests (Redundant.  May as well make inactive) //
//		if ( Flags.IgnoreMaximum() ) {
//			if ( Dividend > Real::Zero )
//				return;
//		}

		// Calculate the push //
		Real Divisor = RayLength;
		if ( Divisor.IsZero() )
			return;
		Real Diff = Dividend / Divisor;

		// Solve the Anchor //
		PointA += Ray * Diff * Strength;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_NodeAnchor_H__ //
// - ------------------------------------------------------------------------------------------ - //
