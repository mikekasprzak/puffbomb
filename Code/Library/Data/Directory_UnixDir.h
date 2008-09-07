// - ------------------------------------------------------------------------------------------ - //
// Directory UnixDir - Unix Style implementation of polling a directory tree //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_UnixDir_H__
#define __Library_Data_Directory_UnixDir_H__
// - ------------------------------------------------------------------------------------------ - //
#include <dirent.h>
#include <sys/stat.h>

#include "Directory_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This is called recursively. //
inline void populate_Directory( DIRECTORY* p, const char* SearchDirectory, const char* Prefix ) {
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
		struct stat Status;
		stat( CurrentFile, &Status );
		
		// If it's a directory //
		if ( S_ISDIR( Status.st_mode ) ) {
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
		else if ( S_ISREG( Status.st_mode ) ) {
			if( Data->d_name[0] != '.' ) {
				if( Data->d_name[0] != '_' ) {
					// Build our filename string //
					char* NewFile = new char[ length_String(Prefix) + length_String(Data->d_name) + 1 ];
					copy_String( Prefix, NewFile );
					cat_String( Data->d_name, NewFile );
		
					// Add the file //
					add_Directory( p, NewFile );
					
					// Delet our filename string //
					delete_String( NewFile );
				}
			}
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
inline void populate_Directory( DIRECTORY* p ) {
	populate_Directory( p, p->BaseName, "" );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline DIRECTORY* new_Directory( const char* _BaseName ) {
	DIRECTORY* NewDir = new DIRECTORY;
	
	NewDir->BaseName = new_String( _BaseName );
	NewDir->FileName = new_Heap(0, 0);
	
	// Work //
	populate_Directory( NewDir );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline bool is_Directory( const char* _Name ) {
	struct stat Status;
	stat( _Name, &Status );
	
	// If it's a directory //
	return S_ISDIR( Status.st_mode );
}
// - ------------------------------------------------------------------------------------------ - //
inline bool is_File( const char* _Name ) {
	struct stat Status;
	stat( _Name, &Status );
	
	// If it's a directory //
	return S_ISREG( Status.st_mode );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_UnixDir_H__ //
// - ------------------------------------------------------------------------------------------ - //
