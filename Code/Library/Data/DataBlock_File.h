// - ------------------------------------------------------------------------------------------ - //
// DataBlock File - Extended DataBlock features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataBlock_File_H__
#define __Library_Data_DataBlock_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	rewind( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	// TODO: Assert failure allocating block //
	
	// Read data //
	fread( p->Data, 1, Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation for C++ Strings //
// - ------------------------------------------------------------------------------------------ - //
//inline DataBlock* new_DataBlock( const string& _FileName ) {
//	return new_DataBlock( _FileName.c_str() );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// NOTE: The above should be part of the streaming library? //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, const char* _FileName ) {
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
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = fread( p->Data, 1, Size > p->Size ? p->Size : Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( DataBlock* p, const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "wb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = fwrite( p->Data, 1, p->Size, fp );
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
//inline DataBlock* read_DataBlock( const char* _FileName ) {
//	return new_DataBlock( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
