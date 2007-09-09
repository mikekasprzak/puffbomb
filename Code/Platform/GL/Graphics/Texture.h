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
	// Dimensions of the Texture //
	unsigned int Width;
	unsigned int Height;
	
	// Timestamp for the last time this texture was requested //
	unsigned int FrameStamp;
	
	void* Pixels;

public:
	unsigned int PixelSize;
	
	typedef unsigned int IdType;
	IdType Id;  // GL specific //

#ifdef EDITOR
	std::string FileName;
#endif // EDITOR //
public:
	void Load( const std::string& _FileName );
	
	void LoadCompressedTexture( const char* Buffer );
public:
	cTexture() :
		Width( 0 ),
		Height( 0 ),
		FrameStamp( 0 ),
		Pixels( 0 ),
		PixelSize( 0 ),
		Id( 0 )
	{
	}
	
	cTexture( const std::string& _FileName ) :
		Width( 0 ),
		Height( 0 ),
		FrameStamp( 0 ),
		Pixels( 0 ),
		PixelSize( 0 ),
		Id( 0 )
	{
		Load( _FileName );
	}
	

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Texture_H__ //
// - ------------------------------------------------------------------------------------------ - //
