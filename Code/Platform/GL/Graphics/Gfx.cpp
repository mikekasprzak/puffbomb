// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GL/gl.h> 
#include <GL/glu.h>

#include <Graphics/Gfx.h>
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
void gfx::Circle( const Real& x, const Real& y, const Real& Radius, int Color ) {
	glBegin(GL_LINE_STRIP);
		// How to draw a circle.  This generates points. //
		int MaxSteps = 20;
		for( int idx = 0; idx <= MaxSteps; idx++ ) {
			Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

			Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
			// Do Stuff Here //
			Point *= Radius;
			
			Point += Vector2D( x, y );

			glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
			glVertex3f( Point.x, Point.y, 0.0 );
		}
	glEnd();

}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Circle( const Vector2D& v, const Real& Radius, int Color ) {
	Circle( v.x, v.y, Radius, Color );
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Line( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color ) {
	glBegin(GL_LINES);
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glVertex3f(x1, y1, 0.0);
		glVertex3f(x2, y2, 0.0);
	glEnd();

}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Line( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color, int Color2 ) {

	glBegin(GL_LINES);
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glVertex3f(x1, y1, 0.0);
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glVertex3f(x2, y2, 0.0);
	glEnd();

}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Line( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, int Color ) {
	glBegin(GL_LINES);
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);
	glEnd();

}
// - ------------------------------------------------------------------------------------------ - //
/*void gfx::Draw3DModel( const size_t& obj, const size_t& lookup, const size_t& idx, const cLevelData* Model )
{
	const Vector3D* FaceA = &Model->Model->Object[obj].Vertex[Model->Model->Object[obj].Group[lookup].Face[idx].Vertex.a];
	const Vector3D* FaceB = &Model->Model->Object[obj].Vertex[Model->Model->Object[obj].Group[lookup].Face[idx].Vertex.b];
	const Vector3D* FaceC = &Model->Model->Object[obj].Vertex[Model->Model->Object[obj].Group[lookup].Face[idx].Vertex.c];
	
	const int ColorA = Model->Model->Object[obj].Group[lookup].Face[idx].VertColor.a;
	const int ColorB = Model->Model->Object[obj].Group[lookup].Face[idx].VertColor.b;
	const int ColorC = Model->Model->Object[obj].Group[lookup].Face[idx].VertColor.c;
	
	const Vector3D* Normal = &Model->Model->VertexNormal[Model->Model->Object[obj].Group[lookup].Face[idx].Normal.a];

	const Vector3D* TexCoordA = &Model->Model->TextureCoord[Model->Model->Object[obj].Group[lookup].Face[idx].UV.a];
	const Vector3D* TexCoordB = &Model->Model->TextureCoord[Model->Model->Object[obj].Group[lookup].Face[idx].UV.b];
	const Vector3D* TexCoordC = &Model->Model->TextureCoord[Model->Model->Object[obj].Group[lookup].Face[idx].UV.c];
	
	// Why is normal x z y?
	glBegin(GL_POLYGON);
		glNormal3f( Normal->x, Normal->z, Normal->y);
		glColor4ub( ColorA & 0xff, (ColorA>>8) & 0xff, (ColorA>>16) & 0xff, (ColorA>>24) & 0xff );
		glTexCoord2f(TexCoordA->x, TexCoordA->y);
		glVertex3f( FaceA->x + Model->Pos.x, FaceA->y + Model->Pos.y, -FaceA->z );
		glColor4ub( ColorB & 0xff, (ColorB>>8) & 0xff, (ColorB>>16) & 0xff, (ColorB>>24) & 0xff );
		glTexCoord2f(TexCoordB->x, TexCoordB->y);
		glVertex3f( FaceB->x + Model->Pos.x, FaceB->y + Model->Pos.y, -FaceB->z );
		glColor4ub( ColorC & 0xff, (ColorC>>8) & 0xff, (ColorC>>16) & 0xff, (ColorC>>24) & 0xff );
		glTexCoord2f(TexCoordC->x, TexCoordC->y);
		glVertex3f( FaceC->x + Model->Pos.x, FaceC->y + Model->Pos.y, -FaceC->z );
	glEnd();

}*/
// - ------------------------------------------------------------------------------------------ - //
void gfx::Face( const Vector3D& a, const Vector3D& b, const Vector3D& c,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc )
{
	glBegin(GL_POLYGON);
		glNormal3f( 1.0f, 0.0f, 0.0f );
		//glColor3ub( 255, 255, 255 );
		glTexCoord2f(UVa.x, UVa.y);
		glVertex3f( a.x, a.y, a.z );
		glTexCoord2f(UVb.x, UVb.y);
		glVertex3f( c.x, c.y, c.z );
		glTexCoord2f(UVc.x, UVc.y);
		glVertex3f( b.x, b.y, b.z );
	glEnd();
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Face( const Vector2D& a, const Vector2D& b, const Vector2D& c,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc )
{
	Vector3D TempA = Vector3D( a.x, a.y, 0.0 );
	Vector3D TempB = Vector3D( b.x, b.y, 0.0 );
	Vector3D TempC = Vector3D( c.x, c.y, 0.0 );
	
	Face( TempA, TempB, TempC, UVa, UVb, UVc );

}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Face( const Vector2D& a, const Vector2D& b, const Vector2D& c,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc,
				const Real& z )
{
	Vector3D TempA = Vector3D( a.x, a.y, z );
	Vector3D TempB = Vector3D( b.x, b.y, z );
	Vector3D TempC = Vector3D( c.x, c.y, z );
	
	Face( TempA, TempB, TempC, UVa, UVb, UVc );

}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Polygon( const Vector3D& a, const Vector3D& b, const Vector3D& c, int Color )
{
//	Vector3D Offset = Vector3D( cGlobal::Origin.x, cGlobal::Origin.y, 0.0 );

	glBegin(GL_POLYGON);
		glNormal3f( 0.0f, 1.0f, 1.0f );
		//glColor3ub(Color&0xff, (Color >> 8) &0xff, (Color >> 16) &0xff);
		glVertex3f( a.x, a.y, a.z );
		glTexCoord2f(0.0, 0.0);
		glVertex3f( c.x, c.y, c.z );
		glTexCoord2f(1.0, 1.0);
		glVertex3f( b.x, b.y, b.z );
		glTexCoord2f(0.0, 1.0);
	glEnd();

}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Line( const Vector2D& v1, const Vector2D& v2, int Color ) {
	Line( v1.x, v1.y, v2.x, v2.y, Color );
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Line( const Vector2D& v1, const Vector2D& v2, int Color, int Color2 ) {
	Line( v1.x, v1.y, v2.x, v2.y, Color, Color2 );
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Line( const Vector2D& v1, const Vector2D& v2, const Real& z, int Color ) {
	Line( v1.x, v1.y, z, v2.x, v2.y, z, Color );
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Rect( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color ) {
//	Vector2D Offset1 = cGlobal::Origin + Vector2D( x1, y1 );
	//Offset1.y = -Offset1.y;
//	Vector2D Offset2 = cGlobal::Origin + Vector2D( x2, y2 );
	//Offset2.y = -Offset2.y;

//	Vector2D Offset1 = Vector2D( x1, y1 );
//	Vector2D Offset2 = Vector2D( x2, y2 );

/*	glBegin(GL_LINES);
		//glColor3f(1.0, 1.0, 0.0);
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glVertex3f(Offset1.x , Offset1.y, 0.0 );
		glVertex3f(Offset2.x , Offset1.y, 0.0 );

		glVertex3f(Offset2.x , Offset1.y, 0.0 );
		glVertex3f(Offset2.x , Offset2.y, 0.0 );

		glVertex3f(Offset2.x , Offset2.y, 0.0 );
		glVertex3f(Offset1.x , Offset2.y, 0.0 );

		glVertex3f(Offset1.x , Offset2.y, 0.0 );
		glVertex3f(Offset1.x , Offset1.y, 0.0 );
	glEnd();
*/
	glBegin(GL_LINES);
		//glColor3f(1.0, 1.0, 0.0);
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glVertex3f(x1, y1, 0.0 );
		glVertex3f(x2, y1, 0.0 );

		glVertex3f(x2, y1, 0.0 );
		glVertex3f(x2, y2, 0.0 );

		glVertex3f(x2, y2, 0.0 );
		glVertex3f(x1, y2, 0.0 );

		glVertex3f(x1, y2, 0.0 );
		glVertex3f(x1, y1, 0.0 );
	glEnd();

/*	rect( Buffer, 
		((int)Offset1.x) + (cGlobal::ScreenW),
		((int)Offset1.y) + (cGlobal::ScreenH),
		((int)Offset2.x) + (cGlobal::ScreenW),
		((int)Offset2.y) + (cGlobal::ScreenH),
		Color
		);
	*/
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Rect( const Vector2D& v1, const Vector2D& v2, int Color ) {
	Rect( v1.x, v1.y, v2.x, v2.y, Color );
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Rect( const Rect2D& _Rect, int Color ) {
	Rect( _Rect.P1().x, _Rect.P1().y, _Rect.P2().x, _Rect.P2().y, Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int gfx::RGB( int r, int g, int b ) {
	return r|(g << 8)|(b << 16);
	//return makecol( r, g, b );
}
// - ------------------------------------------------------------------------------------------ - //
int gfx::RGBA( int r, int g, int b, int a ) {
	return r|(g << 8)|(b << 16)|(a << 24);
	//return makecol( r, g, b );
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Quad( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc, const Vector2D& UVd  )
{
//	Vector3D Offset = Vector3D( 0.0, 0.0, 0.0 );
//	Vector3D Offset = Vector3D( cGlobal::Origin.x, cGlobal::Origin.y, 0.0 );

	glBegin(GL_QUADS);
		glNormal3f( 1.0f, 0.0f, 0.0f );
		glTexCoord2f(UVa.x, UVa.y);
		glVertex3f( a.x, a.y, a.z );

		glTexCoord2f(UVb.x, UVb.y);
		glVertex3f( b.x, b.y, b.z );

		glTexCoord2f(UVc.x, UVc.y);
		glVertex3f( c.x, c.y, c.z );

		glTexCoord2f(UVd.x, UVd.y);
		glVertex3f( d.x, d.y, d.z );
	glEnd();
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Quad( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d,
				Vector2D UVa, Vector2D UVb )
{
	UVa.x /= Real( 512 );
	UVa.y /= Real( 512 );
	UVb.x /= Real( 512 );
	UVb.y /= Real( 512 );

	glBegin(GL_QUADS);
		glNormal3f( 1.0f, 0.0f, 0.0f );
		glTexCoord2f(UVa.x, UVa.y);
		glVertex3f( a.x, a.y, a.z );

		glTexCoord2f(UVa.x, UVb.y);
		glVertex3f( b.x, b.y, b.z );

		glTexCoord2f(UVb.x, UVb.y);
		glVertex3f( c.x, c.y, c.z );

		glTexCoord2f(UVb.x, UVa.y);
		glVertex3f( d.x, d.y, d.z );
	glEnd();
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::Quad( const Vector2D& a, const Vector2D& b, const Vector2D& c, const Vector2D& d,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc, const Vector2D& UVd )
{
	Vector3D TempA = Vector3D( a.x, a.y, 0.0 );
	Vector3D TempB = Vector3D( b.x, b.y, 0.0 );
	Vector3D TempC = Vector3D( c.x, c.y, 0.0 );
	Vector3D TempD = Vector3D( d.x, d.y, 0.0 );
	
	Quad( TempA, TempB, TempC, TempD, UVa, UVb, UVc, UVd );

}
// - ------------------------------------------------------------------------------------------ - //
void gfx::FilledRect( const Vector2D& a, const Vector2D& b, int Color )
{
	//Vector3D Offset = Vector3D( cGlobal::Origin.x, cGlobal::Origin.y, 0.0 );
		
	glBegin(GL_QUADS);
		glNormal3f( 1.0f, 0.0f, 0.0f );
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glTexCoord2f(0.0, 0.0);
		glVertex3f( a.x /*+ Offset.x*/, a.y /*+ Offset.y*/, 0.0 );

		glTexCoord2f(1.0, 0.0);
		glVertex3f( b.x /*+ Offset.x*/, a.y /*+ Offset.y*/, 0.0 );

		glTexCoord2f(1.0, 1.0);
		glVertex3f( b.x /*+ Offset.x*/, b.y /*+ Offset.y*/, 0.0 );

		glTexCoord2f(0.0, 1.0);
		glVertex3f( a.x /*+ Offset.x*/, b.y /*+ Offset.y*/, 0.0 );
	glEnd();
}
// - ------------------------------------------------------------------------------------------ - //
void gfx::FlipFilledRect( const Vector2D& a, const Vector2D& b, int Color )
{
	glBegin(GL_QUADS);
		glNormal3f( 1.0f, 0.0f, 0.0f );
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		glTexCoord2f(0.01, 0.01);
		glVertex3f( a.x, a.y, 0.0 );

		glTexCoord2f(0.01, 0.99);
		glVertex3f( b.x, a.y, 0.0 );

		glTexCoord2f(0.99, 0.99);
		glVertex3f( b.x, b.y, 0.0 );

		glTexCoord2f(0.99, 0.01);
		glVertex3f( a.x, b.y, 0.0 );
	glEnd();
}
// - ------------------------------------------------------------------------------------------ - //
namespace Gfx
{
	// - -------------------------------------------------------------------------------------- - //
	void DrawMesh3d( const cLevelData* LevelData )
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
		for( size_t i = 0; i < LevelData->Mesh3d->Data.size(); ++i )
		{
			cMesh3d& ThisMesh = *LevelData->Mesh3d;
			
			// Tests to see if the VertexPointer is to new data or the same. // not needed in this version of GL //
			//void* ObjectTest = 0;
			//if( ObjectTest != LevelData->Mesh3d->Data[i].Vertex )
			//{			
			//	ObjectTest = LevelData->Mesh3d->Data[i].Vertex;
				
			glBindTexture( GL_TEXTURE_2D, ThisMesh.Data[i].TextureID );
			
			glVertexPointer(3, GL_FLOAT, 0, &(*ThisMesh.Data[i].Vertex)[0]);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, &(*ThisMesh.Data[i].VertexColor)[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &(*ThisMesh.Data[i].TextureCoord)[0]);
			//}
			glPushMatrix();
			glTranslatef( LevelData->Offset.x, LevelData->Offset.y, LevelData->Offset.z );
			glDrawElements(
				GL_TRIANGLES, ThisMesh.Data[i].Indices->Size(),
				GL_UNSIGNED_INT, &(*ThisMesh.Data[i].Indices)[0]
			);
			glPopMatrix();
		}
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	}
	// - -------------------------------------------------------------------------------------- - //
	void DrawQuads(
		const ABCDSet< Vector3D >* Vertex,
		const ABCDSet< Vector2D >* TexCoord,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID,
		const int Color
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
		const ABCDSet< Vector3D >* Vertex,
		const ABCDSet< Vector2D >* TexCoord,
		const ABCDSet< unsigned int >* Color,
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
		const ABCSet< Vector3D >* Vertex,
		const ABCSet< Vector2D >* TexCoord,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID,
		const int Color
		)
	{
		glBindTexture( GL_TEXTURE_2D, TextureID );
	
		glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
		
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
	void DrawPolygons(
		const ABCSet< Vector3D >* Vertex,
		const ABCSet< Vector2D >* TexCoord,
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
	void DrawLines(
		const ABSet< Vector3D >* Vertex,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const int Color
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
		const int Color
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
	int RGB( int r, int g, int b )
	{
		return r|(g << 8)|(b << 16);
	}
	// - -------------------------------------------------------------------------------------- - //
	int RGBA( int r, int g, int b, int a )
	{
		return r|(g << 8)|(b << 16)|(a << 24);
	}
	// - -------------------------------------------------------------------------------------- - //
	void Circle( const Vector3D& Pos, const Real& Radius, int Color )
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
	void Circle( const Real& x, const Real& y, const Real& Radius, int Color )
	{
		Circle( Vector3D( x, y, Real::Zero ), Radius, Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Circle( const Vector2D& Pos, const Real& Radius, int Color )
	{
		Circle( Vector3D( Pos.x, Pos.y, Real::Zero ), Radius, Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Vector3D& v1, const Vector3D& v2, int Color )
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
	void Line( const Vector2D& v1, const Vector2D& v2, int Color )
	{
		Line( v1.ToVector3D(), v2.ToVector3D(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color )
	{
		Line( Vector3D( x1, y1, Real( 0.0 ) ), Vector3D( x2, y2, Real( 0.0 ) ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, int Color )
	{
		Line( Vector3D( x1, y1, z1 ), Vector3D( x2, y2, z2 ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Vector3D& v1, const Vector3D& v2, int Color )
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
	void Rect( const Vector2D& v1, const Vector2D& v2, int Color )
	{
		Rect( v1.ToVector3D(), v2.ToVector3D(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color )
	{
		Rect( Vector3D( x1, y1, Real( 0.0 ) ), Vector3D( x2, y2, Real( 0.0 ) ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, int Color )
	{
		Rect( Vector3D( x1, y1, z1 ), Vector3D( x2, y2, z2 ), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Rect2D& _Rect, int Color )
	{
		Rect( _Rect._P1.ToVector3D(), _Rect._Shape.ToVector3D(), Color );
	}
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Rect3D& _Rect, int Color )
	{
		Rect( _Rect._P1, _Rect._Shape, Color );
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
	void EnableAddBlend()
	{
		// Enables additive blending //
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	// - -------------------------------------------------------------------------------------- - //
	void DisableAddBlend()
	{
		// Disables additive blending //
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	void BindTexture( unsigned int& TextureID )
	{
		glBindTexture( GL_TEXTURE_2D, TextureID );
	}
	// - -------------------------------------------------------------------------------------- - //

// - ------------------------------------------------------------------------------------------ - //
};  // namespace Gfx
// - ------------------------------------------------------------------------------------------ - //
