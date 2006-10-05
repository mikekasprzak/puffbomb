// - ------------------------------------------------------------------------------------------ - //
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/AnimationGenerator.h>
#include <Util/String.h>

#include <Graphics/Mesh2D/Mesh2DPose.h>
#include <Physics/Body2D.h>
#include "ComponentAnimationSet.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Binary/PackedFrame.h"

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
class cEndianWriter {
public:
	ofstream File;
	bool LittleEndian;

public:
	cEndianWriter() :
		LittleEndian( true )
	{
	}
	
	cEndianWriter( const std::string& _FileName, bool _LittleEndian ) :
		File( _FileName.c_str(), ios::binary | ios::out ),
		LittleEndian( _LittleEndian )	
	{
	}

public:
	template< class T >
	void Write( const T& Data ) {
		if ( LittleEndian )
			File.write( (char*)&Data, sizeof(Data) );
		else {
			
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::SaveBinary( const std::string& FileName, const std::string& ArtDirectory, bool LittleEndian ) {
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
		cEndianWriter Out( FileName, LittleEndian );
				
		// 8 byte File Header //
		{
			char MagicNumber[4] = { 'C', 'O', 'M', 'P' };
			unsigned int FileVersion = 0;
			
			// Write File Header //
			Out.File.write( &MagicNumber[0], 4 );
			Out.Write( FileVersion );
		}
		
		// Animations part //
		{
			// Number of Animations //
			Out.Write( Animation.size() );
			
			// For every animation //
			for ( int idx = 0; idx < Animation.size(); idx++ ) {
				// Frame count //
				Out.Write( Animation[ idx ].Frame.size() );
				// Loop point //
				Out.Write( Animation[ idx ].LoopPoint );
				
				// Frames //
				for ( int idx2 = 0; idx2 < Animation[ idx ].Frame.size(); idx2++ ) {
					
				}
			}
		}
		
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
