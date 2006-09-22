// - ------------------------------------------------------------------------------------------ - //
// PackedSphere //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_Binary_PackedSphere_H__
#define __Engine2D_Engine_DynamicComponent_Binary_PackedSphere_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
namespace DynamicComponent {
// - ------------------------------------------------------------------------------------------ - //
class cPackedSphere {
public:
	unsigned int Index:16;
	// Flags //
	bool Actuator:1;
	bool Sensor:1;
private:
	int FlagPad:14;

	int _Radius:32;

	// If fraction is 16, then the integer part is 16 // 
	enum {
		Fraction = 16
	};

public:
	// Radius part //
	inline const Real Radius() const {
		return Real( _Radius ) / Real( 1 << Fraction );
	}
	inline void Radius( const Real _Value ) {
		_Radius = (int)( _Value * Real( 1 << Fraction ) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_Binary_PackedSphere_H__ //
// - ------------------------------------------------------------------------------------------ - //
