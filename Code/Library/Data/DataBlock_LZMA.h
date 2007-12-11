// - ------------------------------------------------------------------------------------------ - //
// DataBlockCompression - Compression code for DataBlock library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataBlock_LZMA_H__
#define __Library_FileIO_DataBlock_LZMA_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock.h"
#include <External/Lzma/LzmaDecode.h>
// - ------------------------------------------------------------------------------------------ - //
//namespace IO {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a new DataBlock //
inline DataBlock* unpack_LZMA_DataBlock( const DataBlock* _Src ) {
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
	
	// Allocate memory for "Probs" //
	state.Probs = new CProb[ LzmaGetNumProbs(&state.Properties) ];
	if (state.Probs == 0) {
		//Log( LOG_MESH_INFO, "state.Probs == 0 (LZMA.h)" );
		return 0;
	}
	
	// Allocate a new DataBlock for our uncompressed Data //
	DataBlock* UBuffer = new_DataBlock( UncompressedSize );

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
	delete [] state.Probs;
	
	// Return our new LZMA decompressed data //
	return UBuffer;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a passed DataBlock //
inline const size_t unpack_LZMA_DataBlock( const DataBlock* _Src, DataBlock* _Dest ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = _Src->Data[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&_Src->Data[LZMA_PROPERTIES_SIZE]);
	
	// If the passed DataBlock is too small for our uncompressed data, fail //
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
	
	// Allocate memory for "Probs" //
	state.Probs = new CProb[ LzmaGetNumProbs(&state.Properties) ];
	if (state.Probs == 0) {
		//Log( LOG_MESH_INFO, "state.Probs == 0 (LZMA.h)" );
		return 0;
	}
	
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
	delete [] state.Probs;
	
	// Return the size of the uncompressed data on success //
	return UncompressedSize;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a passed DataBlock, with a passed workspace //
inline const size_t unpack_LZMA_DataBlock( const DataBlock* _Src, DataBlock* _Dest, DataBlock* _WorkSpace ) {
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = _Src->Data[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&_Src->Data[LZMA_PROPERTIES_SIZE]);
	
	// If the passed DataBlock is too small for our uncompressed data, fail //
	if ( UncompressedSize > _Dest->Size ) {
		// Not enough memory available it passed block! //
		return 0;
	}
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }
	
	// Check how much space we need for our "Probs" //
	size_t ProbsCount = LzmaGetNumProbs(&state.Properties);
	if ( (ProbsCount * sizeof(CProb)) > _WorkSpace->Size ) {
		// Not enough memory available in workspace block //
		return 0;
	}
	
	// Placement new doesn't work here, because there is no constructor //
	//state.Probs = new(_WorkSpace->Data) CProb[ ProbsCount ];
	
	// "Allocate" memory for "Probs", i.e. asuming we passed the workspace size check, use the data //
	state.Probs = reinterpret_cast<CProb*>(_WorkSpace->Data);
	
	// Check if allocation worked //
	if (state.Probs == 0) {
		//Log( LOG_MESH_INFO, "state.Probs == 0 (LZMA.h)" );
		return 0;
	}
	
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
	delete [] state.Probs;
	
	// Return the size of the uncompressed data on success //
	return UncompressedSize;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const cDataBlock cDataBlock::UnpackLZMA( const cDataBlock& _Src ) {
	return cDataBlock( unpack_LZMA_DataBlock( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlock_LZMA_H__ //
// - ------------------------------------------------------------------------------------------ - //
