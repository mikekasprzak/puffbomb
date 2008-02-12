// - ------------------------------------------------------------------------------------------ - //
// Heap File - Extended Heap features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Heap_File_H__
#define __Library_Data_Heap_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Heap_Core.h"
#include "File.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline Heap* new_Heap( const char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Heap is too complicated a type to rely on the file size alone, so we need to read //
	//   and write a stored heap in much the same way as we would to a FILE*. //
	Heap* p = new Heap;
	
	p->Index = new_Array<size_t>( fp );
	p->Data = new_Array<char>( fp );

	
	// Close file //
	close_File( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline Heap* new_Heap( FILE* fp ) {
	Heap* p = new Heap;
	
	p->Index = new_Array<size_t>( fp );
	p->Data = new_Array<char>( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_Heap( Heap* p, const char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	size_t BytesRead = read_Array( p->Index, fp );
	BytesRead += read_Array( p->Data, fp ); 

	// Close file //
	close_File( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Heap( Heap* p, const char* _FileName ) {
	// Open File //
	FILE* fp = open_writeonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}

	size_t BytesWritten = write_Array( p->Index, fp );
	BytesWritten += write_Array( p->Data, fp ); 

	// TODO: Assert on fire write error //
	
	// Close file //
	close_File( fp );
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_Heap which functions the same as new_Heap. //
// Note: This is bad, as it's unclear allocation is done.  new_Heap() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline Heap* read_Heap( const char* _FileName ) {
//	return new_Heap( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Heap( Heap* p, FILE* fp ) {
	size_t BytesWritten = write_Array( p->Index, fp );
	BytesWritten += write_Array( p->Data, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_Heap( Heap* p, FILE* fp ) {
	size_t BytesRead = read_Array( p->Index, fp );
	BytesRead += read_Array( p->Data, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Heap_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
