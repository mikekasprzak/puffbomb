// - ------------------------------------------------------------------------------------------ - //
// DataUtilCompression - Compression code for DataUtil library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataUtilCompression_H__
#define __Library_FileIO_DataUtilCompression_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataUtil.h"
#include <External/Lzma/LzmaDecode.h>
// - ------------------------------------------------------------------------------------------ - //
namespace IO {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a void* //
inline const void* unpack_LZMA_Data( const void* _Src, const size_t _Size ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	const char* Src = reinterpret_cast<const char*>(_Src);
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = Src[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&Src[LZMA_PROPERTIES_SIZE]);
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }
	
	// Allocate memory for "Probs" //
	state.Probs = new CProb[ LzmaGetNumProbs(&state.Properties) ];
	if (state.Probs == 0) {
		//Log( LOG_MESH_INFO, "state.Probs == 0 (LZMA.h)" );
		return 0;
	}
	
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
	// TODO: React to result of the decode //
	
	// Clean up work memory //
	delete [] state.Probs;
	
	// Return our new LZMA decompressed data //
	return reinterpret_cast<const void*>(UBuffer);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataUtilCompression_H__ //
// - ------------------------------------------------------------------------------------------ - //
