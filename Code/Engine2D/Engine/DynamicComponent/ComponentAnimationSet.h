// - ------------------------------------------------------------------------------------------ - //
// ComponentAnimationSet //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_ComponentAnimationSet_H__
#define __Engine2D_Engine_DynamicComponent_ComponentAnimationSet_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentAnimation.h"

#include <Graphics/Mesh2D/Mesh2DPose.h>
#include <Physics/Body2D/Body2DPose.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cComponentAnimationSet {
public:
	std::vector< cComponentAnimation > Animation;
	std::vector< cBody2DPose > BodyPose;

#ifdef EDITOR	
	std::vector< cMesh2DPose > MeshPose;
#endif // EDITOR //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_ComponentAnimationSet_H__ //
// - ------------------------------------------------------------------------------------------ - //
