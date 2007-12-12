// - ------------------------------------------------------------------------------------------ - //
// Animator //
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Animator.h"
#include "AnimationPool.h"

#include <Graphics/Gfx.h>
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
cAnimator::cAnimator() :
	Animation( 0 ),
	CurrentFrame( 0 ),
	Time( 1 ),
	IsActive( true )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
cAnimator::cAnimator( const std::string& AnimationName ) :
	Animation( &AnimationPool.Load( AnimationName ) ),
	CurrentFrame( 0 ),
	Time( 1 ),
	CurDrawFrame( &Animation->Frame[ CurrentFrame ].MyFrame )
{
	IsActive = Animation->IsActive;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Set( cAnimation* _Animation, const int _CurrentFrame )
{
	Animation = _Animation;
	// "-1" means perform an animation inversion //
	if ( _CurrentFrame == -1 ) {
		CurrentFrame = Animation->Frame.size() - 1 - CurrentFrame;
		Time = Animation->Frame[ CurrentFrame ].GetTime() - Time - 2;
		if ( Time < 1 )
			Time = 1;
		if ( Time > Animation->Frame[ CurrentFrame ].GetTime() )
			Time = Animation->Frame[ CurrentFrame ].GetTime();
	}
	else {
		CurrentFrame = _CurrentFrame;
		Time = 1;
	}
	IsActive = Animation->IsActive;
	
	CurDrawFrame = &Animation->Frame[ CurrentFrame ].MyFrame;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::SetFrame( const int _CurrentFrame )
{
	CurrentFrame = _CurrentFrame;
	Time = 1;
	IsActive = Animation->IsActive;
	
	CurDrawFrame = &Animation->Frame[ CurrentFrame ].MyFrame;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Step()
{
	if( IsActive )
	{
		if( Animation->Frame.size() != 1 )
		{
			if( Animation->Interpolate )
			{
				if( size_t( CurrentFrame ) < Animation->Frame.size() - 1 )
				{
					// If we have the same number of vertices, we can interpolate //
					if( Animation->Frame[ CurrentFrame ].MyFrame.Vertex.size() ==
						Animation->Frame[ CurrentFrame + 1 ].MyFrame.Vertex.size() )
					{
						// Vertex Interpolation //
						for( size_t idx = 0; idx < InterpFrame.Vertex.size(); ++idx )
						{
							InterpFrame.Vertex[ idx ].Pos
							 += ( Animation->Frame[ CurrentFrame + 1 ].MyFrame.Vertex[ idx ].Pos -
								Animation->Frame[ CurrentFrame ].MyFrame.Vertex[ idx ].Pos ) *
								( Real( 1 ) / Real( Animation->Frame[ CurrentFrame ].GetTime() ) );
							
						}
					}
					// Color Interpolation //
					int ColorIncrement = 0;
					
					int RedValue = 0;
					int GreenValue = 0;
					int BlueValue = 0;
					int AlphaValue = 0;
					
					int Value1 = 0;
					int Value2 = 0;
					
					Value1 = (Animation->Frame[ CurrentFrame + 1 ].MyFrame.Color) & 0xff;
					Value2 = (Animation->Frame[ CurrentFrame ].MyFrame.Color) & 0xff;
									
					ColorIncrement = Real( Value1 - Value2 ) / Real( Animation->Frame[ CurrentFrame ].GetTime() );
					
					RedValue = ( (InterpFrame.Color) & 0xff ) + ColorIncrement;
	
					Value1 = (Animation->Frame[ CurrentFrame + 1 ].MyFrame.Color>>8) & 0xff;
					Value2 = (Animation->Frame[ CurrentFrame ].MyFrame.Color>>8) & 0xff;
					
					ColorIncrement = Real( Value1 - Value2 ) / Real( Animation->Frame[ CurrentFrame ].GetTime() );
				
					GreenValue = ( (InterpFrame.Color>>8) & 0xff ) + ColorIncrement;
	
					Value1 = (Animation->Frame[ CurrentFrame + 1 ].MyFrame.Color>>16) & 0xff;
					Value2 = (Animation->Frame[ CurrentFrame ].MyFrame.Color>>16) & 0xff;
	
					ColorIncrement = Real( Value1 - Value2 ) / Real( Animation->Frame[ CurrentFrame ].GetTime() );
					
					BlueValue = ( (InterpFrame.Color>>16) & 0xff ) + ColorIncrement;
	
					Value1 = (Animation->Frame[ CurrentFrame + 1 ].MyFrame.Color>>24) & 0xff;
					Value2 = (Animation->Frame[ CurrentFrame ].MyFrame.Color>>24) & 0xff;
	
					ColorIncrement = Real( Value1 - Value2 ) / Real( Animation->Frame[ CurrentFrame ].GetTime() );
					
					AlphaValue = ( (InterpFrame.Color>>24) & 0xff ) + ColorIncrement;
					
					if( RedValue > 255 )
					{
						RedValue = 255;	
					}
					if( GreenValue > 255 )
					{
						GreenValue = 255;	
					}
					if( BlueValue > 255 )
					{
						BlueValue = 255;	
					}
					if( AlphaValue > 255 )
					{
						AlphaValue = 255;	
					}
	
					if( RedValue < 0 )
					{
						RedValue = 0;	
					}
					if( GreenValue < 0 )
					{
						GreenValue = 0;	
					}
					if( BlueValue < 0 )
					{
						BlueValue = 0;	
					}
					if( AlphaValue < 0 )
					{
						AlphaValue = 0;	
					}
					
					InterpFrame.Color = Gfx::RGBA( RedValue, GreenValue, BlueValue, AlphaValue );
						
//					Log( 10, "ColorIncrement " << ColorIncrement );
//					Log( 10, "AlphaValue " << AlphaValue );
							
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
				Time = 1;
			}
			if( Time == 1 )
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
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Draw( const Vector2D& Offset, int Color )
{
	if( !CurDrawFrame->Face.empty() )
	{
		if( size_t( Color ) != Gfx::White() )
		{
			CurDrawFrame->Color = Color;
		}

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
			CurDrawFrame->Color
		);	
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::Draw( const Vector2D& Offset, const Matrix2x2& Matrix, int Color )
{
	if( !CurDrawFrame->Face.empty() )
	{
		if( size_t( Color ) != Gfx::White() )
		{
			CurDrawFrame->Color = Color;
		}

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
			CurDrawFrame->Color
		);	
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::DrawQuad( const Vector2D& Offset, int Color, Real Scale )
{
	if( CurDrawFrame->Face.size() > 1 )
	{
		if( size_t( Color ) != Gfx::White() )
		{
			CurDrawFrame->Color = Color;
		}

		unsigned int IndicesSize = 4;
		
		Vector3D Vertex[ IndicesSize ];
		Vector2D TexCoord[ IndicesSize ];
	
		unsigned int Indices[ IndicesSize ];
			
		Vertex[	0 ] = ( ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos * Scale ) + Offset ).ToVector3D();
		TexCoord[ 0 ] = CurDrawFrame->Face[ 0 ].UV.a;

		Vertex[	1 ] = ( ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos * Scale ) + Offset ).ToVector3D();
		TexCoord[ 1 ] = CurDrawFrame->Face[ 0 ].UV.b;

		Vertex[	2 ] = ( ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos * Scale ) + Offset ).ToVector3D();
		TexCoord[ 2 ] = CurDrawFrame->Face[ 0 ].UV.c;

		Vertex[	3 ] = ( ( CurDrawFrame->Vertex[ CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos * Scale ) + Offset ).ToVector3D();
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
			CurDrawFrame->Color
		);	
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimator::DrawQuad( const Vector2D& Offset, const Matrix2x2& Matrix, int Color )
{
	if( CurDrawFrame->Face.size() > 1 )
	{
		if( size_t( Color ) != Gfx::White() )
		{
			CurDrawFrame->Color = Color;
		}
		
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
			CurDrawFrame->Color
		);	
	}
}
// - ------------------------------------------------------------------------------------------ - //
