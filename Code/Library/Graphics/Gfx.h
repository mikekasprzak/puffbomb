// - ------------------------------------------------------------------------------------------ - //
// Gfx //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Gfx_H__
#define __Graphics_Gfx_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
#include <Geometry/Rect.h>
#include <Geometry/Set.h>

#include <Graphics/Mesh3D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Gfx {
	typedef unsigned int Color;

	// Resets the color back to white with no alpha
	void ResetColor();
	// Returns white with no alpha
	Gfx::Color White();
	Gfx::Color RGB( int r, int g, int b );
	Gfx::Color RGBA( int r, int g, int b, int a );

	void DrawMesh3D( const std::vector< Engine2D::cMesh3D >& Mesh, const Vector3D& Offset );
	//void DrawMesh3d( const cLevelData* LevelData );
	// Draw Quads with Vertex, TexCoord and one Color //
	void DrawQuads(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID,
		const Gfx::Color Color = White()
	);
	// Draw Quads with Vertex, TexCoord, Color //
	void DrawQuads(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Color,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID
	);
	// Draw Polygons with Vertex, TexCoord, Color //
	void DrawPolygons(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Color,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureID
	);

	// Draw Polygons with Vertex, TexCoord and one Color //
	void DrawPolygons(
		const Vector3D* Vertex,
		const Vector2D* TexCoord,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const unsigned int& TextureId,
		const Gfx::Color Color = White()
		);
	// Draw Lines with Vertex and one Color //
	void DrawLines(
		const ABSet< Vector3D >* Vertex,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const Gfx::Color Color = White()
	);
	// Draw a linestrip with Vertex and one Color //
	void DrawLineStrip(
		const Vector3D* Vertex,
		const unsigned int* Indices,
		const unsigned int IndicesSize,
		const Gfx::Color Color = White()
	);
	// - -------------------------------------------------------------------------------------- - //
	void Circle( const Vector3D& Pos, const Real& Radius, Gfx::Color Color );
	void Circle( const Real& x, const Real& y, const Real& Radius, Gfx::Color Color );
	void Circle( const Vector2D& Pos, const Real& Radius, Gfx::Color Color );
	// - -------------------------------------------------------------------------------------- - //
	void Line( const Vector3D& v1, const Vector3D& v2, Gfx::Color Color );
	void Line( const Vector2D& v1, const Vector2D& v2, Gfx::Color Color );
	void Line( const Real& x1, const Real& y1, const Real& x2, const Real& y2, Gfx::Color Color );
	void Line( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, Gfx::Color Color );
	// - -------------------------------------------------------------------------------------- - //
	void Rect( const Vector3D& v1, const Vector3D& v2, Gfx::Color Color );
	void Rect( const Vector2D& v1, const Vector2D& v2, Gfx::Color Color );
	void Rect( const Real& x1, const Real& y1, const Real& x2, const Real& y2, Gfx::Color Color );
	void Rect( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, Gfx::Color Color );
	void Rect( const Rect2D& _Rect, Gfx::Color Color );
	void Rect( const Rect3D& _Rect, Gfx::Color Color );
	// - -------------------------------------------------------------------------------------- - //
	void FilledRect( const Vector3D& v1, const Vector3D& v2, Gfx::Color Color );
	void FilledRect( const Vector2D& v1, const Vector2D& v2, Gfx::Color Color );
	// - -------------------------------------------------------------------------------------- - //
	void EnableTex2D();
	void DisableTex2D();
	void EnableBlend();
	void DisableBlend();
	void AddBlend();
	void StandardBlend();
	void SaturateBlend();
	void EnableDepth();
	void DisableDepth();
	void EnableSmoothPolygon();
	void DisableSmoothPolygon();
	void BindTexture( unsigned int& TextureId );
	void DeleteTexture( unsigned int& TextureId );
	void SetLineWidth( const Real Num );
	// - -------------------------------------------------------------------------------------- - //
	void Viewport( int x, int y, unsigned int Width, unsigned int Height );
	void ProjMatrixMode();
	void ModelMatrixMode();
	void LoadIdentity();
	void Perspective( double Fovy, double Aspect, double zNear, double zFar );
	void PushMatrix();
	void PopMatrix();
	void Translate( const Real x, const Real y, const Real z );
	void Translate( const Vector3D& MyVec );
	void Translate( const Vector2D& MyVec );
	void Rotate( const Real angle, const Real x, const Real y, const Real z );
	void ClearColorDepth();
	void SwapBuffers();
	// - -------------------------------------------------------------------------------------- - //
	void EnableMouseDraw();
	void DisableMouseDraw();
	// - -------------------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Gfx_H__ //
// - ------------------------------------------------------------------------------------------ - //
