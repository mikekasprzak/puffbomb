// - ------------------------------------------------------------------------------------------ - //
// NodeLink //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_NodeLink_H__
#define __Engine2D_Physics_NodeLink_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>

#include <DynamicComponent/DynamicComponent.h>

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
	size_t ObjectA, IndexA;
	size_t ObjectB, IndexB;
	
public:
	cNodeLink() :
		Strength( Real::One ),
		BreakPoint( Real( 3 ) )
	{
	}
	
	cNodeLink( size_t _ObjectIndexA, size_t _NodeIndexA, size_t _ObjectIndexB, size_t _NodeIndexB, Real _BreakPoint = Real( 3 ), Real _Strength = Real::One ) :
		Strength( _Strength ),
		BreakPoint( _BreakPoint ),
		ObjectA( _ObjectIndexA ),
		IndexA( _NodeIndexA ),
		ObjectB( _ObjectIndexB ),
		IndexB( _NodeIndexB )
	{
	}

	
	inline void Step( std::vector< cDynamicComponent >& Component ) {
		// Bail if inactive //
		if ( !Flags.ActiveAndNotBroken() )
			return;
		
		// Create some nice easier to use references //
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
		if ( !Flags.OnlyActive() ) {
			// Disabling of Minimum and Maximum constraining //
			if ( Flags.IgnoreMinimum() ) {
				if ( Dividend <= Real::Zero )
					return;
			}
			else if ( Flags.IgnoreMaximum() ) {
				if ( Dividend > Real::Zero )
					return;
			}
			
			// If Breakable //
			if ( Flags.Breakable() ) {
				// Test if we've reached the break point //
				if ( Dividend >= BreakPoint ) {
					// Break the link //
					Flags.SetBroken();
				}
			}
		}

		// Calculate the weighted push based on masses //
		Real Divisor = RayLength * (InvMassA + InvMassB);
		if ( Divisor.IsZero() )
			return;
		Real Diff = Dividend / Divisor;
		
		// Solve the Spring //
		PointA += InvMassA * Ray * Diff * Strength;
		PointB -= InvMassB * Ray * Diff * Strength;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_NodeLink_H__ //
// - ------------------------------------------------------------------------------------------ - //
