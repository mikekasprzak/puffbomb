// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_TextureInfo_H__
#define __Graphics_TextureInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cTextureInfo
{
public:
	// Name of the actual file //
	std::string FileName;
	
	// Pointer to compressed data //
	unsigned char* RAMCache;
	

	// A handle from GL that identifies the texture //
	unsigned int VRAMCache;

public:
	// Dimensions of the Texture //
	unsigned int Width;
	unsigned int Height;

public: // Information needed by Allocator //
	// How much space we take up in VRAM (so allocator knows how much is used/needed) //
	unsigned int DataSize;
	
	// Time stamp for the last time this texture was requested, in frames //
	unsigned int FrameStamp;
	
	// Number of times this texture is used, before deleted //
	unsigned int UseCount;

public:
	cTextureInfo() :
		RAMCache( 0 ),
		VRAMCache( 0 ),
		
		Width( 0 ),
		Height( 0 ),
		
		DataSize( 0 ),
		FrameStamp( 0 ),
		UseCount( 0 )
	{
	}
	
	cTextureInfo( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) :
		FileName( _FileName ),
		RAMCache( 0 ),
		VRAMCache( 0 ),
		
		Width( 0 ),
		Height( 0 ),
		
		DataSize( 0 ),
		FrameStamp( 0 ),
		UseCount( 0 )
	{
		Load( _FileName, _CacheToVRAM, _CacheToRAM );
	}
	
	~cTextureInfo() {
		FreeVRAM();
		FreeRAM();
	}

public:
	void Load( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false );

	void CacheToVRAM();
	void CacheToRAM();
	
	void FreeVRAM();
	void FreeRAM();

	void Use( int MultiTexture = 0 );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_TextureInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
