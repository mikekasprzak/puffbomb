// - ------------------------------------------------------------------------------------------ - //
// AnimationGenerator //
// - ------------------------------------------------------------------------------------------ - //
#include <algorithm>
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationGenerator.h"

#include <Util/DirectoryCache.h>
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
		//Folders
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
