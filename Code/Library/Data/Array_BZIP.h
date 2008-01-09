// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_BZIP_H__
#define __Library_Data_Array_BZIP_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Array.h"
#include "DataBlock_Core.h"
#include "DataBlock_BZIP.h"
//#include <External/BZip/bzlib.h>
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new Array //
template< class Type >
inline Array<Type>* unpack_BZIP_Array( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_BZIP_DataBlock( _Src );
	
	Array<Type>* UncompressedArray = new_Array<Type>( Uncompressed );
	
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
	
	
	
//	// Assume the compressed Array contains a Array, who's size is the uncompressed size //
//	DataBlock* Compressed = reinterpret_cast<DataBlock*>(_Src->Data);
//	
//	// Allocate a memory block equal to the uncompressed size //
//	Array<Type>* Uncompressed = new_Array<Type>( Compressed->Size / sizeof(Type) );
//	
//	// Decompress the Data //
//	int Error = BZ2_bzBuffToBuffDecompress(
//		(char*)Uncompressed->Data,
//		&Uncompressed->Size,
//		Compressed->Data, // Compressed Data (After Size, and Uncompressed Size (8 bytes)) //
//		_Src->Size - 4, // Source size, since we have an extra 4 byte uncompressed size //
//		0, // small (0 - more memory used, faster. 1 - less memory (2300k max), slower) //
//		0 // verbosity (0, don't talk) //
//		);
//	// TODO: Assert on uncompress error //
//	//if ( Error != BZ_OK )
//	
//	// Return the uncompressed buffer //
//	return Uncompressed;
}
//// - ------------------------------------------------------------------------------------------ - //
//// Decode packed BZIP data to a new Array //
//template< class Type >
//inline Array<Type>* unpack_BZIP_Array( char* _Src, const size_t _Size ) {
//	// Assume the compressed Array contains a Array, who's size is the uncompressed size //
//	DataBlock* Compressed = reinterpret_cast<DataBlock*>(_Src);
//	
//	// Allocate a memory block equal to the uncompressed size //
//	Array<Type>* Uncompressed = new_Array<Type>( Compressed->Size / sizeof(Type) );
//	
//	// Decompress the Data //
//	int Error = BZ2_bzBuffToBuffDecompress(
//		(char*)Uncompressed->Data,
//		&Uncompressed->Size,
//		Compressed->Data, // Compressed Data (After Size, and Uncompressed Size (8 bytes)) //
//		_Size - 4, // Source size, since we have an extra 4 byte uncompressed size //
//		0, // small (0 - more memory used, faster. 1 - less memory (2300k max), slower) //
//		0 // verbosity (0, don't talk) //
//		);
//	// TODO: Assert on uncompress error //
//	//if ( Error != BZ_OK )
//	
//	// Return the uncompressed buffer //
//	return Uncompressed;
//}
// - ------------------------------------------------------------------------------------------ - //
// Encode packed BZIP data to a new Array //
template< class Type >
inline DataBlock* pack_BZIP_Array( Array<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_BZIP_DataBlock( Source );
	
	delete_DataBlock( Source );
	
	return Compressed;
	
//	// Allocate worst case space to store compressed data //
//	Array<Type>* Compressed = new_Array<Type>( ((_Src->Size * sizeof(Type)) + ((_Src->Size * sizeof(Type)) / 100) + 600 + 4) / sizeof(Type) );
//	
//	size_t* UncompressedSize = reinterpret_cast<size_t*>(&Compressed->Data[0]);
//	*UncompressedSize = 0;
//	size_t CompressedSize = (Compressed->Size * sizeof(Type))-4;
//	
//	// Compress the Data //
//	int Error = BZ2_bzBuffToBuffCompress(
//		(char*)(&(Compressed->Data[4])),
//		&CompressedSize,
//		(char*)_Src->Data,
//		_Src->Size,
//		9, // blockSize100k (value * 100000 bytes allocated for work spcae (1-9)) //
//		0, // verbosity (0, don't talk) //
//		0 // workFactor (0 defaults to recommended case, 30) //
//		);
//	// TODO: Assert on compress error //
//	//if ( Error != BZ_OK )
//
//	
//	// Store Sizes //
//	Compressed->Size = (CompressedSize + 4) / sizeof( Type );
//	*UncompressedSize = _Src->Size;
//
//	// If bzip worked, bzip will have changed the size in the Array to less than the //
//	//   memory allocated.  Thusly, we can call reallocate to force the data buffer to be //
//	//   re-allocated to reduce memory usage (causing normal OS fragmentation). //
//	reallocate_Array( &Compressed );
//	
//	// Return the compressed buffer //
//	return Compressed;
}
//// - ------------------------------------------------------------------------------------------ - //
//
//
//// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//const cArray<Type> cArray<Type>::UnpackBZIP( const cArray<Type>& _Src ) {
//	return cArray<Type>( unpack_BZIP_Array( _Src._Data ) );
//}
//// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//const cArray<Type> cArray<Type>::PackBZIP( const cArray<Type>& _Src ) {
//	return cArray<Type>( pack_BZIP_Array( _Src._Data ) );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_BZIP_H__ //
// - ------------------------------------------------------------------------------------------ - //
