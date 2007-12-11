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
		( unsigned char* )&Src[ LZMA_PROPERTIES_SIZE + 8 ],
		_Size,
		&inProcessed,
		( unsigned char* )_Dest,
		UncompressedSize,
		&outProcessed
		);
	// TODO: React to result of the decode //
	
	// Clean up work memory //
	delete [] state.Probs;
	
	// Return our new LZMA decompressed data //
	return UncompressedSize;
}
// - ------------------------------------------------------------------------------------------ - //


//// - ------------------------------------------------------------------------------------------ - //
//// Decode packed BZIP data to a new DataBlock //
//inline const size_t unpack_BZIP_Data( const void* _Src, const size_t _Size, const void** _Dest, const size_t _DestSize ) {
//	// Assume the compressed DataBlock contains a DataBlock, who's size is the uncompressed size //
//	DataBlock* Compressed = reinterpret_cast<DataBlock*>(_Src->Data);
//	
//	// Allocate a memory block equal to the uncompressed size //
//	DataBlock* Uncompressed = new_DataBlock( Compressed->Size );
//	
//	// Decompress the Data //
//	int Error = BZ2_bzBuffToBuffDecompress(
//		Uncompressed->Data,
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
//}
//// - ------------------------------------------------------------------------------------------ - //
//// Encode packed BZIP data to a new DataBlock //
//inline DataBlock* pack_BZIP_Data( const void* _Src, const size_t _Size, const void** _Dest, const size_t _DestSize ) {
//	// Allocate worst case space to store compressed data //
//	DataBlock* Compressed = new_DataBlock( _Src->Size + (_Src->Size / 100) + 600 + 4 );
//	
//	size_t* UncompressedSize = reinterpret_cast<size_t*>(&Compressed->Data[0]);
//	*UncompressedSize = 0;
//	size_t CompressedSize = Compressed->Size-4;
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
//	Compressed->Size = CompressedSize + 4;
//	*UncompressedSize = _Src->Size;
//
//	// If bzip worked, bzip will have changed the size in the DataBlock to less than the //
//	//   memory allocated.  Thusly, we can call reallocate to force the data buffer to be //
//	//   re-allocated to reduce memory usage (causing normal OS fragmentation). //
//	reallocate_DataBlock( &Compressed );
//	
//	// Return the compressed buffer //
//	return Compressed;
//}
//// - ------------------------------------------------------------------------------------------ - //
//
//
//// - ------------------------------------------------------------------------------------------ - //
//// Decode packed ZLIB data to a new DataBlock //
//inline DataBlock* unpack_ZLIB_Data( void* _Src ) {
//	// Assume the compressed DataBlock contains a DataBlock, who's size is the uncompressed size //
//	DataBlock* Compressed = reinterpret_cast<DataBlock*>(_Src->Data);
//	
//	// Allocate a memory block equal to the uncompressed size //
//	DataBlock* Uncompressed = new_DataBlock( Compressed->Size );
//	
//	// Decompress the Data //
//	int Error = uncompress(
//		(Bytef*)Uncompressed->Data,
//		(uLongf*)&Uncompressed->Size,
//		(const Bytef*)Compressed->Data, // Compressed Data (After Size, and Uncompressed Size (8 bytes)) //
//		_Src->Size - 4 // Source size, since we have an extra 4 byte uncompressed size //
//		);
//	// TODO: Assert on uncompress error //
//	//if ( Error != Z_OK )
//	
//	// Return the uncompressed buffer //
//	return Uncompressed;
//}
//// - ------------------------------------------------------------------------------------------ - //
//// Encode packed ZLIB data to a new DataBlock //
//inline DataBlock* pack_ZLIB_Data( void* _Src ) {
//	// Allocate worst case space to store compressed data //
//	DataBlock* Compressed = new_DataBlock( _Src->Size + (_Src->Size / 1000) + 12 + 4 );
//	
//	size_t* UncompressedSize = reinterpret_cast<size_t*>(&Compressed->Data[0]);
//	*UncompressedSize = 0;
//	size_t CompressedSize = Compressed->Size-4;
//	
//	// Compress the Data //
//	int Error = compress(
//		(Bytef*)(&(Compressed->Data[4])),
//		(uLongf*)&CompressedSize,
//		(const Bytef*)_Src->Data,
//		_Src->Size
//		//Z_DEFAULT_COMPRESSION // Compression level.  1 best - 9 worst. 0 none. default is 6 //
//		);
//	// TODO: Assert on compress error //
//	//if ( Error != Z_OK )
//	
//	// Store Sizes //
//	Compressed->Size = CompressedSize + 4;
//	*UncompressedSize = _Src->Size;
//
//	// If zlib worked, zlib will have changed the size in the DataBlock to less than the //
//	//   memory allocated.  Thusly, we can call reallocate to force the data buffer to be //
//	//   re-allocated to reduce memory usage (causing normal OS fragmentation). //
//	reallocate_DataBlock( &Compressed );
//	
//	// Return the compressed buffer //
//	return Compressed;
//}
//// - ------------------------------------------------------------------------------------------ - //
//
//
//// - ------------------------------------------------------------------------------------------ - //
//// NOTE: LZO compression should have and use static work memory.  Allocation slows it down. //
//// - ------------------------------------------------------------------------------------------ - //
//// Decode packed LZO data to a new DataBlock //
//inline DataBlock* unpack_LZO_Data( void* _Src ) {
//	// Assume the compressed DataBlock contains a DataBlock, who's size is the uncompressed size //
//	DataBlock* Compressed = reinterpret_cast<DataBlock*>(_Src->Data);
//	
//	// Allocate a memory block equal to the uncompressed size //
//	DataBlock* Uncompressed = new_DataBlock( Compressed->Size );
//	
//	// Decompress the Data //
//	int Error = lzo1x_decompress(
//		(const lzo_bytep)Compressed->Data, // Compressed Data (After Size, and Uncompressed Size (8 bytes)) //
//		_Src->Size - 4, // Source size, since we have an extra 4 byte uncompressed size //
//		(lzo_bytep)Uncompressed->Data,
//		(lzo_uintp)&Uncompressed->Size,
//		(lzo_voidp)0 // No work memory needed //
//		);
//	// TODO: Assert on uncompress error //
//	//if ( Error != Z_OK )
//	
//	// Return the uncompressed buffer //
//	return Uncompressed;
//}
//// - ------------------------------------------------------------------------------------------ - //
//// Encode packed LZO data to a new DataBlock //
//inline DataBlock* pack_LZO_Data( void* _Src ) {
//	// Allocate worst case space to store compressed data //
//	DataBlock* Compressed = new_DataBlock( _Src->Size + (_Src->Size / 1000) + 12 + 4 );
//	
//	size_t* UncompressedSize = reinterpret_cast<size_t*>(&Compressed->Data[0]);
//	*UncompressedSize = 0;
//	size_t CompressedSize = Compressed->Size-4;
//	
//	// Note: BAD!  Should not allocate here, should pre allocate these! //
//	char* WorkMemory = new char[LZO1X_1_MEM_COMPRESS]; 
//	
//	// Compress the Data //
//	int Error = lzo1x_1_compress(
//		(const lzo_bytep)_Src->Data,
//		_Src->Size,
//		(lzo_bytep)(&(Compressed->Data[4])),
//		(lzo_uintp)&CompressedSize,
//		(lzo_voidp)WorkMemory
//		);
//	// TODO: Assert on compress error //
//	//if ( Error != Z_OK )
//	
//	// Note: BAD!  Should not have to free here! //
//	delete [] WorkMemory;
//	
//	// Store Sizes //
//	Compressed->Size = CompressedSize + 4;
//	*UncompressedSize = _Src->Size;
//
//	// If zlib worked, zlib will have changed the size in the DataBlock to less than the //
//	//   memory allocated.  Thusly, we can call reallocate to force the data buffer to be //
//	//   re-allocated to reduce memory usage (causing normal OS fragmentation). //
//	reallocate_DataBlock( &Compressed );
//	
//	// Return the compressed buffer //
//	return Compressed;
//}
//// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataUtilCompression_H__ //
// - ------------------------------------------------------------------------------------------ - //
