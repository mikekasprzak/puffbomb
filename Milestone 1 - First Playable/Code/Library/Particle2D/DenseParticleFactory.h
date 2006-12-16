// - ------------------------------------------------------------------------------------------ - //
// DenseParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Particle2D_DenseParticleFactory_H__
#define __Library_Particle2D_DenseParticleFactory_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Particle.h"
#include "Segment.h"
#include <Animation/Animation.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
class DenseParticleFactory
{
public:
//	std::vector< cSegment > Segment;	
	std::vector< cSegment* > Segment;	
public:
	// - -------------------------------------------------------------------------------------- - //
	DenseParticleFactory() :
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
};
// - ------------------------------------------------------------------------------------------ - //
extern DenseParticleFactory DenseParticle;
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Particle2D_DenseParticleFactory_H__ //
// - ------------------------------------------------------------------------------------------ - //
