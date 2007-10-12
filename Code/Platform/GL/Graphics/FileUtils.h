
// This should conceptually contain utilities for files. //

// Data Block type //

typedef DataBlock {
	size_t Size;
	char Data[0];
};


// Loaded blocks point to these (DataBlock* CompressedImage) //
// allocated with "(DataBlock*)(new char[Size+4])" //

inline DataBlock* new_DataBlock( size_t _Size ) {
	return (DataBlock*)(new char[_Size+4]);
	//return reinterpret_cast<DataBlock*>(new char[_Size+4]);
}

inline void delete_DataBlock( DataBlock* p ) {
	delete [] (char*)p;
	//delete [] reinterpret_cast<char*>p;
}

// Technically, a C implementation should use malloc+free.  Should file lib be in C? //


// Uncompress function should take one of these as an argument //
//   LZMA, ZLIB.  BZIP not really needed. //
// Uncompress function should optionally be able to accept a "place to put it" pointer //
//   Possibly, a DataBlock itself. //
//   Check the space needed for my data.  If the block is too small, allocate a fresh one. //
//     Do throw an error though, so I know it wasn't used //


// Block read a file from disk, either in to one of these, or creating one of these //

inline DataBlock* ReadFile( char* _FileName ) {
	// Open file //
	
	// Find out how much space we need //
	
	// Allocate space //
	DataBlock* OurData = new_DataBlock( Size );
	
	// Store Size //
	OurData->Size = Size;
	
	// Read data in to block //
	read( &OurData->Data[0], Size );
	
	// Return the data //
	return OurData;
}

// Unfortunately, it's not clear that the data created a "new" pointer.  You just need to know. //

// Option.  Make "new_DataBlock" take an optional char* filename, making reading files //
//   just like data allocation.  Hmmm... :) //

inline DataBlock* new_DataBlock( char* _FileName ) {
	...
}

// Reading suffix doesn't seem to make much sense, 'cause writing wouldn't use "new" //

inline DataBlock* new_DataBlock_Read( char* _FileName ) {
	...
}

// Unless... //

inline void delete_DataBlock_Write( DataBlock* p, char* _FileName ) {
	...
}

// Naw... this is a stupid use of a combo function. //

// Ok, the new_DataBlock accelerator could work. //
// However, reading and writing still needs a function. //

inline void read_DataBlock( DataBlock* p, char* _FileName ) {
	// Should I "false" resize it? //
	// I shouldn't need to, since I'm better off using read allocator. //
	
	// return bytes read? //
	...
}

inline void write_DataBlock( DataBlock* p, char* _FileName ) {
	
	// return bytes written? //
	...
}

// A useful accessory, resizing. //
// Reducing size can work safely, but expanding would require new allocation //
//   this is because new/delete ignore my internal size variable //

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

// Copy one DataBlock to another, no larger than Destination Size Bytes //
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


// Make copies of these functions that take an initializing argument //

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

// new's too.  FileName version doesn't need it, as it'll be filled with data. //

inline DataBlock* new_DataBlock( size_t _Size, int _InitValue ) {
	// Allocate it //
	DataBlock* NewBlock = new_DataBlock( _Size );
	
	// Initialize it //
	memset( NewBlock->Data, _InitValue, NewBlock->Size );
	
	// Return it //
	return NewBlock;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// MemSET wrapper //
inline void set_Data( int _Value, void* _Data, size_t _Size ) {
	memset( _Value, (char*)_Data, _Size );
}

// MemCPY wrapper //
inline void copy_Data( void* _Src, void* _Dest, size_t _Size ) {
	memcpy( _Dest, _Src, _Size );
}


// Make wrapper for reading and writing.  read_DataBlock calls this //

inline void read_Data( char* _FileName, void* Data, size_t _Size ) {
	...
}

inline void write_Data( char* _FlieName, void* Data, size_t _Size ) {
	...
}


inline void* new_Data( size_t _Size ) {
	return (void*)(new char[_Size]);
}

inline void delete_Data( void* _Data ) {
	
}

inline void* new_Data( char* _FileName ) {
	// allocate and load the data //
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// Compression code can thusly work with raw pointers, or DataBlock's //


// Also, don't forget "placement new", to allocate, and call constructor inside a block of memory //

DataBlock* Data = new_DataBlock( 1024 );

DataBlock* CompressedData = (DataBlock*)new(Data->Data) char[CompressSize+4];

// No delete needed, though if type constructed, call explicit destruction //

(*CompressedData)::~DataBlock();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

