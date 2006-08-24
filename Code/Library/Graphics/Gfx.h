// - ------------------------------------------------------------------------------------------ - //
// Gfx //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Gfx_H__
#define __Graphics_Gfx_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
#include <Geometry/Rect.h>
#include <Geometry/Set.h>

#include <Graphics/LevelData.h>
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
// Old Structure //
class gfx {
public:
	static void Circle( const Real& x, const Real& y, const Real& Radius, int Color );
	static void Circle( const Vector2D& v, const Real& Radius, int Color );

//	static void Draw3DModel( const size_t& obj, const size_t& lookup, const size_t& idx, const cLevelData* Model );
	static void Face( const Vector3D& a, const Vector3D& b, const Vector3D& c,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc );
	static void Face( const Vector2D& a, const Vector2D& b, const Vector2D& c,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc );

	static void Face( const Vector2D& a, const Vector2D& b, const Vector2D& c,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc,
				const Real& z );

	static void Polygon( const Vector3D& a, const Vector3D& b, const Vector3D& c, int Color );
	
	static void Line( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color );
	static void Line( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color, int Color2 );
	static void Line( const Real& x1, const Real& y1, const Real& z1, const Real& x2, const Real& y2, const Real& z2, int Color );

	static void Line( const Vector2D& v1, const Vector2D& v2, int Color );
	static void Line( const Vector2D& v1, const Vector2D& v2, int Color, int Color2 );
	static void Line( const Vector2D& v1, const Vector2D& v2, const Real& z, int Color );

	static void Rect( const Real& x1, const Real& y1, const Real& x2, const Real& y2, int Color );
	static void Rect( const Vector2D& v1, const Vector2D& v2, int Color );
	static void Rect( const Rect2D& _Rect, int Color );
	
	static int RGB( int r, int g, int b );
	static int RGBA( int r, int g, int b, int a );
	
	static void Quad( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc, const Vector2D& UVd );
	static void Quad( const Vector2D& a, const Vector2D& b, const Vector2D& c, const Vector2D& d,
				const Vector2D& UVa, const Vector2D& UVb, const Vector2D& UVc, const Vector2D& UVd );

	static void Quad( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d,
				Vector2D UVa, Vector2D UVb);

	static void FilledRect( const Vector2D& a, const Vector2D& b, int Color );
	static void FlipFilledRect( const Vector2D& a, const Vector2D& b, int Color );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// New Structure //
namespace Gfx {
	typedef unsigned int Color;

	// Resets the color back to white with no alpha
	void ResetColor();
	// Returns white with no alpha
	Gfx::Color White();
	Gfx::Color RGB( int r, int g, int b );
	Gfx::Color RGBA( int r, int g, int b, int a );

	
	void DrawMesh3d( const cLevelData* LevelData );
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
	void EnableTex2D();
	void DisableTex2D();
	void EnableBlend();
	void DisableBlend();
	void EnableAddBlend();
	void DisableAddBlend();
	void EnableDepth();
	void DisableDepth();
	void BindTexture( unsigned int& TextureID );
	// - -------------------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Gfx_H__ //
// - ------------------------------------------------------------------------------------------ - //
