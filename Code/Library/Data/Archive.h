// - ------------------------------------------------------------------------------------------ - //
// Archive - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Archive_H__
#define __Library_Data_Archive_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

#include "Array.h"
#include "Heap.h"
// - ------------------------------------------------------------------------------------------ - //
// Archives are lists of file names with Data.  They can be populated manually, or be polled from
//   disk and other sources.
//
// Unfortunately, for archives to work, we need either array of DataBlock pointers, or heap 
//   insert/deletes.
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct Archive {
	// The given Base Archive name (include the trailing backslash .. ?) //
	char* Name;
	// A heap of filenames //
	Heap* FileName;
	// A heap of Data (DataBlocks?) //
	//Heap* Data;
	Array<DataBlock*> Data;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Create a dummy empty Archive //
inline Archive* new_Archive() {
	Archive* NewDir = new Archive;
	
	// Create and initalize an empty name string //
	NewDir->Name = new char[ 1 ];
	NewDir->Name[0] = 0;
	
	NewDir->FileName = new_Heap(0, 0);
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline Archive* new_Archive( const char* _BaseName ) {
	Archive* NewArchive = new Archive;
	
	size_t NameLength = strlen(_BaseName);
	
	NewArchive->Name = new char[NameLength];
	memcpy( NewArchive->Name, _BaseName, NameLength );
	
	// Allocate an empty FileName table //
	NewArchive->FileName = new_Heap(0, 0);
	
	// Allocate an empty Data table //
	NewArchive->Data = new_Heap(0, 0);
	
	// Work //
	
	return NewArchive;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Archive( Archive* p ) {
	if ( p->Name )
		delete [] p->Name;
	if ( p->FileName )
		delete_Heap( p->FileName );
	if ( p->Data )
		delete_Heap( p->Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//inline void add_Archive( Archive* p, char* _String ) {
//	size_t StringLength = strlen( _String );
//	
//	size_t Index = allocate_Heap( p->FileName, StringLength );
//	memcpy( index_Heap( p->FileName, Index ), _String, StringLength );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Archive_H__ //
// - ------------------------------------------------------------------------------------------ - //
