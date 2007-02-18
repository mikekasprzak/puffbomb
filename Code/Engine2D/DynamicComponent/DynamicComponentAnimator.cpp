// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include "DynamicComponentAnimator.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cDynamicComponentAnimator::cDynamicComponentAnimator( ) :
	cBasicAnimator< cComponentAnimationSet >()
{
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicComponentAnimator::cDynamicComponentAnimator( cComponentAnimationSet* _AnimationSet ) :
	cBasicAnimator< cComponentAnimationSet >( _AnimationSet )
{
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cBody2DPose* cDynamicComponentAnimator::GetPose() const {
	// Todo: Assert bounds check CurrentAnimation and CurrentFrame //
	
	return &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];
}
// - ------------------------------------------------------------------------------------------ - //
cBody2DPose* cDynamicComponentAnimator::GetPose( const int _Animation, const int _Frame ) const {
	// Todo: Assert bounds check _Animation and _Frame //

	return &AnimationSet->BodyPose[ AnimationSet->Animation[ _Animation ].Frame[ _Frame ].BodyPoseIndex ];
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponentAnimator::Draw( cBody2D _Body, const int RenderPass ) {
	// Make sure we actually have an associated animation set //
	if ( AnimationSet ) {
		AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Draw( _Body, RenderPass );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
