// - ------------------------------------------------------------------------------------------ - //
// Particle //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_Particle_H__
#define __Rendo_Particle_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Animation/Animator.h>
// - ------------------------------------------------------------------------------------------ - //
class cParticle
{
public:
	Vector2D Pos;
	//Vector2D Velocity;
	Vector2D Old;
	Vector2D Acceleration;
	Vector2D Drift;
	
	int Life;
	int Alpha;
	int Opaque;
	
	int Fade;
	
	cAnimator Animator;
	
public:
	cParticle()
	{
		
	}
	
	inline cParticle(
			const Vector2D &_Pos,
			const Vector2D &_Velocity,
			const Vector2D &_Acceleration,
			const Vector2D &_Drift,
			const int &_Life,
			cAnimation &_Animation ) :
		Pos( _Pos ),
		//Velocity( _Velocity ),
		Old( _Pos - _Velocity ),
		Acceleration( _Acceleration ),
		Drift( _Drift ),
		Life( _Life ),
		Alpha( 128 ),
		Fade( 100 )
	{
		Animator.Set( &_Animation, 0 );
	}

	inline void SetParticle(
		const Vector2D &_Pos,
		const Vector2D &_Velocity,
		const Vector2D &_Acceleration,
		const Vector2D &_Drift,
		const int &_Life,
		cAnimation &_Animation,
		const int _Alpha,
		const int _Fade )
	{
		Pos = _Pos;
		//Velocity = _Velocity;
		Old = _Pos - _Velocity;
		Acceleration = _Acceleration;
		Drift = _Drift;
		Life = _Life;
		Animator.Set( &_Animation, 0 );
		Alpha = _Alpha;
		Fade = _Fade;
		
		Opaque = Alpha;
	}

	inline void SetParticle(
		const Vector2D &_Pos,
		const Vector2D &_Velocity,
		const Vector2D &_Acceleration,
		const Vector2D &_Drift,
		const int &_Life,
		const int _Alpha,
		const int _Fade )
	{
		Pos = _Pos;
		//Velocity = _Velocity;
		Old = _Pos - _Velocity;
		Acceleration = _Acceleration;
		Drift = _Drift;
		Life = _Life;
		Alpha = _Alpha;
		Fade = _Fade;
		
		Opaque = Alpha;
	}


	inline void Step()
	{
//		Pos += Velocity;
//		Velocity += Acceleration;
//		Acceleration += Drift;

		Vector2D NewOld = Pos;
		Pos += (Pos - Old) + Acceleration;
		Old = NewOld;
		Acceleration += Drift;
		--Life;
		
		if( Life < Fade )
		{
			Alpha = ( Life * Opaque ) / Fade;
		}
		
	//	Animator.Step();
	}
	
	inline void Draw()
	{
		//glColor4ub( 255, 255, 255, Alpha );
		//Animator.DrawQuad( Pos );
		//glColor4ub( 255, 255, 255, 255 );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_Particle_H__ //
// - ------------------------------------------------------------------------------------------ - //
