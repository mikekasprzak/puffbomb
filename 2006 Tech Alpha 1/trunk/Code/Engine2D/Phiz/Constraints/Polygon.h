// - ------------------------------------------------------------------------------------------ - //
// Polygon //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_Constraint_Polygon_H__
#define __Phiz_Constraint_Polygon_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>

#include "../DynamicNodes.h"
#include "../StaticNodes.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cPolygon {
public:
	std::vector<size_t> Index;
	std::vector<Vector2D> Normal;
	std::vector<int> Flag;

public:
	inline void CalculateNormals( cStaticNodes& Node ) {
		int idx = 0;
		int Count = Normal.size() - 1;
		for ( ; idx < Count; idx++ ) {
			Vector2D Ray = Node.Pos( Index[ idx + 1 ] ) - Node.Pos( Index[ idx ] );
			Normal[ idx ] = (-Ray.Tangent()).Normal();
		}
		
		Vector2D Ray = Node.Pos( Index[ 0 ] ) - Node.Pos( Index[ idx ] );
		Normal[ idx ] = (-Ray.Tangent()).Normal();
	}

	inline void CalculateNormals( cDynamicNodes& Node ) {
		int idx = 0;
		int Count = Normal.size() - 1;
		for ( ; idx < Count; idx++ ) {
			Vector2D Ray = Node.Pos( Index[ idx + 1 ] ) - Node.Pos( Index[ idx ] );
			Normal[ idx ] = (-Ray.Tangent()).Normal();
		}
		
		Vector2D Ray = Node.Pos( Index[ 0 ] ) - Node.Pos( Index[ idx ] );
		Normal[ idx ] = (-Ray.Tangent()).Normal();
	}
	
	inline size_t Size() {
		return Index.size();	
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_Constraint_Polygon_H__ //
// - ------------------------------------------------------------------------------------------ - //
