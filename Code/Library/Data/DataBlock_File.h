// - ------------------------------------------------------------------------------------------ - //
// DataBlock File - Extended DataBlock features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataBlock_File_H__
#define __Library_Data_DataBlock_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Stream_Core.h"
#include "File_Core.h"
#include "VFile_Core.h"

#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_File( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_File( fp, p->Data, Size );
	
	// Close file //
	close_File( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_File( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_File( fp, p->Data, Size );
	
	// Close file //
	close_File( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( FILE* fp ) {
	// Read Size //
	size_t Size = read_File<size_t>( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_File( fp, p->Data, Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( VFILE* fp ) {
	// Read Size //
	size_t Size = read_VFile<size_t>( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_VFile( fp, p->Data, Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class STREAM >
inline DataBlock* new_DataBlock( STREAM* fp ) {
	// Read Size //
	size_t Size = read_Stream<size_t>( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	read_Stream( fp, p->Data, Size );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* read_DataBlock( FILE* fp ) {
	return new_DataBlock( fp );
}
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* read_DataBlock( VFILE* fp ) {
	return new_DataBlock( fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class STREAM >
inline DataBlock* read_DataBlock( STREAM* fp ) {
	return new_DataBlock( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// NOTE: The above should be part of the streaming library? //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, const char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	size_t Size = size_File( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_File( fp, p->Data, Size > p->Size ? p->Size : Size );

	// Close file //
	close_File( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( const DataBlock* p, const char* _FileName ) {
	// Open File //
	FILE* fp = open_writeonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = write_File( fp, p->Data, p->Size );

	// TODO: Assert on fire write error //
	
	// Close file //
	close_File( fp );
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_DataBlock which functions the same as new_DataBlock. //
// Note: This is bad, as it's unclear allocation is done.  new_DataBlock() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline DataBlock* read_DataBlock( const char* _FileName ) {
//	return new_DataBlock( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, FILE* fp ) {
	// Read Size //
	size_t Size = read_File<size_t>( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_File( fp, p->Data, Size > p->Size ? p->Size : Size );
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead + sizeof( Size );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( const DataBlock* p, FILE* fp ) {
	// Write Size //
	size_t BytesWritten = write_File( fp, p->Size );
	
	// Write the data //
	BytesWritten += write_File( fp, p->Data, p->Size );
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, VFILE* fp ) {
	// Read Size //
	size_t Size = read_VFile<size_t>( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_VFile( fp, p->Data, Size > p->Size ? p->Size : Size );
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead + sizeof( Size );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( const DataBlock* p, VFILE* fp ) {
	// Write Size //
	size_t BytesWritten = write_VFile( fp, p->Size );
	
	// Write the data //
	BytesWritten += write_VFile( fp, p->Data, p->Size );
	
	// TODO: Assert on file write error //
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class STREAM >
inline const size_t read_DataBlock( DataBlock* p, STREAM* fp ) {
	// Read Size //
	size_t Size = read_Stream<size_t>( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = read_Stream( fp, p->Data, Size > p->Size ? p->Size : Size );
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead + sizeof( Size );
}
// - ------------------------------------------------------------------------------------------ - //
template< class STREAM >
inline const size_t write_DataBlock( const DataBlock* p, STREAM* fp ) {
	// Write Size //
	size_t BytesWritten = write_Stream( fp, p->Size );
	
	// Write the data //
	BytesWritten += write_Stream( fp, p->Data, p->Size );
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes write //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
