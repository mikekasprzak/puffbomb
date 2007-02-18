// - ------------------------------------------------------------------------------------------ - //
// BasicAnimator //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_BasicAnimator_H__
#define __Engine2D_BasicAnimator_H__
// - ------------------------------------------------------------------------------------------ - //
// Todo: 
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Geometry/Integer.h>
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
	Real PlaybackRate;
	
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
		PlaybackRate( Real::One )
	{
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	// Move the currently visible animation stuffs forward a frame //
	void Step() {
		// Make sure we actually have an associated animation set //
		if ( AnimationSet ) {
			// Step our current frame time forward by our rate of playback //
			CurrentFrameTime += PlaybackRate;
			
			// If our current frame time breaks the hold length of the current frame //
			if ( CurrentFrameTime >= Real( GetFrameHoldTime() ) ) {
				// Step to the next frame //
				CurrentFrame++;
				
				// If our frame hits the end //
				if ( CurrentFrame >= GetFrameCount() ) {
					// Set frame to the loop point //
					CurrentFrame = GetLoopPoint();
					
					// Set looped flag //
					AnimationFlags.SetLooped();
				}
	
				// Offset the Current Frame Time by the hold of the previous, to correctly accumulate //
				CurrentFrameTime -= Real( GetFrameHoldTime() );
			}
		}	
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Set the current animation to another one //
	void SetAnimation( const int& AnimationNumber, const Real& _PlaybackRate = Real::One ) {
		// Assert if the requested animation doesn't exist //
		Assert( !Integer(AnimationNumber).InRange( 0, GetLastAnimation() ),
			"Animation " << AnimationNumber << " of " << GetLastAnimation() <<
			" requested, but doesn't exist!"
			);

		// Set the animation as requested //
		CurrentAnimation = AnimationNumber;
		
		// Set internal animator variables //
		SetPlaybackRate( _PlaybackRate );
		SetFrame( 0 );
		CurrentFrameTime = Real::Zero;
		
		// Clear Flags //
		AnimationFlags.Clear();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Set the current animation to another one, that doesn't animate //
	void SetStaticAnimation( const int& AnimationNumber ) {
		SetAnimation( AnimationNumber, Real::Zero );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Get the current animation //
	inline const int& GetAnimation() const {
		return CurrentAnimation;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get last animation //
	inline const int GetLastAnimation() const {
		return AnimationSet->Animation.size() - 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get animation count //
	inline const int GetAnimationCount() const {
		return AnimationSet->Animation.size();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Set the current frame //
	inline void SetFrame( const int& _Frame = 0 ) {
		Assert( !Integer(_Frame).InRange( 0, GetLastFrame() ),
			"Frame outside range!  " << _Frame << " of " << GetLastFrame()
			);

		CurrentFrame = _Frame;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the current frame //
	inline const int& GetFrame() const {
		return CurrentFrame;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get last frame //
	inline const int GetLastFrame() const {
		return AnimationSet->Animation[ CurrentAnimation ].Frame.size() - 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get last frame //
	inline const int GetLastFrame( const int& _Animation ) const {
		return AnimationSet->Animation[ _Animation ].Frame.size() - 1;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get frame count //
	inline const int GetFrameCount() const {
		return AnimationSet->Animation[ CurrentAnimation ].Frame.size();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get frame count //
	inline const int GetFrameCount( const int& _Animation ) const {
		return AnimationSet->Animation[ _Animation ].Frame.size();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Set the current animation Play Back Rate //
	void SetPlaybackRate( const Real& _PlaybackRate = Real::One ) {
		Assert( _PlaybackRate < Real::Zero,
			"Playback rate can't be negative!  " << _PlaybackRate
			);

		PlaybackRate = _PlaybackRate;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int& GetPlaybackRate() const {
		return PlaybackRate;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get loop point //
	inline const int GetLoopPoint() const {
		return AnimationSet->Animation[ CurrentAnimation ].LoopPoint;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get loop point //
	inline const int GetLoopPoint( const int& _Animation ) const {
		return AnimationSet->Animation[ _Animation ].LoopPoint;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get frame hold time //
	inline const int GetFrameHoldTime() const {
		return AnimationSet->Animation[ CurrentAnimation ].Frame[ CurrentFrame ].Time;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get frame hold time //
	inline const int GetFrameHoldTime( const int& _Animation, const int& _Frame ) const {
		return AnimationSet->Animation[ _Animation ].Frame[ _Frame ].Time;
	}
	// - -------------------------------------------------------------------------------------- - //

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Arcing animations are animations that change frames based on a scalar with values 0-1 //
	// - -------------------------------------------------------------------------------------- - //
	// Set's the animation mode to/for an Arcing animation (an animation controlled by a scalar) //
	inline void SetArcingAnimation( const int& AnimationNumber ) {
		SetAnimation( AnimationNumber, Real::Zero );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Call this every work frame to update the currently displayed frame //
	inline void SetArc( const Real& Arc ) {
		CurrentFrame = (int)( Arc * Real( GetFrameCount() ) );
	
		// If too big //
		if ( CurrentFrame > GetLastFrame() ) {
			// Clip to the end //
			CurrentFrame = GetLastFrame();
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
