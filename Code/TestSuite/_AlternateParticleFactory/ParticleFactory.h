// - ------------------------------------------------------------------------------------------ - //
// ParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_ParticleFactory_H__
#define __Rendo_ParticleFactory_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Particle.h"
#include <Animation/Animation.h>
#include <list>
// - ------------------------------------------------------------------------------------------ - //
class ParticleFactory;
// - ------------------------------------------------------------------------------------------ - //
extern ParticleFactory FlatParticle;
extern ParticleFactory AdditiveParticle;
// - ------------------------------------------------------------------------------------------ - //
class ParticleFactory
{
public:
	// - -------------------------------------------------------------------------------------- - //
//	std::list< cParticle > Alive;
//	std::list< cParticle > Dead;

public:
	// - -------------------------------------------------------------------------------------- - //
	ParticleFactory() :
		AliveSize( 0 ),
		CurParticle( 0 )
	{
		
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	void Populate( int Num );
	
//	size_t ParticleSize;
	size_t AliveSize;
	size_t CurParticle;

	std::vector< cParticle > Particles;
	
	unsigned int TextureID;

	std::vector< Vector3D > Vertex;
	std::vector< Vector2D > TexCoord;
	std::vector< unsigned int > VertColor;
	std::vector< unsigned int > Indices;

	// - -------------------------------------------------------------------------------------- - //
	inline void Add(
		const Vector2D &_Pos,
		const Vector2D &_Velocity,
		const Vector2D &_Acceleration,
		const Vector2D &_Drift,
		const int _Life,
		cAnimation &_Animation,
		const int _Alpha,
		const int _Fade )
	{
		Particles[ CurParticle ].SetParticle( 
			_Pos,
			_Velocity,
			_Acceleration, 
			_Drift, 
			_Life, 
			_Animation,
			_Alpha,
			_Fade
		);
		
		++CurParticle;
		
		if( CurParticle >= Particles.size() )
		{
			CurParticle = 0;
		}
		
	/*	if( CurParticle < Particles.size() )
		{
			Particles[ CurParticle ].SetParticle( 
				_Pos,
				_Velocity,
				_Acceleration, 
				_Drift, 
				_Life, 
				_Animation,
				_Alpha,
				_Fade
			);
		}
		++CurParticle;*/
		
	}
	// - -------------------------------------------------------------------------------------- - //
/*

	// - -------------------------------------------------------------------------------------- - //
	inline void Add(
		const Vector2D &_Pos,
		const Vector2D &_Velocity,
		const Vector2D &_Acceleration,
		const Vector2D &_Drift,
		const int _Life,
		cAnimation &_Animation,
		const int _Alpha,
		const int _Fade )
	{
		if( !Dead.empty() )
		{
			Alive.splice(
				Alive.end(), 
            	Dead,
            	Dead.begin()
            );
	
			Alive.back().SetParticle( 
				_Pos,
				_Velocity,
				_Acceleration, 
				_Drift, 
				_Life, 
				_Animation,
				_Alpha,
				_Fade
			);
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void AddPriority(
		const Vector2D &_Pos,
		const Vector2D &_Velocity,
		const Vector2D &_Acceleration,
		const Vector2D &_Drift,
		const int _Life,
		cAnimation &_Animation,
		const int _Alpha,
		const int _Fade )
	{
		if( !Dead.empty() )
		{
			Alive.splice(
				Alive.begin(), 
            	Dead,
            	Dead.begin()
            );
		}
		else
		{ // This wont work //
			Alive.splice(
				Alive.begin(), 
            	Alive,
            	--Alive.end()
            );
		}
		
		Alive.front().SetParticle(
			_Pos,
			_Velocity,
			_Acceleration,
			_Drift,
			_Life,
			_Animation,
			_Alpha,
			_Fade
		);
	}
	// - -------------------------------------------------------------------------------------- - //
*/

	void Step();
	// - -------------------------------------------------------------------------------------- - //
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_ParticleFactory_H__ //
// - ------------------------------------------------------------------------------------------ - //
