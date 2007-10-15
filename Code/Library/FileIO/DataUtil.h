// - ------------------------------------------------------------------------------------------ - //
// DataUtil - Data utility/reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataUtil_H__
#define __Library_FileIO_DataUtil_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>
// - ------------------------------------------------------------------------------------------ - //
namespace IO {
// - ------------------------------------------------------------------------------------------ - //
// MemSET wrapper //
inline void set_Data( const int _Value, void* _Data, const size_t _Size ) {
	memset( _Data, _Value, _Size );
}
// - ------------------------------------------------------------------------------------------ - //
// MemCPY wrapper //
inline void copy_Data( void* _Src, void* _Dest, const size_t _Size ) {
	memcpy( _Dest, _Src, _Size );
}
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
inline const size_t read_Data( const char* _FileName, void* Data, const size_t _Size ) {
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
	size_t BytesRead = fread( Data, 1, Size > _Size ? _Size : Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Data( const char* _FileName, void* Data, size_t _Size ) {
	// Open File //
	FILE* fp = fopen( _FileName, "wb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = fwrite( Data, 1, _Size, fp );
	// TODO: Assert on fire write error //
	
	// Close file //
	fclose( fp );
	
	// Return the number of bytes written //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void* new_Data( const size_t _Size ) {
	return (void*)(new char[_Size]);
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Data( void* _Data ) {
	delete [] reinterpret_cast<char*>(_Data);
}
// - ------------------------------------------------------------------------------------------ - //
inline void* new_Data( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	rewind( fp );
	
	// Allocate space //
	void* p = new_Data( Size );
	// TODO: Assert failure allocating block //
	
	// Read data //
	fread( p, 1, Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlock_H__ //
// - ------------------------------------------------------------------------------------------ - //
