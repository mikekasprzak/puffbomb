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
