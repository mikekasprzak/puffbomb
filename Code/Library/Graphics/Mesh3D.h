// - ------------------------------------------------------------------------------------------ - //
// Mesh3D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Graphics_Mesh3D_H__
#define __Engine2D_Graphics_Mesh3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>

#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cMesh3D {
public:
	// Stream Data //
	StaticArray< Vector3D >* Vertex;
	StaticArray< Vector3D >* VertexNormal;
	StaticArray< unsigned int >* VertexColor;
	StaticArray< Vector2D >* TextureCoord;
	
	StaticArray< unsigned int >* Indices;
	
	// Additional Information //
	StaticArray< char >* TextureName; 
	
	unsigned int TextureID;	
public:
	
	const bool NoCollision() const {
		return false;
	}

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Graphics_Mesh3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
