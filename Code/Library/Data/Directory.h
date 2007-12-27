// - ------------------------------------------------------------------------------------------ - //
// Directory - Filename tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_H__
#define __Library_Data_Directory_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

#include "DataBlock.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct Directory {
	char* Name;
	size_t Size;
	
	int* Index;
	DataBlock* String;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline Directory* new_Directory( const char* _BaseName ) {
	Directory* NewDir = new Directory;
	
	size_t NameLength = strlen(_BaseName);
	
	NewDir.Name = new char[NameLength];
	memcpy( NewDir.Name, _BaseName, NameLength );
	Size = 0;
	
	
	
	
	//DataBlock* p = (DataBlock*)(new char[_Size+4]);
	DataBlock* p = reinterpret_cast<DataBlock*>(new char[_Size+4]);
	p->Size = _Size;
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_DataBlock( DataBlock* p ) {
	//delete [] (char*)p;
	delete [] reinterpret_cast<char*>(p);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_H__ //
// - ------------------------------------------------------------------------------------------ - //
