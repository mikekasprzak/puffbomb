// - ------------------------------------------------------------------------------------------ - //
// SolidParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#include <Animation/AnimationPool.h>
#include "SolidParticleFactory.h"

#include <algorithm>
#include <functional>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
SolidParticleFactory SolidParticle;
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Populate( int Num )
{
//	Vertex.resize( Num * 4 );
//	TexCoord.resize( Num * 4 );
//	VertColor.resize( Num * 4 );
//	Indices.resize( Num * 4 );

	Vertex.resize( Num << 2 );
	TexCoord.resize( Num << 2 );
	VertColor.resize( Num << 2 );
	Indices.resize( Num << 2 );

	cAnimation& DummyAni = AnimationPool.Load( "Dummy" );

	for( int idx = 0; idx < Num; idx++ )
	{
		Particles.push_back( cParticle() );
		
		Particles[ idx ].SetParticle(
			Vector2D( 0, 0 ),
			Vector2D( 0, 0 ),
			Vector2D( 0, 0 ),
			Vector2D( 0, 0 ),
			0,
			DummyAni,
			0,
			100
		);
	}

	Particles.resize( Num );
	
	Segment.reserve( 1024 );
}
// - ------------------------------------------------------------------------------------------ - //
int SolidParticleFactory::Allocate( const int SegmentSize, const bool _IsAdditive )
{
	int ParticleIdx = 0;
	
	// Sort Segment //
	std::sort( Segment.begin(), Segment.end(), cSegment::less_segment );
	
	for( size_t idx = 0; idx < Segment.size(); idx++ )
	{
//		Log( LOG_HIGHEST_LEVEL, "Segment[ idx ] = " << Segment[ idx ].Start << " - " << Segment[ idx ].Size << " Segment.size() = " << Segment.size() );
		
		if( ( ParticleIdx == Segment[ idx ]->Start ) )
		{

		}
		else
		{
			if( size_t( ParticleIdx + SegmentSize ) < Particles.size() )
			{
				if( ( ParticleIdx + SegmentSize ) < Segment[ idx ]->Start )
				{

					//Log( LOG_HIGHEST_LEVEL, "( ParticleIdx + SegmentSize ) = " << ( ParticleIdx + SegmentSize ) );
					//Log( LOG_HIGHEST_LEVEL, "Segment[ idx + 1 ].Start = " << Segment[ idx + 1 ].Start );

					Segment.push_back( new cSegment( ParticleIdx, SegmentSize, _IsAdditive ) );					
					
					return Segment.size() - 1;
				}

			}
		}
		ParticleIdx = ( Segment[ idx ]->Size );
	}
	
	if( size_t( ParticleIdx + SegmentSize ) < Particles.size() )
	{
		Segment.push_back( new cSegment( ParticleIdx, SegmentSize, _IsAdditive ) );
		
		return Segment.size() - 1;
	}

	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Release( const int SegIdx )
{
	Segment[ SegIdx ]->Start = Particles.size();
	
	std::sort( Segment.begin(), Segment.end(), cSegment::less_segment );
	
	delete Segment.back();
	
	Segment.pop_back();
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Clear()
{
	Segment.clear();
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Add(
	const Vector2D &_Pos,
	const Vector2D &_Velocity,
	const Vector2D &_Acceleration,
	const Vector2D &_Drift,
	const int _Life,
	cAnimation &_Animation,
	const int _Alpha,
	const int _Fade,
	const int SegIdx )
{
	if( Segment[ SegIdx ]->SegIdx < Segment[ SegIdx ]->Size )
	{
		Particles[ Segment[ SegIdx ]->SegIdx ].SetParticle( 
			_Pos,
			_Velocity,
			_Acceleration, 
			_Drift, 
			_Life,
			_Animation,
			_Alpha,
			_Fade
		);
	
		Segment[ SegIdx ]->SegIdx++;
		
		if( Segment[ SegIdx ]->SegIdx == Segment[ SegIdx ]->Size )
		{
			SetParticleData( SegIdx );
		}
	}
	else // Perhaps delete this later when all the particle effects are done //
	{
		Log( LOG_HIGHEST_LEVEL, "Error, did not allocate enough particles for the particle effect" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SetParticleData( const int SegIdx )
{
	OffsetIdx = Segment[ SegIdx ]->IndicesIdx;

	for( int idx = Segment[ SegIdx ]->Start; idx < Segment[ SegIdx ]->Size; idx++ )
	{
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.a;
		VertColor[ OffsetIdx ] = Gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.b;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.c;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].UV.c;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
	}
	Segment[ SegIdx ]->TextureID = Particles[ Segment[ SegIdx ]->Start ].Animator.CurDrawFrame->TextureId;
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Step()
{
	// For every segment //
	for( size_t SegIdx = 0; SegIdx < Segment.size(); SegIdx++ )
	{
		// Calculate first polygon co-ordinate offset //
		OffsetIdx = Segment[ SegIdx ]->IndicesIdx;
		// For every part of a segment //
		for( int idx = Segment[ SegIdx ]->Start; idx < Segment[ SegIdx ]->SegIdx; idx++ )
		{
			// Step the physics of the particle (move it based on all it's factors) //
			Particles[ idx ].Step();
			
			// Do collision //
			SolveVsImpulses( Particles[ idx ] );
			SolveVsObjects( Particles[ idx ] );
			SolveVsStatics( Particles[ idx ] );
			
			// If the particle dies, remove it's particle //
			if( Particles[ idx ].Life <= 0 )
			{
				while( Particles[ idx ].Life <= 0 && Segment[ SegIdx ]->Start < Segment[ SegIdx ]->SegIdx )
				{
					Segment[ SegIdx ]->IndicesSize -= 4;
					Segment[ SegIdx ]->SegIdx--;
	
					Particles[ idx ] = Particles[ Segment[ SegIdx ]->SegIdx ];
					
					Particles[ idx ].Step();
				}
			}
/*	
			Vertex[ OffsetIdx ].x += Particles[ idx ].Velocity.x;  // this made the particles twitch once and a while
			Vertex[ OffsetIdx ].y += Particles[ idx ].Velocity.y;
*/
			
			// Generate co-ordinates for the polygons in a particle //			
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = Gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
		
			++OffsetIdx;
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
		
			++OffsetIdx;
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
		
			++OffsetIdx;
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
		
			++OffsetIdx;
		}
		
		// If the segment dies, remove the segment //
		if( Segment[ SegIdx ]->SegIdx == Segment[ SegIdx ]->Start )
		{
			Release( SegIdx );
			
			SegIdx--;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Draw()
{
	int AdditiveArray[ Segment.size() ];
	size_t AdditiveSize = 0;
	
	for( size_t SegIdx = 0; SegIdx < Segment.size(); SegIdx++ )
	{
		if( Segment[ SegIdx ]->IsAdditive )
		{
			AdditiveArray[ AdditiveSize ] = SegIdx;
			
			AdditiveSize++;
		}
		else
		{
			Gfx::DrawQuads(
				&Vertex[ 0 ],
				&TexCoord[ 0 ],
				&VertColor[ 0 ],
				&Indices[ Segment[ SegIdx ]->IndicesIdx ],
				Segment[ SegIdx ]->IndicesSize - Segment[ SegIdx ]->IndicesIdx,
				Segment[ SegIdx ]->TextureID
			);
		}
	}
	// Cheezy additive sort hack //
	for( size_t SegIdx = 0; SegIdx < AdditiveSize; SegIdx++ )
	{
		// Enables additive blending //
		Gfx::AddBlend();

		Gfx::DrawQuads(
			&Vertex[ 0 ],
			&TexCoord[ 0 ],
			&VertColor[ 0 ],
			&Indices[ Segment[ AdditiveArray[ SegIdx ] ]->IndicesIdx ],
			Segment[ AdditiveArray[ SegIdx ] ]->IndicesSize - Segment[ AdditiveArray[ SegIdx ] ]->IndicesIdx,
			Segment[ AdditiveArray[ SegIdx ] ]->TextureID
		);
		
		// Disables additive blending //
		Gfx::StandardBlend();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SolveVsObjects( cParticle& Particle ) {
	// Calculate bounding rectangle of particle  //
	
	// For every dynamic component //
	for ( size_t idx = 0; idx < Engine2D::cEngine2D::Current->DynamicComponent.size(); idx++ ) {
		const Engine2D::cDynamicComponent& MyComponent = *(Engine2D::cEngine2D::Current->DynamicComponent[ idx ]);
		
		// Early out Active //
		if ( !MyComponent.IsActive() ) 
			continue;
		
		// Early out Rectangle //
		
		
		// Test all speheres against point //
		for ( size_t idx2 = 0; idx2 < MyComponent.Body.SphereSize(); idx2++ ) {
			const Engine2D::cSphere& MySphere = MyComponent.Body.Sphere( idx2 );
			const int& Index = MySphere.Index;

			// Sum of Radius //				
			Real RadiusSum = MySphere.Radius + Real( 0 );
			Real RadiusSumSquared = RadiusSum * RadiusSum;

			// Optimized Verlet with Square Root Approximation //
			Vector2D Ray = Particle.Pos - MyComponent.Body.Nodes.Pos( Index );
			
			// Bail if not touching //
			if ( RadiusSumSquared < Ray.MagnitudeSquared() ) {
				continue;
			}

			// Bail if he's a sensor //
			if ( MySphere.Flags.Sensor() ) {
				continue;
			}
			
			// Solve (Massless with square root approximation) //
			Real Divisor = ( (Ray * Ray) + (RadiusSumSquared) ) - Real( 0.5 );
			if ( Divisor.IsZero() )
				continue;

			Ray *= (RadiusSumSquared) / Divisor;

			Particle.Velocity += Ray;
			Particle.Velocity += Ray;
			Particle.Velocity += Ray;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SolveVsStatics( cParticle& Particle ) {
	
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SolveVsImpulses( cParticle& Particle ) {
	
}
// - ------------------------------------------------------------------------------------------ - //
