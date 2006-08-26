// - ------------------------------------------------------------------------------------------ - //
// Animator //
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GL/gl.h>  // **Remove** //
#include <GL/glu.h> // **Remove** //
// - ------------------------------------------------------------------------------------------ - //
#include "Animator.h"
#include <Graphics/Gfx.h>
#include <Geometry/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
cAnimator::cAnimator() :
	CurrentFrame( 0 ),
	Time( 0 )
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
void cAnimator::Draw( const Vector2D& Offset )
{
	glBindTexture( GL_TEXTURE_2D, CurDrawFrame->TextureId );

	for( size_t idx = 0; idx < CurDrawFrame->Face.size(); ++idx )
	{
		gfx::Face(
			CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.a ].Pos + Offset,
			CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.c ].Pos + Offset,
			CurDrawFrame->Vertex[ CurDrawFrame->Face[ idx ].VertexIdx.b ].Pos + Offset,
			CurDrawFrame->Face[ idx ].UV.a,
			CurDrawFrame->Face[ idx ].UV.b,
			CurDrawFrame->Face[ idx ].UV.c
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Draw( const Vector2D& Offset, const Matrix2x2& Matrix )
{
	glBindTexture( GL_TEXTURE_2D, CurDrawFrame->TextureId );

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
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::DrawQuad( const Vector2D& Offset )
{
	if( !CurDrawFrame->Face.empty() )
	{
		glBindTexture( GL_TEXTURE_2D, CurDrawFrame->TextureId );
	
		gfx::Quad(
			CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Offset,
			CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Offset,
			CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Offset,
			CurDrawFrame->Vertex[ CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Offset,
			CurDrawFrame->Face[ 0 ].UV.a,
			CurDrawFrame->Face[ 0 ].UV.b,
			CurDrawFrame->Face[ 0 ].UV.c,
			CurDrawFrame->Face[ 1 ].UV.c
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::DrawQuad( const Vector2D& Offset, const Matrix2x2& Matrix )
{
	if( !CurDrawFrame->Face.empty() )
	{
		glBindTexture( GL_TEXTURE_2D, CurDrawFrame->TextureId );
	
		gfx::Quad(
			( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos.ToMatrix2x1() * Matrix ) + Offset,
			( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos.ToMatrix2x1() * Matrix ) + Offset,
			( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos.ToMatrix2x1() * Matrix ) + Offset,
			( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos.ToMatrix2x1() * Matrix ) + Offset,
			CurDrawFrame->Face[ 0 ].UV.a,
			CurDrawFrame->Face[ 0 ].UV.b,
			CurDrawFrame->Face[ 0 ].UV.c,
			CurDrawFrame->Face[ 1 ].UV.c
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
