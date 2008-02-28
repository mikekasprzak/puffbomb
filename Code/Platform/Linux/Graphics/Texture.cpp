// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Texture.h>

#include <Util/Debug.h>
#include <String/String.h>
#include <FileIO/LZMA.h>
// - ------------------------------------------------------------------------------------------ - //
//#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#include <ddraw.h>    // Required for DirectX's DDSURFACEDESC2 structure definition
// - ------------------------------------------------------------------------------------------ - //
struct DDS_IMAGE_DATA
{
    GLsizei  width;
    GLsizei  height;
    GLint    components;
    GLenum   format;
    int      numMipMaps;
    unsigned char *pixels;
};
// - ------------------------------------------------------------------------------------------ - //
void cTexture::Load( const std::string& _FileName )
{
	Log( 10, "Loading Texture... (" << _FileName << ")" );

	FileName = _FileName;
	
	// Validate it's a texture by checking end extension //
	if( String::LastExtension( _FileName ) == ".tx" )
	{
		// Decompress the loaded data //
		char* Buffer = LZMA::UnPack( _FileName );
	
		// Hack for determining if the texture is S3TC compressed //
		if( String::HasExtension( _FileName, ".dds" ) ){
			LoadCompressedTexture( Buffer );
		}
		else {
			unsigned int* tempPixelSize	= (unsigned int*)&Buffer[0];
			unsigned int PixelSize = *tempPixelSize;
		
			unsigned int* tempWidth	= (unsigned int*)&Buffer[4];
			Width = *tempWidth;
	
			unsigned int* tempHeight	= (unsigned int*)&Buffer[8];
			Height = *tempHeight;
	
			void* Data = (unsigned char*)&Buffer[12];
			
			glGenTextures( 1, &Id );
			glBindTexture( GL_TEXTURE_2D, Id );
			
			//Log( LOG_HIGHEST_LEVEL, "Loaded Texture Id ( Texture Pool ( .tx ) ) " );
		
	//		Log( LOG_HIGHEST_LEVEL, "PixelSize = " << PixelSize );
	//		Log( LOG_HIGHEST_LEVEL, "Width = " << Width );
	//		Log( LOG_HIGHEST_LEVEL, "Height = " << Height );
	
			// Size hack, until I care to figure out how many mipmaps were generated //
			DataSize = (int)((double)(PixelSize * Width * Height) * 1.333333333);
			
			if( PixelSize == 4 ) {
				Log( 10, "Raw uncompressed 32bit Texture" );
				
				// Make it an Alpha Texture //
			    glTexImage2D(
			    	GL_TEXTURE_2D,
			    	0,
			    	GL_RGBA8,
			    	Width,
					Height,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					Data
					);
		
				gluBuild2DMipmaps(
					GL_TEXTURE_2D,
					GL_RGBA8,
					Width,
					Height,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					Data
					);
			}
			else {
				Log( 10, "Raw uncompressed 24bit Texture" );
				
				// No Alpha in this Texture //
			    glTexImage2D(
			    	GL_TEXTURE_2D,
			    	0,
			    	GL_RGB8,
			    	Width,
					Height,
					0,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					Data
					);
		
				gluBuild2DMipmaps(
					GL_TEXTURE_2D,
					GL_RGB8,
					Width,
					Height,
					GL_RGB,
				    GL_UNSIGNED_BYTE,
				    Data
				    );
			}
		}
		
		delete[] Buffer;
		
		Active = true;
		
		Log( 10, "Texture Loaded.  " << DataSize << " bytes." );
	}
	else {
		// TODO: Add .PNG file testing, as an alternative to .TX files, for development advantage //
		Log( 10, "Error: Texture not loaded.  Not a .TX file (" << FileName << ") " );
	}
}
// - ------------------------------------------------------------------------------------------ - //
DDS_IMAGE_DATA* loadDDSTextureFile( const char* Buffer )
{
    DDS_IMAGE_DATA *pDDSImageData;
    DDSURFACEDESC2 *ddsd;
    char filecode[4];
    int factor;
    int bufferSize;

	*((int*)&filecode[0]) = *((int*)&Buffer[0]);
	
	if( strncmp( filecode, "DDS ", 4 ) != 0 )
    {
    	Log( 10, "Not DDS texture File! " );
    	return NULL;
    }
	
	//Log( 10, "filecode =  " << filecode << " ****" );

	// Get the surface descriptor
	ddsd = (DDSURFACEDESC2*)&Buffer[4];
	
	//pDDSImageData = (DDS_IMAGE_DATA*)&Buffer[4 + sizeof(DDSURFACEDESC2)];
	//pDDSImageData = (DDS_IMAGE_DATA*)&Buffer[4 + sizeof(DDSURFACEDESC2)];
	
	pDDSImageData = (DDS_IMAGE_DATA*) malloc(sizeof(DDS_IMAGE_DATA));

    memset( pDDSImageData, 0, sizeof(DDS_IMAGE_DATA) );
	
    // This .dds loader supports the loading of compressed formats DXT1, DXT3 
    // and DXT5.

    switch( ddsd->ddpfPixelFormat.dwFourCC )
    {
        case FOURCC_DXT1: {
        	Log( 10, "Compressed DXT1 Texture (8:1)" );
        	
            // DXT1's compression ratio is 8:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            factor = 2;
            break;
        }

        case FOURCC_DXT3: {
        	Log( 10, "Compressed DXT3 Texture" );
        	
            // DXT3's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            factor = 4;
            break;
        }

        case FOURCC_DXT5: {
        	Log( 10, "Compressed DXT5 Texture" );
        	
            // DXT5's compression ratio is 4:1
            pDDSImageData->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            factor = 4;
            break;
        }

        default:
			Log( 10, "Error: The DDS file doesn't appear to be DXT1, DXT3, or DXT5!" );
			return NULL;
	}
    // How big will the buffer need to be to load all of the pixel data 
    // including mip-maps?

    if( ddsd->dwLinearSize == 0 )
    {
    	Log( 10, "dwLinearSize is 0!" );
    	return NULL;
    }

    if( ddsd->dwMipMapCount > 1 )
        bufferSize = ddsd->dwLinearSize * factor;
    else
        bufferSize = ddsd->dwLinearSize;

    pDDSImageData->pixels = (unsigned char*)&Buffer[ 4 + sizeof(DDSURFACEDESC2) ];

    pDDSImageData->width      = ddsd->dwWidth;
    pDDSImageData->height     = ddsd->dwHeight;
    pDDSImageData->numMipMaps = ddsd->dwMipMapCount;

    if( ddsd->ddpfPixelFormat.dwFourCC == FOURCC_DXT1 )
        pDDSImageData->components = 3;
    else
        pDDSImageData->components = 4;

    return pDDSImageData;
}
// - ------------------------------------------------------------------------------------------ - //
void cTexture::LoadCompressedTexture( const char* Buffer )
{
	// NOTE: Unlike "lena.bmp", "lena.dds" actually contains its own mip-map 
	// levels, which are also compressed.
	DDS_IMAGE_DATA *pDDSImageData = loadDDSTextureFile( Buffer );
	
	if( pDDSImageData != NULL )
	{
	    int nHeight     = pDDSImageData->height;
	    int nWidth      = pDDSImageData->width;
	    
	    Height = nHeight;
	    Width = nWidth;

	    int nNumMipMaps = pDDSImageData->numMipMaps;
	
	    int nBlockSize;
	
	    if( pDDSImageData->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT )
	        nBlockSize = 8;
	    else
	        nBlockSize = 16;
	    
	    glGenTextures( 1, &Id );
	    glBindTexture( GL_TEXTURE_2D, Id );
		
		//Log( LOG_HIGHEST_LEVEL, "Loaded Texture Id ( Texture Pool ( .dds.tx ) ) " );
		
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	    int nSize;
	    int nOffset = 0;

	    // Load the mip-map levels
	
	    for( int i = 0; i < nNumMipMaps; ++i )
	    {
	        if( nWidth  == 0 ) nWidth  = 1;
	        if( nHeight == 0 ) nHeight = 1;

	        nSize = ((nWidth+3)/4) * ((nHeight+3)/4) * nBlockSize;
			
			extern PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
			
	        glCompressedTexImage2DARB( 
	        	GL_TEXTURE_2D,
	            i,
	            pDDSImageData->format,
				nWidth,
				nHeight,
				0,
				nSize,
				pDDSImageData->pixels + nOffset
				);

	        nOffset += nSize;
	
	        // Half the image size for the next mip-map level...
	        nWidth  = (nWidth  / 2);
	        nHeight = (nHeight / 2);
	    }
	    
	    DataSize = nOffset;
	}

	if( pDDSImageData != NULL )
	{		
		free( pDDSImageData );
	}
}
// - ------------------------------------------------------------------------------------------ - //
