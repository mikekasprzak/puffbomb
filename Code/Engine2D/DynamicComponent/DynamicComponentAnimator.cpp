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
	// Current Animation Bounds Checking //
	Assert( (CurrentAnimation < 0) || (CurrentAnimation >= (int)AnimationSet->Animation.size()),
		"CurrentAnimation out of bounds!  " << CurrentAnimation << " of " <<
		AnimationSet->Animation.size()
		);

	// Current Frame Bounds Checking //
	Assert( (CurrentFrame < 0) || (CurrentFrame >= (int)AnimationSet->Animation[ CurrentAnimation ].Frame.size()),
		"CurrentFrame out of bounds!  " << CurrentFrame << " of " <<
		AnimationSet->Animation[ CurrentAnimation ].Frame.size()
		);
	
	// Return the requested pose //
	return &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];
}
// - ------------------------------------------------------------------------------------------ - //
cBody2DPose* cDynamicComponentAnimator::GetPose( const int _Animation, const int _Frame ) const {
	// _Animation Bounds Checking //
	Assert( (_Animation < 0) || (_Animation >= (int)AnimationSet->Animation.size()),
		"_Animation out of bounds!  " << _Animation << " of " <<
		AnimationSet->Animation.size()
		);

	// _Frame Bounds Checking //
	Assert( (_Frame < 0) || (_Frame >= (int)AnimationSet->Animation[ _Animation ].Frame.size()),
		"_Frame out of bounds!  " << _Frame << " of " <<
		AnimationSet->Animation[ _Animation ].Frame.size()
		);

	// Return the requested pose //
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
