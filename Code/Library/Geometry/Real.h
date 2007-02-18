// - ------------------------------------------------------------------------------------------ - //
// Real //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Real_H__
#define __Geometry_Real_H__
// - ------------------------------------------------------------------------------------------ - //
// Todo: 
// - ------------------------------------------------------------------------------------------ - //
#include <cmath>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
// This set is used for straight duplicate overloading of types, such as the float/Real wrapper //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Real& operator _OP_ ( const Real& _Vs ) { \
		Data _OP_ _Vs.Data; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( _OP_ ) \
	inline const Real& operator _OP_ () { \
		_OP_ Data; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( _OP_ ) \
	inline const Real operator _OP_ ( int ) { \
		return Data _OP_; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_OPERATOR( _OP_ ) \
	inline const bool operator _OP_ ( const Real& _Vs ) const { \
		return Data _OP_ _Vs.Data; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOL_OPERATOR( _OP_ ) \
	inline const Real operator _OP_ ( const Real& _Vs ) const { \
		return Data _OP_ _Vs.Data; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A type to wrap a floating point type (float/double) //
// - ------------------------------------------------------------------------------------------ - //
class Real {
	// - -------------------------------------------------------------------------------------- - //
	typedef float _RealType;
	// - -------------------------------------------------------------------------------------- - //	
	// Our actual data contents // 
	_RealType Data;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Real Identity;
	static const Real Zero;
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Other constants special to this type //
	// - -------------------------------------------------------------------------------------- - //
	static const Real One;
	static const Real Half;
	static const Real Quarter;
	static const Real SmallestUnit;
	
	static const Real Pi;
	static const Real TwoPi;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Real() :
		Data( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real( const _RealType& _Data ) :
		Data( _Data )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Set( const Real& _Vs ) {
		Data = _Vs.Data;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Covert all reals into our floating point type automatically //
	// - -------------------------------------------------------------------------------------- - //
	// Might need a non const float returning variant //
	inline operator const _RealType () const {
		return Data;	
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators, essentially a wrapping for float/double's normal operators //
	// - -------------------------------------------------------------------------------------- - //
	OVERLOAD_SYMBOLEQUALS_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( -= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( /= );

	OVERLOAD_SYMBOL_OPERATOR( + );
	OVERLOAD_SYMBOL_OPERATOR( - );
	OVERLOAD_SYMBOL_OPERATOR( * );
	OVERLOAD_SYMBOL_OPERATOR( / );

	OVERLOAD_TEST_OPERATOR( == );
	OVERLOAD_TEST_OPERATOR( != );
	OVERLOAD_TEST_OPERATOR( <= );
	OVERLOAD_TEST_OPERATOR( >= );
	
	OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( ++ );
	OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( -- );

	OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( ++ );
	OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( -- );
	// - -------------------------------------------------------------------------------------- - //
	// Dot Product //
	inline const Real operator - ( ) const {
		return -Data;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline void Normalize() {
		if ( Data > Zero )
			Data = One;
		else if ( Data < Zero )
			Data = -One;
		else
			Data = Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real NormalizeRet() {
		Real Temp( *this );
		if ( Data > Zero )
			Data = One;
		else if ( Data < Zero ) {
			Data = -One;
			Temp = -Temp;
		}
		else
			Data = Zero;
		return Temp;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Real Normal() const {
		if ( Data > Zero )
			return One;
		else if ( Data < Zero )
			return -One;
		else
			return Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const Real Magnitude() const {
		return Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Real MagnitudeSquared() const {
		return Data * Data;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// No Dot or Cross, as their's not enough axis for tangents //
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Min( const Real& _Vs ) const {
		Real Number = *this;
		if ( Number > _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Max( const Real& _Vs ) const {
		Real Number = *this;
		if ( Number < _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& MinClamp( const Real& _Vs ) {
		if ( *this > _Vs )
			*this = _Vs;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& MaxClamp( const Real& _Vs ) {
		if ( *this < _Vs )
			*this = _Vs;
		return *this;
	}	
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real Range( const Real& _Min, const Real& _Max ) const {
		Real Number = *this;
		// Min //
		if ( Number < _Min )
			return _Min;
		// Max //
		if ( Number > _Max )
			return _Max;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& RangeClamp( const Real& _Min, const Real& _Max ) {
		// Min //
		if ( *this < _Min )
			*this = _Min;
		// Max //
		if ( *this > _Max )
			*this = _Max;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool InRange( const Real& _Min, const Real& _Max ) const {
		// Min //
		if ( *this < _Min )
			return false;
		// Max //
		if ( *this > _Max )
			return false;
		return true;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Specific Functions that apply to this type //
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Abs() const {
		if ( Data < Zero )
			return -Data;
		else
			return Data;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const Real Sqrt() const {
		if ( !IsZero() )
			return std::sqrt( *this );
		else
			return Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Sine //
	inline const Real Sin() const {
		return std::sin( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Cosine //
	inline const Real Cos() const {
		return std::cos( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Tangent //
	inline const Real Tan() const {
		return std::tan( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Floor //
	inline const Real Floor() const {
		return std::floor( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ceil //
	inline const Real Ceil() const {
		return std::ceil( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Round //
	inline const Real Round() const {
		if ( (*this - this->Floor()) > Real::Half )
			return this->Ceil();
		else
			return this->Floor();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Square Root ( 1 / sqrt(Value) ) //
//	inline const Real InvSqrt() const {
//		if ( !this->IsZero() )
//			return std::sqrt( *this );
//		else
//			return Real::Zero;
//	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		//return *this == Real::Zero;
		return (*this).Abs() < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroPositive() const {
		//return *this == Real::Zero;
		return *this < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const bool Is( const Real& _Vs ) const {
		//return (*this - _Vs) == Real::Zero;
		return (*this - _Vs).Abs() < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //


	// Random Numbers //
	static Real Random();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR
#undef OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR
#undef OVERLOAD_TEST_OPERATOR
#undef OVERLOAD_SYMBOL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Real_H__ //
// - ------------------------------------------------------------------------------------------ - //
