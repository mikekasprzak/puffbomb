// - ------------------------------------------------------------------------------------------ - //
// Array - A dynamically allocated array.  A C implementation, and a lightweight STL vector. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_H__
#define __Library_Data_Array_H__
// - ------------------------------------------------------------------------------------------ - //
//#include <cstdio>
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct Array {
	size_t CurrentSize;
	size_t MaxSize;
	Type* Data;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const size_t _Size ) {
	Array<Type>* p = new Array<Type>;

	p->CurrentSize = _Size;
	p->MaxSize = _Size;
	
	// Allocate our data //
	p->Data = new Type[_Size];

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the Arary to a value //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const size_t _Size, const Type _InitValue ) {
	// Allocate it //
	Array* NewArray = new_Array( _Size );
	
	// Initialize it //
	for( int idx = _Size; idx--; ) {
		NewArray->Data[idx] = _InitValue;
	}
	//memset( NewArray->Data, _InitValue, NewArray->Size );
	
	// Return it //
	return NewArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array() {
	Array<Type>* p = new Array<Type>;

	p->CurrentSize = 0;
	p->MaxSize = 0;
	
	// Normally, we'd allocate something, but we were given nothing to allocate //
	p->Data = 0;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void delete_Array( Array* p ) {
	if ( p->Data )
		delete [] p->Data;
	
	delete p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_H__ //
// - ------------------------------------------------------------------------------------------ - //
