// - ------------------------------------------------------------------------------------------ - //
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/AnimationGenerator.h>
#include <Util/String.h>

#include <Physics/Body2D.h>
#include "ComponentAnimationSet.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Binary/PackedVertex.h"
#include "Binary/PackedUV.h"
#include "Binary/PackedFace.h"
#include "Binary/PackedOrientation.h"

#include "Binary/PackedNode.h"
#include "Binary/PackedSpring.h"
#include "Binary/PackedSphere.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
using namespace DynamicComponent;
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::LoadBinary( const std::string& FileName ) {
	// Read Data //
	ifstream InFile( FileName.c_str(), ios::binary | ios::out );
		
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::SaveBinary( const std::string& FileName, const std::string& ArtDirectory ) {
	// Generate Data //
	{
		// Acquire art assets, and description of animation timings //
		cAnimationGenerator Art( ArtDirectory );
		
		// Look up, and convert all mesh poses in to meshes //
		for ( size_t AnimIndex = 0; AnimIndex < Animation.size(); AnimIndex++ ) {
			for ( size_t FrameIndex = 0; FrameIndex < Animation[ AnimIndex ].Frame.size(); FrameIndex++ ) {
				// Generate an active body from the pose //
				cBody2D TempBody( BodyPose[ Animation[ AnimIndex ].Frame[ FrameIndex ].BodyPoseIndex ] );
				
				// Calculate the Mesh from the mesh pose and a body //
				Animation[ AnimIndex ].Frame[ FrameIndex ].Mesh = 
					cMesh2D( MeshPose[ Animation[ AnimIndex ].Frame[ FrameIndex ].MeshPoseIndex ], TempBody );
			}
		}
	}
	
	
	// Write Data //
	{
		ofstream OutFile( FileName.c_str(), ios::binary | ios::out );
		
		
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
