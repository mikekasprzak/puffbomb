// - ------------------------------------------------------------------------------------------ - //
// TexturePool //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <GL/gl.h>
// - ------------------------------------------------------------------------------------------ - //
cTexturePool TexturePool;
// - ------------------------------------------------------------------------------------------ - //
cTexturePool::~cTexturePool()
{
	for( std::map<std::string,cTexture>::iterator it = Pool.begin(); it != Pool.end(); ++it )
	{
		glDeleteTextures( 1, &it->second.Id );
		Log( LOG_HIGHEST_LEVEL, "Deleted Texture Id (Mesh3dPool) " );
		
		if( it->second.WhiteId != 0 )
		{
			glDeleteTextures( 1, &it->second.WhiteId );
			Log( LOG_HIGHEST_LEVEL, "Deleted Texture WhiteId (Mesh3dPool) " );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
