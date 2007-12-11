// - ------------------------------------------------------------------------------------------ - //
// DataUtil - Data utility/reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataUtil_H__
#define __Library_FileIO_DataUtil_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>
// - ------------------------------------------------------------------------------------------ - //
// NOTE: This code could "technically" be made in to a general purpose reader/writer for all //
//   IO Operations.  F:/Art/DataFile.img for files, M1:/MyData.img for a memory card, 
//   FTP://Urb.com/neffle.dat for a remote file, etc. //
// This is open for debate though.  Memory Card code is almost worth abstracting to a custom //
//   interface, because it's a different task than reading game data, saving editor information. //
// The ability to poll local and remote data is fascinating though, even if it's LAN data. //
// Thusly, it's probably of interest to be able to either define a source (CD, HD, LAN), and all //
//   this code pulls from that source.  Do this on a per platform basis though. //
// DS or PSP could benefit greatly from this. //
// - ------------------------------------------------------------------------------------------ - //
// TODO: Come up with a standard interface for streamable data. //
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
#endif // __Library_FileIO_DataUtil_H__ //
// - ------------------------------------------------------------------------------------------ - //
