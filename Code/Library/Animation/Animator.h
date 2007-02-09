// - ------------------------------------------------------------------------------------------ - //
// Animator //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_Animator_H__
#define __Rendo_Animator_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Animation.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
class cAnimator
{
public:
	cAnimation* Animation;
	
	int CurrentFrame;
	int Time;
	
	cFrame InterpFrame;
	
	cFrame* CurDrawFrame;
	
public:
	cAnimator();
	cAnimator( const std::string& AnimationName );

	void Set( cAnimation* _Animation, const int _CurrentFrame );
	void SetFrame( const int _CurrentFrame );
	
	void Step();

	void Draw( const Vector2D& Offset, int Color = Gfx::White() );
	void Draw( const Vector2D& Offset, const Matrix2x2& Matrix, int Color = Gfx::White() );
	void DrawQuad( const Vector2D& Offset, int Color = Gfx::White(), Real Scale = Real::One );
	void DrawQuad( const Vector2D& Offset, const Matrix2x2& Matrix, int Color = Gfx::White() );

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_Animator_H__ //
// - ------------------------------------------------------------------------------------------ - //
