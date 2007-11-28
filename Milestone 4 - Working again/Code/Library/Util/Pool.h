// - ------------------------------------------------------------------------------------------ - //
// Pool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_Pool_H__
#define __Util_Pool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <FileIO/SearchPath.h>
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class cPool {
protected:
	// STL MAP structure to reference and access the elements //
	std::map< std::string, Type > Pool;
	// What directories to search.  Populate this in your constructor. //
	cSearchPath SearchPath;
	
	// A dummy entry.  Should be stably constructed without arguments //
	Type Dummy;
	
public:
	// This load/cache is implicit, by texture request name. //
	// It will only correctly cache files searched for the same way. //
	// i.e. Texture.tx, not /Content/Textures/Texture.tx //
	// The trade off is it'll have to search directory cache every time it requests a file, which //
	//   is slow.
	//   SearchPath's fault, and would suck.  SearchPath could cache directories, but it would //
	//   still have to do the string work, but would take up space.  Maybe necessary.  TBD. //
	inline Type& Load( const std::string _FileName ) {
		// If not in the pool //
		if ( Pool.find( _FileName ) == Pool.end() ) {
			// Find the file //
			std::string FileName = SearchPath.Find( _FileName );
	
			// If no file was found //
			if ( FileName == "" ) {
				Log( LOG_HIGHEST_LEVEL, "** Pool can't find " << _FileName );
				
				//Global::Shutdown = true;
				return Dummy;
			}
			else {
				Log( LOG_HIGHEST_LEVEL, "Not found in Pool Cache.  Loading " << FileName );				
			}

			// If we're here, then an entry was found.  Load it, and add it to the map //
			Pool[ _FileName ] = Type( FileName );
		}

		// Get a reference //
		return Pool[ _FileName ];
	}
	
	inline void Clear() {
		// Erase all elements //
		Pool.clear();
	}
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Pool_H__ //
// - ------------------------------------------------------------------------------------------ - //
