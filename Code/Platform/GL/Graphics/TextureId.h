// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_TextureId_H__
#define __Graphics_TextureId_H__
// - ------------------------------------------------------------------------------------------ - //
#include "TextureInfo.h"
#include "NewTexturePool.h"
// - ------------------------------------------------------------------------------------------ - //
// TextureId's are containers for texture references.  They're used to make sure data exists in //
//   VRAM, and to use them in geometry rendering.  This is built on top of a more sophisticated //
//   system that's designed to automatically handle removal of unused (or low priority) textures //
//   from VRAM, so to make things just a little more seamless and easier than unloading and //
//   reloading everything, every time. //
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
	// To get access to a texture, we need to "Load" it. Technically, just finding it in the pool //
	inline void Load( const std::string& _FileName, const bool _CacheToVRAM = true, const bool _CacheToRAM = false ) {
		// If we had an Id, remove our reference to the Id //
		if ( Id ) {
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
