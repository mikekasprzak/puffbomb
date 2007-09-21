// - ------------------------------------------------------------------------------------------ - //
// NewTexturePool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Graphics_NewTexturePool_H__
#define __Library_Graphics_NewTexturePool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/SearchPath.h>
#include "TextureInfo.h"
// - ------------------------------------------------------------------------------------------ - //
class cNewTexturePool {
// promote to private? //
public:
	cSearchPath SearchPath;
	
	std::vector< cTextureInfo > TextureInfo;

	//std::map< 
public:
	cNewTexturePool();
	~cNewTexturePool();
	
	void AddSearchPaths()
	{
		// TODO: Is this the best way to populate file lists? //
		// Would a better design be to have a single "all files" list, and search structures //
		//   ran a filter on the data to get the files that are meaningful to each subsystem? //
		SearchPath.Add( "Textures" );
		SearchPath.Add( "2D" );
		SearchPath.Add( "Maps" );
	}
	
public:
	// Array indexing operator for quick access to TextureInfo instances //
	inline cTextureInfo& operator [] ( size_t _Index ) {
		return TextureInfo[ _Index ];
	}
	inline const cTextureInfo& operator [] ( size_t _Index ) const {
		return TextureInfo[ _Index ];
	}
	
	// Search code, given a filename, locate it, and return an Id //
	unsigned int Find( const std::string& _FileName ) const;

	
	// TODO: Smart code that knows how to free up memory goes here... somewhere //

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Remove Texture from the pool //
	//void Remove( const std::string& _FileName );
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
extern cNewTexturePool NewTexturePool;
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Graphics_NewTexturePool_H__ //
// - ------------------------------------------------------------------------------------------ - //
