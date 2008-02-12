// - ------------------------------------------------------------------------------------------ - //
// Array File - Extended Array features, reading, writing, and initializing from a file/FILE* //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_File_H__
#define __Library_Data_Array_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Array.h"
#include "File.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to read a whole file //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const char* _FileName ) {
	// Open File //
//	FILE* fp = fopen( _FileName, "rb" );
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		// Return a dummy instance.  This might be bad, since an empty file will look the same. //
		//return new_Array<Type>( (size_t)0 );
		
		// Or return a zero pointer.  Better, because it's clearer that allocation failed. //
		return 0;
	}
	
	// Determine how large file is //
//	fseek( fp, 0, SEEK_END );
//	size_t Size = ftell( fp );
//	rewind( fp );
	size_t Size = size_File( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	Array<Type>* p = new_Array<Type>( Size / sizeof(Type) );
	
	// TODO: Assert failure allocating block //
	
	// Read data //
	//fread( p->Data, 1, Size, fp );
	read_File( fp, (char*)&p->Data[0], Size );
	
	// Close file //
	//fclose( fp );
	close_File( fp );
	
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
//	FILE* fp = fopen( _FileName, "rb" );
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Determine how large file is //
//	fseek( fp, 0, SEEK_END );
//	size_t Size = ftell( fp );
//	rewind( fp );
	size_t Size = size_File( fp );
	
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
//	size_t BytesRead = fread( p->Data, 1, Size > DataSize ? DataSize : Size, fp );
	size_t BytesRead = read_File( fp, p->Data, Size > DataSize ? DataSize : Size );
	
	// Close file //
//	fclose( fp );
	close_File( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_Array( Array<Type>* p, const char* _FileName ) {
	// Open File //
//	FILE* fp = fopen( _FileName, "wb" );
	FILE* fp = open_writeonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Write the data //
//	size_t BytesWritten = fwrite( p->Data, 1, p->Size * sizeof(Type), fp );
	size_t BytesWritten = write_File( fp, p->Data, p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
	
	// Close file //
//	fclose( fp );
	close_File( fp );
		
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


// - ------------------------------------------------------------------------------------------ - //
// FILE* Versions read and write sizes //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t read_Array( Array<Type>* p, FILE* fp ) {
	// Read Size //
	size_t Size = read_File<size_t>( fp );
	
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
//	size_t BytesRead = fread( p->Data, 1, Size > DataSize ? DataSize : Size, fp );
	size_t BytesRead = read_File( fp, p->Data, Size > DataSize ? DataSize : Size );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_Array( Array<Type>* p, FILE* fp ) {
	// Write Size //
	write_File( fp, p->Size );

	// Write the data //
	//size_t BytesWritten = fwrite( p->Data, 1, p->Size * sizeof(Type), fp );
	size_t BytesWritten = write_File( fp, p->Data, p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
			
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_File_H__ //
// - ------------------------------------------------------------------------------------------ - //
