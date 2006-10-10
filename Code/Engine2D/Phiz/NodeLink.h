// - ------------------------------------------------------------------------------------------ - //
// NodeLink //
// - NodeLink's are springs that attach objects together.  In theory, since I'm using Nodes //
//   (the base part that includes the actual verts), it should be possible to attach an Object //
//   and a PolyObject together. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_NodeLink_H__
#define __Phiz_NodeLink_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "DynamicNodes.h"

#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cNodeLink {
public:
	Real Length;
	Real Strength;

	// Ends A and B for a spring //
	cDynamicNodes* ObjectA;
	int IndexA;
	
	cDynamicNodes* ObjectB;
	int IndexB;
	
public:
	enum {
		
		flIgnoreMinimum = bit29,
		flIgnoreMaximum = bit30,
		flActive = bit31,
	};
	int Flags;
		
public:	
	// - -------------------------------------------------------------------------------------- - //
	inline bool IsActive() {
		return Flags & flActive;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetActive() {
		Flags |= flActive;
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline void SetInactive() {
		Flags &= ~flActive;
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline void IgnoreMinimum() {
		Flags |= flIgnoreMinimum;
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline void IgnoreMaximum() {
		Flags |= flIgnoreMaximum;
	}	
	// - -------------------------------------------------------------------------------------- - //

public:
	cNodeLink( cDynamicNodes* _ObjectA, int _IndexA, cDynamicNodes* _ObjectB, int _IndexB ) :
		Strength( Real::One ),
		ObjectA( _ObjectA ),
		IndexA( _IndexA ),
		ObjectB( _ObjectB ),
		IndexB( _IndexB )
	{
		Length = (ObjectB->Pos( IndexB ) - ObjectA->Pos( IndexA )).Magnitude();
	}

public:
	// Do the solving for this spring //
	void Step() {
		Vector2D Ray = ObjectB->Pos( IndexB ) - ObjectA->Pos( IndexA );
		Real RayLength = Ray.Magnitude();
		
		Real Dividend = (RayLength - Length);

		// Early out for all flag tests //
		if ( Flags & (flIgnoreMinimum | flIgnoreMaximum )) {
			if ( Flags & flIgnoreMinimum ) {
				if ( Dividend <= Real::Zero )
					return;
			}
			else if ( Flags & flIgnoreMaximum ) {
				if ( Dividend > Real::Zero )
					return;
			}
		}

		Real Divisor = (RayLength * (ObjectA->InvMass( IndexA ) + ObjectB->InvMass( IndexB )));
		if ( Divisor.IsZero() )
			return;
		Real Diff = Dividend / Divisor;
		
		ObjectA->Pos( IndexA ) += ObjectA->InvMass( IndexA ) * Ray * Diff * Strength;
		ObjectB->Pos( IndexB ) -= ObjectB->InvMass( IndexB ) * Ray * Diff * Strength;
	}
	
	void DebugDraw() {
		if ( cGlobal::DebugDraw & (cGlobal::flExtraInfo | cGlobal::flCollision) ) {
			// Draw springs //
			{
				Vector2D DrawMeA, DrawMeB;
				DrawMeA = ObjectA->Pos( IndexA );
				DrawMeB = ObjectB->Pos( IndexB );
					
				Gfx::Line( DrawMeA, DrawMeB, Gfx::RGB( 255, 255, 0 ) );
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_NodeLink_H__ //
// - ------------------------------------------------------------------------------------------ - //
