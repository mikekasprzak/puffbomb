// - ------------------------------------------------------------------------------------------ - //
// OldTexturePool //
// - ------------------------------------------------------------------------------------------ - //
#include "OldTexturePool.h"
/*
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
std::vector< std::string > OldTexturePool::SearchPath;
std::map< std::string, OldTexturePool::cTextureInfo > OldTexturePool::Pool;
// - ------------------------------------------------------------------------------------------ - //
OldTexturePool::Texture OldTexturePool::Load( const std::string& _FileName ) {
	if ( Pool.find( _FileName ) == Pool.end() ) {
		for ( size_t idx = 0; idx < SearchPath.size(); idx++ ) {
			std::string TextureFile = SearchPath[ idx ] + _FileName;
			SDL_Surface* Image = IMG_Load( TextureFile.c_str() );
			
			if ( Image ) {
				// Push opacity that's nearly 100% transparent all the way //
				if ( Image->flags & SDL_SRCALPHA ) {
					Uint32* Pixel = (Uint32*)Image->pixels;
					
					for ( int idx2 = 0; idx2 < (Image->w*Image->h); idx2++ ) {
						if ( (Pixel[idx2] >> 24) < 8 ) {
							Pixel[idx2] &= 0xffffff;//0xff << 24;
						}
					}
				}
				
				size_t _Width = Image->w;
				size_t _Height = Image->h;
		
				OldTexturePool::Texture Id;
				
				glGenTextures( 1, &Id );
				glBindTexture( GL_TEXTURE_2D, Id );
				
				if( Image->flags & SDL_SRCALPHA )
				{
					// Make it an Alpha Texture //
				    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, Image->w,
					  Image->h, 0, GL_RGBA,
					  GL_UNSIGNED_BYTE, Image->pixels );
		
					gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8, Image->w,
					      Image->h, GL_RGBA,
					       GL_UNSIGNED_BYTE, Image->pixels );
			
				}
				else
				{
					// No Alpha in this Texture //
				    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, Image->w,
					  Image->h, 0, GL_RGB,
					  GL_UNSIGNED_BYTE, Image->pixels );
		
					gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB8, Image->w,
					      Image->h, GL_RGB,
					       GL_UNSIGNED_BYTE, Image->pixels );
				}

				SDL_FreeSurface( Image );

				// Success, put the texture on the pool! //
				Pool[ _FileName ] = OldTexturePool::cTextureInfo( _FileName, Id, _Width, _Height );
				Log( LOG_TEXTURE_CREATE, "Texture File Loaded Successfully \"" << _FileName << "\"" );
				
				return Id;
			}
		}
		Log( LOG_TEXTURE_CREATE, "### Texture File Not Found \"" << _FileName << "\"" );
		return 0;
	}
	else {
		//Log( LOG_HIGHEST_LEVEL, _FileName << " found" );
		return Pool[ _FileName ].TextureId;
	}
}
// - ------------------------------------------------------------------------------------------ - //
size_t OldTexturePool::GetWidth( const std::string& _FileName )
{
	if( Pool.find( _FileName ) != Pool.end() )
	{
		return Pool[ _FileName ].Width;
	}
	else
	{
		return 0;	
	}
}
// - ------------------------------------------------------------------------------------------ - //
size_t OldTexturePool::GetHeight( const std::string& _FileName )
{
	if( Pool.find( _FileName ) != Pool.end() )
	{
		return Pool[ _FileName ].Height;
	}
	else
	{
		return 0;	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void OldTexturePool::Clear() {
	// Erase all textures (tell GL to go home) //
	for ( std::map< std::string, cTextureInfo >::iterator idx = Pool.begin(); idx != Pool.end(); idx++ ) {
		glDeleteTextures( 1, &(idx->second.TextureId) );	
	}
	
	Pool.clear();
}
// - ------------------------------------------------------------------------------------------ - //
*/
