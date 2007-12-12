// - ------------------------------------------------------------------------------------------ - //
// Statically allocated Array - Allows you to work with data like it was a dynamic array //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_ClassDesigner_StaticArray_H__
#define __Library_ClassDesigner_StaticArray_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
class StaticArray {
	size_t CurrentSize;
	Type Data[MaxSize];
public:
	inline StaticArray( const size_t _CurrentSize = 0 ) :
		CurrentSize( _CurrentSize )
	{
	}
	
public:
	inline const size_t Size() const {
		return CurrentSize;
	}

	inline const size_t MaxSize() const {
		return MaxSize;
	}
	
	inline Type& operator [] ( const size_t Index ) {
		// TODO: Assert if index larger than max size (current size?) //
		return Data[ Index ];
	}

	inline Type* operator * () {
		return Data;
	}
	
public:
	inline void Resize( const size_t _NewSize ) {
		// TODO: Assert if too large //
		CurrentSize = _NewSize;
	}
	
	inline void PushBack( const Type& _NewData ) {
		Data[CurrentSize] = _NewData;
	
		CurrentSize++;
		// TODO: Assert if larger than MaxSize //	
	}
	
	inline Type& PopBack() {
		CurrentSize--;
		
		return Data[CurrentSize];
	}
	
	// TODO: Insert, PushFront, and iterators //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_ClassDesigner_StaticArray_H__ //
// - ------------------------------------------------------------------------------------------ - //
