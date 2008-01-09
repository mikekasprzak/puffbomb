// - ------------------------------------------------------------------------------------------ - //
// Array Class - Class version of DataBlock. Deletes self as it goes out of scope. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_Class_H__
#define __Library_Data_Array_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_Class.h"

#include "Array_Core.h"
#include "Array_File.h"
#include "Array_Hash32.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class cArray {
protected:
	Array<Type>* _Data;
	
public:
	// Constructor //
	inline cArray() :
		_Data( 0 )
	{
	}
	
	// Since this is a "power use" class, I'm making initializing optional //
	inline cArray( const size_t _Size ) :
		_Data( new_Array<Type>( _Size ) )
	{
	}
	
	inline cArray( const size_t _Size, const Type& _InitValue ) :
		_Data( new_Array<Type>( _Size, _InitValue ) )
	{
	}
	
	// Given a filename as an argument, load it //
	inline cArray( const char* _FileName ) :
		_Data( new_Array<Type>( _FileName ) )
	{
	}
	
	// Given an Array, make our Array directly what we were given //
	// Note: I'm now in charge of freeing, so don't try sharing this data //
	inline cArray( Array<Type>* _Src ) :
		_Data( _Src )
	{
	}
	
	// Copy Constructor - replicates the contents of a DataBlock//
	inline cArray( const cArray<Type>& _Src ) :
		_Data( copy_Array<Type>( _Src ) )
	{
	}
	
	// Destructor //
	inline ~cArray() {
		// TODO: Make this Data Check an Assert //
		if (_Data)
			delete_Array<Type>( _Data );
	}
public:
	inline size_t Size() const {
		// TODO: Make this Data Check an Assert //
		if (_Data)
			return _Data->Size;
		return 0;
	}
	
	inline const char* Data() const {
		// TODO: Make this Data Check an Assert //
		if (_Data)
			return _Data->Data;
		return 0;
	}
	
	inline Type& operator [] ( const size_t Index ) {
		// TODO: Assert indexing in to valid memory, and within size? //
		return _Data->Data[ Index ];
	}
	
	inline Array<Type>* operator * () {
		return _Data;	
	}
public:
	inline void Load( const char* _FileName ) {
		// TODO: Make this Data Check an Assert //
		// Delete the file if there is one loaded //
		if (_Data)
			delete_Array<Type>( _Data );
		// load the file //
		_Data = new_Array<Type>( _FileName );
	}
	
	inline void Save( const char* _FileName ) {
		// TODO: Make this Data Check an Assert //
		if (_Data)
			write_Array<Type>( _Data, _FileName );
	}

public:
	inline void Resize( const size_t _Size ) {
		// TODO: Make this Data Check an Assert //
		if (_Data)
			resize_Array<Type>( &_Data, _Size );
	}
	
	inline void Set( const Type& _InitValue ) {
		// TODO: Make this Data Check an Assert //				
		if (_Data)
			set_Array<Type>( _Data, _InitValue );
	}
	
	inline void Clear( ) {
		Set( 0 );
	}
	
	inline void Reset( ) {
		Resize( 0 );
	}
	
	inline void PushBack( const Type& _InitValue ) {
		pushback_Array<Type>( &_Data, _InitValue );
	}
	
	inline const Type PopBack() {
		return popback_Array<Type>( &_Data );
	}
	
public:
	// STL Compatability //
	inline void push_back( const Type& _InitValue ) {
		PushBack( _InitValue );
	}
	inline const Type pop_back() {
		return PopBack();
	}
	inline void clear() {
		Reset();
	}
	inline void resize( const size_t _Size ) {
		Resize( _Size );
	}
	
public:
	// Compression //
	inline void UnpackLZMA( const cDataBlock& _Src );
	inline void UnpackLZMA( const DataBlock* _Src );
	
	inline void UnpackBZIP( cDataBlock& _Src );
	inline void UnpackBZIP( DataBlock* _Src );
	inline DataBlock* PackBZIP();
	
	inline static const cArray<Type> UnpackZLIB( const cArray<Type>& _Src );
	inline static const cArray<Type> PackZLIB( const cArray<Type>& _Src );
	
	inline static const cArray<Type> UnpackLZO( const cArray<Type>& _Src );
	inline static const cArray<Type> PackLZO( const cArray<Type>& _Src );
	
	// Hash //
	inline const unsigned int Hash32() const {
		return hash32_Array( _Data );
	}
	//inline static const MD5Hash HashMD5( const cArray<Type>& _Src  );
	//inline static const SHA1Hash HashSHA1( const cArray<Type>& _Src  );
};
// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
