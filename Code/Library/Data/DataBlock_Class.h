// - ------------------------------------------------------------------------------------------ - //
// DataBlock Class - Class version of DataBlock. Deletes self as it goes out of scope. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataBlock_Class_H__
#define __Library_Data_DataBlock_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_File.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
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
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
