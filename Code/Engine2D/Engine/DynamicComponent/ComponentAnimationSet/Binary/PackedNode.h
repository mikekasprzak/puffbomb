// - ------------------------------------------------------------------------------------------ - //
// PackedNode //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_Binary_PackedNode_H__
#define __Engine2D_Engine_DynamicComponent_Binary_PackedNode_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
namespace DynamicComponent {
// - ------------------------------------------------------------------------------------------ - //
class cPackedNode {
	int _x:32;
	int _y:32;
	int _Mass:32;

	// If fraction is 16, then the integer part is 16 // 
	enum {
		Fraction = 16
	};

public:
	// X part //
	inline const Real x() const {
		return Real( _x ) / Real( 1 << Fraction );
	}
	inline void x( const Real _Value ) {
		_x = (int)( _Value * Real( 1 << Fraction ) );
	}

	// Y part //
	inline const Real y() const {
		return Real( _y ) / Real( 1 << Fraction );
	}
	inline void y( const Real _Value ) {
		_y = (int)( _Value * Real( 1 << Fraction ) );
	}

	// Mass part //
	inline const Real Mass() const {
		return Real( _Mass ) / Real( 1 << Fraction );
	}
	inline void Mass( const Real _Value ) {
		_Mass = (int)( _Value * Real( 1 << Fraction ) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_Binary_PackedNode_H__ //
// - ------------------------------------------------------------------------------------------ - //
