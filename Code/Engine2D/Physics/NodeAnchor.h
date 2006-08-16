// - ------------------------------------------------------------------------------------------ - //
// NodeAnchor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_NodeAnchor_H__
#define __Engine2D_Physics_NodeAnchor_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>

#include <Engine/DynamicObjectCollection/DynamicObject.h>
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


	// Object number and Index numbers used //
	unsigned int Object, Index;
		
public:
	void Step( std::vector< cDynamicObject >& Component ) {
		cBody2D& Body = Component[ Object ].Body;

		Vector2D& PointA = Body.Nodes.Pos( Index );
		const Vector2D& PointB = Pos;
		
		const Real& InvMass = Body.Nodes.InvMass( Index );
		
		// Do spring thing //
		Vector2D Ray = PointB - PointA;
		Real RayLength = Ray.Magnitude();
		
		Real Dividend = (RayLength - Real::Zero);

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

		Real Divisor = RayLength;// * (InvMassA + Real::Zero);
		if ( Divisor.IsZero() )
			return;
		Real Diff = Dividend / Divisor;
		
		//PointA += InvMassA * Ray * Diff * Strength;
		PointA += Ray * Diff * Strength;
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_NodeAnchor_H__ //
// - ------------------------------------------------------------------------------------------ - //
