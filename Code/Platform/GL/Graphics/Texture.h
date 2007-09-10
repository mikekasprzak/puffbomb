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
public: // Standard information //
	// Dimensions of the Texture //
	unsigned int Width;
	unsigned int Height;
	
	// The name of the file, so we can check it or reload it as needed once removed //
	std::string FileName;

public: // Information needed by Allocator //
	// How much space we take up in VRAM (so allocator knows how much is used/needed) //
	unsigned int DataSize;
	
	// Time stamp for the last time this texture was requested, in frames //
	unsigned int FrameStamp;
	
	// Number of times this texture is used, before deleted //
	unsigned int UseCount;
	
	// If a texture is active and loaded in VRAM //
	bool Active; 

public:	// Platform specific information //
	typedef unsigned int IdType;
	IdType Id;  // GL specific //


public:
	void Load( const std::string& _FileName );
	
	void LoadCompressedTexture( const char* Buffer );
public:
	cTexture() :
		Width( 0 ),
		Height( 0 ),
		FrameStamp( 0 ),
		Active( false ),
		Id( 0 )
	{
	}
	
	cTexture( const std::string& _FileName ) :
		Width( 0 ),
		Height( 0 ),
		FrameStamp( 0 ),
		Active( false ),
		Id( 0 )
	{
		Load( _FileName );
	}
	

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Texture_H__ //
// - ------------------------------------------------------------------------------------------ - //
