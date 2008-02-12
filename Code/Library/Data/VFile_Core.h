// - ------------------------------------------------------------------------------------------ - //
// VFile - "FILE*" like implementation that's to a virtual file in RAM //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_VFile_Core_H__
#define __Library_Data_VFile_Core_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a function for reading a DataBlock from an open file //
// TODO: Also add functions for reading data of an expected size, zero terminated strings, etc. //
// TODO: Add functions for reading/adapting floating point numbers from IEEE to other needed types
// TODO: Add functions for converting/writing floats to fixed point numbers (a cheat)
// - ------------------------------------------------------------------------------------------ - //
#include "Array.h"

#include "Endian.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct VFILE {
	size_t Position;
	Array<char>* Data;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Get the size of an open file, in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_File( VFILE* fp ) {
	return fp->Data->Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Opening files //
// - ------------------------------------------------------------------------------------------ - //
inline VFILE* open_VFile( const char* = "rb" ) {
	VFILE* MyFile = new VFILE;
	MyFile->Position = 0;
	MyFile->Data = new Array<char>();
	return MyFile;
}
// - ------------------------------------------------------------------------------------------ - //
inline VFILE* open_readonly_VFile( ) {
	return open_VFile();
}
// - ------------------------------------------------------------------------------------------ - //
inline VFILE* open_writeonly_VFile( ) {
	return open_VFile();
}
// - ------------------------------------------------------------------------------------------ - //

// NOTE: C library has 2 interesting functions.  tmpfile() and tmpname( .. ).  tmpfile creates //
//   a temorary file instance, that erases itself when closed.  tmpname returns a legit temporary //
//   filename, that does not conflict (with what, I don't know).  If you choose to open the file, //
//   don't forget to delete it with "remove( "File.blah" );". //


// - ------------------------------------------------------------------------------------------ - //
// Closing Files //
// - ------------------------------------------------------------------------------------------ - //
inline void close_VFile( VFILE* fp ) {
	delete_Array<char>( fp->Data );
	
	delete fp;
}
// - ------------------------------------------------------------------------------------------ - //


// NOTE: fread( TargetPointer, DataSize, Count, FilePointer ); //

// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type read_VFile( VFILE* fp ) {	
	Type Target;
	copy_Data( &(fp->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	//fread( &Target, sizeof(Target), 1, fp );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readswap_VFile( VFILE* fp ) {
	Type Target;
	copy_Data( &(fp->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	//fread( &Target, sizeof(Target), 1, fp );
	return byteswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readbe_VFile( VFILE* fp ) {
	Type Target;
	copy_Data( &(fp->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	//fread( &Target, sizeof(Target), 1, fp );
	return beswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readle_VFile( VFILE* fp ) {
	Type Target;
	copy_Data( &(fp->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	//fread( &Target, sizeof(Target), 1, fp );
	return leswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_VFile( VFILE* fp, char* Data, const size_t Size ) {
	copy_Data( &(fp->Data[fp->Position]), Data, Size );
	fp->Position += Size;
	return Size;

	//return fread( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_VFile( VFILE* fp, const Type Data ) {
	copy_Data( (char*)&Data, &(fp->Data[fp->Position]), sizeof( Data ) );
	fp->Position += sizeof( Data );
	return sizeof( Data );
	//return fwrite( &Data, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writeswap_VFile( VFILE* fp, const Type Data ) {
	Type Copy = byteswap(Data);
	
	copy_Data( (char*)&Copy, &(fp->Data[fp->Position]), sizeof( Copy ) );
	fp->Position += sizeof( Copy );
	return sizeof( Copy );
//	return fwrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writebe_VFile( VFILE* fp, const Type Data ) {
	Type Copy = beswap(Data);
	
	copy_Data( (char*)&Copy, &(fp->Data[fp->Position]), sizeof( Copy ) );
	fp->Position += sizeof( Copy );
	return sizeof( Copy );
//	return fwrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writele_VFile( VFILE* fp, const Type Data ) {
	Type Copy = leswap(Data);
	
	copy_Data( (char*)&Copy, &(fp->Data[fp->Position]), sizeof( Copy ) );
	fp->Position += sizeof( Copy );
	return sizeof( Copy );
//	return fwrite( &Copy, sizeof(Data), 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_VFile( VFILE* fp, const char* Data, const size_t Size ) {
	copy_Data( Data, &(fp->Data[fp->Position]), Size );
	fp->Position += Size;
	return Size;

//	return fwrite( Data, Size, 1, fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_VFile_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
