// - ------------------------------------------------------------------------------------------ - //
// AnimationGenerator //
// - ------------------------------------------------------------------------------------------ - //
#include <algorithm>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/DirectoryCache.h>

#include "AnimationGenerator.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cAnimationGenerator::Load( ) {
	// Get list of everything in Directory //
	cDirectoryCache DirectoryCache( Directory );
	
	// Sort Filenames //
	std::sort( DirectoryCache.File.begin(), DirectoryCache.File.end() );
	
	// Gather names of unique folders, and create structure using associated id's //
	for ( size_t idx = 0; idx < DirectoryCache.File.size(); idx++ ) {
		if ( String::HasAnyArgExtension( DirectoryCache.File[ idx ], ".Id" ) ) {
			Log( 10, "- " << DirectoryCache.File[ idx ] << " " << String::Directory(DirectoryCache.File[ idx ]) );

			// Check every Animation added to see if it's already been added //
			bool Found = false;			
			for ( size_t idx2 = 0; idx2 < Animation.size(); idx2++ ) {
				if ( Animation[ idx2 ].DirectoryName == String::Directory(DirectoryCache.File[ idx ]) ) {
					Found = true;
					break;
				}
			}
			
			// If not found, then we've got a new one! //
			if ( !Found ) {
				// Grab the Id //
				int Id = String::GetIntArgExtension( DirectoryCache.File[ idx ], ".Id" );
				//Log( 10, "ID = " << Id );
				
				// Add dummy animation entries until we get to the correct spot //
				for ( int idx2 = 0; idx2 <= Id; idx2 ++ ) {
					Animation.push_back( cAnimation() );
				}
				
				// Populate our entry //
				{
					// Directory Name //
					Animation[ Id ].DirectoryName = String::Directory(DirectoryCache.File[ idx ]);
						
					// Framerate (hold) - At 60fps: 1 = 60fps, 2 = 30fps, 3 = 20fps //
					if ( String::HasAnyArgExtension( DirectoryCache.File[ idx ], ".Hold" ) )
						Animation[ Id ].FrameHold = String::GetIntArgExtension( DirectoryCache.File[ idx ], ".Hold" );
					
					// Number of Frames //
					int FrameCount = 0;
					for ( size_t idx2 = 0; idx2 < DirectoryCache.File.size(); idx2++ ) {
						// If Id's are the same //
						if ( String::GetIntArgExtension( DirectoryCache.File[ idx2 ], ".Id" ) == Id ) {
							// If it has a number //
							if ( String::GetBaseNameNumber( DirectoryCache.File[ idx2 ] ) != -1 ) {
								FrameCount++;
							}
						}
					}
					
					// Resize teh number of frames in the animation //
					Animation[ Id ].Frame.resize( FrameCount );

					Log( 10,
						"Id = " << Id <<
						" FrameHold = " << Animation[ Id ].FrameHold <<
						" FrameCount = " << FrameCount
						);
				}
			}
		}
	}
	
	
	
	//SDL_Surface* ThisImage = IMG_Load( ImageLocation.c_str() );

	//int Image_Size = Image->w * Image->h;
	//int* Pixels = (int*)Image->pixels;

	//SDL_FreeSurface( Image );	


//	glGenTextures( 1, &GroundTexID );
//	glBindTexture( GL_TEXTURE_2D, GroundTexID );
//
//    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, GroundImage.Height,
//	  GroundImage.Width, 0, GL_BGRA,
//	  GL_UNSIGNED_BYTE, ( void* )(&GroundImage.Pixels[0]) );
//
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
}
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
