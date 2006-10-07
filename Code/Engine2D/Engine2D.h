// - ------------------------------------------------------------------------------------------ - //
// Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine2D_H__
#define __Engine2D_Engine2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include <Engine/DynamicCollection.h>
#include <Engine/StaticObjectCollection.h>
#include <Engine/PassiveObject.h>
#include <Engine/Zone.h>

#include <Physics/Impulse.h>

#include <MessageEntity.h>
//#include <Engine2D/Graphics/NewCamera.h>
#include <Graphics/Camera.h>
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
	std::vector< cDynamicCollection > DynamicObject;
	std::vector< cStaticObjectCollection > StaticObject;
	std::vector< cPassiveObject > PassiveObject;
	std::vector< cZone > Zone;

	// A collection of impulse forces to apply to dynamic objects //
	std::vector< cImpulse > Impulse;

public:
	cEngine2D();
	~cEngine2D();
	cCamera *Camera;
	cCamera *HudCamera;

public:
	// Move and Display Everything //
	void Step();
	void Draw();
	void HudDraw();

	// Reset game back to a neutral state //
	void Reset();

public:
	// Claim the engine in control status //
	inline void SetActive() {
		Current = this;
	}	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
