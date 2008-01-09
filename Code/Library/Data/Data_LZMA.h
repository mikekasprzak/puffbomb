// - ------------------------------------------------------------------------------------------ - //
// DataCompression - Compression code for Data library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Data_LZMA_H__
#define __Library_Data_Data_LZMA_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Data.h"
#include <External/Lzma/LzmaDecode.h>
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a void* (Size is lost though, as it isn't returned) //
// - ------------------------------------------------------------------------------------------ - //
inline const void* unpack_LZMA_Data( const void* _Src, const size_t _Size, size_t* _DestSize = 0 ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	const char* Src = reinterpret_cast<const char*>(_Src);
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = Src[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&Src[LZMA_PROPERTIES_SIZE]);
	
	// If a destination size was passed //
	if ( _DestSize )
		*_DestSize = UncompressedSize;
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }

	CProb Probs[ LzmaGetNumProbs(&state.Properties) ];
	state.Probs = (UInt16*)&Probs;
	
	// Allocate a new DataBlock for our uncompressed Data //
	const char* UBuffer = reinterpret_cast<const char*>(new_Data( UncompressedSize ));

	// Temporary variables modified by decode function, so to learn about how it went //
	size_t inProcessed = 0;
	size_t outProcessed = 0;
	
	// Decode the file //
	int Result = LzmaDecode( 
		&state,
		( unsigned char* )&Src[ LZMA_PROPERTIES_SIZE + 8 ],
		_Size,
		&inProcessed,
		( unsigned char* )UBuffer,
		UncompressedSize,
		&outProcessed
		);
	
	// Return our new LZMA decompressed data //
	return reinterpret_cast<const void*>(UBuffer);
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a passed void* and size_t //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t unpack_LZMA_Data( const void* _Src, const size_t _Size, const void** _Dest, const size_t _DestSize ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	const char* Src = reinterpret_cast<const char*>(_Src);
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = Src[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&Src[LZMA_PROPERTIES_SIZE]);

	// If the passed DataBlock is too small for our uncompressed data, fail //
	if ( UncompressedSize > _DestSize ) {
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
	
	// Temporary variables modified by decode function, so to learn about how it went //
	size_t inProcessed = 0;
	size_t outProcessed = 0;
	
	// Decode the file //
	int Result = LzmaDecode( 
		&state,
		( unsigned char* )&Src[ LZMA_PROPERTIES_SIZE + 8 ],
		_Size,
		&inProcessed,
		( unsigned char* )_Dest,
		UncompressedSize,
		&outProcessed
		);

	// Return our new LZMA decompressed data //
	return UncompressedSize;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Data_LZMA_H__ //
// - ------------------------------------------------------------------------------------------ - //
