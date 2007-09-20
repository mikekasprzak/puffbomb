// - ------------------------------------------------------------------------------------------ - //
// TextureInfo //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TextureInfo.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Load is a rather meaty function that, once populated, brings our data in to memory. //
// - ------------------------------------------------------------------------------------------ - //
void cTextureInfo::Load( const std::string& _FileName, const bool _CacheToVRAM, const bool _CacheToRAM ) {
	// Remove caches, in case I already contain something //
	FreeRAM();
	FreeVRAM();
	
	// Do something impressive //
	FileName = _FileName;
	
	// If we want a copy of the compressed data in normal RAM, make one. //
	// We do this first, so the CacheToVRAM code can find it and use it if available. //
	if (_CacheToRAM) {
		CacheToRAM();
	}
	
	// If we actually want the graphic resident in VRAM, do it //
	if (_CacheToVRAM) {
		CacheToVRAM();
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// VRAM Caching is the core thing we do to textures.  Otherwise, we can't see them. //
// - ------------------------------------------------------------------------------------------ - //
void cTextureInfo::CacheToVRAM() {
	// First, make sure we're not already in VRAM //
	if ( !VRAMCache ) {
		unsigned char* CompressedData = 0;
		
		// If not RAM cached, load the data manually //
		if ( !RAMCache ) {
			// FileIO magic goes here //
			// Read in to a constant "load" buffer, to avoid fragmentation //
		}
		else {
			CompressedData = RAMCache;
		}
		
		// Decompress data in to a "preload" RAM buffer large enough to accomodate the predefined //
		//   maxiumum texture size.  If load code is threaded, each thread will need a buffer. //
		
		// Decompression code should know what type of file it is, PNG, TX, and their variants. //
		
		// Set Width, Height, and (uncompressed) DataSize variables //
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cTextureInfo::FreeVRAM() {
	// First, make sure we are in VRAM //
	if ( VRAMCache ) {
		// Remove it from VRAM //
		
		// Note our texture is no longer cached //
		VRAMCache = 0;
		
		// Reset the UseCount, since we were demoted from VRAM //
		UseCount = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// RAM Caching is something else we can do speed up performance of textures that dip in and out //
//   of VRAM on a regular basis.  Either as a further memory optimization, or to simply improve //
//   load time of the game, so long as there's enough memory to cache everything.  //
// - ------------------------------------------------------------------------------------------ - //
void cTextureInfo::CacheToRAM() {
	// First, make sure we're not already in RAM //
	if ( !RAMCache ) {
		// FileIO magic goes here //
		
		// Allocate a block of memory, and read in the data as a whole //
		//RamCache = new unsigned char[ LOTS!! ];
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cTextureInfo::FreeRAM() {
	// First, make sure we are in RAM //
	if ( RAMCache ) {
		// Remove it from RAM //
		//delete [] RAMCache;
		
		// Note our texture is no longer cached //
		RAMCache = 0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Called every time a texture change is requested.  Not only does it encapsulate the //
//  functionality in a general purpose way, but it allows us to collect statistics we can then //
//  use to remove textures that haven't been requested in a while, freeing up room for new //
//  textures that need the room to fit. //
// - ------------------------------------------------------------------------------------------ - //
void cTextureInfo::Use( int MultiTexture ) {
	// If the texture is NOT cached in VRAM, we need to cache it. //
	if ( !VRAMCache ) {
		CacheToVRAM();
	}
	
	// If a multitexturing layer is requested, specify it //
	// NOTE: This should always be done, so that the multitexture layer is always initally set. //
	//   Otherwise, remove it entirely if no multitexturing support is needed. //
	if ( MultiTexture ) {
		// Set Multitexture layer //
	}
	
	// Bind Texture for use //
	//glBind( ... );
}
// - ------------------------------------------------------------------------------------------ - //
