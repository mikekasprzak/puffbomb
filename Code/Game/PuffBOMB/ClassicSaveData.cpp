// - ------------------------------------------------------------------------------------------ - //
#include "ClassicSaveData.h"
// - ------------------------------------------------------------------------------------------ - //
#include <FileIO/DirectoryCache.h>
#include <String/String.h>
// - ------------------------------------------------------------------------------------------ - //
void cClassicSaveData::Load()
{
	GenerateSaveData();
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicSaveData::Save()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicSaveData::GenerateSaveData()
{
	FindMaps();
	
	if( MapData.size() > 2 )
	{
		MapData[ 0 ].Locked = false;	
		MapData[ 1 ].Locked = false;	
		MapData[ 2 ].Locked = false;	
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cClassicSaveData::FindMaps()
{
	// Find all the .map files //
	cDirectoryCache MapDirCache( "Maps/Classic/" );
	
	for( size_t idx = 0; idx < MapDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( MapDirCache.File[idx] ) == ".map" )
		{
			// push back the map name and set the defaults for all the map data //
			MapData.push_back( cMapData( MapDirCache.File[idx] ) );
		}
	}

}
// - ------------------------------------------------------------------------------------------ - //
