// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Math/Integer.h>
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
cDynamicComponentAnimator::cDynamicComponentAnimator( cComponentAnimationSet* const _AnimationSet ) :
	cBasicAnimator< cComponentAnimationSet >( _AnimationSet )
{
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cBody2DPose* const cDynamicComponentAnimator::GetPose() const {
	// Current Animation Bounds Checking //
	Assert( !Integer(CurrentAnimation).InRange( 0, GetLastAnimation() ),
		"CurrentAnimation out of bounds!  " << CurrentAnimation << " of " << GetLastAnimation()
		);

	// Current Frame Bounds Checking //
	Assert( !Integer(CurrentFrame).InRange( 0, GetLastFrame() ),
		"CurrentFrame out of bounds!  " << CurrentFrame << " of " << GetLastFrame()
		);
	
	// Return the requested pose //
	return &AnimationSet->BodyPose[ AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].BodyPoseIndex ];
}
// - ------------------------------------------------------------------------------------------ - //
cBody2DPose* const cDynamicComponentAnimator::GetPose( const int _Animation, const int _Frame ) const {
	// _Animation Bounds Checking //
	Assert( !Integer(_Animation).InRange( 0, GetLastAnimation() ),
		"_Animation out of bounds!  " << _Animation << " of " << GetLastAnimation()
		);

	// _Frame Bounds Checking //
	Assert( !Integer(_Frame).InRange( 0, GetLastFrame() ),
		"_Frame out of bounds!  " << _Frame << " of " << GetLastFrame()
		);

	// Return the requested pose //
	return &AnimationSet->BodyPose[ AnimationSet->Animation[ _Animation ].Frame[ _Frame ].BodyPoseIndex ];
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponentAnimator::Draw( cBody2D& _Body, const int RenderPass ) {
	// Make sure we actually have an associated animation set //
	if ( AnimationSet ) {
		AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Draw( _Body, RenderPass );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
