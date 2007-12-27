// - ------------------------------------------------------------------------------------------ - //
// DataBlock - Arbitrary data reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataBlock_Core_H__
#define __Library_Data_DataBlock_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
struct DataBlock {
	size_t Size;
	char Data[0];
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const size_t _Size ) {
	//DataBlock* p = (DataBlock*)(new char[_Size+4]);
	DataBlock* p = reinterpret_cast<DataBlock*>(new char[ _Size + sizeof(DataBlock) ]);
	p->Size = _Size;
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_DataBlock( DataBlock* p ) {
	//delete [] (char*)p;
	delete [] reinterpret_cast<char*>(p);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the block to a value //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const size_t _Size, const int _InitValue ) {
	// Allocate it //
	DataBlock* NewBlock = new_DataBlock( _Size );
	
	// Initialize it //
	memset( NewBlock->Data, _InitValue, NewBlock->Size );
	
	// Return it //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Copy one DataBlock to another, no larger than Destination Size Bytes //
// - ------------------------------------------------------------------------------------------ - //
inline void copy_DataBlock( DataBlock* _Src, DataBlock* _Dest ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy source number of bytes //
		memcpy( _Dest->Data, _Src->Data, _Src->Size );
	}
	else {
		// Otherwise, copy destination number of bytes //
		memcpy( _Dest->Data, _Src->Data, _Dest->Size );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Return a duplicate of a DataBlock //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* copy_DataBlock( DataBlock* _Src ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _Src->Size );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
// Set DataBlock //
// - ------------------------------------------------------------------------------------------ - //
inline void set_DataBlock( DataBlock* _Data, const int _InitValue ) {
	memset( _Data->Data, _InitValue, _Data->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// A useful accessory, resizing. //
// Reducing size can work safely, but expanding would require new allocation //
//   this is because new/delete ignore my internal size variable //
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_DataBlock( DataBlock** p, const size_t _NewSize ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _NewSize );
	
	// Copy the data to our new block //
	copy_DataBlock( *p, NewBlock );
	
	// Delete the old block ponted to //
	delete_DataBlock( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
inline void resize_DataBlock( DataBlock** p, const size_t _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataBlock( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Variation of reallocate that looks at the internal size //
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_DataBlock( DataBlock** p ) {
	reallocate_DataBlock( p, (*p)->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Initializer capable versions of resize, reallocate, and copy //
// - ------------------------------------------------------------------------------------------ - //
// Copy one DataBlock to another, no larger than Destination Size Bytes //
inline void copy_DataBlock( DataBlock* _Src, DataBlock* _Dest, const int _InitValue ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy source number of bytes //
		memcpy( _Dest->Data, _Src->Data, _Src->Size );
		// Fill the rest of the data with initializer //
		memset( &_Dest->Data[_Src->Size], _InitValue, _Dest->Size - _Src->Size );
	}
	else {
		// Otherwise, copy destination number of bytes //
		memcpy( _Dest->Data, _Src->Data, _Dest->Size );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void reallocate_DataBlock( DataBlock** p, const size_t _NewSize, const int _InitValue ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _NewSize );
	
	// Copy the data to our new block //
	copy_DataBlock( *p, NewBlock, _InitValue );
	
	// Delete the old block ponted to //
	delete_DataBlock( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
inline void resize_DataBlock( DataBlock** p, const size_t _NewSize, const int _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->Size ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_DataBlock( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
