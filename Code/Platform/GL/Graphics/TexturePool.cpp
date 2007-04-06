// - ------------------------------------------------------------------------------------------ - //
// TexturePool //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
//#include <windows.h>
// - ------------------------------------------------------------------------------------------ - //
//#define GL_GLEXT_PROTOTYPES 1
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
cTexturePool TexturePool;
// - ------------------------------------------------------------------------------------------ - //
/*#define WINAPI __stdcall
typedef  const char *LPCSTR;
typedef int (WINAPI *PROC)();
PROC wglGetProcAddress( LPCSTR  lpszProcName );*/
// ARB_texture_compression
//PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;

/*
typedef void (APIENTRY * GL_CompressedTexImage2DARB_Func)(
											GLenum target,
                                            GLint level,
                                            GLenum format,
                                            GLsizei width,
                                            GLsizei height,
                                            GLint border,
                                            GLsizei imageSize,
                                            const GLvoid* Data);
GL_CompressedTexImage2DARB_Func glCompressedTexImage2DARB = 0;
*/
// - ------------------------------------------------------------------------------------------ - //
cTexturePool::cTexturePool()
{
		Log( LOG_HIGHEST_LEVEL,	"-fUCK" );
	AddSearchPaths();
 		Log( LOG_HIGHEST_LEVEL,	"-111" );
   
	char *ext = (char*)glGetString( GL_EXTENSIONS );
		Log( LOG_HIGHEST_LEVEL,	"-222" );
	

	Log( LOG_HIGHEST_LEVEL,	"-33333" );
//	glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)wglGetProcAddress("glCompressedTexImage2DARB");

/*	glCompressedTexImage2DARB_PTR = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)SDL_GL_GetProcAddress("glCompressedTexImage2DARB");

	Log( LOG_HIGHEST_LEVEL,	"-44454" );

    if( !glCompressedTexImage2DARB )
    {
        Log( LOG_HIGHEST_LEVEL, "One or more ARB_texture_compression functions were not found!!!!" );
    }*/
}
// - ------------------------------------------------------------------------------------------ - //
cTexturePool::~cTexturePool()
{
	for( std::map<std::string,cTexture>::iterator it = Pool.begin(); it != Pool.end(); ++it )
	{
		glDeleteTextures( 1, &it->second.Id );
		Log( LOG_HIGHEST_LEVEL, "Deleted Texture Id ( Texture Pool ) " );
		
		if( it->second.WhiteId != 0 )
		{
			glDeleteTextures( 1, &it->second.WhiteId );
			Log( LOG_HIGHEST_LEVEL, "Deleted Texture WhiteId ( Texture Pool ) " );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cTexturePool::Remove( const std::string& _FileName )
{
	glDeleteTextures( 1, &Pool.find( _FileName )->second.Id );
	Log( LOG_HIGHEST_LEVEL, "Deleted Texture Id ( Remove Texture Pool ) " << _FileName );
	
	if( Pool.find( _FileName )->second.WhiteId != 0 )
	{
		glDeleteTextures( 1, &Pool.find( _FileName )->second.WhiteId );
		Log( LOG_HIGHEST_LEVEL, "Deleted Texture WhiteId ( Remove Texture Pool ) " );
	}
	
	Pool.erase( _FileName );
}
// - ------------------------------------------------------------------------------------------ - //
