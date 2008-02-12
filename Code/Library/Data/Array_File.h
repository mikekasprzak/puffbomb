// - ------------------------------------------------------------------------------------------ - //
// Array File - Extended Array features, reading, writing, and initializing from a file/FILE* //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_File_H__
#define __Library_Data_Array_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Stream_Core.h"
#include "File_Core.h"
#include "VFile_Core.h"

#include "Array_Core.h"
#include "DataBlock_File.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big it is //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		// Return a dummy instance.  This might be bad, since an empty file will look the same. //
		//return new_Array<Type>( (size_t)0 );
		
		// Or return a zero pointer.  Better, because it's clearer that allocation failed. //
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_File( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	Array<Type>* p = new_Array<Type>( Size / sizeof(Type) );
	
	// Read data //
	read_File( fp, (char*)&p->Data[0], Size );
	
	// Close file //
	close_File( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( FILE* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_File<size_t>( fp );
	
	// Allocate space (size in bytes divided by the size of a type) //
	Array<Type>* p = new_Array<Type>( Size / sizeof(Type) );
	
	// Read data (in bytes) //
	read_File( fp, (char*)&p->Data[0], Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( VFILE* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_VFile<size_t>( fp );
	
	// Allocate space (size in bytes divided by the size of a type) //
	Array<Type>* p = new_Array<Type>( Size / sizeof(Type) );
	
	// Read data (in bytes) //
	read_VFile( fp, (char*)&p->Data[0], Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type, class STREAM >
inline Array<Type>* new_Array( STREAM* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_Stream<size_t>( fp );
	
	// Allocate space (size in bytes divided by the size of a type) //
	Array<Type>* p = new_Array<Type>( Size / sizeof(Type) );
	
	// Read data (in bytes) //
	read_Stream( fp, (char*)&p->Data[0], Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* read_Array( FILE* fp ) {
	return new_Array<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* read_Array( VFILE* fp ) {
	return new_Array<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type, class STREAM >
inline Array<Type>* read_Array( STREAM* fp ) {
	return new_Array<Type>( fp );
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
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_File( fp );
	
	// Verify if we have enough room //
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_File( fp, p->Data, Size > DataSize ? DataSize : Size );
	
	// Close file //
	close_File( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_Array( const Array<Type>* p, const char* _FileName ) {
	// Open File //
	FILE* fp = open_writeonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = write_File( fp, p->Data, p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
	
	// Close file //
	close_File( fp );
		
	// Return the number of bytes written //
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
	// Read Size (in bytes) //
	size_t Size = read_File<size_t>( fp );
	
	// Verify if we have enough room //
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_File( fp, (char*)&p->Data[0], Size > DataSize ? DataSize : Size );
	
	// Return the number of bytes read //
	return BytesRead + sizeof( size_t );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_Array( const Array<Type>* p, FILE* fp ) {
	// Write Size (Size multiplied by size of a type) //
	size_t BytesWritten = write_File( fp, p->Size * sizeof(Type) );

	// Write the data (Size multiplied by size of a type) //
	BytesWritten += write_File( fp, (char*)&p->Data[0], p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
			
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// VFILE* Versions read and write sizes //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t read_Array( Array<Type>* p, VFILE* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_VFile<size_t>( fp );
	
	// Verify if we have enough room //
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_VFile( fp, (char*)&p->Data[0], Size > DataSize ? DataSize : Size );
	
	// Return the number of bytes read //
	return BytesRead + sizeof( size_t );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_Array( const Array<Type>* p, VFILE* fp ) {
	// Write Size (Size multiplied by size of a type) //
	size_t BytesWritten = write_VFile( fp, p->Size * sizeof(Type) );

	// Write the data (Size multiplied by size of a type) //
	BytesWritten += write_VFile( fp, (char*)&p->Data[0], p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
			
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// STREAM* Versions read and write sizes //
// - ------------------------------------------------------------------------------------------ - //
template< class Type, class STREAM >
inline const size_t read_Array( Array<Type>* p, STREAM* fp ) {
	// Read Size (in bytes) //
	size_t Size = read_Stream<size_t>( fp );
	
	// Verify if we have enough room //
	size_t DataSize = p->Size * sizeof(Type);
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_File( fp, (char*)&p->Data[0], Size > DataSize ? DataSize : Size );
	
	// Return the number of bytes read //
	return BytesRead + sizeof( size_t );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type, class STREAM >
inline const size_t write_Array( const Array<Type>* p, STREAM* fp ) {
	// Write Size (Size multiplied by size of a type) //
	size_t BytesWritten = write_Stream( fp, p->Size * sizeof(Type) );

	// Write the data (Size multiplied by size of a type) //
	BytesWritten += write_Stream( fp, (char*)&p->Data[0], p->Size * sizeof(Type) );

	// TODO: Assert on fire write error //
			
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_File_H__ //
// - ------------------------------------------------------------------------------------------ - //
