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
public:
	cSearchPath SearchPath;
	
	std::vector< cTextureInfo > TextureInfo;

public:
	cNewTexturePool();
	~cNewTexturePool();
	
	void AddSearchPaths()
	{
		// TODO: Is this the best way to populate file lists? //
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
