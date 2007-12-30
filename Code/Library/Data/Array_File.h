// - ------------------------------------------------------------------------------------------ - //
// Array File - Extended Array features, reading, writing, and initializing from a file/FILE* //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_File_H__
#define __Library_Data_Array_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Array.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to read a whole file //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		// Return a dummy instance.  This might be bad, since an empty file will look the same. //
		//return new_Array<Type>( (size_t)0 );
		
		// Or return a zero pointer.  Better, because it's clearer that allocation failed. //
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	rewind( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	Array<Type>* p = new_Array<Type>( Size / sizeof(Type) );
	// TODO: Assert failure allocating block //
	
	// Read data //
	fread( p->Data, 1, Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// NOTE: The above should be part of the streaming library? //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t read_Array( Array<Type>* p, const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	rewind( fp );
	
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = fread( p->Data, 1, Size > DataSize ? DataSize : Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_Array( Array<Type>* p, const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "wb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = fwrite( p->Data, 1, p->Size * sizeof(Type), fp );
	// TODO: Assert on fire write error //
	
	// Close file //
	fclose( fp );
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_DataBlock which functions the same as new_DataBlock. //
// Note: This is bad, as it's unclear allocation is done.  new_DataBlock() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline Array<Type>* read_Array( const char* _FileName ) {
//	return new_Array<Type>( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //


// File Versions read and write sizes //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_File_H__ //
// - ------------------------------------------------------------------------------------------ - //