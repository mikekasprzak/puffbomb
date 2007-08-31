// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_Texture_H__
#define __Util_Texture_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cTexture
{
public:
	typedef unsigned int IdType;
	
	unsigned int PixelSize;
	unsigned int Width;
	unsigned int Height;
	
	IdType Id;  // Prob GL specific //
	void* Pixels;

	IdType WhiteId;
	void* WhitePixels;

#ifdef EDITOR
	std::string FileName;
#endif // EDITOR //
public:
	void Load( const std::string& _FileName );
	
	void LoadCompressedTexture( const char* Buffer );
public:
	cTexture() :
		Id( 0 ),
		WhiteId( 0 )
	{

	}
	
	cTexture( const std::string& _FileName ) :
		PixelSize( 0 ),
		Width( 0 ),
		Height( 0 ),
		Id( 0 ),
		WhiteId( 0 )
	{
		Load( _FileName );
	}
	

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Texture_H__ //
// - ------------------------------------------------------------------------------------------ - //
