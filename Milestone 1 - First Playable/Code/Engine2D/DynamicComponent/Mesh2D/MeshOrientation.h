// - ------------------------------------------------------------------------------------------ - //
// MeshOrientation //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Graphics_Mesh2D_MeshOrientation_H__
#define __Engine2D_Graphics_Mesh2D_MeshOrientation_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Matrix.h>

#include <DynamicComponent/Body2D/DynamicNodes/DynamicNodes.h>
#include <DynamicComponent/Body2D/Pose/BodyPoseNode.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cMeshOrientation {
public:
	size_t PivotIndex;
	size_t HandleIndex;

	// Inverse of the home matrix //
	Matrix2x2 InvHomeMatrix;

public:
	cMeshOrientation( ) :
		PivotIndex( 0 ),
		HandleIndex( 0 )
	{
	}

	cMeshOrientation( const size_t& _PivotIndex, const size_t& _HandleIndex ) :
		PivotIndex( _PivotIndex ),
		HandleIndex( _HandleIndex )
	{
	}

public:
	void CalculateHomeMatrix( const cDynamicNodes& Node ) {
		Vector2D Line = Node.Pos( HandleIndex ) - Node.Pos( PivotIndex );
		Line.Normalize();
		
		InvHomeMatrix[ 0 ] = Line.x;
		InvHomeMatrix[ 1 ] = Line.y;
		InvHomeMatrix[ 2 ] = Line.Tangent().x;
		InvHomeMatrix[ 3 ] = Line.Tangent().y;
		
		InvHomeMatrix = InvHomeMatrix.Inverse();
	}

	void CalculateHomeMatrix( const std::vector< cBodyPoseNode >& Node ) {
		Vector2D Line = Node[ HandleIndex ].Pos - Node[ PivotIndex ].Pos;
		Line.Normalize();
		
		InvHomeMatrix[ 0 ] = Line.x;
		InvHomeMatrix[ 1 ] = Line.y;
		InvHomeMatrix[ 2 ] = Line.Tangent().x;
		InvHomeMatrix[ 3 ] = Line.Tangent().y;
		
		InvHomeMatrix = InvHomeMatrix.Inverse();
	}

public:
	inline Matrix2x2 CalculateMatrix( const cDynamicNodes& Node ) const {
		Vector2D Line = Node.Pos( HandleIndex ) - Node.Pos( PivotIndex );
		Line.Normalize();

		// A matrix to hold our orientation //
		Matrix2x2 Matrix;
		
		Matrix[ 0 ] = Line.x;
		Matrix[ 1 ] = Line.y;
		Matrix[ 2 ] = Line.Tangent().x;
		Matrix[ 3 ] = Line.Tangent().y;
		
		return Matrix;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Graphics_Mesh2D_MeshOrientation_H__ //
// - ------------------------------------------------------------------------------------------ - //
