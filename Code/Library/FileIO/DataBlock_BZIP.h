// - ------------------------------------------------------------------------------------------ - //
// DataBlockCompression - Compression code for DataBlock library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataBlock_BZIP_H__
#define __Library_FileIO_DataBlock_BZIP_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock.h"
#include <External/BZip/bzlib.h>
// - ------------------------------------------------------------------------------------------ - //
//namespace IO {
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
//}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlock_BZIP_H__ //
// - ------------------------------------------------------------------------------------------ - //
