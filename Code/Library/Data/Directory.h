// - ------------------------------------------------------------------------------------------ - //
// Directory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_H__
#define __Library_Data_Directory_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

#include <dirent.h>
#include <sys/stat.h>

#include "String.h"
#include "Heap.h"
// - ------------------------------------------------------------------------------------------ - //
// Directories are lists of file names.  They can be populated manually, or be polled from disk
//   and other sources.  The next step up from a Directory is an Archive, which contains data too.
//
// TODO: When indexing a string, consider attaching the name (BaseName) to the front.
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct Directory {
	// The given Base Directory name (include the trailing backslash .. ?) //
	char* BaseName;
	// A heap of filenames //
	Heap* FileName;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t add_Directory( Directory* p, const char* _String ) {
	size_t StringLength = length_String( _String ) + 1;
	
	return allocate_Heap( p->FileName, _String, StringLength );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_Directory( const Directory* p ) {
	return size_Heap( p->FileName );
}
// - ------------------------------------------------------------------------------------------ - //
inline const char* index_Directory( const Directory* p, const size_t Index ) { 
	return index_Heap( p->FileName, Index );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void populate_Directory( Directory* p, const char* SearchDirectory, const char* Prefix ) {
	// Extract the directory part, and open the directory //
	DIR* ThisDir = opendir( SearchDirectory );

	// Read the first entry in the directory //
	dirent* Data = readdir( ThisDir );
	
	// While we still have entries left in this directory //
	while( Data != 0 ) {
		// Full path and name of the file //
		//std::string CurrentFile = SearchDirectory + String::Slash + Data->d_name;
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
					//populate_Directory( p, CurrentFile, Prefix + Data->d_name + String::Slash );
					populate_Directory( p, CurrentFile, PrefixString );
						
					// Delete our prefix string //
					delete_String( PrefixString );
				}
		}
		// If it's a regular file //
		else if ( _S_ISREG( Status.st_mode ) ) {
			//File.push_back( Prefix + Data->d_name );

			// Build our filename string //
			char* NewFile = new char[ length_String(Prefix) + length_String(Data->d_name) + 1 ];
			copy_String( Prefix, NewFile );
			cat_String( Data->d_name, NewFile );

			// Add the file //
			add_Directory( p, NewFile );
			
			// Delet our filename string //
			delete_String( NewFile );
		}
		
		delete_String( CurrentFile );
	
		// Read the next entry //
		Data = readdir( ThisDir );
	};
	
	// Close the directory //
	closedir( ThisDir );		
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Create a dummy empty File Name list //
inline Directory* new_Directory() {
	Directory* NewDir = new Directory;
	
	// Create and initalize an empty name string //
	NewDir->BaseName = new_String("");
	
	NewDir->FileName = new_Heap(0, 0);
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline Directory* new_Directory( const char* _BaseName ) {
	Directory* NewDir = new Directory;
	
	NewDir->BaseName = new_String( _BaseName );
	NewDir->FileName = new_Heap(0, 0);
	
	// Work //
	populate_Directory( NewDir, NewDir->BaseName, "" );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Directory( Directory* p ) {
	if ( p->BaseName )
		delete [] p->BaseName;
		
	if ( p->FileName )
		delete_Heap( p->FileName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_H__ //
// - ------------------------------------------------------------------------------------------ - //
