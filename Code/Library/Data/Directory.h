// - ------------------------------------------------------------------------------------------ - //
// Directory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_H__
#define __Library_Data_Directory_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

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
inline void add_Directory( Directory* p, const char* _String ) {
	size_t StringLength = length_String( _String ) + 1;
	
//	size_t Index = allocate_Heap( p->FileName, StringLength );
//	memcpy( index_Heap( p->FileName, Index ), _String, StringLength );
	allocate_Heap( p->FileName, _String, StringLength );
}
// - ------------------------------------------------------------------------------------------ - //
inline size_t size_Directory( const Directory* p ) {
	return size_Heap( p->FileName );
}
// - ------------------------------------------------------------------------------------------ - //
inline const char* index_Directory( const Directory* p, const size_t Index ) { 
	return index_Heap( p->FileName, Index );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_H__ //
// - ------------------------------------------------------------------------------------------ - //
