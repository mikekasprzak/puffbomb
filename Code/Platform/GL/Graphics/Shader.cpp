// - ------------------------------------------------------------------------------------------ - //
// Shader //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Shader.h>

#include <Util/Debug.h>
#include <Util/String.h>
#include <Util/LZMA.h>
// - ------------------------------------------------------------------------------------------ - //
//#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cShader::Load( const std::string& _FileName )
{
#ifdef EDITOR
	FileName = _FileName;
#endif // EDITOR //

	Log( 10, "Attempting to load Shader" );

	// Validate it's a texture by checking end extension //
	if( String::LastExtension( _FileName ) == ".fx" )
	{
		// Decompress the loaded data //
		char* Buffer = LZMA::UnPack( _FileName );
	
//		// Hack for determining if the texture is S3TC compressed //
//		if( String::HasExtension( _FileName, ".dds" ) ){
//			LoadCompressedTexture( Buffer );
//		}
//		else {
//			unsigned int* tempPixelSize	= (unsigned int*)&Buffer[0];
//			PixelSize = *tempPixelSize;
//		
//			unsigned int* tempWidth	= (unsigned int*)&Buffer[4];
//			Width = *tempWidth;
//	
//			unsigned int* tempHeight	= (unsigned int*)&Buffer[8];
//			Height = *tempHeight;
//	
//			Pixels = (unsigned char*)&Buffer[12];
//			
//			glGenTextures( 1, &Id );
//			glBindTexture( GL_TEXTURE_2D, Id );
//			
//			//Log( LOG_HIGHEST_LEVEL, "Loaded Texture Id ( Texture Pool ( .tx ) ) " );
//		
//	//		Log( LOG_HIGHEST_LEVEL, "PixelSize = " << PixelSize );
//	//		Log( LOG_HIGHEST_LEVEL, "Width = " << Width );
//	//		Log( LOG_HIGHEST_LEVEL, "Height = " << Height );
//			
//			if( PixelSize == 4 ) {
//				// Make it an Alpha Texture //
//			    glTexImage2D(
//			    	GL_TEXTURE_2D,
//			    	0,
//			    	GL_RGBA8,
//			    	Width,
//					Height,
//					0,
//					GL_RGBA,
//					GL_UNSIGNED_BYTE,
//					Pixels
//					);
//		
//				gluBuild2DMipmaps(
//					GL_TEXTURE_2D,
//					GL_RGBA8,
//					Width,
//					Height,
//					GL_RGBA,
//					GL_UNSIGNED_BYTE,
//					Pixels
//					);
//			}
//			else {
//				// No Alpha in this Texture //
//			    glTexImage2D(
//			    	GL_TEXTURE_2D,
//			    	0,
//			    	GL_RGB8,
//			    	Width,
//					Height,
//					0,
//					GL_RGB,
//					GL_UNSIGNED_BYTE,
//					Pixels
//					);
//		
//				gluBuild2DMipmaps(
//					GL_TEXTURE_2D,
//					GL_RGB8,
//					Width,
//					Height,
//					GL_RGB,
//				    GL_UNSIGNED_BYTE,
//				    Pixels
//				    );
//			}
//		}
		
		delete[] Buffer;
	}
	
	Log( 10, "Shader Loaded" );

}
// - ------------------------------------------------------------------------------------------ - //
