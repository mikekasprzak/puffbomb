// - ------------------------------------------------------------------------------------------ - //
// SearchPath //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_SearchPath_H__
#define __Util_SearchPath_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>

#include <String/String.h>
#include "DirectoryCache.h"
// - ------------------------------------------------------------------------------------------ - //
// SearchPath Class that cache's directories (and all subdirectories) //
// - ------------------------------------------------------------------------------------------ - //
class cSearchPath {
public:
	// Cache and list of the directories to search //
	std::vector< cDirectoryCache > DirectoryCache;

public:
	// Given a string, find a matching file in any of our paths //
	inline std::string Find( const std::string& _FileName ) {
		// For all my search paths //
		for ( size_t idx = 0; idx < DirectoryCache.size(); idx++ ) {
			// For all files in the search path //
			for ( size_t idx2 = 0; idx2 < DirectoryCache[ idx ].File.size(); idx2++ ) {
				std::string& VsFileName = DirectoryCache[ idx ].File[ idx2 ];

				// If the input file has a prerequisite directory //
				if ( String::Directory( _FileName ) != String::Empty ) {
					// Test if the file doesn't include the requested directory //
					if ( !String::HasDirectory( 
							DirectoryCache[ idx ].Name + String::Slash + VsFileName,
							String::Directory( _FileName )
							)
						)
						continue;
				}

				// Test if base names are the same //
				if ( String::BaseName( _FileName ) == String::BaseName( VsFileName ) ) {
					// Test if last extensions are the same //
					if ( String::LastExtension( _FileName ) == String::LastExtension( VsFileName ) ) {	
						// Return this found file, with the attached directory we've searched //
						return DirectoryCache[ idx ].Name + String::Slash + VsFileName;
					}
				}
			}
		}
		
		// No file found, so return an empty string //
		return String::Empty;
	}

public:
	// Add a directory to our search path's //
	inline void Add( const std::string& _Directory ) {
		DirectoryCache.push_back( cDirectoryCache( _Directory ) );
	}
	
	// Erase all directories //
	inline void Clear() {
		DirectoryCache.clear();
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// SearchPath Class that doesn't cache directories (untested :( ) //
// - ------------------------------------------------------------------------------------------ - //
//class cSearchPath {
//	// All the directories to search //
//	std::vector< std::string > Path;
//	
//public:
//	// Given a string, find a matching file in any of our paths //
//	inline std::string Find( const std::string& _FileName ) {
//		// For all my search paths //
//		for ( size_t idx = 0; idx < Path.size(); idx++ ) {
//			// Append the filename, just in case it contains directory information //
//			std::string WorkFile = Path[ idx ] + _FileName;
//			
//			// Extract the directory part, and open the directory //
//			DIR* ThisDir = opendir( String::Directory(WorkFile).c_str() );
//
//			// Read the first entry in the directory //
//			dirent* Data = readdir( ThisDir );
//			// While we still have entries left in this directory //
//			while( Data != 0 ) {
//				string CurrentFileName = Data->d_name;
//				
//				// if base names are the same //
//				if ( String::BaseName(WorkFile) == String::BaseName(CurrentFileName) ) {
//					// if last extensions are the same //
//					if ( String::LastExtension(WorkFile) == String::LastExtension(CurrentFileName) ) {	
//						// We have a match!! //
//						closedir( ThisDir );
//						
//						// Return this found file, with the attached directory we've searched //
//						return String::Directory(WorkFile) + CurrentFileName;
//					}
//				}
//			
//				// Read the next entry //
//				Data = readdir( ThisDir );
//			};
//			
//			// Close the directory //
//			closedir( ThisDir );
//		}
//		
//		// No file found, so return an empty string //
//		return "";
//	}
//
//public:
//	// Add a directory to our search path's //
//	inline void Add( const std::string& _Directory ) {
//		Path.push_back( _Directory );
//	}
//	
//	// Erase all directories //
//	inline void Clear() {
//		Path.clear();
//	}
//};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_SearchPath_H__ //
// - ------------------------------------------------------------------------------------------ - //
