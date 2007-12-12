// - ------------------------------------------------------------------------------------------ - //
// Statically allocated Wrapping Array - Allows you to work with data like it was a dynamic array //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_ClassDesigner_WrapArray_H__
#define __Library_ClassDesigner_WrapArray_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
class WrapArray {
	size_t CurrentSize;
	size_t BaseIndex;
	Type Data[MaxSize];
public:
	inline StaticArray( const size_t _CurrentSize = 0 ) :
		CurrentSize( _CurrentSize ),
		BaseIndex( 0 )
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
		return Data[ (BaseIndex+Index) % MaxSize ];
	}
	
public:
	inline void Resize( const size_t _NewSize ) {
		// TODO: Assert if too large //
		CurrentSize = _NewSize;
	}
	
	inline void PushBack( const Type& _NewData ) {
		Data[(BaseIndex+CurrentSize) % MaxSize] = _NewData;
	
		CurrentSize++;
		// TODO: Assert if larger than MaxSize //	
	}
	
	inline Type& PopBack() {
		CurrentSize--;
		
		return Data[(BaseIndex+CurrentSize) % MaxSize];
	}

	inline void PushFront( const Type& _NewData ) {
		BaseIndex--;
		
		Data[BaseIndex % MaxSize] = _NewData;
	
		CurrentSize++;
		// TODO: Assert if larger than MaxSize //	
	}
	
	inline Type& PopFront() {
		CurrentSize--;
		
		return Data[BaseIndex % MaxSize];
		
		BaseIndex++;
	}
		
	// TODO: Insert and iterators //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_ClassDesigner_WrapArray_H__ //
// - ------------------------------------------------------------------------------------------ - //
