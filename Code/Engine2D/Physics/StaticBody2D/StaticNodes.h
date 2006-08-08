// - ------------------------------------------------------------------------------------------ - //
// StaticNodes //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_StaticBody2D_StaticNodes_H__
#define __Engine2D_Physics_StaticBody2D_StaticNodes_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticNodes {
	std::vector< Vector2D > Node;
public:
	// Constructor //
	cStaticNodes( int _Count ) :
		Node( _Count )
	{
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	// Get the Current Position as a pointer //
	inline Vector2D* const Pos() {
		return &Node[ 0 ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the Current Position as an index //
	inline Vector2D& Pos( const size_t& _Index ) {
		return Node[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline size_t Size() {
		return Node.size();
	}
	// - -------------------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D // 
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_StaticBody2D_StaticNodes_H__ //
// - ------------------------------------------------------------------------------------------ - //
