// - ------------------------------------------------------------------------------------------ - //
// DataBlock - Arbitrary data reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataBlock_H__
#define __Library_FileIO_DataBlock_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
#include <cstdio>
// - ------------------------------------------------------------------------------------------ - //
//namespace IO {
// - ------------------------------------------------------------------------------------------ - //
struct DataBlock {
	size_t Size;
	char Data[0];
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const size_t _Size ) {
	//DataBlock* p = (DataBlock*)(new char[_Size+4]);
	DataBlock* p = reinterpret_cast<DataBlock*>(new char[_Size+(sizeof(DataBlock)]);
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
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline DataBlock* new_DataBlock( const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	rewind( fp );
	
	// Allocate space (Size is automatically set inside new_DataBlock) //
	DataBlock* p = new_DataBlock( Size );
	// TODO: Assert failure allocating block //
	
	// Read data //
	fread( p->Data, 1, Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation for C++ Strings //
// - ------------------------------------------------------------------------------------------ - //
//inline DataBlock* new_DataBlock( const string _FileName ) {
//	return new_DataBlock( _FileName.c_str() );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// These functions are for when you know how large a file is //
// TODO: Add file offsetting as optional 3rd argument (defalts to 0) //
// TODO: Or, add a "file" type that you can construct at the top of a function, and pass to these //
// NOTE: The above should be part of the streaming library? //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_DataBlock( DataBlock* p, const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "rb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Determine how large file is //
	fseek( fp, 0, SEEK_END );
	size_t Size = ftell( fp );
	rewind( fp );
	
	// Read data (only as much as the smallest size) //
	size_t BytesRead = fread( p->Data, 1, Size > p->Size ? p->Size : Size, fp );
	
	// Close file //
	fclose( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_DataBlock( DataBlock* p, const char* _FileName ) {
	// Open File //
	FILE* fp = fopen( _FileName, "wb" );
	if ( fp == 0 ) {
		// TODO: Log file open error //
		return 0;
	}
	
	// Write the data //
	size_t BytesWritten = fwrite( p->Data, 1, p->Size, fp );
	// TODO: Assert on fire write error //
	
	// Close file //
	fclose( fp );
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_DataBlock which functions the same as new_DataBlock. //
// Note: This is bad, as it's unclear allocation is done.  new_DataBlock() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline DataBlock* read_DataBlock( const char* _FileName ) {
//	return new_DataBlock( _FileName );
//}
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
// Class version of DataBlock. Deletes self as it goes out of scope. //
// - ------------------------------------------------------------------------------------------ - //
class cDataBlock {
protected:
	DataBlock* _Data;
	
public:
	// Constructor //
	inline cDataBlock() :
		_Data( 0 )
	{
	}
	
	// Since this is a "power use" class, I'm making initializing optional //
	inline cDataBlock( const size_t _Size ) :
		_Data( new_DataBlock( _Size ) )
	{
	}
	
	inline cDataBlock( const size_t _Size, const int _InitValue ) :
		_Data( new_DataBlock( _Size, _InitValue ) )
	{
	}
	
	// Given a filename as an argument, load it //
	inline cDataBlock( const char* _FileName ) :
		_Data( new_DataBlock( _FileName ) )
	{
	}
	
	// Given a DataBlock, make our DataBlock directly what we were given //
	// Note: I'm now in charge of freeing, so don't try sharing this data //
	inline cDataBlock( DataBlock* _Src ) :
		_Data( _Src )
	{
	}
	
	// Copy Constructor - replicates the contents of a DataBlock//
	inline cDataBlock( const cDataBlock& _Src ) :
		_Data( copy_DataBlock( _Src._Data ) )
	{
	}
	
	// Destructor //
	inline ~cDataBlock() {
		if (_Data)
			delete_DataBlock( _Data );
	}
public:
	inline size_t Size() const {
		if (_Data)
			return _Data->Size;
		return 0;
	}
	
	inline const char* Data() const {
		if (_Data)
			return _Data->Data;
		return 0;
	}
	
	inline char& operator [] ( const size_t Index ) {
		// TODO: Assert indexing in to valid memory, and within size? //
		return _Data->Data[ Index ];
	}
	
	inline DataBlock* operator * () {
		return _Data;	
	}
public:
	inline void Load( const char* _FileName ) {
		// Delete the file if there is one loaded //
		if (_Data)
			delete_DataBlock( _Data );
		// load the file //
		_Data = new_DataBlock( _FileName );
	}
	
	inline void Save( const char* _FileName ) {
		if (_Data)
			write_DataBlock( _Data, _FileName );
	}

public:
	inline void Resize( const size_t _Size ) {
		if (_Data)
			resize_DataBlock( &_Data, _Size );
	}
	
	inline void Set( const int _InitValue ) {
		if (_Data)
			set_DataBlock( _Data, _InitValue );
	}
	
	inline void Clear( ) {
		Set( 0 );
	}
public:
	// Compression //
	inline static const cDataBlock UnpackLZMA( const cDataBlock& _Src );
	
	inline static const cDataBlock UnpackBZIP( const cDataBlock& _Src );
	inline static const cDataBlock PackBZIP( const cDataBlock& _Src );
	
	inline static const cDataBlock UnpackZLIB( const cDataBlock& _Src );
	inline static const cDataBlock PackZLIB( const cDataBlock& _Src );
	
	inline static const cDataBlock UnpackLZO( const cDataBlock& _Src );
	inline static const cDataBlock PackLZO( const cDataBlock& _Src );
};
// - ------------------------------------------------------------------------------------------ - //
//}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlock_H__ //
// - ------------------------------------------------------------------------------------------ - //
