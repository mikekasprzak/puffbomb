// - ------------------------------------------------------------------------------------------ - //
// Animator //
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Animator.h"
#include "AnimationPool.h"

#include <Graphics/Gfx.h>
#include <Geometry/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
cAnimator::cAnimator() :
	Animation( 0 ),
	CurrentFrame( 0 ),
	Time( 0 )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
cAnimator::cAnimator( const std::string& AnimationName ) :
	Animation( &AnimationPool.Load( AnimationName ) ),
	CurrentFrame( 0 ),
	Time( 0 ),
	CurDrawFrame( &Animation->Frame[ CurrentFrame ].MyFrame )
{
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Set( cAnimation* _Animation, const int _CurrentFrame )
{
	Animation = _Animation;
	CurrentFrame = _CurrentFrame;
	Time = 0;
	
	CurDrawFrame = &Animation->Frame[ CurrentFrame ].MyFrame;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Step()
{
	if( Animation->Frame.size() != 1 )
	{
		if( Animation->Interpolate )
		{
			if( size_t( CurrentFrame ) < Animation->Frame.size() - 1 )
			{
				if( Animation->Frame[ CurrentFrame ].MyFrame.Vertex.size() ==
					Animation->Frame[ CurrentFrame + 1 ].MyFrame.Vertex.size() )
				{
					for( size_t idx = 0; idx < InterpFrame.Vertex.size(); ++idx )
					{
						InterpFrame.Vertex[ idx ].Pos
						 += ( Animation->Frame[ CurrentFrame + 1 ].MyFrame.Vertex[ idx ].Pos -
							Animation->Frame[ CurrentFrame ].MyFrame.Vertex[ idx ].Pos ) *
							( Real( 1 ) / Real( Animation->Frame[ CurrentFrame ].GetTime() ) );
						
					}
				}
				
			}
		}
		
		if( Time > Animation->Frame[ CurrentFrame ].GetTime() )
		{
			if( CurrentFrame < int( Animation->Frame.size() - 1 ) )
			{
				++CurrentFrame;
				
				CurDrawFrame = &Animation->Frame[ CurrentFrame ].MyFrame;
				
				if( Animation->Interpolate )
				{
					InterpFrame = Animation->Frame[ CurrentFrame ].MyFrame;
					
					CurDrawFrame = &InterpFrame;
				}
			}
			else
			{
				CurrentFrame = Animation->LoopPoint;
				
				CurDrawFrame = &Animation->Frame[ CurrentFrame ].MyFrame;
			}
			Time = 0;
		}
		if( Time == 0 )
		{
			if( Animation->Interpolate )
			{
				InterpFrame = Animation->Frame[ CurrentFrame ].MyFrame;
				
				CurDrawFrame = &InterpFrame;
			}	
		}
		
		++Time;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Draw( const Vector2D& Offset, int Color )
{
	if( !CurDrawFrame->Face.empty() )
	{
		unsigned int IndicesSize = CurDrawFrame->Face.size() * 3;
		
		Vector3D Vertex[ IndicesSize ];
		Vector2D TexCoord[ IndicesSize ];
	
		unsigned int Indices[ IndicesSize ];
		
		int VertexIdx = 0;
		
		for( size_t idx = 0; idx < CurDrawFrame->Face.size(); ++idx )
		{
			
			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.a ].Pos + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.a;
			VertexIdx++;

			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.c ].Pos + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.b;
			VertexIdx++;

			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.b ].Pos + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.c;
			VertexIdx++;
		}		
		
		for( size_t idx = 0; idx < IndicesSize; ++idx )
		{
			Indices[ idx ] = idx;
		}
		
		Gfx::DrawPolygons(
			Vertex,
			TexCoord,
			Indices,
			IndicesSize,
			CurDrawFrame->TextureId,
			Color
		);	
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Draw( const Vector2D& Offset, const Matrix2x2& Matrix, int Color )
{
	if( !CurDrawFrame->Face.empty() )
	{
		unsigned int IndicesSize = CurDrawFrame->Face.size() * 3;
		
		Vector3D Vertex[ IndicesSize ];
		Vector2D TexCoord[ IndicesSize ];
	
		unsigned int Indices[ IndicesSize ];
		
		int VertexIdx = 0;
		
		for( size_t idx = 0; idx < CurDrawFrame->Face.size(); ++idx )
		{
			
			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.a ].Pos.ToMatrix2x1() * Matrix + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.a;
			VertexIdx++;

			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.c ].Pos.ToMatrix2x1() * Matrix + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.b;
			VertexIdx++;

			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.b ].Pos.ToMatrix2x1() * Matrix + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.c;
			VertexIdx++;
		}		
		
		for( size_t idx = 0; idx < IndicesSize; ++idx )
		{
			Indices[ idx ] = idx;
		}
		
		Gfx::DrawPolygons(
			Vertex,
			TexCoord,
			Indices,
			IndicesSize,
			CurDrawFrame->TextureId,
			Color
		);	
	}	
	
/*	if( !CurDrawFrame->Face.empty() )
	{
		unsigned int IndicesSize = CurDrawFrame->Face.size() * 3;
		
		Vector3D Vertex[ IndicesSize ];
		Vector2D TexCoord[ IndicesSize ];
	
		unsigned int Indices[ IndicesSize ];
		
		int VertexIdx = 0;
		
		for( size_t idx = 0; idx < CurDrawFrame->Face.size(); ++idx )
		{
			
			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.a ].Pos.ToMatrix2x1() * Matrix ) + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.a;
			VertexIdx++;

			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.c ].Pos.ToMatrix2x1() * Matrix ) + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.b;
			VertexIdx++;

			Vertex[	VertexIdx ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.b ].Pos.ToMatrix2x1() * Matrix ) + Offset ).ToVector3D();
			TexCoord[ VertexIdx ] = CurDrawFrame->Face[ idx ].UV.c;
			VertexIdx++;
		}		
				
		Gfx::DrawPolygons(
			Vertex,
			TexCoord,
			Indices,
			IndicesSize,
			CurDrawFrame->TextureId
		);	
	}	
	*/
/*	glBindTexture( GL_TEXTURE_2D, CurDrawFrame->TextureId );

	for( size_t idx = 0; idx < CurDrawFrame->Face.size(); ++idx )
	{
		gfx::Face(
			( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.a ].Pos.ToMatrix2x1() * Matrix ) + Offset,
			( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.c ].Pos.ToMatrix2x1() * Matrix ) + Offset,
			( CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.b ].Pos.ToMatrix2x1() * Matrix ) + Offset,
			CurDrawFrame->Face[ idx ].UV.a,
			CurDrawFrame->Face[ idx ].UV.b,
			CurDrawFrame->Face[ idx ].UV.c
		);
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::DrawQuad( const Vector2D& Offset, int Color )
{
	if(  CurDrawFrame->Face.size() > 1 )
	{
		unsigned int IndicesSize = 4;
		
		Vector3D Vertex[ IndicesSize ];
		Vector2D TexCoord[ IndicesSize ];
	
		unsigned int Indices[ IndicesSize ];
			
		Vertex[	0 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Offset ).ToVector3D();
		TexCoord[ 0 ] = CurDrawFrame->Face[ 0 ].UV.a;

		Vertex[	1 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Offset ).ToVector3D();
		TexCoord[ 1 ] = CurDrawFrame->Face[ 0 ].UV.b;

		Vertex[	2 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Offset ).ToVector3D();
		TexCoord[ 2 ] = CurDrawFrame->Face[ 0 ].UV.c;

		Vertex[	3 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Offset ).ToVector3D();
		TexCoord[ 3 ] = CurDrawFrame->Face[ 1 ].UV.c;
		
		for( size_t idx = 0; idx < IndicesSize; ++idx )
		{
			Indices[ idx ] = idx;
		}
		
		Gfx::DrawQuads(
			Vertex,
			TexCoord,
			Indices,
			IndicesSize,
			CurDrawFrame->TextureId,
			Color
		);	
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::DrawQuad( const Vector2D& Offset, const Matrix2x2& Matrix, int Color )
{
	if( CurDrawFrame->Face.size() > 1 )
	{
		unsigned int IndicesSize = 4;
		
		Vector3D Vertex[ IndicesSize ];
		Vector2D TexCoord[ IndicesSize ];
	
		unsigned int Indices[ IndicesSize ];
			
		Vertex[	0 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos.ToMatrix2x1() * Matrix + Offset ).ToVector3D();
		TexCoord[ 0 ] = CurDrawFrame->Face[ 0 ].UV.a;

		Vertex[	1 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos.ToMatrix2x1() * Matrix + Offset ).ToVector3D();
		TexCoord[ 1 ] = CurDrawFrame->Face[ 0 ].UV.b;

		Vertex[	2 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos.ToMatrix2x1() * Matrix + Offset ).ToVector3D();
		TexCoord[ 2 ] = CurDrawFrame->Face[ 0 ].UV.c;

		Vertex[	3 ] = ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos.ToMatrix2x1() * Matrix + Offset ).ToVector3D();
		TexCoord[ 3 ] = CurDrawFrame->Face[ 1 ].UV.c;
		
		for( size_t idx = 0; idx < IndicesSize; ++idx )
		{
			Indices[ idx ] = idx;
		}
		
		Gfx::DrawQuads(
			Vertex,
			TexCoord,
			Indices,
			IndicesSize,
			CurDrawFrame->TextureId,
			Color
		);	
	}
}
// - ------------------------------------------------------------------------------------------ - //
