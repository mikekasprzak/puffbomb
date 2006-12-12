// - ------------------------------------------------------------------------------------------ - //
// AnimParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#include "AnimParticleFactory.h"
// - ------------------------------------------------------------------------------------------ - //
AnimParticleFactory AnimFlatParticle;
AnimParticleFactory AnimAdditiveParticle;
// - ------------------------------------------------------------------------------------------ - //
void AnimParticleFactory::Populate( int Num )
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
void AnimParticleFactory::Step()
{
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
			VertColor[ ParticleSize ] = Gfx::RGBA( 255, 255, 255, iter->Alpha );

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
}
// - ------------------------------------------------------------------------------------------ - //
void AnimParticleFactory::Draw()
{
// Without Color changes or alpha //
	Gfx::DrawQuads(
		&Vertex[0],
		&TexCoord[0],
		&VertColor[0],
		&Indices[0],
		ParticleSize,
		TextureID
	);
}
// - ------------------------------------------------------------------------------------------ - //
