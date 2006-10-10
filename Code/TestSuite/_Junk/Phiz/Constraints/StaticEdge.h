// - ------------------------------------------------------------------------------------------ - //
// StaticEdge //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_StaticEdge_H__
#define __Phiz_StaticEdge_H__
// - ------------------------------------------------------------------------------------------ - //

#include <Util/ClassDesigner.h>
#include <Phiz/Physics.h>

// - ------------------------------------------------------------------------------------------ - //
class cStaticEdge: public ABSet< size_t > {
public:
	typedef RadiusRect2D RectType;
	RectType BoundingRect;

	Vector2D Normal;
	Real Length;
	
public:
	cStaticEdge( ) {
	}

	cStaticEdge( const size_t& _a, const size_t& _b ) :
		ABSet< size_t >( _a, _b )
	{
	}

public:
	inline const Vector2D& SurfaceNormal() const {
		return Normal;
	}

	inline const Vector2D DirectionalNormal() const {
		return Normal.Tangent();
	}
	
public:
	enum {
		flEdge = bit1,
		flCorner = bit2
	};
	
	inline const Vector2D ClosestPoint( cStaticNodes& Node, const Vector2D& Vs, int& Flags = cPhysics::OperationFlags ) const {
		Vector2D ToCorner = Node.Pos( a ) - Vs;
		Real DistanceToSurface = ToCorner * SurfaceNormal();
		Vector2D Point = Vs + (DistanceToSurface * SurfaceNormal());
		
		ToCorner = Point - Node.Pos( a );
		Real Dot = ToCorner * DirectionalNormal();
		
		if ( Dot > Length ) {
			Flags = flCorner;
			return Node.Pos( b );
		}
		else if ( Dot < Real::Zero ) {
			Flags = flCorner;
			return Node.Pos( a );
		}
		else {
			Flags = flEdge;
			return Point;
		}
	}

public:
	inline void CalcNormal( cStaticNodes& Node ) {
		// Calculate the Directional Vector //
		Normal = Node.Pos( b ) - Node.Pos( a );
		// Normalize it, and store the Length //
		Length = Normal.NormalizeRet();
		// Now, take the Tangent of the vector //
		Normal = -Normal.Tangent();
	}
	
	inline void CalcBoundingRect( cStaticNodes& Node ) {
		BoundingRect = RectType::Pair( Node.Pos( a ), Node.Pos( b ) );
	}	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_StaticEdge_H__ //
// - ------------------------------------------------------------------------------------------ - //
