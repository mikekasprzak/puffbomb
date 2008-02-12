// - ------------------------------------------------------------------------------------------ - //
// Directory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_File_H__
#define __Library_Data_Directory_File_H__
// - ------------------------------------------------------------------------------------------ - //
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
//inline Directory* new_Directory( const char* _BaseName ) {
//	Directory* NewDir = new Directory;
//	
//	NewDir->BaseName = new_String( _BaseName );
//	NewDir->FileName = new_Heap(0, 0);
//	
//	// Work //
//	populate_Directory( NewDir );
//	
//	return NewDir;
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_File_H__ //
// - ------------------------------------------------------------------------------------------ - //
