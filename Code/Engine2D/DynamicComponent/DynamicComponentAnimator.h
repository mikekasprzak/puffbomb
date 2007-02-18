// - ------------------------------------------------------------------------------------------ - //
// DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_DynamicComponent_DynamicComponentAnimator_H__
#define __Engine2D_DynamicComponent_DynamicComponentAnimator_H__
// - ------------------------------------------------------------------------------------------ - //
#include "BasicAnimator.h"

#include "Body2D/Body2D.h"
#include "ComponentAnimationSet/ComponentAnimationSet.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicComponentAnimator: public cBasicAnimator< cComponentAnimationSet > {
public:
	cDynamicComponentAnimator();
	cDynamicComponentAnimator( cComponentAnimationSet* _AnimationSet );

public:	
	// Accessory functions for acquiring the Body Pose of an animation //
	cBody2DPose* GetPose() const;
	cBody2DPose* GetPose( const int _Animation, const int _Frame ) const;
	
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
