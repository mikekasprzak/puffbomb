// - ------------------------------------------------------------------------------------------ - //
// ParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#include "ParticleFactory.h"
// - ------------------------------------------------------------------------------------------ - //
//std::list< cParticle > ParticleFactory::Alive;
//std::list< cParticle > ParticleFactory::Dead;
ParticleFactory FlatParticle;
ParticleFactory AdditiveParticle;
// - ------------------------------------------------------------------------------------------ - //
void ParticleFactory::Populate( int Num )
{
	Vertex.resize( Num * 4 );
	TexCoord.resize( Num * 4 );
	VertColor.resize( Num * 4 );
	Indices.resize( Num * 4 );
//	Indices.resize( Num * 4 );
	
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
		
			Vertex[ ParticleSize ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + iter->Pos).ToVector3D();
			Vertex[ ParticleSize + 1 ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + iter->Pos).ToVector3D();
			Vertex[ ParticleSize + 2 ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + iter->Pos).ToVector3D();
			Vertex[ ParticleSize + 3 ] = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + iter->Pos).ToVector3D();
			TexCoord[ ParticleSize ] = iter->Animator.CurDrawFrame->Face[ 0 ].UV.a;
			TexCoord[ ParticleSize + 1 ] = iter->Animator.CurDrawFrame->Face[ 0 ].UV.b;
			TexCoord[ ParticleSize + 2 ] = iter->Animator.CurDrawFrame->Face[ 0 ].UV.c;
			TexCoord[ ParticleSize + 3 ] = iter->Animator.CurDrawFrame->Face[ 1 ].UV.c;
			VertColor[ ParticleSize ] = gfx::RGBA( 255, 255, 255, iter->Alpha );
			VertColor[ ParticleSize + 1 ] = VertColor[ ParticleSize ];
			VertColor[ ParticleSize + 2 ] = VertColor[ ParticleSize ];
			VertColor[ ParticleSize + 3 ] = VertColor[ ParticleSize ];

			ParticleSize += 4;

/*
//			Indices[ ParticleSize ] = ParticleSize;

			Vertex[ ParticleSize ].a = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + iter->Pos).ToVector3D();
			Vertex[ ParticleSize ].b = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + iter->Pos).ToVector3D();
			Vertex[ ParticleSize ].c = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + iter->Pos).ToVector3D();
			Vertex[ ParticleSize ].d = (iter->Animator.CurDrawFrame->Vertex[ iter->Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + iter->Pos).ToVector3D();
			TexCoord[ ParticleSize ].a = iter->Animator.CurDrawFrame->Face[ 0 ].UV.a;
			TexCoord[ ParticleSize ].b = iter->Animator.CurDrawFrame->Face[ 0 ].UV.b;
			TexCoord[ ParticleSize ].c = iter->Animator.CurDrawFrame->Face[ 0 ].UV.c;
			TexCoord[ ParticleSize ].d = iter->Animator.CurDrawFrame->Face[ 1 ].UV.c;
			VertColor[ ParticleSize ].a = gfx::RGBA( 255, 255, 255, iter->Alpha );
			VertColor[ ParticleSize ].b = VertColor[ ParticleSize ].a;
			VertColor[ ParticleSize ].c = VertColor[ ParticleSize ].a;
			VertColor[ ParticleSize ].d = VertColor[ ParticleSize ].a;

			Indices[ ParticleSize ] = ParticleSize;
			
			++ParticleSize;
*/
			
//			TextureID = iter->Animator.CurDrawFrame->TextureId;
			
		}	
	}
	if( ParticleSize > 0 )
	{
		TextureID = Alive.begin()->Animator.CurDrawFrame->TextureId;
		//Log( LOG_HIGHEST_LEVEL, "ParticleSize " << ParticleSize );
		
		ParticleSize -= 3;
		
		for( size_t idx = 0; idx < ParticleSize; ++idx )
		{
			Indices[ idx ] = idx;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ParticleFactory::Draw()
{
	Gfx::DrawQuads(
		&Vertex[0],
		&TexCoord[0],
		&VertColor[0],
		&Indices[0],
		ParticleSize,
		TextureID
	);

/*	std::list< cParticle >::iterator iter;

	for ( iter = Alive.begin(); iter != Alive.end(); iter++ )
	{
		iter->Draw();
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
