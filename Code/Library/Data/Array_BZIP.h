// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_BZIP_H__
#define __Library_Data_Array_BZIP_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_BZIP.h"

#include "Array_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new Array //
template< class Type >
inline Array<Type>* unpack_BZIP_Array( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_BZIP_DataBlock( _Src );
	Array<Type>* UncompressedArray = new_Array<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new Array //
template< class Type >
inline Array<Type>* unpack_BZIP_Array( char* _Src, const size_t _SrcSize ) {
	DataBlock* Uncompressed = unpack_BZIP_DataBlock( _Src, _SrcSize );
	Array<Type>* UncompressedArray = new_Array<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode array data to a packed BZIP DataBlock //
template< class Type >
inline DataBlock* pack_BZIP_DataBlock( Array<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_BZIP_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cArray<Type>::UnpackBZIP( cDataBlock& _Src ) {
	*this = cArray<Type>( unpack_BZIP_Array<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cArray<Type>::UnpackBZIP( DataBlock* _Src ) {
	*this = cArray<Type>( unpack_BZIP_Array<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* cArray<Type>::PackBZIP() {
	return pack_BZIP_DataBlock( _Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_BZIP_H__ //
// - ------------------------------------------------------------------------------------------ - //
