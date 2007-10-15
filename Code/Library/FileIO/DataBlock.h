// - ------------------------------------------------------------------------------------------ - //
// DataBlock - Arbitrary data reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataBlock_H__
#define __Library_FileIO_DataBlock_H__
// - ------------------------------------------------------------------------------------------ - //
namespace IO {
// - ------------------------------------------------------------------------------------------ - //
typedef struct DataBlock {
	size_t Size;
	char Data[0];
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( size_t _Size ) {
	DataBlock* p = (DataBlock*)(new char[_Size+4]);
	//DataBlock* p = reinterpret_cast<DataBlock*>(new char[_Size+4]);
	p->Size = _Size;
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_DataBlock( DataBlock* p ) {
	delete [] (char*)p;
	//delete [] reinterpret_cast<char*>p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the block to a value //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( size_t _Size, int _InitValue ) {
	// Allocate it //
	DataBlock* NewBlock = new_DataBlock( _Size );
	
	// Initialize it //
	memset( NewBlock->Data, _InitValue, NewBlock->Size );
	
	// Return it //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( char* _FileName ) {
	// Open File //
	
	// Determine how large file is //
	size_t Size = 0;
	
	// Allocate space //
	DataBlock* p = new_DataBlock( Size );
	
	// Read data //
	
	return p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// - ------------------------------------------------------------------------------------------ - //
inline void read_DataBlock( DataBlock* p, char* _FileName ) {
	// Should I "false" resize it? //
	// I shouldn't need to, since I'm better off using read allocator. //
	
	// return bytes read? //
	
}
// - ------------------------------------------------------------------------------------------ - //
inline void write_DataBlock( DataBlock* p, char* _FileName ) {
	
	// return bytes written? //
	
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// A useful accessory, resizing. //
// Reducing size can work safely, but expanding would require new allocation //
//   this is because new/delete ignore my internal size variable //
// - ------------------------------------------------------------------------------------------ - //
inline void resize_DataBlock( DataBlock** p, size_t _NewSize ) {
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
inline void reallocate_DataBlock( DataBlock** p, size_t _NewSize ) {
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

// - ------------------------------------------------------------------------------------------ - //
// Initializer capable versions of resize, reallocate, and copy //
// - ------------------------------------------------------------------------------------------ - //
inline void resize_DataBlock( DataBlock** p, size_t _NewSize, int _InitValue ) {
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
inline void reallocate_DataBlock( DataBlock** p, size_t _NewSize, int _InitValue ) {
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
// Copy one DataBlock to another, no larger than Destination Size Bytes //
inline void copy_DataBlock( DataBlock* _Src, DataBlock* _Dest, int _InitValue ) {
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


// - ------------------------------------------------------------------------------------------ - //
}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlock_H__ //
// - ------------------------------------------------------------------------------------------ - //
