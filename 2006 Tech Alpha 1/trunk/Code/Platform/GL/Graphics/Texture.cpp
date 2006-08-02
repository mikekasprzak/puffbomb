// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Texture.h>

#include <Util/Debug.h>
#include <Util/String.h>
#include <Util/LZMA.h>

#include <GL/gl.h>
#include <GL/glu.h>
// - ------------------------------------------------------------------------------------------ - //
void cTexture::Load( const std::string& FileName )
{
	if( String::LastExtension( FileName ) == ".tx" )
	{
		Buffer = LZMA::UnPack( FileName );
		
		unsigned int* tempPixelSize	= (unsigned int*)&Buffer[0];
		PixelSize = *tempPixelSize;
	
		unsigned int* tempWidth	= (unsigned int*)&Buffer[4];
		Width = *tempWidth;

		unsigned int* tempHeight	= (unsigned int*)&Buffer[8];
		Height = *tempHeight;

		Pixels = (unsigned char*)&Buffer[12];
		
		glGenTextures( 1, &ID );
		glBindTexture( GL_TEXTURE_2D, ID );
	
//		Log( LOG_HIGHEST_LEVEL, "PixelSize = " << PixelSize );
//		Log( LOG_HIGHEST_LEVEL, "Width = " << Width );
//		Log( LOG_HIGHEST_LEVEL, "Height = " << Height );
		
		if( PixelSize == 4 )
		{
			// Make it an Alpha Texture //
		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, Width,
			  Height, 0, GL_RGBA,
			  GL_UNSIGNED_BYTE, Pixels );
	
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8, Width,
			      Height, GL_RGBA,
			       GL_UNSIGNED_BYTE, Pixels );
		}
		else
		{
			// No Alpha in this Texture //
		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, Width,
			  Height, 0, GL_RGB,
			  GL_UNSIGNED_BYTE, Pixels );
	
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB8, Width,
			      Height, GL_RGB,
			       GL_UNSIGNED_BYTE, Pixels );
		}
		
		delete[] Buffer;
	}
}
// - ------------------------------------------------------------------------------------------ - //
