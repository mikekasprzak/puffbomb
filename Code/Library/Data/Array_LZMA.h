// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_LZMA_H__
#define __Library_Data_Array_LZMA_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Array.h"
#include <External/Lzma/LzmaDecode.h>
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a new Array //
template< class Type >
inline Array<Type>* unpack_LZMA_Array( const Array<Type>* _Src ) {
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
	
	// Allocate memory for "Probs" //
//	state.Probs = new CProb[ LzmaGetNumProbs(&state.Properties) ];
//	if (state.Probs == 0) {
//		//Log( LOG_MESH_INFO, "state.Probs == 0 (LZMA.h)" );
//		return 0;
//	}
	
	// Allocate a new Array for our uncompressed Data //
	Array<Type>* UBuffer = new_Array<Type>( UncompressedSize );

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
	// TODO: React to result of the decode //
	
	// Clean up work memory //
//	delete [] state.Probs;
	
	// Return our new LZMA decompressed data //
	return UBuffer;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a passed Array //
template< class Type >
inline const size_t unpack_LZMA_Array( const Array<Type>* _Src, Array<Type>* _Dest ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = _Src->Data[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&_Src->Data[LZMA_PROPERTIES_SIZE]);
	
	// If the passed Array is too small for our uncompressed data, fail //
	if ( UncompressedSize > _Dest->Size ) {
		// Not enough memory available in passed block! //
		return 0;
	}
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }

	CProb Probs[ LzmaGetNumProbs(&state.Properties) ];
	state.Probs = (UInt16*)&Probs;

//	// Allocate memory for "Probs" //
//	state.Probs = new CProb[ LzmaGetNumProbs(&state.Properties) ];
//	if (state.Probs == 0) {
//		//Log( LOG_MESH_INFO, "state.Probs == 0 (LZMA.h)" );
//		return 0;
//	}
	
	// Temporary variables modified by decode function, so to learn about how it went //
	size_t inProcessed = 0;
	size_t outProcessed = 0;
	
	// Decode the file //
	int Result = LzmaDecode( 
		&state,
		( unsigned char* )&_Src->Data[ LZMA_PROPERTIES_SIZE + 8 ],
		_Src->Size,
		&inProcessed,
		( unsigned char* )_Dest->Data,
		UncompressedSize,
		&outProcessed
		);
	// TODO: React to result of the decode //
	
	// Clean up work memory //
//	delete [] state.Probs;
	
	// Return the size of the uncompressed data on success //
	return UncompressedSize;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
const cArray<Type> cArray<Type>::UnpackLZMA( const cArray<Type>& _Src ) {
	return cArray<Type>( unpack_LZMA_Array<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_LZMA_H__ //
// - ------------------------------------------------------------------------------------------ - //
