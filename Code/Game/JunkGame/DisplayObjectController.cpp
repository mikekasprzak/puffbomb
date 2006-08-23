// - ------------------------------------------------------------------------------------------ - //
// DisplayObjectController //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TexturePool.h>
#include <Engine2D/DisplayMeshPool.h>

#include "DisplayObjectController.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cDisplayObjectController::cDisplayObjectController( cSphereObject* _Object, const std::string& BodyFile ) :
	cObjectController( _Object, BodyFile )	
{
	Log( LOG_HIGHEST_LEVEL, "Loading Reference Body File " << BodyFile );

	class cScriptPool : public cPool< cScriptParser > {
	public:
		cScriptPool( const string& _Directory ) {
			SearchPath.Add( _Directory );
		}
	};

	//cScriptPool Templates( "Content/PuffBOMB/2D" );
	cScriptPool Templates( "2D" );

	cSphereObject Original( Templates.Load( BodyFile ), 0, 0, Real::One );


	string MeshFile =
		String::DirectorySlash( BodyFile ) +
		String::BaseName( BodyFile ) +
		String::NoLastExtension( BodyFile ) +
		".mesh2d";

	Log( LOG_MESH_INFO, "Loading Mesh File " << MeshFile );
	cDisplayMesh& DisplayMesh = DisplayMeshPool.Load( MeshFile );
	

	TextureId = TexturePool.Load( DisplayMesh.TextureName ).Id;

//	{
//		std::string TexturePath = "src/Content/Experimental/Textures/" + DisplayMesh.TextureName;
//		SDL_Surface* Image = IMG_Load( TexturePath.c_str() );
//		
//		glGenTextures( 1, &TextureId );
//		glBindTexture( GL_TEXTURE_2D, TextureId );
//		
//		if( Image->flags & SDL_SRCALPHA )
//		{
//		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, Image->w,
//			  Image->h, 0, GL_RGBA,
//			  GL_UNSIGNED_BYTE, Image->pixels );
//
//			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8, Image->w,
//			      Image->h, GL_RGBA,
//			       GL_UNSIGNED_BYTE, Image->pixels );
//	
//		}
//		else
//		{
//		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, Image->w,
//			  Image->h, 0, GL_RGB,
//			  GL_UNSIGNED_BYTE, Image->pixels );
//
//			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB8, Image->w,
//			      Image->h, GL_RGB,
//			       GL_UNSIGNED_BYTE, Image->pixels );
//		}
//		
//		SDL_FreeSurface( Image );
//	}
	
	// Get all verts and orientations //
	for( size_t idx = 0; idx < DisplayMesh.DisplayNode.size(); idx++ ) {
		// Store/Find Orientation //
		int ThisOrientation = -1;
		for( size_t idx2 = 0; idx2 < Orientation.size(); idx2++ ) {
			if ( Orientation[idx2].Pivot == DisplayMesh.DisplayNode[idx].Pivot ) {
				if ( Orientation[idx2].Handle == DisplayMesh.DisplayNode[idx].Handle ) {
					ThisOrientation = idx2;
					break;
				}
			}
		}
		// if no orientation was found in the search, add a new one //
		if ( ThisOrientation == -1 ) {
			ThisOrientation = Orientation.size();
			Orientation.push_back( 
				cOrientation(
					DisplayMesh.DisplayNode[idx].Pivot,
					DisplayMesh.DisplayNode[idx].Handle
					)
				);
		}
		
		Vertex.push_back( 
			cVertex(
				DisplayMesh.DisplayNode[idx].Pos - Original.Pos( DisplayMesh.DisplayNode[idx].Pivot ),
				ThisOrientation
				) 
			);
	}
	
	// Copy Faces //
	for( size_t idx = 0; idx < DisplayMesh.Face.size(); idx++ ) {
		Face.push_back(
			cFace(
				DisplayMesh.Face[idx].Vertex,
				DisplayMesh.Face[idx].UV,
				Real( DisplayMesh.Face[idx].Layer / 5 )
				)
			);
	}

	// Calculate Home Matrices //	
	for ( size_t idx = 0; idx < Orientation.size(); idx++ ) {
		Orientation[idx].CalculateHomeMatrix( *SphereObject );
	}
}
// - ------------------------------------------------------------------------------------------ - //
cDisplayObjectController::~cDisplayObjectController() {
}
// - ------------------------------------------------------------------------------------------ - //
void cDisplayObjectController::Draw() {
	// Transform Matricies //
	for ( size_t idx = 0; idx < Orientation.size(); idx++ ) {
		Orientation[idx].CalculateMatrix( *SphereObject );
	}
	
	// Transform Vertices //
	std::vector< Vector2D > Transformed;
	for ( size_t idx = 0; idx < Vertex.size(); idx++ ) {
		Transformed.push_back( 
			(Vertex[idx].ToMatrix2x1() * Orientation[ Vertex[idx].Orientation ].HomeMatrix * Orientation[ Vertex[idx].Orientation ].Matrix).ToVector2D() +
			SphereObject->Pos( Orientation[ Vertex[idx].Orientation ].Pivot )
			);
	}
	
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	glBindTexture( GL_TEXTURE_2D, TextureId );
	
	for( size_t idx = 0; idx < Face.size(); ++idx ) {
		gfx::Face( 
			Transformed[ Face[idx].Index.a ],
			Transformed[ Face[idx].Index.b ],
			Transformed[ Face[idx].Index.c ],
			Face[idx].UV.a,
			Face[idx].UV.b,
			Face[idx].UV.c
		);
	}
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
// - ------------------------------------------------------------------------------------------ - //
