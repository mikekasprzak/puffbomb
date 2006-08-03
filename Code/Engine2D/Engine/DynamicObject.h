// - ------------------------------------------------------------------------------------------ - //
// DynamicObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicObject_H__
#define __Engine2D_Engine_DynamicObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include "DynamicObjectComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicObject {
public:
	// Parts connecting this object together //
	
	// Parts of this object //
	std::vector< cDynamicObjectComponent > Component;

public:
	// Do physics //
	inline void Step() {
		// Move all my parts //
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			Component[ idx ].Step();
		}
	}

	// Do any work (control/AI) I may have //
	inline void Work() {
	}

	// Draw Myself //
	inline void Draw() {
	}

public:
	inline bool IsActive() {
		return true;
	}

public:
	// Solve Collisions/Actions //
	void Solve( cDynamicObject& _Vs );
	void Solve( class cStaticObject& _Vs );
	void Solve( class cPassiveObject& _Vs );
	void Solve( class cZone& _Vs );
	void Solve( class cImpulse& _Vs );
	
	// Messanging //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
