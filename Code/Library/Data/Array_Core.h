// - ------------------------------------------------------------------------------------------ - //
// Array - A dynamically allocated array.  A C implementation, and a lightweight STL vector. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Array_Core_H__
#define __Library_Data_Array_Core_H__
// - ------------------------------------------------------------------------------------------ - //
//#include <cstring>
#include "DataBlock_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: Insertion code, Alignment resizing (min, max), searching, sorting  //
// NOTE: Consider making reallocate specific to max size change.
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct Array {
	size_t MaxSize;
	size_t Size;
	Type Data[0];
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
template< class Type >
inline void copy_Array( DataBlock* _Src, Array<Type>* _Dest ) {
	Type* SrcPtr = (Type*)_Src->Data;
	size_t SrcSize = _Src->Size / sizeof( Type );
	
	// If source is smaller than the destination //
	if ( _Dest->Size > SrcSize ) {
		// Copy only Source number of entries //
		for( size_t idx = SrcSize; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
	else {
		// Copy Destination number of entries //
		for( size_t idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_DataBlock( Array<Type>* _Src, DataBlock* _Dest  ) {
	char* SrcPtr = (char*)_Src->Data;
	size_t SrcSize = _Src->Size * sizeof( Type );
	
	copy_DataBlock( SrcPtr, SrcSize, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( const size_t _Size ) {
	Array<Type>* p = reinterpret_cast<Array<Type>*>(new char[ (_Size * sizeof(Type)) + sizeof(Array<Type>) ]);

	p->Size = _Size;
	p->MaxSize = _Size;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the Array to a value //
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
	delete p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// New that set the maximum size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* newmax_Array( const size_t _MaxSize ) {
	Array<Type>* p = reinterpret_cast<Array<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(Array<Type>) ]);

	p->Size = 0;
	p->MaxSize = _MaxSize;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* newmax_Array( const size_t _MaxSize, const size_t _Size ) {
	Array<Type>* p = reinterpret_cast<Array<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(Array<Type>) ]);

	p->Size = _Size;
	p->MaxSize = _MaxSize;

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* newmax_Array( const size_t _MaxSize, const size_t _Size, const Type& _InitValue ) {
	// Allocate it //
	Array<Type>* NewArray = newmax_Array<Type>( _MaxSize, _Size );
	
	// Initialize it //
	set_Array<Type>( NewArray, _InitValue );
	
	// Return it //
	return NewArray;
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
template< class Type >
inline Array<Type>* new_Array( Array<Type>* _Src ) {
	return copy_Array<Type>( _Src );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Construct an Array from a DataBlock //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* copy_Array( DataBlock* _Src ) {
	// Allocate our new block //
	Array<Type>* NewBlock = new_Array<Type>( _Src->Size / sizeof(Type) );
	
	// Copy the data to our new block //
	copy_Array<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Array<Type>* new_Array( DataBlock* _Src ) {
	return copy_Array<Type>( _Src );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* copy_DataBlock( Array<Type>* _Src ) {
	// Allocate our new block //
	DataBlock* NewBlock = new_DataBlock( _Src->Size * sizeof( Type ) );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* new_DataBlock( Array<Type>* _Src ) {
	return copy_DataBlock( _Src );
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
inline void reallocatemax_Array( Array<Type>** p, const size_t _NewMaxSize ) {
	// Allocate our new block //
	Array<Type>* NewArray = newmax_Array<Type>( _NewMaxSize, (*p)->Size );
	
	// Copy the data to our new block //
	copy_Array<Type>( *p, NewArray );
	
	// Delete the old block ponted to //
	delete_Array<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocatemax_Array( Array<Type>** p, const size_t _NewMaxSize, const size_t _NewSize ) {
	// Allocate our new block //
	Array<Type>* NewArray = newmax_Array<Type>( _NewMaxSize, _NewSize );
	
	// Copy the data to our new block //
	copy_Array<Type>( *p, NewArray );
	
	// Delete the old block ponted to //
	delete_Array<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewArray;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocatemax_Array( Array<Type>** p, const size_t _NewMaxSize, const size_t _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	Array<Type>* NewArray = newmax_Array<Type>( _NewMaxSize, _NewSize );
	
	// Copy the data to our new block //
	copy_Array<Type>( *p, NewArray, _InitValue );
	
	// Delete the old block ponted to //
	delete_Array<Type>( *p );
	
	// Make the pointer point to the new block //
	(*p) = NewArray;
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
		size_t OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// If this grows us //
		if ( OldSize < _NewSize ) {
			// Fill in new values with passed value //
			for( size_t idx = (_NewSize - OldSize); idx--; ) {
				(*p)->Data[OldSize + idx] = _InitValue;
			}
		}
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_Array<Type>( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize2_Array( Array<Type>** p, const size_t _NewSize ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		size_t DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
		size_t NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
		
		reallocatemax_Array<Type>( p, NewMaxSize, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize2_Array( Array<Type>** p, const size_t _NewSize, const Type& _InitValue ) {
	// A cheat.  We can resize the block without reallocating
	if ( _NewSize <= (*p)->MaxSize ) {
		size_t OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// If this grows us //
		if ( OldSize < _NewSize ) {
			// Fill in new values with passed value //
			for( size_t idx = (_NewSize - OldSize); idx--; ) {
				(*p)->Data[OldSize + idx] = _InitValue;
			}
		}
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		size_t DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
		size_t NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
		
		reallocatemax_Array<Type>( p, NewMaxSize, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_Array( Array<Type>** p, const Type& _InitValue ) {
	resize2_Array( p, (*p)->Size + 1, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popback_Array( Array<Type>** p ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Push and pop large groups of objects on to the Array //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_Array( Array<Type>** p, const size_t _Value ) {
	resize2_Array( p, (*p)->Size + _Value );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_Array( Array<Type>** p, const size_t _Value, const Type& _InitValue ) {
	resize2_Array( p, (*p)->Size + _Value, _InitValue );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type popblockback_Array( Array<Type>** p, const size_t _Value ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size -= _Value;
	
	return (*p)->Data[ (*p)->Size ];
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Array_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
