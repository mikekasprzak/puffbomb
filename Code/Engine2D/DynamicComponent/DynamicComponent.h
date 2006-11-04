// - ------------------------------------------------------------------------------------------ - //
// DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_H__
#define __Engine2D_Engine_DynamicComponent_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include "Body2D/Body2D.h"
#include "ComponentAnimationSet/ComponentAnimationSet.h"
#include "StateFlags.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicComponent {
public:
	// Who our parent is //
	const class cDynamicCollection* Parent;

public:
	// Parts of a component //
	cComponentAnimationSet* AnimationSet;
	cBody2D Body;
	
	// Activity State Flags //
	cStateFlags State;


public:
	int CurrentAnimation;
	int CurrentFrame;
	Real CurrentFrameTime;

	// The rate at which to play back the animation //
	Real PlayBackRate;

public:
	cDynamicComponent();
	cDynamicComponent( const class cDynamicCollection* const _Parent, const std::string& ComponentFile, const Vector2D& Offset = Vector2D::Zero );

public:
	// - -------------------------------------------------------------------------------------- - //
	// Do physics as a self sustaining object //
	void Step();

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Draw object Mesh transformed by Body //
	void Draw();

public:
	// - -------------------------------------------------------------------------------------- - //
	// Debug Drawing //
	void DrawBody( const bool Selected = false ) const;

public:
	// - -------------------------------------------------------------------------------------- - //
	// Query the state to know if component is active //
	inline bool IsActive() {
		return State.Active();
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	// Solve Collisions/Actions //
	void Solve( cDynamicComponent& _Vs );
	void Solve( class cStaticObjectInstance& _Vs );
	void Solve( class cPassiveObject& _Vs );
	void Solve( class cZone& _Vs );
	void Solve( class cImpulse& _Vs );

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Messanging //
	// * needs to be here to relay the message back to the parent ** //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_H__ //
// - ------------------------------------------------------------------------------------------ - //
