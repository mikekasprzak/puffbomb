// - ------------------------------------------------------------------------------------------ - //
// PackedUV //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_Binary_PackedUV_H__
#define __Engine2D_Engine_DynamicComponent_Binary_PackedUV_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
namespace DynamicComponent {
// - ------------------------------------------------------------------------------------------ - //
class cPackedUV {
	int _u:16;
	int _v:16;

	// If fraction is 12, then the integer part is 4 // 
	enum {
		Fraction = 12
	};

public:
	// U part //
	inline const Real u() const {
		return Real( _u ) / Real( 1 << Fraction );
	}
	inline void u( const Real _Value ) {
		_u = (int)( _Value * Real( 1 << Fraction ) );
	}

	// V part //
	inline const Real v() const {
		return Real( _v ) / Real( 1 << Fraction );
	}
	inline void v( const Real _Value ) {
		_v = (int)( _Value * Real( 1 << Fraction ) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_Binary_PackedUV_H__ //
// - ------------------------------------------------------------------------------------------ - //
