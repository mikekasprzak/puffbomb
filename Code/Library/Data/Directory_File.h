// - ------------------------------------------------------------------------------------------ - //
// Directory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Directory_File_H__
#define __Library_Data_Directory_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Stream_Core.h"
#include "File_Core.h"
#include "VFile_Core.h"

#include "Directory_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Directories are lists of file names.  They can be populated manually, or be polled from disk
//   and other sources.  The next step up from a Directory is an Archive, which contains data too.
//
// TODO: When indexing a string, consider attaching the name (BaseName/) to the front.
// TODO: Searching for a file (given a pattern to match)
// TODO: Saving and loading Directories to and from disk/streams. (Need FILE* library)
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline Directory* new_Directory( FILE* fp ) {
	Directory* p = new Directory;
	
	p->BaseName = new_String( fp );
	p->FileName = new_Heap( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline Directory* read_Directory( const char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Directory is too complicated a type to rely on the file size alone, so we need to read //
	//   and write a stored heap in much the same way as we would to a FILE*. //
	Directory* p = new Directory;
	
	p->BaseName = new_String( fp );
	p->FileName = new_Heap( fp );

	
	// Close file //
	close_File( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it relys on the arrays being correctly allocated //
inline const size_t read_Directory( Directory* p, const char* _FileName ) {
	// Open File //
	FILE* fp = open_readonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	size_t BytesRead = read_String( p->BaseName, fp );
	BytesRead += read_Heap( p->FileName, fp ); 

	// Close file //
	close_File( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Directory( const Directory* p, const char* _FileName ) {
	// Open File //
	FILE* fp = open_writeonly_File( _FileName );
	if ( fp == 0 ) {
		return 0;
	}

	size_t BytesWritten = write_String( p->BaseName, fp );
	BytesWritten += write_Heap( p->FileName, fp ); 

	// TODO: Assert on fire write error //
	
	// Close file //
	close_File( fp );
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_Heap which functions the same as new_Heap. //
// Note: This is bad, as it's unclear allocation is done.  new_Heap() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline Heap* read_Heap( const char* _FileName ) {
//	return new_Heap( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it rely's on the arrays being correctly allocated //
inline const size_t read_Directory( Directory* p, FILE* fp ) {
	size_t BytesRead = read_String( p->BaseName, fp );
	BytesRead += read_Heap( p->FileName, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Directory( const Directory* p, FILE* fp ) {
	size_t BytesWritten = write_String( p->BaseName, fp );
	BytesWritten += write_Heap( p->FileName, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it rely's on the arrays being correctly allocated //
inline const size_t read_Directory( Directory* p, VFILE* fp ) {
	size_t BytesRead = read_String( p->BaseName, fp );
	BytesRead += read_Heap( p->FileName, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Directory( const Directory* p, VFILE* fp ) {
	size_t BytesWritten = write_String( p->BaseName, fp );
	BytesWritten += write_Heap( p->FileName, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it rely's on the arrays being correctly allocated //
template< class STREAM >
inline const size_t read_Directory( Directory* p, STREAM* fp ) {
	size_t BytesRead = read_String( p->BaseName, fp );
	BytesRead += read_Heap( p->FileName, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
template< class STREAM >
inline const size_t write_Directory( const Directory* p, STREAM* fp ) {
	size_t BytesWritten = write_String( p->BaseName, fp );
	BytesWritten += write_Heap( p->FileName, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Directory_File_H__ //
// - ------------------------------------------------------------------------------------------ - //
