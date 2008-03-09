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
	cTexturePool();
	~cTexturePool();
	
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
	// Acquire the width of an image, via it's filename //
	inline size_t GetWidth( const std::string& _FileName ) {
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
	// Acquire the height of an image, via it's filename //
	inline size_t GetHeight( const std::string& _FileName ) {
		if( Pool.find( _FileName ) != Pool.end() )
		{
			return Pool[ _FileName ].Height;
		}
		else
		{
			return 0;	
		}
	}
	// ******************* Explicit kill function for broken destructor ********************** //
	void Kill();
	
	// - -------------------------------------------------------------------------------------- - //
	// Remove Texture from the pool //
	void Remove( const std::string& _FileName );
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
extern cTexturePool TexturePool;
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Graphics_TexturePool_H__ //
// - ------------------------------------------------------------------------------------------ - //