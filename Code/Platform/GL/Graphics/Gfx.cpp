// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GL/gl.h> 
#include <GL/glu.h>

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gfx
{
	// - -------------------------------------------------------------------------------------- - //
	void DrawMesh3D( const std::vector< Engine2D::cMesh3D >& Mesh, const Vector3D& Offset )
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		for( size_t i = 0; i < Mesh.size(); ++i )
		{
			glBindTexture( GL_TEXTURE_2D, Mesh[i].TextureID );
			
			glVertexPointer(3, GL_FLOAT, 0, &(*Mesh[i].Vertex)[0]);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, &(*Mesh[i].VertexColor)[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &(*Mesh[i].TextureCoord)[0]);

			glPushMatrix();
				glTranslatef( Offset.x, Offset.y, Offset.z );
				glDrawElements(
					GL_TRIANGLES, Mesh[i].Indices->Size(),
					GL_UNSIGNED_INT, &(*Mesh[i].Indices)[0]
				);
			glPopMatrix();
		}
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	}	
	// - -------------------------------------------------------------------------------------- - //
	void DrawQuads(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID,
		const Gfx::Color Color
		)
	{
		glBindTexture( GL_TEXTURE_2D, TextureID );
	
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		glVertexPointer(3, GL_FLOAT, 0, &Vertex[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &TexCoord[0]);
	
		glDrawElements(
			GL_QUADS, IndicesSize,
			GL_UNSIGNED_INT, &Indices[0]
		);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	// - -------------------------------------------------------------------------------------- - //
	void DrawQuads(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Color,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID
		)
	{
		glBindTexture( GL_TEXTURE_2D, TextureID );
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		glVertexPointer(3, GL_FLOAT, 0, &Vertex[0]);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, &Color[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &TexCoord[0]);
	
		glDrawElements(
			GL_QUADS, IndicesSize,
			GL_UNSIGNED_INT, &Indices[0]
		);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	// - -------------------------------------------------------------------------------------- - //
	void DrawPolygons(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Color,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID
	)
	{
		glBindTexture( GL_TEXTURE_2D, TextureID );
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		glVertexPointer(3, GL_FLOAT, 0, &Vertex[0]);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, &Color[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &TexCoord[0]);
	
		glDrawElements(
			GL_TRIANGLES, IndicesSize,
			GL_UNSIGNED_INT, &Indices[0]
		);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	// - -------------------------------------------------------------------------------------- - //
	void DrawPolygons(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureId,
		const Gfx::Color Color
		)
	{
		glBindTexture( GL_TEXTURE_2D, TextureId );
	
		//glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glColor4ubv( (GLubyte*)&Color );
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		glVertexPointer(3, GL_FLOAT, 0, &Vertex[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &TexCoord[0]);
	
		glDrawElements(
			GL_TRIANGLES, IndicesSize,
			GL_UNSIGNED_INT, &Indices[0]
		);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	// - -------------------------------------------------------------------------------------- - //
	void DrawLines(
		const ABSet< Vector3D >* Vertex,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const Gfx::Color Color
	)
	{
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		
		glEnableClientState(GL_VERTEX_ARRAY);
	
		glVertexPointer(3, GL_FLOAT, 0, &Vertex[0]);
	
		glDrawElements(
			GL_LINES, IndicesSize,
			GL_UNSIGNED_INT, &Indices[0]
		);
	
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	// - -------------------------------------------------------------------------------------- - //
	void DrawLineStrip(
		const Vector3D* Vertex,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const Gfx::Color Color
	)
	{
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		
		glEnableClientState(GL_VERTEX_ARRAY);
	
		glVertexPointer(3, GL_FLOAT, 0, &Vertex[0]);
	
		glDrawElements(
			GL_LINE_STRIP, IndicesSize,
			GL_UNSIGNED_INT, &Indices[0]
		);
	
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	// - -------------------------------------------------------------------------------------- - //
	void ResetColor()
	{
		glColor4ub( 255, 255, 255, 255 );
	}	
	// - -------------------------------------------------------------------------------------- - //
	unsigned int White()
	{
		return (255) | (255<<8) | (255<<16) | (255<<24);
	}
	// - -------------------------------------------------------------------------------------- - //
	Gfx::Color RGB( int r, int g, int b )
	{
		return r|(g << 8)|(b << 16)|(0xff << 24);
	}
	// - -------------------------------------------------------------------------------------- - //
	Gfx::Color RGBA( int r, int g, int b, int a )
	{
		return r|(g << 8)|(b << 16)|(a << 24);
	}
	// - -------------------------------------------------------------------------------------- - //
	void Circle( const Vector3D& Pos, const Real& Radius, Gfx::Color Color )
	{
		int MaxSteps = 16;
		
		Vector3D Vertex[ MaxSteps + 1 ];
		unsigned int Indices[ MaxSteps + 1 ];
		
		for( int idx = 0; idx <= MaxSteps; idx++ )
		{
			Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

			Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );

			Point *= Radius;
			
			Point += Vector2D( Pos.x, Pos.y );
			
			Vertex[ idx ] = Vector3D( Point.x, Point.y, Pos.z );
			
			Indices[ idx ] = idx;
		}
		
		DrawLineStrip( Vertex, Indices, MaxSteps + 1, Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Circle( const Real& x, const Real& y, const Real& Radius, Gfx::Color Color )
	{
		Circle( Vector3D( x, y, Real::Zero ), Radius, Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Circle( const Vector2D& Pos, const Real& Radius, Gfx::Color Color )
	{
		Circle( Vector3D( Pos.x, Pos.y, Real::Zero ), Radius, Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Vector3D& v1, const Vector3D& v2, Gfx::Color Color )
	{
		Vector3D Vertex[ 2 ];
		unsigned int Indices[ 2 ];
		
		Vertex[ 0 ] = v1;
		Vertex[ 1 ] = v2;
		
		Indices[ 0 ] = 0;
		Indices[ 1 ] = 1;
				
		DrawLineStrip( Vertex, Indices, 2, Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Vector2D& v1, const Vector2D& v2, Gfx::Color Color )
	{
		Line( v1.ToVector3D(), v2.ToVector3D(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Real& x1, const Real& y1, const Real& x2, const Real& y2, Gfx::Color Color )
	{
		Line( Vector3D( x1, y1, Real( 0.0 ) ), Vector3D( x2, y2, Real( 0.0 ) ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, Gfx::Color Color )
	{
		Line( Vector3D( x1, y1, z1 ), Vector3D( x2, y2, z2 ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Vector3D& v1, const Vector3D& v2, Gfx::Color Color )
	{
		Vector3D Vertex[ 4 ];
		unsigned int Indices[ 5 ];
		
		Vertex[ 0 ] = v1;
		Vertex[ 1 ] = Vector3D( v1.x, v2.y, v1.z );
		Vertex[ 2 ] = v2;
		Vertex[ 3 ] = Vector3D( v2.x, v1.y, v2.z );
		
		for( int idx = 0; idx < 4; idx++ )
		{
			Indices[ idx ] = idx;
		}
		Indices[ 4 ] = 0;
				
		DrawLineStrip( Vertex, Indices, 5, Color );		
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Vector2D& v1, const Vector2D& v2, Gfx::Color Color )
	{
		Rect( v1.ToVector3D(), v2.ToVector3D(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Real& x1, const Real& y1, const Real& x2, const Real& y2, Gfx::Color Color )
	{
		Rect( Vector3D( x1, y1, Real( 0.0 ) ), Vector3D( x2, y2, Real( 0.0 ) ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, Gfx::Color Color )
	{
		Rect( Vector3D( x1, y1, z1 ), Vector3D( x2, y2, z2 ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Rect2D& _Rect, Gfx::Color Color )
	{
		Rect( _Rect.P1(), _Rect.P2(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Rect3D& _Rect, Gfx::Color Color )
	{
		Rect( _Rect.P1(), _Rect.P2(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void FilledRect( const Vector3D& v1, const Vector3D& v2, Gfx::Color Color )
	{
		Vector3D Vertex[ 4 ];
		unsigned int Indices[ 4 ];
		
		Vertex[ 0 ] = Vector3D( v1.x, v2.y, v1.z );
		Vertex[ 1 ] = v1;
		Vertex[ 2 ] = Vector3D( v2.x, v1.y, v2.z );
		Vertex[ 3 ] = v2;
		
		for( int idx = 0; idx < 4; idx++ )
		{
			Indices[ idx ] = idx;
		}
				
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		
		glEnableClientState(GL_VERTEX_ARRAY);
	
		glVertexPointer(3, GL_FLOAT, 0, &Vertex[0]);
	
		glDrawElements(
			GL_QUADS, 4,
			GL_UNSIGNED_INT, &Indices[0]
		);
	
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	// - -------------------------------------------------------------------------------------- - //
	void FilledRect( const Vector2D& v1, const Vector2D& v2, Gfx::Color Color )
	{
		FilledRect( v1.ToVector3D(), v2.ToVector3D(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	// This section is to add a wrapper to the gl functions we can't do without.
	// - -------------------------------------------------------------------------------------- - //
	void EnableTex2D()
	{
		glEnable( GL_TEXTURE_2D );
	}
	// - -------------------------------------------------------------------------------------- - //
	void DisableTex2D()
	{
		glDisable( GL_TEXTURE_2D );
	}
	// - -------------------------------------------------------------------------------------- - //
	void EnableBlend()
	{
		glEnable( GL_BLEND );
	}
	// - -------------------------------------------------------------------------------------- - //
	void DisableBlend()
	{
		glDisable( GL_BLEND );
	}
	// - -------------------------------------------------------------------------------------- - //
	void AddBlend()
	{
		// Enables additive blending //
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	// - -------------------------------------------------------------------------------------- - //
	void StandardBlend()
	{
		// Disables additive blending //
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	// - -------------------------------------------------------------------------------------- - //
	void SaturateBlend()
	{
		// Disables additive blending //
		glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	}
	// - -------------------------------------------------------------------------------------- - //
	void EnableDepth()
	{
		glEnable( GL_DEPTH_TEST );
	}
	// - -------------------------------------------------------------------------------------- - //
	void DisableDepth()
	{
		glDisable( GL_DEPTH_TEST );
	}
	// - -------------------------------------------------------------------------------------- - //
	void EnableSmoothPolygon()
	{
		glEnable( GL_POLYGON_SMOOTH );	
	}
	// - -------------------------------------------------------------------------------------- - //
	void DisableSmoothPolygon()
	{
		glDisable( GL_POLYGON_SMOOTH );	
	}
	// - -------------------------------------------------------------------------------------- - //
	void BindTexture( unsigned int& TextureId )
	{
		glBindTexture( GL_TEXTURE_2D, TextureId );
	}
	// - -------------------------------------------------------------------------------------- - //
	void DeleteTexture( unsigned int& TextureId )
	{
		glDeleteTextures( 1, &TextureId );
	}
	// - -------------------------------------------------------------------------------------- - //
	void SetLineWidth( const Real Num )
	{
		glLineWidth( Num );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Viewport( int x, int y, unsigned int Width, unsigned int Height )
	{
		glViewport( x, y, Width, Height );
	}
	// - -------------------------------------------------------------------------------------- - //
	void ProjMatrixMode()
	{
		glMatrixMode (GL_PROJECTION);
	}
	// - -------------------------------------------------------------------------------------- - //
	void ModelMatrixMode()
	{
		glMatrixMode(GL_MODELVIEW);
	}
	// - -------------------------------------------------------------------------------------- - //
	void LoadIdentity()
	{
		glLoadIdentity();
	}
	// - -------------------------------------------------------------------------------------- - //
	void Perspective( double Fovy, double Aspect, double zNear, double zFar )
	{
		gluPerspective( Fovy, Aspect, zNear, zFar );
	}
	// - -------------------------------------------------------------------------------------- - //
	void PushMatrix()
	{
		glPushMatrix();
	}
	// - -------------------------------------------------------------------------------------- - //
	void PopMatrix()
	{
		glPopMatrix();
	}
	// - -------------------------------------------------------------------------------------- - //
	void Translate( const Real x, const Real y, const Real z )
	{
		glTranslatef ( x, y, z );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Translate( const Vector3D& MyVec )
	{
		glTranslatef ( MyVec.x, MyVec.y, MyVec.z );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Translate( const Vector2D& MyVec )
	{
		glTranslatef ( MyVec.x, MyVec.y, Real( 0.0 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rotate( const Real angle, const Real x, const Real y, const Real z )
	{
		glRotatef( angle, x, y, z );
	}
	// - -------------------------------------------------------------------------------------- - //
	void ClearColorDepth()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
	// - -------------------------------------------------------------------------------------- - //
	void SwapBuffers()
	{
		SDL_GL_SwapBuffers();
	}
	// - -------------------------------------------------------------------------------------- - //

// - ------------------------------------------------------------------------------------------ - //
};  // namespace Gfx
// - ------------------------------------------------------------------------------------------ - //
