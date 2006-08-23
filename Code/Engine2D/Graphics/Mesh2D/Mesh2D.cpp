// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Mesh2D.h>
#include <Physics/Body2D.h>

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cMesh2D::Draw( const cBody2D& Body ) const {
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
		Texture.Id
		);
	
//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	
//	glBindTexture( GL_TEXTURE_2D, TextureId );
//	
//	for( size_t idx = 0; idx < Face.size(); ++idx ) {
//		gfx::Face( 
//			Transformed[ Face[idx].Index.a ],
//			Transformed[ Face[idx].Index.b ],
//			Transformed[ Face[idx].Index.c ],
//			Face[idx].UV.a,
//			Face[idx].UV.b,
//			Face[idx].UV.c
//		);
//	}
//	glDisable(GL_BLEND);
//	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
