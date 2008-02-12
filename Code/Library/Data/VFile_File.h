// - ------------------------------------------------------------------------------------------ - //
// VFile File - Extended VFile features, reading, writing, and initializing from a file/FILE*
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_VFile_File_H__
#define __Library_Data_VFile_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "File_Core.h"

#include "VFile_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline VFILE* new_VFile( const char* _FileName ) {
	// VFile is too complicated a type to rely on the file size alone, so we need to read //
	//   and write a stored heap in much the same way as we would to a FILE*. //
	VFILE* p = new VFILE;
	
	p->Position = 0;
	p->Data = new_Array<char>( _FileName );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline VFILE* new_VFile( FILE* fp ) {
	VFILE* p = new VFILE;
	
	p->Position = 0;
	p->Data = new_Array<char>( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void delete_VFile( VFILE* fp ) {
	close_VFile( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it relys on the arrays being correctly allocated //
inline const size_t readfile_VFile( VFILE* p, const char* _FileName ) {
	size_t BytesRead = read_Array( p->Data, _FileName ); 

	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t writefile_VFile( const VFILE* p, const char* _FileName ) {
	size_t BytesWritten = write_Array( p->Data, _FileName ); 

	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
inline VFILE* readfile_VFile( const char* _FileName ) {
	return new_VFile( _FileName );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_VFile_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
