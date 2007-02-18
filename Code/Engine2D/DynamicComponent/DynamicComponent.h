// - ------------------------------------------------------------------------------------------ - //
// DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_DynamicComponent_DynamicComponent_H__
#define __Engine2D_DynamicComponent_DynamicComponent_H__
// - ------------------------------------------------------------------------------------------ - //
// Todo: 
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include "Body2D/Body2D.h"
#include "ComponentFlags.h"
#include "DynamicComponentAnimator.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicComponent {
public:
	// Who our parent is //
	class cDynamicCollection* Parent;

public:
	// Animator, to display animations and update the body //
	cDynamicComponentAnimator Animator;

	// Body, to interact with physics //
	cBody2D Body;
	
	// Flags, to analize what's occured //
	cComponentFlags Flags;

public:
	cDynamicComponent();
	cDynamicComponent( class cDynamicCollection* const _Parent, const std::string& ComponentFile, const Vector2D& Offset = Vector2D::Zero );

public:
	// - -------------------------------------------------------------------------------------- - //
	// Do physics as a self sustaining object (Go to Body.Step() for new systems) //
	void Step();

public:
	// - -------------------------------------------------------------------------------------- - //
	// Move the currently visible animation stuffs forward a frame //
	void StepAnimation();

	// - -------------------------------------------------------------------------------------- - //
	// Set the current animation to another one //
	void SetAnimation( const int AnimationNumber, const Real& _PlayBackRate = Real::One );
	
	// - -------------------------------------------------------------------------------------- - //
	// Arcing animations are animations that change frames based on a scalar with values 0-1 //
	// - -------------------------------------------------------------------------------------- - //
	// Set's the animation mode to/for an Arcing animation (an animation controlled by a scalar) //
	void SetArcingAnimation( const int AnimationNumber );
	// Call this every work frame to update the currently displayed frame //
	void SetArc( const Real& Arc );
	
public:	
	// - -------------------------------------------------------------------------------------- - //
	// Draw object Mesh transformed by Body //
	void Draw( const int RenderPass = 0 );
	// - -------------------------------------------------------------------------------------- - //
	// Debug Drawing //
	void DrawBody( const bool Selected = false ) const;

public:
	// - -------------------------------------------------------------------------------------- - //
	// Query the state to know if component is active //
	inline bool IsActive() const {
		return Flags.Active();
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	// Solve Collisions/Actions //
	void Solve( cDynamicComponent& _Vs );
	void Solve( class cStaticObjectInstance& _Vs );
	void Solve( class cPassiveObject& _Vs );
	void Solve( class cZone& _Vs );
	void Solve( class cImpulse& _Vs );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_DynamicComponent_DynamicComponent_H__ //
// - ------------------------------------------------------------------------------------------ - //
