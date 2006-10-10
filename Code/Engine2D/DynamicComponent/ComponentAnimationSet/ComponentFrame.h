// - ------------------------------------------------------------------------------------------ - //
// ComponentFrame //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_ComponentFrame_H__
#define __Engine2D_Engine_DynamicComponent_ComponentFrame_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicComponent/Body2D/Body2DPose.h>
#include <DynamicComponent/Mesh2D/Mesh2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cComponentFrame {
public:
	unsigned int Time;
	unsigned int Flags;

	size_t BodyPoseIndex;
	size_t TextureIndex;
	cMesh2D Mesh;

#ifdef EDITOR
	size_t MeshPoseIndex;
#endif // EDITOR //

public:
	cComponentFrame() :
		Time( 1 ),
#ifdef EDITOR
		BodyPoseIndex( 0 ),
		MeshPoseIndex( 0 )
#else // EDITOR //
		BodyPoseIndex( 0 )
#endif // EDITOR //	
	{
	}
	
#ifdef EDITOR
	cComponentFrame( size_t _BodyPoseIndex, size_t _MeshPoseIndex ) :
		Time( 1 ),
		BodyPoseIndex( _BodyPoseIndex ),
		MeshPoseIndex( _MeshPoseIndex )
	{
	}	
#endif // EDITOR //

public:
	void Draw( const cBody2D& Body ) {
		Mesh.Draw( Body, TextureIndex );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_ComponentFrame_H__ //
// - ------------------------------------------------------------------------------------------ - //
