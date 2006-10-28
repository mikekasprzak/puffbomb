// - ------------------------------------------------------------------------------------------ - //
// Mesh3d //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Graphics_Mesh3d_H__
#define __Library_Graphics_Mesh3d_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/ClassDesigner.h>

#include <Geometry/Set.h>
#include <Geometry/Vector.h>
#include <Geometry/Rect.h>

#include <string>

#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
class cMesh3d
{
public:
	class cData
	{
	public:
		StaticArray< Vector3D >* Vertex;
		StaticArray< Vector3D >* VertexNormal;
		StaticArray< unsigned int >* VertexColor;
		StaticArray< Vector2D >* TextureCoord;
		
		StaticArray< unsigned int >* Indices;
		
		StaticArray< char >* TextureName; 
		
		unsigned int TextureID;
	};
	std::vector< cData > Data;
	
	// The block of binary data, as read from the file //
	char* Buffer;
	
	// - -------------------------------------------------------------------------------------- - //
	typedef Rect3D RectType;
	RectType BoundingRect;
	// - -------------------------------------------------------------------------------------- - //
		
	
public:
	cMesh3d() :
		Buffer( 0 )
	{
		
	}
	
	~cMesh3d()
	{
	//	delete[] Buffer;
	}
	
	cMesh3d( const std::string& FileName )
	{
		Load( FileName );
		CalcBoundingRect();
	}
	
	inline void CalcBoundingRect() {
		Vector3D P1 = (*Data[0].Vertex)[0];
		Vector3D P2 = (*Data[0].Vertex)[0];
		
		for ( size_t idx = 0; idx < Data.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Data[idx].Vertex->Size(); idx2++ ) {
				P1 = (*Data[idx].Vertex)[idx2].Min( P1 );
				P2 = (*Data[idx].Vertex)[idx2].Max( P2 );

			}
		}
		
		BoundingRect = RectType::Pair( P1, P2 );
	}

	
	void Draw();
	void Load( const std::string& FileName );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Graphics_Mesh3d_H__ //
// - ------------------------------------------------------------------------------------------ - //
