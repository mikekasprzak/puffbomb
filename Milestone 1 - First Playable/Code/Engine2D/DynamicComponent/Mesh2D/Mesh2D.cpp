// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2D.h"
#include <DynamicComponent/Body2D/Body2D.h>

#include <Graphics/Gfx.h>

#include <gl/gl.h>

#include "Pose/Mesh2DPose.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
cMesh2D::cMesh2D( const cMesh2DPose& _Pose, const cBody2D& Body ) {
	// Resize vertices and UV's for manipulation //
	Vertex.resize( _Pose.Node.size() );
	UV.resize( _Pose.Node.size() );
	Orientation.clear();
	
	// Copy Node Positions //
	for ( size_t idx = 0; idx < _Pose.Node.size(); idx++ ) {
		int Orient = -1;
		
		// Find a matching orientation //
		for ( size_t idx2 = 0; idx2 < Orientation.size(); idx2++ ) {
			if ( Orientation[ idx2 ].PivotIndex == _Pose.Node[ idx ].PivotIndex ) {
				if ( Orientation[ idx2 ].HandleIndex == _Pose.Node[ idx ].HandleIndex ) {
					Orient = idx2;
					break;
				}
			}
		}
		
		// If the orientation wasn't found, add a new one //
		if ( Orient == -1 ) {
			Orient = Orientation.size();
			
			Orientation.push_back(
				cMeshOrientation( _Pose.Node[ idx ].PivotIndex, _Pose.Node[ idx ].HandleIndex )
				);
		}
		
		// Set the vertex //
		Vertex[ idx ] = cMeshVertex(
			_Pose.Node[ idx ].Pos - Body.Nodes.Pos( _Pose.Node[ idx ].PivotIndex ),
			Orient
			);
		
		// Generate the UV //
		Vector2D Offset( -256, -256 );	// ** Hack, until magic numbers //
		Real SizeScalar = Real::One / Real( 512 ); // ** Hack, until magic numbers //
		UV[ idx ] = (_Pose.Node[ idx ].Pos - Offset) * SizeScalar;
		UV[ idx ].y *=  Real( -1 );
	}


	// Copy (Generate) Faces //
	Face = _Pose.Face;
	
	
	// Calculate Orientations //
	for ( size_t idx = 0; idx < Orientation.size(); idx++ ) {
		Orientation[ idx ].CalculateHomeMatrix( Body.Nodes );
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2D::Draw( const cBody2D& Body, const cTexture::IdType& Texture ) const {
	// Calculate Matricies //
	std::vector< Matrix2x2 > MyOrientation( Orientation.size() );
	for ( size_t idx = 0; idx < Orientation.size(); idx++ ) {
		MyOrientation[ idx ] = Orientation[ idx ].CalculateMatrix( Body.Nodes );
	}
	
	// Transform Vertices //
	std::vector< Vector3D > MyVertex( Vertex.size() );
	for ( size_t idx = 0; idx < Vertex.size(); idx++ ) {
		const cMeshVertex& Vert = Vertex[ idx ];		
		const Matrix2x2& InvHome = Orientation[ Vert.OrientationIndex ].InvHomeMatrix;
		const Matrix2x2& Matrix = MyOrientation[ Vert.OrientationIndex ];
		
		MyVertex[ idx ] = (
			(Vert.ToMatrix2x1() * InvHome * Matrix).ToVector2D() +
			Body.Nodes.Pos( Orientation[ Vert.OrientationIndex ].PivotIndex ) ).ToVector3D();
	}
	
	// Draw //
	Gfx::DrawPolygons(
		&MyVertex[0],
		&UV[0],
		(unsigned int*)&Face[0],
		Face.size() * 3,
		Texture
		);
	
/*	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	glBindTexture( GL_TEXTURE_2D, Texture.Id );
	
	for( size_t idx = 0; idx < Face.size(); ++idx ) {
		gfx::Face( 
			MyVertex[ Face[idx].a ],
			MyVertex[ Face[idx].b ],
			MyVertex[ Face[idx].c ],
			UV[ Face[idx].a ],
			UV[ Face[idx].b ],
			UV[ Face[idx].c ]
		);
	}
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);	*/
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
