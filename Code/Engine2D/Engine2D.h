// - ------------------------------------------------------------------------------------------ - //
// Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine2D_H__
#define __Engine2D_Engine2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include <Engine/DynamicObject.h>
#include <Engine/StaticObject.h>
#include <Engine/PassiveObject.h>
#include <Engine/Zone.h>

#include <Physics/Impulse.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cEngine2D {
public:
	// Current instance of the Engine. Step and Draw update this, so to support multiple engines. //
	static cEngine2D* Current;
public:
	// Our instance of physics engine info //
	cPhysics Physics;

public:
	// Our in game entities //
	std::vector< cDynamicObject > DynamicObject;
	std::vector< cStaticObject > StaticObject;
	std::vector< cPassiveObject > PassiveObject;
	std::vector< cZone > Zone;

	// A collection of impulse forces to apply to dynamic objects //
	std::vector< cImpulse > Impulse;


public:
	// Move and Display Everything //
	void Step();
	void Draw();

	// Reset game back to a neutral state //
	void Reset();
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
