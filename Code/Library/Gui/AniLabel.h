// - ------------------------------------------------------------------------------------------ - //
// AniLabel //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_AniLabel_H__
#define __Gui_AniLabel_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Label.h"
#include <Animation/Animator.h>
// - ------------------------------------------------------------------------------------------ - //
class cAniLabel : public cLabel
{
public:
	cAnimator Animator;
	cAnimation* SelectAni;
	cAnimation* PassiveAni;

public:
	
	cAniLabel(
		const Vector2D& _Pos,
		const bool _IsPassive,
		const int _ActionID, 
		cAnimation& _Animation,
		cAnimation& _SelectAni,
		const int _CurrentFrame
		) :
			cLabel( _Pos, _IsPassive, _ActionID )
	{
		Animator.Set( &_Animation, _CurrentFrame );
		PassiveAni = &_Animation;
		SelectAni = &_SelectAni;
	}
	
	void Step()
	{
		Animator.Step();
	}
	void Draw()
	{
		glColor4ub( 255, 255, 255, 255 );
		Animator.DrawQuad( Pos );
	}
	void SwapAnimation()
	{
		if( Animator.Animation == PassiveAni )
		{
			Animator.Set( SelectAni, 0 );
		}
		else
		{
			Animator.Set( PassiveAni, 0 );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_AniLabel_H__ //
// - ------------------------------------------------------------------------------------------ - //