// - ------------------------------------------------------------------------------------------ - //
// TexturePool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Graphics_TexturePool_H__
#define __Library_Graphics_TexturePool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/Pool.h>
#include "Texture.h"
// - ------------------------------------------------------------------------------------------ - //
class cTexturePool : public cPool< cTexture > {
public:
	cTexturePool()
	{
		SearchPath.Add( "Textures" );
	}
	~cTexturePool();

public:
	inline size_t GetWidth( const std::string& _FileName )
	{
		if( Pool.find( _FileName ) != Pool.end() )
		{
			return Pool[ _FileName ].Width;
		}
		else
		{
			return 0;	
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline size_t GetHeight( const std::string& _FileName )
	{
		if( Pool.find( _FileName ) != Pool.end() )
		{
			return Pool[ _FileName ].Height;
		}
		else
		{
			return 0;	
		}
	}
	// - -------------------------------------------------------------------------------------- - //	
};

extern cTexturePool TexturePool;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Graphics_TexturePool_H__ //
// - ------------------------------------------------------------------------------------------ - //
