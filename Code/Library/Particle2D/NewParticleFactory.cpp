// - ------------------------------------------------------------------------------------------ - //
// NewParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#include <Animation/AnimationPool.h>
#include "NewParticleFactory.h"

#include <algorithm>
#include <functional>
// - ------------------------------------------------------------------------------------------ - //
NewParticleFactory NewParticle;
// - ------------------------------------------------------------------------------------------ - //
void NewParticleFactory::Populate( int Num )
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
	
	Segment.reserve( 256 );
}
// - ------------------------------------------------------------------------------------------ - //
bool compare_segment(const NewParticleFactory::cSegment &a, const NewParticleFactory::cSegment &b) 
{
    return a.Start < b.Start;
}
// - ------------------------------------------------------------------------------------------ - //
int NewParticleFactory::Allocate( const int SegmentSize, const bool _IsAdditive )
{
	int ParticleIdx = 0;
	
	// Sort Segment //
	std::sort( Segment.begin(), Segment.end(), compare_segment );
	
	for( size_t idx = 0; idx < Segment.size(); idx++ )
	{
//		if( ( ParticleIdx >= Segment[ idx ].Start ) && ( ( ParticleIdx ) < ( Segment[ idx ].Size ) ) )
		if( ( ParticleIdx == Segment[ idx ].Start ) )
		{

		}
		else
		{
			if( idx < Segment.size() - 1 )
			{
				if( size_t( ParticleIdx + SegmentSize ) < Particles.size() )
				{
					if( ( ParticleIdx + SegmentSize ) < Segment[ idx + 1 ].Start )
					{
						Segment.push_back( cSegment( ParticleIdx, SegmentSize, _IsAdditive ) );					
						
						return Segment.size() - 1;
					}
				}
			}
		}
		ParticleIdx = ( Segment[ idx ].Size );
	}
	
	if( size_t( ParticleIdx + SegmentSize ) < Particles.size() )
	{
		Segment.push_back( cSegment( ParticleIdx, SegmentSize, _IsAdditive ) );
		
		return Segment.size() - 1;
	}

	return -1;
}
void NewParticleFactory::Release( const int SegIdx )
{
	Segment[ SegIdx ].Start = Particles.size();
	
	std::sort( Segment.begin(), Segment.end(), compare_segment );
		
	Segment.pop_back();
}
// - ------------------------------------------------------------------------------------------ - //
void NewParticleFactory::Add(
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
	if( Segment[ SegIdx ].SegIdx < Segment[ SegIdx ].Size )
	{
		Particles[ Segment[ SegIdx ].SegIdx ].SetParticle( 
			_Pos,
			_Velocity,
			_Acceleration, 
			_Drift, 
			_Life, 
			_Animation,
			_Alpha,
			_Fade
		);
	
		Segment[ SegIdx ].SegIdx++;
		
		if( Segment[ SegIdx ].SegIdx == Segment[ SegIdx ].Size )
		{
			SetParticleData( SegIdx );
		}
	}
	else // Perhaps delete this later when all the particle effects are done //
	{
		Log( LOG_HIGHEST_LEVEL, "Error, did not allocate enough particles for particle effect" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void NewParticleFactory::SetParticleData( const int SegIdx )
{
	OffsetIdx = Segment[ SegIdx ].IndicesIdx;

	for( int idx = Segment[ SegIdx ].Start; idx < Segment[ SegIdx ].Size; idx++ )
	{
		//set to this later when you get diff working //
		// Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos).ToVector3D();
		Indices[ OffsetIdx ] = OffsetIdx;
//		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.a;
		VertColor[ OffsetIdx ] = gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
//		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.b;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
//		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.c;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
//		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].UV.c;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
	}
	Segment[ SegIdx ].TextureID = Particles[ Segment[ SegIdx ].Start ].Animator.CurDrawFrame->TextureId;
}
// - ------------------------------------------------------------------------------------------ - //
void NewParticleFactory::Step()
{
	for( size_t SegIdx = 0; SegIdx < Segment.size(); SegIdx++ )
	{
		OffsetIdx = Segment[ SegIdx ].IndicesIdx;
		for( int idx = Segment[ SegIdx ].Start; idx < Segment[ SegIdx ].SegIdx; idx++ )
		{
			Particles[ idx ].Step();
			if( Particles[ idx ].Life <= 0 )
			{
				while( Particles[ idx ].Life <= 0 && Segment[ SegIdx ].Start != Segment[ SegIdx ].SegIdx )
				{
					Segment[ SegIdx ].IndicesSize -= 4;
					Segment[ SegIdx ].SegIdx--;
	
					Particles[ idx ] = Particles[ Segment[ SegIdx ].SegIdx ];
					
					Particles[ idx ].Step();
				}
/*
				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
			
				++OffsetIdx;
				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
			
				++OffsetIdx;
				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
			
				++OffsetIdx;
				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
			
				++OffsetIdx;*/
			}
	//		else
			{
/*				Vertex[ OffsetIdx ].x += Particles[ idx ].Velocity.x;
				Vertex[ OffsetIdx ].y += Particles[ idx ].Velocity.y;
//				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
			
				++OffsetIdx;
				Vertex[ OffsetIdx ].x += Particles[ idx ].Velocity.x;
				Vertex[ OffsetIdx ].y += Particles[ idx ].Velocity.y;
//				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
			
				++OffsetIdx;
				Vertex[ OffsetIdx ].x += Particles[ idx ].Velocity.x;
				Vertex[ OffsetIdx ].y += Particles[ idx ].Velocity.y;
//				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
			
				++OffsetIdx;
				Vertex[ OffsetIdx ].x += Particles[ idx ].Velocity.x;
				Vertex[ OffsetIdx ].y += Particles[ idx ].Velocity.y;
//				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
			
				++OffsetIdx;
*/
				Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
				VertColor[ OffsetIdx ] = gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
			
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
		}
		if( Segment[ SegIdx ].SegIdx == Segment[ SegIdx ].Start )
		{
			Segment[ SegIdx ].Start = Particles.size();
			
			std::sort( Segment.begin(), Segment.end(), compare_segment );
				
			Segment.pop_back();
			
			SegIdx--;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void NewParticleFactory::Draw()
{
	for( size_t SegIdx = 0; SegIdx < Segment.size(); SegIdx++ )
	{
		if( Segment[ SegIdx ].IsAdditive )
		{
			// Enables additive blending //
			Gfx::EnableAddBlend();

			Gfx::DrawQuads(
				&Vertex[ 0 ],
				&TexCoord[ 0 ],
				&VertColor[ 0 ],
				&Indices[ Segment[ SegIdx ].IndicesIdx ],
				Segment[ SegIdx ].IndicesSize - Segment[ SegIdx ].IndicesIdx,
				Segment[ SegIdx ].TextureID
			);
			
			// Disables additive blending //
			Gfx::DisableAddBlend();
		}
		else
		{
			Gfx::DrawQuads(
				&Vertex[ 0 ],
				&TexCoord[ 0 ],
				&VertColor[ 0 ],
				&Indices[ Segment[ SegIdx ].IndicesIdx ],
				Segment[ SegIdx ].IndicesSize - Segment[ SegIdx ].IndicesIdx,
				Segment[ SegIdx ].TextureID
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
