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
	char* RAMCache;
	unsigned int RAMDataSize;

	// A handle from GL that identifies the texture //
	unsigned int VRAMCache;
	unsigned int VRAMDataSize;

public:
	// Dimensions of the Texture //
	unsigned int Width;
	unsigned int Height;

public: // Information needed by Allocator //
	// How much space we take up in VRAM (so allocator knows how much is used/needed) //
	//unsigned int DataSize;
	
	// Time stamp for the last time this texture was requested, in frames //
	unsigned int FrameStamp;
	
	// For a possible smarter stamping technique, to check the actual age of the last use. //
	// Set only after a gap beteen uses?  Not sure... might not be useful data. //
	//unsigned int LastFrameStamp;
	
	// Number of times this texture is used, before deleted.  A statistic for prioritizing a //
	//   heavily used texture ahead of a rarely used one, when VRAM space is requested. //
	unsigned int UseCount;
	
	// A running total of currently active references to a texture.  Textures with a reference //
	//   count of zero should be the first to be removed, as far as prioritization is concerned. //
	unsigned int ReferenceCount;

public:
	cTextureInfo() :
		RAMCache( 0 ),
		RAMDataSize( 0 ),
		VRAMCache( 0 ),
		VRAMDataSize( 0 ),
		
		Width( 0 ),
		Height( 0 ),
		
		FrameStamp( 0 ),
		UseCount( 0 ),
		ReferenceCount( 0 )
	{
	}
	
	cTextureInfo( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) :
		RAMCache( 0 ),
		RAMDataSize( 0 ),
		VRAMCache( 0 ),
		VRAMDataSize( 0 ),
		
		Width( 0 ),
		Height( 0 ),
		
		FrameStamp( 0 ),
		UseCount( 0 ),
		ReferenceCount( 0 )
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
