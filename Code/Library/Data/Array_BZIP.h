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
	
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new Array //
template< class Type >
inline Array<Type>* unpack_BZIP_Array( char* _Src, const size_t _SrcSize ) {

}
// - ------------------------------------------------------------------------------------------ - //
// Encode packed BZIP data to a new Array //
template< class Type >
inline DataBlock* pack_BZIP_Array( Array<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_BZIP_DataBlock( Source );
	
	delete_DataBlock( Source );
	
	return Compressed;
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
