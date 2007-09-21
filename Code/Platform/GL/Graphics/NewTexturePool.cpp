// - ------------------------------------------------------------------------------------------ - //
// NewTexturePool //
// - ------------------------------------------------------------------------------------------ - //
#include "NewTexturePool.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
// The Global Class Instance (TODO: Singleton instead?) //
cNewTexturePool NewTexturePool;
// - ------------------------------------------------------------------------------------------ - //
cNewTexturePool::cNewTexturePool()
{
	// Find all the files //
	AddSearchPaths();
	
	// TODO: Fix SearchPath or DirectoryCache to work as I want it, not requiring seen below //
	
	// Count the number of possible files //
	int FileCount = 0;
	for ( size_t idx = 0; idx < SearchPath.DirectoryCache.size(); idx++ ) {
		FileCount += SearchPath.DirectoryCache[ idx ].File.size();
	}
	
	// Create an array large enough to hold instances of every usable texture //
	TextureInfo.resize( FileCount );
	
	// Initialize every texture, FileName's names only //
	for ( size_t idx = 0; idx < SearchPath.DirectoryCache.size(); idx++ ) {
		// For all files in the search path //
		for ( size_t idx2 = 0; idx2 < SearchPath.DirectoryCache[ idx ].File.size(); idx2++ ) {
			TextureInfo[ idx ].Load( SearchPath.DirectoryCache[idx].File[idx2], false, false );
		}
	}
	
	// Build map for optimized searching //
}
// - ------------------------------------------------------------------------------------------ - //
cNewTexturePool::~cNewTexturePool()
{
//	for( std::map<std::string,cTexture>::iterator it = Pool.begin(); it != Pool.end(); ++it )
//	{
//		glDeleteTextures( 1, &it->second.Id );
//		Log( LOG_HIGHEST_LEVEL, "Deleted Texture Id ( Texture Pool ) " );
//	}
//	Pool.clear();
}
// - ------------------------------------------------------------------------------------------ - //
//void cNewTexturePool::Remove( const std::string& _FileName )
//{
//	glDeleteTextures( 1, &Pool.find( _FileName )->second.Id );
//	Log( LOG_HIGHEST_LEVEL, "Deleted Texture Id ( Remove Texture Pool ) " << _FileName );
//	
//	Pool.erase( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //
