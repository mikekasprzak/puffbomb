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
		SearchPath.Add( "Textures" );
		SearchPath.Add( "2D" );
		SearchPath.Add( "Maps" );
	}
	
public:
//	inline unsigned int Load( const std::string _FileName ) {
//		return (cPool< cTexture >::Load( _FileName )).Id;
//	}

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
