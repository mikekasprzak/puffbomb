// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_TextureId_H__
#define __Graphics_TextureId_H__
// - ------------------------------------------------------------------------------------------ - //
#include "TextureInfo.h"
// - ------------------------------------------------------------------------------------------ - //
class cTextureId
{
	unsigned int Id;

public:
	inline cTextureId() :
		Id( 0 )
	{
	}
	
	inline cTextureId( const unsigned int _Id ) :
		Id( _Id )
	{
		// Notify Texture it's now used (reference counting) //
	}
	
	inline cTextureId( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) :
		Id( 0 )
	{
		// Lookup index of requested FileName //
		
		// Load and cache this file (Tell the TextureInfo to do it at least) //		
		//Load( _FileName, _CacheToVRAM, _CacheToRAM );
		
		// Do reference counting in Load method, just so we're accurate and not accidential //
	}
	
	inline ~cTextureId() {
		// Notify Texture it's been removed (reference counting) //
	}

public:
	inline void Load( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) {
		
	}

	inline void CacheToVRAM() {
	}
	inline void FreeVRAM() {
	}
	
	inline void CacheToRAM() {
	}
	inline void FreeRAM() {
	}

	inline void Use( int MultiTexture = 0 ) {
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_TextureInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
