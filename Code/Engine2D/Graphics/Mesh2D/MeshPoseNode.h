// - ------------------------------------------------------------------------------------------ - //
// MeshPoseNode //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Graphics_Mesh2D_MeshPoseNode_H__
#define __Engine2D_Graphics_Mesh2D_MeshPoseNode_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cMeshPoseNode {
public:
	Vector2D Pos;
	
	// Orientation //
	size_t PivotIndex;
	size_t HandleIndex;
	
	cMeshPoseNode()
	{
		
	}
	
	cMeshPoseNode( const Vector2D& _Pos, const size_t _PivotIndex, const size_t _HandleIndex ) :
		Pos( _Pos ),
		PivotIndex( _PivotIndex ),
		HandleIndex( _HandleIndex )
	{
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Graphics_Mesh2D_MeshPoseNode_H__ //
// - ------------------------------------------------------------------------------------------ - //
