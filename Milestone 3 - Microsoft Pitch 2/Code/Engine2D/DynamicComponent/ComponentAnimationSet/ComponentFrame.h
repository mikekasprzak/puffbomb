// - ------------------------------------------------------------------------------------------ - //
// ComponentFrame //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_ComponentFrame_H__
#define __Engine2D_Engine_DynamicComponent_ComponentFrame_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicComponent/Body2D/Pose/Body2DPose.h>
#include <DynamicComponent/Mesh2D/Mesh2D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cComponentFrame {
public:
	unsigned int Time;
	unsigned int Flags;

	size_t BodyPoseIndex;
	size_t TextureId[3];
	cMesh2D Mesh;

	size_t MeshPoseIndex;

public:
	cComponentFrame() :
		Time( 1 ),
		BodyPoseIndex( 0 ),
		MeshPoseIndex( 0 )
	{
	}

	cComponentFrame( size_t _BodyPoseIndex, size_t _MeshPoseIndex ) :
		Time( 1 ),
		BodyPoseIndex( _BodyPoseIndex ),
		MeshPoseIndex( _MeshPoseIndex )
	{
	}	

/*
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
*/

public:
	inline void Draw( const cBody2D& Body, const int RenderPass = 0 ) {
		if ( TextureId[ RenderPass ] != 0 ) {
			Mesh.Draw( Body, TextureId[ RenderPass ] );
		}
		//Mesh.Draw( Body, TextureIndex );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_ComponentFrame_H__ //
// - ------------------------------------------------------------------------------------------ - //
