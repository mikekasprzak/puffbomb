// - ------------------------------------------------------------------------------------------ - //
// Statically allocated Wrapping Array - Allows you to work with data like it was a dynamic array //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_ClassDesigner_PowerWrapArray_H__
#define __Library_ClassDesigner_PowerWrapArray_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// MaxSize is expected to be a power of 2.  The code uses & to wrap, so this should be very cheap //
// - ------------------------------------------------------------------------------------------ - //
// TODO: Investigate making this a specialization of WrapArray, when MaxSize is a Power of 2 //
// - ------------------------------------------------------------------------------------------ - //
template< class Type, size_t MaxSize >
class PowerWrapArray {
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
		return Data[ (BaseIndex+Index) & (MaxSize-1) ];
	}
	
public:
	inline void Resize( const size_t _NewSize ) {
		// TODO: Assert if too large //
		CurrentSize = _NewSize;
	}
	
	inline void PushBack( const Type& _NewData ) {
		Data[(BaseIndex+CurrentSize) & (MaxSize-1)] = _NewData;
	
		CurrentSize++;
		// TODO: Assert if larger than MaxSize //	
	}
	
	inline Type& PopBack() {
		CurrentSize--;
		
		return Data[(BaseIndex+CurrentSize) & (MaxSize-1)];
	}

	inline void PushFront( const Type& _NewData ) {
		BaseIndex--;
		
		Data[BaseIndex & (MaxSize-1)] = _NewData;
	
		CurrentSize++;
		// TODO: Assert if larger than MaxSize //	
	}
	
	inline Type& PopFront() {
		CurrentSize--;
		
		return Data[BaseIndex & (MaxSize-1)];
		
		BaseIndex++;
	}
		
	// TODO: Insert and iterators //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_ClassDesigner_PowerWrapArray_H__ //
// - ------------------------------------------------------------------------------------------ - //
