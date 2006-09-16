// - ------------------------------------------------------------------------------------------ - //
// ComponentFrame //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_ComponentFrame_H__
#define __Engine2D_Engine_DynamicComponent_ComponentFrame_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Body2D/Body2DPose.h>
#include <Engine2D/Graphics/Mesh2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cComponentFrame {
public:
	size_t BodyPoseIndex;
	cMesh2D Mesh;

#ifdef EDITOR
	size_t MeshPoseIndex;
#endif // EDITOR //

	unsigned int Time;

public:
	cComponentFrame() :
		BodyPoseIndex( 0 ),
#ifdef EDITOR
		MeshPoseIndex( 0 ),
#endif // EDITOR //
		Time( 1 )
	{
	}
	
#ifdef EDITOR
	cComponentFrame( size_t _BodyPoseIndex, size_t _MeshPoseIndex ) :
		BodyPoseIndex( _BodyPoseIndex ),
		MeshPoseIndex( _MeshPoseIndex ),
		Time( 1 )
	{
	}	
#endif // EDITOR //
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_ComponentFrame_H__ //
// - ------------------------------------------------------------------------------------------ - //
