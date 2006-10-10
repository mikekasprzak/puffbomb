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
#include <DynamicComponent/Body2D/Body2DPose.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cComponentAnimationSet {
public:
	std::vector< cComponentAnimation > Animation;
	std::vector< cBody2DPose > BodyPose;
	std::vector< cTexture::IdType > Texture;

#ifdef EDITOR	
	std::vector< cMesh2DPose > MeshPose;
#endif // EDITOR //

public:
	// Functions for saving/loading the Binary based Component format //
	void LoadBinary( const std::string& FileName );
	void SaveBinary( const std::string& FileName, const std::string& ArtDirectory, bool LittleEndian = true );

#ifdef EDITOR	
	// Functions for saving/loading the Text based Component format //
	void LoadText( const std::string& FileName );
	void SaveText( const std::string& FileName );
#endif // EDITOR //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_ComponentAnimationSet_H__ //
// - ------------------------------------------------------------------------------------------ - //
