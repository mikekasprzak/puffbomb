// - ------------------------------------------------------------------------------------------ - //
// ParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#include "ParticleFactory.h"
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
ParticleFactory FlatParticle;
ParticleFactory AdditiveParticle;
// - ------------------------------------------------------------------------------------------ - //
void ParticleFactory::Populate( int Num )
{
	Vertex.resize( Num * 4 );
	TexCoord.resize( Num * 4 );
	VertColor.resize( Num * 4 );
	Indices.resize( Num * 4 );

	cAnimation& DummyAni = AnimationPool.Load( "Smoke2.anim" );

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
}
// - ------------------------------------------------------------------------------------------ - //
void ParticleFactory::Step()
{
	AliveSize = 0;
	for( size_t idx = 0; idx < Particles.size(); idx++ )
//	for( size_t idx = 0; idx < CurParticle; idx++ )
	{
		if( Particles[ idx ].Life <= 0 )
		{
			//--CurParticle;
		}
		else
		{
			Particles[ idx ].Step();
			
			Indices[ AliveSize ] = AliveSize;
			Vertex[ AliveSize ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
			TexCoord[ AliveSize ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.a;
			VertColor[ AliveSize ] = gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );

			++AliveSize;
			Indices[ AliveSize ] = AliveSize;
			Vertex[ AliveSize ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
			TexCoord[ AliveSize ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.b;
			VertColor[ AliveSize ] = VertColor[ AliveSize - 1 ];

			++AliveSize;
			Indices[ AliveSize ] = AliveSize;
			Vertex[ AliveSize ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
			TexCoord[ AliveSize ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.c;
			VertColor[ AliveSize ] = VertColor[ AliveSize - 1 ];

			++AliveSize;
			Indices[ AliveSize ] = AliveSize;
			Vertex[ AliveSize ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
			TexCoord[ AliveSize ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].UV.c;
			VertColor[ AliveSize ] = VertColor[ AliveSize - 1 ];

			++AliveSize;
		}	
	}
	if( Particles.size() > 0 )
	{
		TextureID = Particles[ 0 ].Animator.CurDrawFrame->TextureId;
		//Log( LOG_HIGHEST_LEVEL, "ParticleSize " << ParticleSize );
	}
}
/*// - ------------------------------------------------------------------------------------------ - //
void ParticleFactory::Populate( int Num )
{
	Vertex.resize( Num * 4 );
	TexCoord.resize( Num * 4 );
	VertColor.resize( Num * 4 );
	Indices.resize( Num * 4 );
	
	for( int idx = 0; idx < Num; ++idx )
	{
		Dead.push_back( cParticle() );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ParticleFactory::Step()
{
	std::list< cParticle >::iterator iter;
	std::list< cParticle >::iterator TempIter;
	
	ParticleSize = 0;
	
	for ( iter = Alive.begin(); iter != Alive.end(); iter++ )
	{
		iter->Step();
		
		if( iter->Life <= 0 )
		{
			TempIter = iter;
			iter++;
			
			Dead.splice(
				Dead.end(), 
            	Alive,
            	TempIter
            );
			iter--;
		}
		else
		{
			Indices[ ParticleSize ] = ParticleSize;
			Vertex[ ParticleSize ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + iter->Pos).ToVector3D();
			TexCoord[ ParticleSize ] = iter->Animator.CurDrawFrame->Face[ 0 ].UV.a;
			VertColor[ ParticleSize ] = gfx::RGBA( 255, 255, 255, iter->Alpha );

			++ParticleSize;
			Indices[ ParticleSize ] = ParticleSize;
			Vertex[ ParticleSize ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + iter->Pos).ToVector3D();
			TexCoord[ ParticleSize ] = iter->Animator.CurDrawFrame->Face[ 0 ].UV.b;
			VertColor[ ParticleSize ] = VertColor[ ParticleSize - 1 ];


			++ParticleSize;
			Indices[ ParticleSize ] = ParticleSize;
			Vertex[ ParticleSize ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + iter->Pos).ToVector3D();
			TexCoord[ ParticleSize ] = iter->Animator.CurDrawFrame->Face[ 0 ].UV.c;
			VertColor[ ParticleSize ] = VertColor[ ParticleSize - 1 ];

			++ParticleSize;
			Indices[ ParticleSize ] = ParticleSize;
			Vertex[ ParticleSize ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + iter->Pos).ToVector3D();
			TexCoord[ ParticleSize ] = iter->Animator.CurDrawFrame->Face[ 1 ].UV.c;
			VertColor[ ParticleSize ] = VertColor[ ParticleSize - 1 ];

			++ParticleSize;
		}	
	}
	if( ParticleSize > 0 )
	{
		TextureID = Alive.begin()->Animator.CurDrawFrame->TextureId;
		//Log( LOG_HIGHEST_LEVEL, "ParticleSize " << ParticleSize );
	}
}*/
// - ------------------------------------------------------------------------------------------ - //
void ParticleFactory::Draw()
{
	Gfx::DrawQuads(
		&Vertex[0],
		&TexCoord[0],
		&VertColor[0],
		&Indices[0],
		AliveSize,
		TextureID
	);
/*
	Gfx::DrawQuads(
		&Vertex[0],
		&TexCoord[0],
		&VertColor[0],
		&Indices[0],
		Indices.size(),
		TextureID
	);
*/
}
// - ------------------------------------------------------------------------------------------ - //
