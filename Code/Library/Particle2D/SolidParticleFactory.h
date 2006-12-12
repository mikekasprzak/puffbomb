// - ------------------------------------------------------------------------------------------ - //
// SolidParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Particle2D_SolidParticleFactory_H__
#define __Library_Particle2D_SolidParticleFactory_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Particle.h"
#include "Segment.h"
#include <Animation/Animation.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
class SolidParticleFactory
{
public:
	std::vector< cSegment* > Segment;	
public:
	// - -------------------------------------------------------------------------------------- - //
	SolidParticleFactory() :
		OffsetIdx( 0 )
	{
		
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	void Populate( int Num );

	size_t OffsetIdx;

	std::vector< cParticle > Particles;  // Particle Pointers may help performance when removing a particle?? //

	std::vector< Vector3D > Vertex;
	std::vector< Vector2D > TexCoord;
	std::vector< unsigned int > VertColor;
	std::vector< unsigned int > Indices;

	// - -------------------------------------------------------------------------------------- - //
	int Allocate( const int SegmentSize, const bool _IsAdditive );
	void Release( const int SegIdx );
	void Clear();

	void Add(
		const Vector2D &_Pos,
		const Vector2D &_Velocity,
		const Vector2D &_Acceleration,
		const Vector2D &_Drift,
		const int _Life,
		cAnimation &_Animation,
		const int _Alpha,
		const int _Fade,
		const int SegIdx
	);

	void SetParticleData( const int SegIdx );

	// - -------------------------------------------------------------------------------------- - //

	void Step();
	void Draw();

	// - -------------------------------------------------------------------------------------- - //
	
	void SolveVsObjects( cParticle& Particle );
	void SolveVsStatics( cParticle& Particle );
	void SolveVsImpulses( cParticle& Particle );
};
// - ------------------------------------------------------------------------------------------ - //
extern SolidParticleFactory SolidParticle;
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Particle2D_SolidParticleFactory_H__ //
// - ------------------------------------------------------------------------------------------ - //
