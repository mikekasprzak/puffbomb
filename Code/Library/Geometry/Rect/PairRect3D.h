// - ------------------------------------------------------------------------------------------ - //
// PairRect3D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_PairRect3D_H__
#define __Geometry_PairRect3D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

class PairRect3D {
public:
	// - -------------------------------------------------------------------------------------- - //
	// A typedef for the current rect type, that way, similar code can be cut+paste easier //
	typedef PairRect3D RectType;
	typedef Vector3D VectorType;
	// - -------------------------------------------------------------------------------------- - //
	VectorType _P1;
	VectorType _P2;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	PairRect3D() {
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Normal Creation (RectXD style (x,y,w,h)) //
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect3D( const Real& _x, const Real& _y, const Real& _z, const Real& _w, const Real& _h, const Real& _l ) :
		_P1( _x, _y, _z ),
		_P2( _x + _w, _y + _h, _z + _l )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect3D( const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1 ),
		_P2( _Vec1 + _Vec2 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Pair Creation (P1, P2) //
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect3D( const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1.x.Min( _Vec2.x ), _Vec1.y.Min( _Vec2.y ), _Vec1.z.Min( _Vec2.z ) ),
		_P2( _Vec1.x.Max( _Vec2.x ), _Vec1.y.Max( _Vec2.y ), _Vec1.z.Max( _Vec2.z ) )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect3D( const bool&, const bool&, const VectorType& _Vec1, const VectorType& _Vec2 ) :
		_P1( _Vec1 ),
		_P2( _Vec2 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Radius Creation (Center, HalfShape) //
	// - -------------------------------------------------------------------------------------- - //
	inline PairRect3D( const bool&, const bool&, const bool&, const VectorType& _VecCenter, const VectorType& _VecShape ) :
		_P1( _VecCenter - _VecShape ),
		_P2( _VecCenter + _VecShape )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Pair //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Pair( const Real& _x1, const Real& _y1, const Real& _z1, const Real& _x2, const Real& _y2, const Real& _z2 ) {
		return RectType( true, VectorType( _x1, _y1, _z1 ), VectorType( _x2, _y2, _z2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Pair( const VectorType& _Vec1, const VectorType& _Vec2 ) {
		return RectType( true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Optimized Pair Creation (both points must be in the correct space, no min/max'ing done) //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType _Pair( const VectorType& _Vec1, const VectorType& _Vec2 ) {
		return RectType( true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Radius //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Radius( const Real& _x1, const Real& _y1, const Real& _z1, const Real& _x2, const Real& _y2, const Real& _z2 ) {
		return RectType( true, true, true, VectorType( _x1, _y1, _z1 ), VectorType( _x2, _y2, _z2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RectType Radius( const VectorType& _Vec1, const VectorType& _Vec2 ) {
		return RectType( true, true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //
	
public:
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType& P1() const {
		return _P1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType& P2() const {
		return _P2;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType Center() const {
		return P1() + HalfShape();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real Width() const {
		return P2().x - P1().x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HalfWidth() const {
		return Width() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Height() const {
		return P2().y - P1().y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HalfHeight() const {
		return Height() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Length() const {
		return P2().z - P1().z;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HalfLength() const {
		return Length() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType Shape() const {
		return P2() - P1();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const VectorType HalfShape() const {
		return Shape() * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
public:	
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Volume() const {
		return Width() * Height() * Length();
	}
	// - -------------------------------------------------------------------------------------- - //

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Test for intersection between rectangles //
	inline const bool operator == ( const RectType& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator != ( const RectType& Vs ) const {
		return !(*this == Vs);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator == ( const VectorType& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Difference //
	inline const RectType operator - ( const RectType& Vs ) const {
		return Pair(
			VectorType( P1().x.Max( Vs.P1().x ), P1().y.Max( Vs.P1().y ), P1().z.Max( Vs.P1().z ) ),
			VectorType( P2().x.Min( Vs.P2().x ), P2().y.Min( Vs.P2().y ), P1().z.Min( Vs.P1().z ) )
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Union //
	inline const RectType operator + ( const RectType& Vs ) const {
		return Pair(
			VectorType( P1().x.Min( Vs.P1().x ), P1().y.Min( Vs.P1().y ), P1().z.Min( Vs.P1().z ) ),
			VectorType( P2().x.Max( Vs.P2().x ), P2().y.Max( Vs.P2().y ), P1().z.Max( Vs.P1().z ) )
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline VectorType ClosestPoint( const VectorType& v ) const {
		VectorType Point;
	
		if ( v.x < P1().x )
			Point.x = P1().x;
		else if ( v.x > P2().x )
			Point.x = P2().x;
		else
			Point.x = v.x;
	
		if ( v.y < P1().y )
			Point.y = P1().y;
		else if ( v.y > P2().y )
			Point.y = P2().y;
		else
			Point.y = v.y;

		if ( v.z < P1().z )
			Point.z = P1().z;
		else if ( v.z > P2().z )
			Point.z = P2().z;
		else
			Point.z = v.z;
	
		return Point;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Adding vectors to offset the position of a rectangle //
	inline const RectType operator + ( const VectorType& Vs ) const {
		return Pair( P1() + Vs, P2() + Vs );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Subtracting vectors to offset the position of a rectangle //
	inline const RectType operator - ( const VectorType& Vs ) const {
		return Pair( P1() - Vs, P2() - Vs );
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	inline const class Rect3D ToRect() const;
	inline const class RadiusRect3D ToRadiusRect() const;
	inline const PairRect3D& ToPairRect() const {
		return *this;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_PairRect3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
