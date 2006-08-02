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
	Vertex.resize( Num );
	TexCoord.resize( Num );
	VertColor.resize( Num );
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
			
			//TextureID = iter->Animator.CurDrawFrame->TextureID;
			
		}	
	}
	if( ParticleSize > 0 )
	{
		TextureID = Alive.begin()->Animator.CurDrawFrame->TextureID;
				
		size_t VertexSize = ParticleSize;
		ParticleSize *= 4;
		for( size_t idx = VertexSize; idx < ParticleSize; ++idx )
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
