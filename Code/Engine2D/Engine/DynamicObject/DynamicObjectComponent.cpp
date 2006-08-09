// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include "DynamicObjectComponent.h"
#include <Engine/StaticObject/StaticObjectComponent.h>
#include <Engine/Zone.h>
#include <Engine/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Step() {
	// Step the nodes //
	Body.Step();

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update all Springs //
		Body.StepSprings();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Draw() {
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Solve( cDynamicObjectComponent& _Vs ) {
	// If either object is more than simply active //
	if ( !State.OnlyActive() || !_Vs.State.OnlyActive() ) {
		// If either of us are ignoring our family, and we are part of the same family, bail //
		if ( State.IgnoreFamily() || _Vs.State.IgnoreFamily() ) {
			if ( Parent == _Vs.Parent ) {
				return;
			}
		}
		
		// If either of us are ignoring objects, bail //
		if ( State.IgnoreObjects() || _Vs.State.IgnoreObjects() ) {
			return;
		}

		// If either of us are inactive objects, bail //
		if ( !State.Active() || !_Vs.State.Active() ) {
			return;
		}
	}
	
	// Solve the collision //
	Body.Solve( _Vs.Body ); 
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Solve( cStaticObjectComponent& _Vs ) {
	// If I'm more than simply active //
	if ( !State.OnlyActive() ) {
		// If I'm ignoring scenery, bail//
		if ( State.IgnoreScenery() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !State.Active() ) {
			return;
		}
	}
	
	// Solve the collision //
	Body.Solve( _Vs.Body ); 
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Solve( cZone& _Vs ) {
	// If I'm more than simply active //
	if ( !State.OnlyActive() ) {
		// If I'm ignoring scenery, bail//
		if ( State.IgnoreZones() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !State.Active() ) {
			return;
		}
	}
	
	// Test Bounding Rectangles //
	if ( Body.BoundingRect != _Vs.BoundingRect )
		return;

	// Send message //
	_Vs.Action( *this );
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObjectComponent::Solve( cPassiveObject& _Vs ) {
	// If I'm more than simply active //
	if ( !State.OnlyActive() ) {
		// If I'm ignoring scenery, bail//
		if ( State.IgnorePassive() ) {
			return;
		}

		// If I'm inactive, bail //
		if ( !State.Active() ) {
			return;
		}
	}
	
	// Test Bounding Rectangles //
	if ( Body.BoundingRect != _Vs.BoundingRect )
		return;

	// Send message //
	_Vs.Action( *this );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
