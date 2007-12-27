// - ------------------------------------------------------------------------------------------ - //
// Array - A dynamically allocated array.  A C implementation, and a lightweight STL vector. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_H__
#define __Library_Data_Array_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cstring>
// - ------------------------------------------------------------------------------------------ - //
// The type must use a Data pointer.  Otherwise, we can't reallocate.  //
// It's also unfortunate that I've had to make it a pointer+pointer, meaning that the functions //
//   return a pointer, as well the returned data contains a pointer.  //
// This may be avoidable with the C++ Type. //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct Array {
	size_t Size;
	size_t MaxSize;
	Type* Data;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Set Array //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void set_Array( Array<Type>* _Dest, const Type& _InitValue ) {
	// Set value in all entries //
	for( size_t idx = _Dest->Size; idx--; ) {
		_Dest->Data[idx] = _InitValue;
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Copy one Array to another, no larger than Destination Array Size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_Array( Array<Type>* _Src, Array<Type>* _Dest ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy only Source number of entries //
		for( size_t idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
	else {
		// Copy Destination number of entries //
		for( size_t idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const size_t _Size ) {
	Array<Type>* p = new Array<Type>;

	p->Size = _Size;
	p->MaxSize = _Size;
	
	// Allocate our data //
	if ( _Size )
		p->Data = new Type[_Size];
	else
		p->Data = 0;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the Arary to a value //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const size_t _Size, const Type& _InitValue ) {
	// Allocate it //
	Array<Type>* NewArray = new_Array<Type>( _Size );
	
	// Initialize it //
	set_Array<Type>( NewArray, _InitValue );
	
	// Return it //
	return NewArray;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void delete_Array( Array<Type>* p ) {
	if ( p->Data )
		delete [] p->Data;
	
	delete p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_Array( Array<Type>* _Src, Array<Type>* _Dest, const Type& _InitValue ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy Source number of entries //
		for( size_t idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
		
		// Fill the rest of the data with initializer //
		Type* NewDest = &_Dest->Data[_Src->Size];
		for( size_t idx = (_Dest->Size - _Src->Size); idx--; ) {
			NewDest[idx] = _InitValue;
		}
	}
	else {
		// Copy Destination number of entries //
		for( size_t idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Return a duplicate of an Array //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* copy_Array( Array<Type>* _Src ) {
	// Allocate our new block //
	Array<Type>* NewBlock = new_Array<Type>( _Src->Size );
	
	// Copy the data to our new block //
	copy_Array<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// I'm not sure if I really need these, since the members are obviously accessable //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t size_Array( Array<Type>* p ) {
	return p->Size;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t maxsize_Array( Array<Type>* p ) {
	return p->MaxSize;
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_Array( Array<Type>** p, const size_t _NewSize ) {
	// Allocate our new block //
	Array<Type>* NewArray = new_Array<Type>( _NewSize );
	
	// Copy the data to our new block //
	copy_Array<Type>( *p, NewArray );
	
	// Delete the old block ponted to //
	delete_Array<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_Array( Array<Type>** p, const size_t _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	Array<Type>* NewArray = new_Array<Type>( _NewSize );
	
	// Copy the data to our new block //
	copy_Array<Type>( *p, NewArray, _InitValue );
	
	// Delete the old block ponted to //
	delete_Array<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation of reallocate that looks at the internal size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_Array( Array<Type>** p ) {
	reallocate_Array<Type>( p, (*p)->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_Array( Array<Type>** p, const size_t _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_Array<Type>( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_Array( Array<Type>** p, const size_t _NewSize, const Type& _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_Array<Type>( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_H__ //
// - ------------------------------------------------------------------------------------------ - //
