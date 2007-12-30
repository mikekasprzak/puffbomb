// - ------------------------------------------------------------------------------------------ - //
// FileUtil - C "FILE*" wrapping and utility library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_FileUtil_Core_H__
#define __Library_Data_FileUtil_Core_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a function for reading a DataBlock from an open file //
// TODO: Also add functions for reading data of an expected size, zero terminated strings, etc. //
// TODO: Add functions for reading/adapting floating point numbers from IEEE to other needed types
// TODO: Add functions for converting/writing floats to fixed point numbers (a cheat)
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

#include "EndianUtil.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
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
inline const size_t size_File( FILE* fp ) {
	size_t Position = ftell( fp );
	
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	fseek( fp, Position, SEEK_CUR );
	
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline FILE* open_File( char* _FileName, char* _OpenMask = "rb" ) {
	return fopen( _FileName, _OpenMask );
}
// - ------------------------------------------------------------------------------------------ - //
inline FILE* open_readonly_File( char* _FileName ) {
	return fopen( _FileName, "rb" );
}
// - ------------------------------------------------------------------------------------------ - //
inline FILE* open_writeonly_File( char* _FileName ) {
	return fopen( _FileName, "wb" );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void close_File( FILE* fp ) {
	fclose( fp );
}
// - ------------------------------------------------------------------------------------------ - //

// NOTE: C library has 2 interesting functions.  tmpfile() and tmpname( .. ).  tmpfile creates //
//   a temorary file instance, that erases itself when closed.  tmpname returns a legit temporary //
//   filename, that does not conflict (with what, I don't know).  If you choose to open the file, //
//   don't forget to delete it with "remove( "File.blah" );". //

// fread( TargetPointer, DataSize, Count, FilePointer );

// - ------------------------------------------------------------------------------------------ - //
// Templated Access functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type read_File( FILE* fp ) {
	Type Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readswap_File( FILE* fp ) {
	Type Target;
	fread( &Target, sizeof(Target), 1, fp );
	return byteswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readbe_File( FILE* fp ) {
	Type Target;
	fread( &Target, sizeof(Target), 1, fp );
	return beswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readle_File( FILE* fp ) {
	Type Target;
	fread( &Target, sizeof(Target), 1, fp );
	return leswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_FileUtil_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
