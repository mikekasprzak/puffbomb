// - ------------------------------------------------------------------------------------------ - //
// Animator //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_Animator_H__
#define __Rendo_Animator_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Animation.h"
// - ------------------------------------------------------------------------------------------ - //
class cAnimator
{
public:
	// Stores a sequence of animations //
	cAnimation* Animation;
	
	int CurrentFrame;
	int Time;
	
	cFrame InterpFrame;
	
	cFrame* CurDrawFrame;
	

public:
	cAnimator();

	void Set( cAnimation* _Animation, const int _CurrentFrame );
	
	void Step();

	void Draw( const Vector2D& Offset );
	void Draw( const Vector2D& Offset, const Matrix2x2& Matrix );
	void DrawQuad( const Vector2D& Offset );
	void DrawQuad( const Vector2D& Offset, const Matrix2x2& Matrix );

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_Animator_H__ //
// - ------------------------------------------------------------------------------------------ - //
