// - ------------------------------------------------------------------------------------------ - //
// Mesh2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Graphics_Mesh2D_H__
#define __Engine2D_Graphics_Mesh2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Set.h>

#include <Graphics/Texture.h>

#include "Mesh2D/MeshVertex.h"
#include "Mesh2D/MeshOrientation.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cMesh2D {
public:
	// Vertices (with orientation indices for transformations) //
	std::vector< cMeshVertex > Vertex;
	// A UV for every vertex (streamable) //
	std::vector< Vector2D > UV;

	// Face list //
	std::vector< ABCSet< size_t > > Face;
	
	// Relative Orientations //
	std::vector< cMeshOrientation >	Orientation;


	// Texture Used //
	cTexture Texture;
public:
	cMesh2D()
	{
	}
	
	cMesh2D( const class cMesh2DPose& _Pose, const class cBody2D& Body );
public:
	void Draw( const class cBody2D& Body ) const;
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Graphics_Mesh2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
