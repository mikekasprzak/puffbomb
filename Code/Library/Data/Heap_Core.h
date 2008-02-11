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
inline Heap* new_Heap( const size_t _IndexMax, const size_t _DataMax ) {
	Heap* p = new Heap;

	// Allocate an array for our entries //
	p->Index = newmax_Array<size_t>(_IndexMax);
	
	// Allocate a mass of data //
	p->Data = newmax_Array<char>(_DataMax);

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
inline char* index_Heap( Heap* p, const size_t _Index ) {
	return &(p->Data->Data[ p->Index->Data[ _Index ] ]);
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_Heap( Heap* p ) {
	return p->Index->Size;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t heapsize_Heap( Heap* p ) {
	return p->Data->Size;
}
// - ------------------------------------------------------------------------------------------ - //
inline size_t allocate_Heap( Heap* p, const size_t _AllocationSize ) {
	// Allocate a key //
	size_t Key = p->Index->Size;
	pushback_Array<size_t>( &p->Index, p->Data->Size );
	
	// Allocate memory //
	pushblockback_Array<char>( &p->Data, _AllocationSize );
	
	// Return key //
	return Key;
}
// - ------------------------------------------------------------------------------------------ - //
inline size_t allocate_Heap( Heap* p, const char* Src, const size_t _AllocationSize ) {
	// Allocate a key //
	size_t Key = p->Index->Size;
	pushback_Array<size_t>( &p->Index, p->Data->Size );
	
	// Allocate memory //
	pushblockback_Array<char>( &p->Data, _AllocationSize );
	
	// Copy Data //
	copy_Data( Src, index_Heap( p, Key ), _AllocationSize );
	
	// Return key //
	return Key;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Heap_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
