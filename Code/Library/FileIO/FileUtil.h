// - ------------------------------------------------------------------------------------------ - //
// FileUtil - C "FILE*" wrapping and utility library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_FileUtil_H__
#define __Library_FileIO_FileUtil_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Come up with a standard interface for streamable data. //
// - ------------------------------------------------------------------------------------------ - //
//namespace IO {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the size of a file in bytes //
inline const size_t size_File( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: File code.  
//   - A File Type
//   - a size checking function (that uses ftell( fp ) to find where it was, jump to the end, and
//   jump back, so it's non destructive).
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_File( FILE* fp ) {
	size_t Position = ftell( fp );
	
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	fseek( fp, Position, SEEK_CUR );
	
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// TODO: Add a function for reading a DataBlock from an open file //
// TODO: Also add functions for reading data of an expected size, zero terminated strings, etc. //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
//#endif // __Library_FileIO_FileUtil_H__ //
// - ------------------------------------------------------------------------------------------ - //
