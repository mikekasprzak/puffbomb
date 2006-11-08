// - ------------------------------------------------------------------------------------------ - //
// Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine2D_H__
#define __Engine2D_Engine2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicCollection/DynamicCollection.h>
#include <StaticObject/StaticObjectInstance.h>
#include <PassiveObject/PassiveObject.h>
#include <Zone/Zone.h>

#include <Impulse/Impulse.h>

#include <Graphics/Camera.h>
#include <Map/Map.h>
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
	cMap Map;

	std::vector< cDynamicCollection* > DynamicCollection;
	std::vector< cStaticObjectInstance > StaticObjectInstance;
	std::vector< cPassiveObject* > PassiveObject;
	std::vector< cZone* > Zone;

	// Partitioning //
	std::vector< cDynamicComponent* > DynamicComponent;

	// A collection of impulse forces to apply to dynamic objects //
	std::vector< cImpulse > Impulse;

public:
	cCamera *Camera;

public:
	cEngine2D();
	~cEngine2D();

public:
	// Move and Display Everything //
	void Step();
	void Draw();
	void LoadMap();

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
