// - ------------------------------------------------------------------------------------------ - //
// RadiusRect2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_RadiusRect2D_H__
#define __Geometry_RadiusRect2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

class RadiusRect2D {
public:
	// - -------------------------------------------------------------------------------------- - //
	Vector2D _Center;
	Vector2D _HalfShape;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect2D() {
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Normal Creation (RectXD style (x,y,w,h)) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect2D( const Real& _x, const Real& _y, const Real& _w, const Real& _h ) :
		_Center( _x + (_w * Real::Half), _y + (_h * Real::Half) ),
		_HalfShape( _w * Real::Half, _h * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect2D( const Vector2D& _Vec1, const Vector2D& _Vec2 ) :
		_Center( _Vec1 + (_Vec2 * Real::Half) ),
		_HalfShape( _Vec2 * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Pair Creation (P1, P2) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect2D( const bool&, const Vector2D& _Vec1, const Vector2D& _Vec2 ) :
		_Center( 
			(_Vec1.x.Min( _Vec2.x )) + ((_Vec2.x - _Vec1.x).Abs() * Real::Half),
			(_Vec1.y.Min( _Vec2.y )) + ((_Vec2.y - _Vec1.y).Abs() * Real::Half)
			),
		_HalfShape( 
			(_Vec2.x - _Vec1.x).Abs() * Real::Half,
			(_Vec2.y - _Vec1.y).Abs() * Real::Half
			)
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect2D( const bool&, const bool&, const Vector2D& _Vec1, const Vector2D& _Vec2 ) :
		_Center( _Vec1 + ((_Vec2 - _Vec1) * Real::Half) ),
		_HalfShape( (_Vec2 - _Vec1) * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Radius Creation (Center, HalfShape) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect2D( const bool&, const bool&, const bool&, const Vector2D& _VecCenter, const Vector2D& _VecShape ) :
		_Center( _VecCenter ),
		_HalfShape( _VecShape )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Pair //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect2D Pair( const Real& _x1, const Real& _y1, const Real& _x2, const Real& _y2 ) {
		return RadiusRect2D( true, Vector2D( _x1, _y1 ), Vector2D( _x2, _y2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect2D Pair( const Vector2D& _Vec1, const Vector2D& _Vec2 ) {
		return RadiusRect2D( true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Optimized Pair Creation (both points must be in the correct space, no min/max'ing done) //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect2D _Pair( const Vector2D& _Vec1, const Vector2D& _Vec2 ) {
		return RadiusRect2D( true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Radius //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect2D Radius( const Real& _x1, const Real& _y1, const Real& _x2, const Real& _y2 ) {
		return RadiusRect2D( true, true, true, Vector2D( _x1, _y1 ), Vector2D( _x2, _y2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect2D Radius( const Vector2D& _Vec1, const Vector2D& _Vec2 ) {
		return RadiusRect2D( true, true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D P1() const {
		return _Center - _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D P2() const {
		return _Center + _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& Center() const {
		return _Center;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real Width() const {
		return _HalfShape.x + _HalfShape.x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& HalfWidth() const {
		return _HalfShape.x;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Height() const {
		return _HalfShape.y + _HalfShape.y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& HalfHeight() const {
		return _HalfShape.y;
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Shape() const {
		return _HalfShape + _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& HalfShape() const {
		return _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
public:	
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Area() const {
		return Width() * Height();
	}
	// - -------------------------------------------------------------------------------------- - //

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Test for intersection between rectangles //
	inline const bool operator == ( const RadiusRect2D& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator != ( const RadiusRect2D& Vs ) const {
		return !(*this == Vs);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator == ( const Vector2D& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Difference //
	inline const RadiusRect2D operator - ( const RadiusRect2D& Vs ) const {
		return Pair(
			Vector2D( P1().x.Max( Vs.P1().x ), P1().y.Max( Vs.P1().y ) ),
			Vector2D( P2().x.Min( Vs.P2().x ), P2().y.Min( Vs.P2().y ) )
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Union //
	inline const RadiusRect2D operator + ( const RadiusRect2D& Vs ) const {
		return Pair(
			Vector2D( P1().x.Min( Vs.P1().x ), P1().y.Min( Vs.P1().y ) ),
			Vector2D( P2().x.Max( Vs.P2().x ), P2().y.Max( Vs.P2().y ) )
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector2D ClosestPoint( const Vector2D& v ) const {
		Vector2D Point;
	
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
	
		return Point;
	}
	// - -------------------------------------------------------------------------------------- - //	
public:
	inline const class Rect2D ToRect() const;
	inline const class PairRect2D ToPairRect() const;
	inline const RadiusRect2D& ToRadiusRect() const {
		return *this;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_RadiusRect2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
