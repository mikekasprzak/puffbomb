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

public:
	// Time stamp for the last time this texture was requested, in frames //
	unsigned int FrameStamp;
	
	// Number of times this texture is used, before deleted.  A statistic for prioritizing a //
	//   heavily used texture ahead of a rarely used one, when VRAM space is requested. //
	unsigned int UseCount;
	
	// A running total of currently active references to a texture.  Textures with a reference //
	//   count of zero should be the first to be removed, as far as prioritization is concerned. //
	unsigned int ReferenceCount;

public:
	// Null Constructor //
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
	
	// Normal use Constructor (or call Load yourself) //
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
	
	// Destructor //
	~cTextureInfo() {
		FreeVRAM();
		FreeRAM();
	}

public:
	// Store a filename, clean up, and cache data as requested //
	void Load( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false );
		
	// Load variant that takes only the caching parameters as arguments, using the already set //
	//   filename as our
	inline void Load( const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) {
		Load( FileName, _CacheToVRAM, _CacheToRAM );
	}

	// Load the respected data in to memory //
	void CacheToVRAM();
	void CacheToRAM();
	
	// Remove the respected data from memory //
	void FreeVRAM();
	void FreeRAM();

	// Mark the texture as used this frame, caching it if it's not already available, and //
	void Use( /*int MultiTexture = 0*/ );

public:	
	// Our reference counting system, handled by functions, so we can cleanly expand the //
	//   functionality, as needed. //
	inline void AddReference() {
		ReferenceCount++;
	}
	
	inline void RemoveReference() {
		ReferenceCount--;
	}	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_TextureInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
