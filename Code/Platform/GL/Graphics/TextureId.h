// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_TextureId_H__
#define __Graphics_TextureId_H__
// - ------------------------------------------------------------------------------------------ - //
#include "TextureInfo.h"
#include "NewTexturePool.h"
// - ------------------------------------------------------------------------------------------ - //
class cTextureId
{
	unsigned int Id;

public:
	// Null Constructor //
	inline cTextureId() :
		Id( 0 )
	{
	}
	
	// Copy Constructor //
	inline cTextureId( const cTextureId& _Copy ) :
		Id( _Copy.Id )
	{
		// Notify Texture it's now used (reference counting) //
		NewTexturePool[ Id ].AddReference();
	}
	
	// TODO: Might be obsolete, because Id is private, and copy construction would do function //
	inline cTextureId( const unsigned int _Id ) :
		Id( _Id )
	{
		// Notify Texture it's now used (reference counting) //
		NewTexturePool[ Id ].AddReference();
	}
	
	// Standard argument constructor (given a file and some options, flag me and cache me) //
	inline cTextureId( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) :
		Id( 0 )
	{
		// Load and cache this file (Tell the TextureInfo to do it at least) //
		// Note: Reference counting for this one is done in Load	
		Load( _FileName, _CacheToVRAM, _CacheToRAM );
	}
	
	// Destructor //
	inline ~cTextureId() {
		// Notify Texture it's been removed (reference counting) //
		NewTexturePool[ Id ].RemoveReference();
	}

public:
	inline void Load( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) {
		// If we had an Id, we are about to lose it //
		if ( Id ) {
			// Remove our reference to the Id //
			NewTexturePool[ Id ].RemoveReference();
		}
		
		// Lookup index of requested FileName //
		Id = 0;
		
		// Call their Load method with our caching arguments //
		NewTexturePool[ Id ].Load( _CacheToVRAM, _CacheToRAM );
		
		// Add a reference to that texture, so it knows it's in use //
		NewTexturePool[ Id ].AddReference();
	}

	// Use/Bind this texture to the geometry I'm about to render //
	inline void Use( int MultiTexture = 0 ) const {
		NewTexturePool[ Id ].Use( MultiTexture );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_TextureInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
