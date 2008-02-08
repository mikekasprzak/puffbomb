// - ------------------------------------------------------------------------------------------ - //
// Directory - Filename tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_H__
#define __Library_Data_Directory_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

#include "Array.h"
#include "Heap.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: When indexing a string, consider attaching the name (BaseName) to the front.
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct Directory {
	// The given Base Directory name (include the trailing backslash .. ?) //
	char* Name;
	
	Heap* String;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline Directory* new_Directory( const char* _BaseName = "" ) {
	Directory* NewDir = new Directory;
	
	size_t NameLength = strlen(_BaseName);
	
	NewDir->Name = new char[NameLength];
	memcpy( NewDir->Name, _BaseName, NameLength );
	
	// Allocate some starting room.  Should be large enough for "." and "..". //
	NewDir->String = new_Heap(2, 16);
	
	// Work //
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Directory( Directory* p ) {
	delete [] p->Name;
	delete_Heap( p->String );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_H__ //
// - ------------------------------------------------------------------------------------------ - //
