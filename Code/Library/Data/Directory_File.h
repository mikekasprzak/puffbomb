// - ------------------------------------------------------------------------------------------ - //
// Directory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_File_H__
#define __Library_Data_Directory_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

#include <dirent.h>
#include <sys/stat.h>

#include "Directory_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Directories are lists of file names.  They can be populated manually, or be polled from disk
//   and other sources.  The next step up from a Directory is an Archive, which contains data too.
//
// TODO: When indexing a string, consider attaching the name (BaseName/) to the front.
// TODO: Searching for a file (given a pattern to match)
// TODO: Saving and loading Directories to and from disk/streams. (Need FILE* library)
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This is called recursively. //
inline void populate_Directory( Directory* p, const char* SearchDirectory, const char* Prefix ) {
	// Extract the directory part, and open the directory //
	DIR* ThisDir = opendir( SearchDirectory );

	// Read the first entry in the directory //
	dirent* Data = readdir( ThisDir );
	
	// While we still have entries left in this directory //
	while( Data != 0 ) {
		// Build the full path name of the file //
		char* CurrentFile = new char[ length_String(SearchDirectory) + 1 + length_String(Data->d_name) + 1 ];
		copy_String( SearchDirectory, CurrentFile );
		cat_String( "/", CurrentFile );
		cat_String( Data->d_name, CurrentFile );

		// Get the status of the file //
		struct _stat Status;
		_stat( CurrentFile, &Status );
		
		// If it's a directory //
		if ( _S_ISDIR( Status.st_mode ) ) {
			// Recursively do this again, if not a dot file or folder //
			if( Data->d_name[0] != '.' ) 
				if( Data->d_name[0] != '_' ) {
					// Build our prefix string //
					char* PrefixString = new char[ length_String(Prefix) + length_String(Data->d_name) + 2 ];
					copy_String( Prefix, PrefixString );
					cat_String( Data->d_name, PrefixString );
					cat_String( "/", PrefixString );
					
					// Recursive call //
					populate_Directory( p, CurrentFile, PrefixString );
						
					// Delete our prefix string //
					delete_String( PrefixString );
				}
		}
		// If it's a regular file //
		else if ( _S_ISREG( Status.st_mode ) ) {
			// Build our filename string //
			char* NewFile = new char[ length_String(Prefix) + length_String(Data->d_name) + 1 ];
			copy_String( Prefix, NewFile );
			cat_String( Data->d_name, NewFile );

			// Add the file //
			add_Directory( p, NewFile );
			
			// Delet our filename string //
			delete_String( NewFile );
		}
		
		// Remove our string //
		delete_String( CurrentFile );
	
		// Read the next entry //
		Data = readdir( ThisDir );
	};
	
	// Close the directory //
	closedir( ThisDir );		
}
// - ------------------------------------------------------------------------------------------ - //
inline void populate_Directory( Directory* p ) {
	populate_Directory( p, p->BaseName, "" );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline Directory* new_Directory( const char* _BaseName ) {
	Directory* NewDir = new Directory;
	
	NewDir->BaseName = new_String( _BaseName );
	NewDir->FileName = new_Heap(0, 0);
	
	// Work //
	populate_Directory( NewDir );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_File_H__ //
// - ------------------------------------------------------------------------------------------ - //
