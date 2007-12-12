// - ------------------------------------------------------------------------------------------ - //
// PackedVertex //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_Binary_PackedVertex_H__
#define __Engine2D_Engine_DynamicComponent_Binary_PackedVertex_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
namespace DynamicComponent {
// - ------------------------------------------------------------------------------------------ - //
class cPackedVertex {
	int _x:28;
	int _y:28;
public:
	unsigned int _OrientationIndex:8;

private:
	// If fraction is 14, then the integer part is 14.  If fraction is 12, the integer is 16. // 
	enum {
		Fraction = 14
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
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_Binary_PackedVertex_H__ //
// - ------------------------------------------------------------------------------------------ - //
