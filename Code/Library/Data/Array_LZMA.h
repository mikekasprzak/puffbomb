// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_LZMA_H__
#define __Library_Data_Array_LZMA_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_LZMA.h"

#include "Array_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// This decompressor is done from scratch because it'll be used very often.  Other compressors //
//   will mainly only be used for intermediary formats. //
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a new Array //
template< class Type >
inline Array<Type>* unpack_LZMA_Array( const DataBlock* _Src ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = _Src->Data[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&_Src->Data[LZMA_PROPERTIES_SIZE]);
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }
	
	CProb Probs[ LzmaGetNumProbs(&state.Properties) ];
	state.Probs = (UInt16*)&Probs;
	
	// Allocate a new Array for our uncompressed Data //
	Array<Type>* UBuffer = new_Array<Type>( UncompressedSize / sizeof(Type) );
	
	// TODO: Assert if uncompressed size doesn't divide evenly by Type //

	// Temporary variables modified by decode function, so to learn about how it went //
	size_t inProcessed = 0;
	size_t outProcessed = 0;
	
	// Decode the file //
	int Result = LzmaDecode( 
		&state,
		( unsigned char* )&_Src->Data[ LZMA_PROPERTIES_SIZE + 8 ],
		_Src->Size,
		&inProcessed,
		( unsigned char* )UBuffer->Data,
		UncompressedSize,
		&outProcessed
		);
	
	// Return our new LZMA decompressed data //
	return UBuffer;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a new Array //
template< class Type >
inline Array<Type>* unpack_LZMA_Array( const char* _Src, const size_t _SrcSize ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = _Src[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&_Src[LZMA_PROPERTIES_SIZE]);
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }
	
	CProb Probs[ LzmaGetNumProbs(&state.Properties) ];
	state.Probs = (UInt16*)&Probs;
	
	// Allocate a new Array for our uncompressed Data //
	Array<Type>* UBuffer = new_Array<Type>( UncompressedSize / sizeof(Type) );
	
	// TODO: Assert if uncompressed size doesn't divide evenly by Type //

	// Temporary variables modified by decode function, so to learn about how it went //
	size_t inProcessed = 0;
	size_t outProcessed = 0;
	
	// Decode the file //
	int Result = LzmaDecode( 
		&state,
		( unsigned char* )&_Src[ LZMA_PROPERTIES_SIZE + 8 ],
		_SrcSize,
		&inProcessed,
		( unsigned char* )UBuffer->Data,
		UncompressedSize,
		&outProcessed
		);
	
	// Return our new LZMA decompressed data //
	return UBuffer;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cArray<Type>::UnpackLZMA( const cDataBlock& _Src ) {
	*this = cArray<Type>( unpack_LZMA_Array<Type>( _Src.Data() ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cArray<Type>::UnpackLZMA( const DataBlock* _Src ) {
	*this = cArray<Type>( unpack_LZMA_Array<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_LZMA_H__ //
// - ------------------------------------------------------------------------------------------ - //
