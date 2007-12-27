// - ------------------------------------------------------------------------------------------ - //
// Heap - A combination block of data + Index Key directory type //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Heap_Core_H__
#define __Library_Data_Heap_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "Array_Core.h"
// - ------------------------------------------------------------------------------------------ - //
struct Heap {
	Array<size_t>* Index;
	Array<char>* Data;
	
	// Since this is a complicated struct, I've added this //
	inline char* operator [] ( const size_t _Index ) {
		return &(Data->Data[ Index->Data[ _Index ] ]);
	}

	inline const char* operator [] ( const size_t _Index ) const {
		return &(Data->Data[ Index->Data[ _Index ] ]);
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline Heap* new_Heap( const size_t _IndexCount, const size_t _DataSize ) {
	Heap* p = new Heap;

	// Allocate an array for our entries //
	p->Index = newmax_Array<size_t>(_IndexCount);
	
	// Allocate a mass of data //
	p->Data = newmax_Array<char>(_DataSize);

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Heap( Heap* p ) {
	if ( p->Index )
		delete_Array<size_t>( p->Index );
	
	if ( p->Data )
		delete_Array<char>( p->Data );
	
	delete p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline size_t allocate_Heap( Heap* p, const size_t _MemorySize ) {
	// Allocate a key //
	size_t Key = p->Index->Size;
	pushback_Array<size_t>( &p->Index, p->Data->Size );
	
	// Allocate memory //
	pushblockback_Array<char>( &p->Data, _MemorySize );
//	
//	p->Data->Size += _MemorySize;
//	
//	// TODO: Update Array to include a means of growing size //
//	if ( p->Data->Size > p->Data->MaxSize )
//		reallocate_Array<char>( &p->Data );
	
	// Return key //
	return Key;
}
// - ------------------------------------------------------------------------------------------ - //
inline char* index_Heap( Heap* p, const size_t _Index ) {
	return &(p->Data->Data[ p->Index->Data[ _Index ] ]);
}
// - ------------------------------------------------------------------------------------------ - //





// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Heap_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
