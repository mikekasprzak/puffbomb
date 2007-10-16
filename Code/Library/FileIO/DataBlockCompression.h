// - ------------------------------------------------------------------------------------------ - //
// DataBlockCompression - Compression code for DataBlock library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataBlockCompression_H__
#define __Library_FileIO_DataBlockCompression_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock.h"
#include <External/Lzma/LzmaDecode.h>
#include <External/BZip/bzlib.h>
#include <External/ZLib/zlib.h>
// - ------------------------------------------------------------------------------------------ - //
namespace IO {
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
// Decode packed BZIP data to a new DataBlock //
inline DataBlock* unpack_BZIP_DataBlock( DataBlock* _Src ) {
	// Assume the compressed DataBlock contains a DataBlock, who's size is the uncompressed size //
	DataBlock* Compressed = reinterpret_cast<DataBlock*>(_Src->Data);
	
	// Allocate a memory block equal to the uncompressed size //
	DataBlock* Uncompressed = new_DataBlock( Compressed->Size );
	
	// Decompress the Data //
	int Error = BZ2_bzBuffToBuffDecompress(
		Uncompressed->Data,
		&Uncompressed->Size,
		Compressed->Data, // Compressed Data (After Size, and Uncompressed Size (8 bytes)) //
		_Src->Size - 4, // Source size, since we have an extra 4 byte uncompressed size //
		0, // small (0 - more memory used, faster. 1 - less memory (2300k max), slower) //
		0 // verbosity (0, don't talk) //
		);
	// TODO: Assert on uncompress error //
	//if ( Error != BZ_OK )
	
	// Return the uncompressed buffer //
	return Uncompressed;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode packed BZIP data to a new DataBlock //
inline DataBlock* pack_BZIP_DataBlock( DataBlock* _Src ) {
	// Allocate worst case space to store compressed data //
	DataBlock* Compressed = new_DataBlock( _Src->Size + (_Src->Size / 100) + 600 + 4 );
	
	size_t* UncompressedSize = reinterpret_cast<size_t*>(&Compressed->Data[0]);
	*UncompressedSize = 0;
	size_t CompressedSize = Compressed->Size-4;
	
	// Compress the Data //
	int Error = BZ2_bzBuffToBuffCompress(
		(char*)(&(Compressed->Data[4])),
		&CompressedSize,
		(char*)_Src->Data,
		_Src->Size,
		9, // blockSize100k (value * 100000 bytes allocated for work spcae (1-9)) //
		0, // verbosity (0, don't talk) //
		0 // workFactor (0 defaults to recommended case, 30) //
		);
	// TODO: Assert on compress error //
	//if ( Error != BZ_OK )

	
	// Store Sizes //
	Compressed->Size = CompressedSize + 4;
	*UncompressedSize = _Src->Size;

	// If bzip worked, bzip will have changed the size in the DataBlock to less than the //
	//   memory allocated.  Thusly, we can call reallocate to force the data buffer to be //
	//   re-allocated to reduce memory usage (causing normal OS fragmentation). //
	reallocate_DataBlock( &Compressed );
	
	// Return the compressed buffer //
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
const cDataBlock cDataBlock::UnpackBZIP( const cDataBlock& _Src ) {
	return cDataBlock( unpack_BZIP_DataBlock( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
const cDataBlock cDataBlock::PackBZIP( const cDataBlock& _Src ) {
	return cDataBlock( pack_BZIP_DataBlock( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Decode packed ZLIB data to a new DataBlock //
inline DataBlock* unpack_ZLIB_DataBlock( DataBlock* _Src ) {
	// Assume the compressed DataBlock contains a DataBlock, who's size is the uncompressed size //
	DataBlock* Compressed = reinterpret_cast<DataBlock*>(_Src->Data);
	
	// Allocate a memory block equal to the uncompressed size //
	DataBlock* Uncompressed = new_DataBlock( Compressed->Size );
	
	// Decompress the Data //
	int Error = uncompress(
		(Bytef*)Uncompressed->Data,
		(uLongf*)&Uncompressed->Size,
		(const Bytef*)Compressed->Data, // Compressed Data (After Size, and Uncompressed Size (8 bytes)) //
		_Src->Size - 4 // Source size, since we have an extra 4 byte uncompressed size //
		);
	// TODO: Assert on uncompress error //
	//if ( Error != Z_OK )
	
	// Return the uncompressed buffer //
	return Uncompressed;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode packed ZLIB data to a new DataBlock //
inline DataBlock* pack_ZLIB_DataBlock( DataBlock* _Src ) {
	// Allocate worst case space to store compressed data //
	DataBlock* Compressed = new_DataBlock( _Src->Size + (_Src->Size / 1000) + 12 + 4 );
	
	size_t* UncompressedSize = reinterpret_cast<size_t*>(&Compressed->Data[0]);
	*UncompressedSize = 0;
	size_t CompressedSize = Compressed->Size-4;
	
	// Compress the Data //
	int Error = compress(
		(Bytef*)(&(Compressed->Data[4])),
		(uLongf*)&CompressedSize,
		(const Bytef*)_Src->Data,
		_Src->Size
		//Z_DEFAULT_COMPRESSION // Compression level.  1 best - 9 worst. 0 none. default is 6 //
		);
	// TODO: Assert on compress error //
	//if ( Error != Z_OK )
	
	// Store Sizes //
	Compressed->Size = CompressedSize + 4;
	*UncompressedSize = _Src->Size;

	// If zlib worked, zlib will have changed the size in the DataBlock to less than the //
	//   memory allocated.  Thusly, we can call reallocate to force the data buffer to be //
	//   re-allocated to reduce memory usage (causing normal OS fragmentation). //
	reallocate_DataBlock( &Compressed );
	
	// Return the compressed buffer //
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const cDataBlock cDataBlock::UnpackZLIB( const cDataBlock& _Src ) {
	return cDataBlock( unpack_ZLIB_DataBlock( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
const cDataBlock cDataBlock::PackZLIB( const cDataBlock& _Src ) {
	return cDataBlock( pack_ZLIB_DataBlock( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlockCompression_H__ //
// - ------------------------------------------------------------------------------------------ - //
