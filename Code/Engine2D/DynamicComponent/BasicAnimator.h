// - ------------------------------------------------------------------------------------------ - //
// BasicAnimator //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_BasicAnimator_H__
#define __Engine2D_BasicAnimator_H__
// - ------------------------------------------------------------------------------------------ - //
// Todo: 
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Geometry/Real.h>
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
template< class AnimationSetType >
class cBasicAnimator {
public:
	// Parts of a component //
	AnimationSetType* AnimationSet;

public:
	// Variables for playback //
	int CurrentAnimation;
	int CurrentFrame;
	Real CurrentFrameTime;

	// The rate at which to play back the animation //
	Real PlayBackRate;
	
	// Flags for monitoring aspects of the animation (looping) //
	cAnimationFlags AnimationFlags;


public:
	// No argument constructor //
	cBasicAnimator() :
		AnimationSet( 0 )
	{
	}
	
	// With an animation set from a pool as an arugment //
	cBasicAnimator( AnimationSetType* _AnimationSet ) :
		AnimationSet( _AnimationSet ),
		CurrentAnimation( 0 ),
		CurrentFrame( 0 ),
		CurrentFrameTime( Real::Zero ),
		PlayBackRate( Real::One )
	{
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	// Move the currently visible animation stuffs forward a frame //
	void Step() {
		// Make sure we actually have an associated animation set //
		if ( AnimationSet ) {
			// Step our current frame time forward by our rate of playback //
			CurrentFrameTime += PlayBackRate;
			
			// If our current frame time breaks the hold length of the current frame //
			if ( CurrentFrameTime >= Real( AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Time ) ) {
				// Step to the next frame //
				CurrentFrame++;
				
				// If our frame hits the end //
				if ( CurrentFrame >= (int)AnimationSet->Animation[ CurrentAnimation ].Frame.size() ) {
					// Set frame to the loop point //
					CurrentFrame = AnimationSet->Animation[ CurrentAnimation ].LoopPoint;
					
					// Set looped flag //
					AnimationFlags.SetLooped();
				}
	
				// Offset the Current Frame Time by the hold of the previous, to correctly accumulate //
				CurrentFrameTime -= Real( AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Time );
			}
		}	
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Set the current animation to another one //
	void SetAnimation( const int AnimationNumber, const Real& _PlayBackRate = Real::One ) {
		// Assert if the requested animation doesn't exist //
		Assert( AnimationNumber >= (int)AnimationSet->Animation.size(),
			"Animation " << AnimationNumber << " Requested, but doesn't exist!"
			);

		// Set the animation as requested //
		CurrentAnimation = AnimationNumber;
		
		// Set internal animator variables //
		PlayBackRate = _PlayBackRate;
		CurrentFrame = 0;
		CurrentFrameTime = Real::Zero;
		
		// Clear Flags //
		AnimationFlags.Clear();
	}
	// - -------------------------------------------------------------------------------------- - //

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Arcing animations are animations that change frames based on a scalar with values 0-1 //
	// - -------------------------------------------------------------------------------------- - //
	// Set's the animation mode to/for an Arcing animation (an animation controlled by a scalar) //
	void SetArcingAnimation( const int AnimationNumber ) {
		// Assert if the requested animation doesn't exist //
		Assert( AnimationNumber >= (int)AnimationSet->Animation.size(),
			"Arcing Animation " << AnimationNumber << " Requested, but doesn't exist!"
			);
		
		// Set the animation as requested //
		CurrentAnimation = AnimationNumber;
		
		// Set internal animator variables //
		PlayBackRate = Real::Zero;
		CurrentFrame = 0;
		CurrentFrameTime = Real::Zero;
		
		// Clear Flags //
		AnimationFlags.Clear();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Call this every work frame to update the currently displayed frame //
	void SetArc( const Real& Arc ) {
		CurrentFrame = (int)( Arc * Real( AnimationSet->Animation[ CurrentAnimation ].Frame.size() ) );
	
		// If too big //
		if ( CurrentFrame >= (int)AnimationSet->Animation[ CurrentAnimation ].Frame.size() ) {
			// Clip to the end //
			CurrentFrame = AnimationSet->Animation[ CurrentAnimation ].Frame.size() - 1;
		}
		// If too small //
		else if ( CurrentFrame < 0 ) {
			CurrentFrame = 0;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_BasicAnimator_H__ //
// - ------------------------------------------------------------------------------------------ - //
