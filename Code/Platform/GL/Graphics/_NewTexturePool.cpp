// - ------------------------------------------------------------------------------------------ - //
// NewTexturePool //
// - ------------------------------------------------------------------------------------------ - //
#include "NewTexturePool.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/String.h>
// - ------------------------------------------------------------------------------------------ - //
// The Global Class Instance (TODO: Singleton instead?) //
//cNewTexturePool NewTexturePool;
// - ------------------------------------------------------------------------------------------ - //
cNewTexturePool::cNewTexturePool()
{
	// Find all the files //
	AddSearchPaths();
	
	// TODO: Fix SearchPath or DirectoryCache to work as I want it, not requiring seen below //
	//   Or, change the concept of AddSearchPath's, to singe out all images I care about. //
	
	// Count the number of possible files //
	int FileCount = 0;
	for ( size_t idx = 0; idx < SearchPath.DirectoryCache.size(); idx++ ) {
		FileCount += SearchPath.DirectoryCache[ idx ].File.size();
	}
	
	// Create an array large enough to hold instances of every usable texture //
	// Note: "+1" creates room for the dummy entry (0) //
	TextureInfo.resize( FileCount + 1 );
	
	// Initialize every texture, FileName's names only //
	for ( size_t idx = 0; idx < SearchPath.DirectoryCache.size(); idx++ ) {
		// For all files in the search path //
		for ( size_t idx2 = 0; idx2 < SearchPath.DirectoryCache[idx].File.size(); idx2++ ) {
			TextureInfo[ idx + 1 ].Load( SearchPath.DirectoryCache[idx].File[idx2], false, false );
		}
	}
	
	// Build map for optimized searching //
	for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
		LookUp[ String::NoExtensions(TextureInfo[idx].FileName) ] = idx;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
cNewTexturePool::~cNewTexturePool()
{
}
// - ------------------------------------------------------------------------------------------ - //
unsigned int cNewTexturePool::Find( const std::string& _FileName ) {
	// Optimized Map Search //
	if ( LookUp.find( String::NoExtensions(_FileName) ) != LookUp.end() ) {
		return LookUp[ String::NoExtensions(_FileName) ];
	}
	
	// Linear pattern matching search (if it contains the pattern, instead of exact match) //
	for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
		// Chop off the file extensions in both strings, and search the first string for the 2nd //
		//   string.  If it contains it, then we have a match. //
		if ( String::NoExtensions(TextureInfo[idx].FileName).find( String::NoExtensions(_FileName) ) != std::string::npos ) {
			return idx;
		}
	}
	
	// File not found... TODO: something more extravagant.  Assert. //
	return 0;
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
