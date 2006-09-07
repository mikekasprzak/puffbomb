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

public:
	// Functions for saving/loading the Binary based Component format //
	void LoadBinary( std::string FileName );
	void SaveBinary( std::string FileName );

#ifdef EDITOR	
	// Functions for saving/loading the Text based Component format //
	void LoadText( std::string FileName );
	void SaveText( std::string FileName );
#endif // EDITOR //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_ComponentAnimationSet_H__ //
// - ------------------------------------------------------------------------------------------ - //
