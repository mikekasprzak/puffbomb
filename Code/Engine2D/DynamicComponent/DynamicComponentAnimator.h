// - ------------------------------------------------------------------------------------------ - //
// DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_DynamicComponent_DynamicComponentAnimator_H__
#define __Engine2D_DynamicComponent_DynamicComponentAnimator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Body2D/Body2D.h"
#include "ComponentAnimationSet/ComponentAnimationSet.h"
#include "AnimationFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicComponentAnimator {
public:
	// Parts of a component //
	cComponentAnimationSet* AnimationSet;

public:
	int CurrentAnimation;
	int CurrentFrame;
	Real CurrentFrameTime;

	// The rate at which to play back the animation //
	Real PlayBackRate;
	
	// Flags for monitoring aspects of the animation (looping) //
	cAnimationFlags AnimationFlags;


public:
	cDynamicComponentAnimator();
	cDynamicComponentAnimator( cComponentAnimationSet* _AnimationSet );

public:
	// - -------------------------------------------------------------------------------------- - //
	// Move the currently visible animation stuffs forward a frame //
	void Step();
	
	// Accessory functions for acquiring the Body Pose of an animation //
	cBody2DPose* GetPose() const;
	cBody2DPose* GetPose( const int _Animation, const int _Frame ) const;

public:
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
	void Draw( cBody2D _Body, const int RenderPass = 0 );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_DynamicComponent_DynamicComponentAnimator_H__ //
// - ------------------------------------------------------------------------------------------ - //
