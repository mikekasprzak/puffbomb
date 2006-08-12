// - ------------------------------------------------------------------------------------------ - //
// RadiusRect3D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_RadiusRect3D_H__
#define __Geometry_RadiusRect3D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

class RadiusRect3D {
public:
	// - -------------------------------------------------------------------------------------- - //
	Vector3D _Center;
	Vector3D _HalfShape;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D() {
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Normal Creation (RectXD style (x,y,w,h)) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const Real& _x, const Real& _y, const Real& _z, const Real& _w, const Real& _h, const Real& _l ) :
		_Center( _x + (_w * Real::Half), _y + (_h * Real::Half), _z + (_l * Real::Half) ),
		_HalfShape( _w * Real::Half, _h * Real::Half, _l * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const Vector3D& _Vec1, const Vector3D& _Vec2 ) :
		_Center( _Vec1 + (_Vec2 * Real::Half) ),
		_HalfShape( _Vec2 * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Pair Creation (P1, P2) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const bool&, const Vector3D& _Vec1, const Vector3D& _Vec2 ) :
		_Center( 
			(_Vec1.x.Min( _Vec2.x )) + ((_Vec2.x - _Vec1.x).Abs() * Real::Half),
			(_Vec1.y.Min( _Vec2.y )) + ((_Vec2.y - _Vec1.y).Abs() * Real::Half),
			(_Vec1.z.Min( _Vec2.z )) + ((_Vec2.z - _Vec1.z).Abs() * Real::Half)
			),
		_HalfShape( 
			(_Vec2.x - _Vec1.x).Abs() * Real::Half,
			(_Vec2.y - _Vec1.y).Abs() * Real::Half,
			(_Vec2.z - _Vec1.z).Abs() * Real::Half
			)
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const bool&, const bool&, const Vector3D& _Vec1, const Vector3D& _Vec2 ) :
		_Center( _Vec1 + ((_Vec2 - _Vec1) * Real::Half) ),
		_HalfShape( (_Vec2 - _Vec1) * Real::Half )
	{
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Radius Creation (Center, HalfShape) //
	// - -------------------------------------------------------------------------------------- - //
	inline RadiusRect3D( const bool&, const bool&, const bool&, const Vector3D& _VecCenter, const Vector3D& _VecShape ) :
		_Center( _VecCenter ),
		_HalfShape( _VecShape )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Pair //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect3D Pair( const Real& _x1, const Real& _y1, const Real& _z1, const Real& _x2, const Real& _y2, const Real& _z2 ) {
		return RadiusRect3D( true, Vector3D( _x1, _y1, _z1 ), Vector3D( _x2, _y2, _z2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect3D Pair( const Vector3D& _Vec1, const Vector3D& _Vec2 ) {
		return RadiusRect3D( true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Optimized Pair Creation (both points must be in the correct space, no min/max'ing done) //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect3D _Pair( const Vector3D& _Vec1, const Vector3D& _Vec2 ) {
		return RadiusRect3D( true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	// Creation as a Radius //
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect3D Radius( const Real& _x1, const Real& _y1, const Real& _z1, const Real& _x2, const Real& _y2, const Real& _z2 ) {
		return RadiusRect3D( true, true, true, Vector3D( _x1, _y1, _z1 ), Vector3D( _x2, _y2, _z2 ) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const RadiusRect3D Radius( const Vector3D& _Vec1, const Vector3D& _Vec2 ) {
		return RadiusRect3D( true, true, true, _Vec1, _Vec2 );
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D P1() const {
		return _Center - _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D P2() const {
		return _Center + _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& Center() const {
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
	inline const Real Length() const {
		return _HalfShape.z + _HalfShape.z;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& HalfLength() const {
		return _HalfShape.z;
	}
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Shape() const {
		return _HalfShape + _HalfShape;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& HalfShape() const {
		return _HalfShape;
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
	inline const bool operator == ( const RadiusRect3D& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator != ( const RadiusRect3D& Vs ) const {
		return !(*this == Vs);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool operator == ( const Vector3D& Vs ) const;
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Difference //
	inline const RadiusRect3D operator - ( const RadiusRect3D& Vs ) const {
		return Pair(
			Vector3D( P1().x.Max( Vs.P1().x ), P1().y.Max( Vs.P1().y ), P1().z.Max( Vs.P1().z ) ),
			Vector3D( P2().x.Min( Vs.P2().x ), P2().y.Min( Vs.P2().y ), P1().z.Min( Vs.P1().z ) )
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Rectangle Union //
	inline const RadiusRect3D operator + ( const RadiusRect3D& Vs ) const {
		return Pair(
			Vector3D( P1().x.Min( Vs.P1().x ), P1().y.Min( Vs.P1().y ), P1().z.Min( Vs.P1().z ) ),
			Vector3D( P2().x.Max( Vs.P2().x ), P2().y.Max( Vs.P2().y ), P1().z.Max( Vs.P1().z ) )
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector3D ClosestPoint( const Vector3D& v ) const {
		Vector3D Point;
	
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
	inline const RadiusRect3D operator + ( const Vector3D& Vs ) const {
		return Pair( P1() + Vs, P2() + Vs );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Subtracting vectors to offset the position of a rectangle //
	inline const RadiusRect3D operator - ( const Vector3D& Vs ) const {
		return Pair( P1() - Vs, P2() - Vs );
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	inline const class Rect3D ToRect() const;
	inline const class PairRect3D ToPairRect() const;
	inline const RadiusRect3D& ToRadiusRect() const {
		return *this;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_RadiusRect3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
