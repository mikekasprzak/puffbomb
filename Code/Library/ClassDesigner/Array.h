// - ------------------------------------------------------------------------------------------ - //
// Array - A dynamically allocated array.  A lightweight version of STL vector. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_ClassDesigner_Array_H__
#define __Library_ClassDesigner_Array_H__
// - ------------------------------------------------------------------------------------------ - //
//#include <cstdio>
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class Array {
	size_t CurrentSize;
	size_t MaxSize;
	Type* Data;
public:
	inline Array( ) :
		CurrentSize( 0 ),
		MaxSize( 0 ),
		Data( 0 )
	{
	}
	
	inline Array( const size_t _CurrentSize ) :
		CurrentSize( _CurrentSize ),
		MaxSize( _CurrentSize ),
		Data( new Data[_CurrentSize] )
	{
	}
	
	// TODO: Add adjustable initalization syntax //
	
//	// Copy Constructor - Exact replica version //
//	inline Array( const Array<Type>& _Copy ) :
//		CurrentSize( _Copy.CurrentSize ),
//		MaxSize( _Copy.MaxSize ),
//		Data( new Data[_Copy.MaxSize] )
//	{
//		memcpy( Data, _Copy.Data, MaxSize );
//	}
	
	// Copy Constructor - CurrentSize replica version //
	inline Array( const Array<Type>& _Copy ) :
		CurrentSize( _Copy.CurrentSize ),
		MaxSize( _Copy.CurrentSize ),
		Data( new Data[_Copy.CurrentSize] )
	{
		memcpy( Data, _Copy.Data, CurrentSize );
	}
	
	// Destructor //
	inline ~Array() {
		if ( Data )
			delete [] Data;
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
	inline void Reallocate( const size_t _NewSize ) {
		// Allocate our new block //
		Type* NewData = new Type[_NewSize];
		
		// To be sure we're pointing to something //
		if ( Data ) {
			// Copy the data to our new block //
			memcpy( NewData, Data, _NewSize > CurrentSize ? CurrentSize : _NewSize );
			
			// Delete the old block ponted to //
			delete [] Data;
		}
		
		// Take the new Maximum Size //
		MaxSize = _NewSize;
		
		// Make the pointer point to the new block //
		Data = NewData;
	}
	
	inline void Resize( const size_t _NewSize ) {
		// If the new size requested is larger than our current size //
		if ( _NewSize > MaxSize ) {
			// Reallocate our memory //
			Reallocate( _NewSize );
		}
		else {
			// Otherwise, just use what we have //
			CurrentSize = _NewSize;
		}
	}
	
	inline void PushBack( const Type& _NewData ) {
		if ( CurrentSize+1 > MaxSize ) {
			Reallocate( MaxSize + MaxSize );
		}
		
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
#endif // __Library_ClassDesigner_Array_H__ //
// - ------------------------------------------------------------------------------------------ - //
