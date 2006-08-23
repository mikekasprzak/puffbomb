// - ------------------------------------------------------------------------------------------ - //
// MeshFace //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Graphics_Mesh2D_MeshFace_H__
#define __Engine2D_Graphics_Mesh2D_MeshFace_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Set.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cMeshFace {
public:
	ABCSet< size_t > NodeIndex;
	ABCSet< Vector2D > UV;

public:
	cMeshFace( const ABCSet< size_t >& _Index, const ABCSet<Vector2D>& _UV ) :
		NodeIndex( _Index ),
		UV( _UV )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Graphics_Mesh2D_MeshFace_H__ //
// - ------------------------------------------------------------------------------------------ - //
