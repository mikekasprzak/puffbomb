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
			Log( 0, "- " << DirectoryCache.File[ idx ] << " " << String::Directory(DirectoryCache.File[ idx ]) );

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
				for ( int idx2 = Animation.size(); idx2 <= Id; idx2 ++ ) {
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
	
	// Load animation frames (images), removing duplicates //
	for ( size_t idx = 0; idx < Animation.size(); idx++ ) {
		Log( 10, "Building Animation \"" << Animation[ idx ].DirectoryName << "\"" );
		
		// For each frame in this animation, get my art //
		int CurrentFile = 0;
		int UniqueFrame = 0;
		for ( size_t idx2 = 0; idx2 < Animation[ idx ].Frame.size(); idx2++ ) {
			// Go to the next occurence of a file that 
			while ( DirectoryCache.File[ CurrentFile ].find( Animation[ idx ].DirectoryName ) == std::string::npos ) {
				Log( 10, "- " << DirectoryCache.File[ CurrentFile ] << " - " << Animation[ idx ].DirectoryName );
				CurrentFile++;
			};
			
			// Load Image //
			{
				Log( 0, "- Loading Image \"" << DirectoryCache.File[ CurrentFile ] << "\"" );
				
				// Load file //
				SDL_Surface* Image = IMG_Load( (Directory + "/" + DirectoryCache.File[ CurrentFile ]).c_str() );
				unsigned int CRC = 0;
				
				//Log( 10, "- CRC" );
				// Calculate CRC //
				for ( int idx3 = 0; idx3 < (Image->w * Image->h); idx3++ ) {
					CRC += ((unsigned int*)Image->pixels)[ idx3 ];
				}
				
				//Log( 10, "- IsLoaded" );
				// Check if current image is already loaded //
				for ( size_t idx3 = 0; idx3 < ImagePool.size(); idx3++ ) {
					// Test CRC //
					if ( ImageCRC[ idx3 ] == CRC ) {
						// If CRC Passes, test image dimensions //
						if ( ImagePool[ idx3 ]->w == Image->w ) {
							if ( ImagePool[ idx3 ]->h == Image->h ) {
								// If dimensions pass, test bit depth //
								if ( ImagePool[ idx3 ]->format->BytesPerPixel == Image->format->BytesPerPixel ) {
									// Finally, test image //
									int EqualPixels = 0;
									int PixelsToTest = ((Image->w * Image->h * Image->format->BytesPerPixel) / 4);
									for ( int idx4 = 0; idx4 < PixelsToTest; idx4++ ) {
										if ( ((unsigned int*)ImagePool[ idx3 ]->pixels)[ idx4 ] == ((unsigned int*)Image->pixels)[ idx4 ] ) {
											EqualPixels++;
										}
										else {
											break;
										}
									}
									
									// If images are the same, use this image //
									if ( EqualPixels == PixelsToTest ) {
										// Free image //
										SDL_FreeSurface( Image );
										Image = 0;
										
										// Use existing index //
										Animation[ idx ].Frame[ idx2 ].ImageIndex = idx3;
										
										// Since it's the same, we don't need to find a new one //
										break;
									}
								}
							}
						}
					}
				}
				
				// Image not found!!! Add it! //
				if ( Image != 0 ) {
					Log( 0, "+ Added new unique frame" );
					UniqueFrame++;
					
					ImagePool.push_back( Image );
					ImageCRC.push_back( CRC );
					ImageFileName.push_back( DirectoryCache.File[ CurrentFile ] );
					
					// Use new index //
					Animation[ idx ].Frame[ idx2 ].ImageIndex = ImagePool.size() - 1;
				}
			}
			
			// Next Image //
			CurrentFile++;
		}
		Log( 0, "* " << UniqueFrame << " unique frames found" );
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
