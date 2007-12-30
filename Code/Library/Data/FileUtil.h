// - ------------------------------------------------------------------------------------------ - //
// FileUtil - C "FILE*" wrapping and utility library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_FileUtil_H__
#define __Library_Data_FileUtil_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>

#include "EndianUtil.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: Come up with a standard interface for streamable data. //
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
// Standard reads, no endianness correction //
// - ------------------------------------------------------------------------------------------ - //
inline const long long int read_int64_File( FILE* fp ) {
	long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned long long int read_uint64_File( FILE* fp ) {
	unsigned long long int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const int read_int_File( FILE* fp ) {
	int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int read_uint_File( FILE* fp ) {
	unsigned int Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const short read_short_File( FILE* fp ) {
	short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned short read_ushort_File( FILE* fp ) {
	unsigned short Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const char read_char_File( FILE* fp ) {
	char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned char read_uchar_File( FILE* fp ) {
	unsigned char Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const float read_float_File( FILE* fp ) {
	float Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
inline const double read_double_File( FILE* fp ) {
	double Target;
	fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Platform endianness inversion read //
// - ------------------------------------------------------------------------------------------ - //
inline const int reade_int_File( FILE* fp ) {
	int Target;
	unsigned char Data[sizeof(Target)];
	fread( &Data, sizeof(Target), 1, fp );
	
	return Data[3] | (Data[2] << 8 ) | (Data[1] << 16) | (Data[0] << 24);
}
// - ------------------------------------------------------------------------------------------ - //


// TODO: Add a function for reading a DataBlock from an open file //
// TODO: Also add functions for reading data of an expected size, zero terminated strings, etc. //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_FileUtil_H__ //
// - ------------------------------------------------------------------------------------------ - //
