// - ------------------------------------------------------------------------------------------ - //
// PackedSpring //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_Binary_PackedSpring_H__
#define __Engine2D_Engine_DynamicComponent_Binary_PackedSpring_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
namespace DynamicComponent {
// - ------------------------------------------------------------------------------------------ - //
class cPackedSpring {
public:
	unsigned int IndexA:16;
	unsigned int IndexB:16;
	
	// Flags //
	bool MinConstraint:1;
	bool MaxConstraint:1;
private:
	int FlagPad:14;
	unsigned int _Strength:16;

	int _Length:32;

	// If fraction is 16, then the integer part is 16 // 
	enum {
		Fraction = 16,
		StrengthRange = (1 << 16) - 1
	};

public:
	// Length part //
	inline const Real Length() const {
		return Real( _Length ) / Real( 1 << Fraction );
	}
	inline void Length( const Real _Value ) {
		_Length = (int)( _Value * Real( 1 << Fraction ) );
	}

	// Strength part //
	inline const Real Strength() const {
		return Real( _Strength ) / Real( StrengthRange );
	}
	inline void Strength( const Real _Value ) {
		_Strength = (int)( _Value * Real( StrengthRange ) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_Binary_PackedSpring_H__ //
// - ------------------------------------------------------------------------------------------ - //
