// - ------------------------------------------------------------------------------------------ - //
// Directory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_Core_H__
#define __Library_Data_Directory_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include "String_Core.h"
#include "String_File.h"
#include "Heap_Core.h"
#include "Heap_File.h"
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
struct DIRECTORY {
	// The given Base Directory name (include the trailing backslash .. ?) //
	char* BaseName;
	// A heap of filenames //
	Heap* FileName;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t add_Directory( DIRECTORY* p, const char* _String ) {
	size_t StringLength = length_String( _String ) + 1;
	
	return allocate_Heap( p->FileName, _String, StringLength );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_Directory( const DIRECTORY* p ) {
	return size_Heap( p->FileName );
}
// - ------------------------------------------------------------------------------------------ - //
inline const char* index_Directory( const DIRECTORY* p, const size_t Index ) { 
	return index_Heap( p->FileName, Index );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Create a dummy empty File Name list //
inline DIRECTORY* new_Directory() {
	DIRECTORY* NewDir = new DIRECTORY;
	
	// Create and initalize an empty name string //
	NewDir->BaseName = new_String("");
	
	NewDir->FileName = new_Heap(0, 0);
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Directory( DIRECTORY* p ) {
	if ( p->BaseName )
		delete [] p->BaseName;
		
	if ( p->FileName )
		delete_Heap( p->FileName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Create a directory from an existing directory, by pattern matching //
inline DIRECTORY* new_Directory( DIRECTORY* p, const char* Pattern ) {
	DIRECTORY* NewDir = new_Directory();
	delete_String( NewDir->BaseName );
	NewDir->BaseName = new_String( p->BaseName );
	
	for (size_t idx = 0; idx < size_Directory( p ); idx++ ) {
		if ( find_String( Pattern, index_Directory( p, idx ) ) )
			add_Directory( NewDir, index_Directory( p, idx ) );
	}
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
