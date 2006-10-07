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
			for ( size_t idx = 0; idx < Animation.size(); idx++ ) {
				// Frame count //
				Out.Write( Animation[ idx ].Frame.size() );
				// Loop point //
				Out.Write( Animation[ idx ].LoopPoint );
				
				// Frames //
				for ( size_t idx2 = 0; idx2 < Animation[ idx ].Frame.size(); idx2++ ) {
					// Data //
					Out.Write( Animation[ idx ].Frame[ idx2 ].Time );
					Out.Write( Animation[ idx ].Frame[ idx2 ].Flags );
					Out.Write( Animation[ idx ].Frame[ idx2 ].BodyPoseIndex );
					Out.Write( Animation[ idx ].Frame[ idx2 ].TextureIndex );
					
					// Mesh //
					{
						// Vertices //
						Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Vertex.size() );
						for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.Vertex.size(); idx3++ ) {
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Vertex[ idx3 ].x );
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Vertex[ idx3 ].y );
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Vertex[ idx3 ].OrientationIndex );
						}
						
						// UV //
						Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.UV.size() );
						for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.UV.size(); idx3++ ) {
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.UV[ idx3 ].x );
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.UV[ idx3 ].y );
						}

						// Faces //
						Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Face.size() );
						for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.Face.size(); idx3++ ) {
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Face[ idx3 ].a );
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Face[ idx3 ].b );
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Face[ idx3 ].c );
						}

						// Orientation //
						Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Orientation.size() );
						for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.Orientation.size(); idx3++ ) {
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Orientation[ idx3 ].PivotIndex );
							Out.Write( Animation[ idx ].Frame[ idx2 ].Mesh.Orientation[ idx3 ].HandleIndex );
						}
						
					}
				}
			}
						
			// Body Poses //
			Out.Write( BodyPose.size() );
			// For every body //
			for ( size_t idx = 0; idx < BodyPose.size(); idx++ ) {
				// Calculate Mass Distribution //
				Real MassDistribution = 0;
				for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Node.size(); idx2++ ) {
					MassDistribution += BodyPose[ idx ].Node[ idx2 ].Mass;
				}
				
				// Write nodes //
				for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Node.size(); idx2++ ) {
					Out.Write( BodyPose[ idx ].Node[ idx2 ].Pos.x );
					Out.Write( BodyPose[ idx ].Node[ idx2 ].Pos.y );
					Out.Write( (BodyPose[ idx ].Node[ idx2 ].Mass / MassDistribution) * BodyPose[ idx ].TotalMass );
				}

				// Write Springs //
				for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Spring.size(); idx2++ ) {
					// If ManualLength flag not set, calculate the length //
					if ( !BodyPose[ idx ].Spring[ idx2 ].Flags.ManualLength() ) {
						BodyPose[ idx ].Spring[ idx2 ].Length =
							(BodyPose[ idx ].Node[ BodyPose[ idx ].Spring[ idx2 ].IndexB ].Pos -
							BodyPose[ idx ].Node[ BodyPose[ idx ].Spring[ idx2 ].IndexA ].Pos).Magnitude();
					}
					
					// Write //
					Out.Write( BodyPose[ idx ].Spring[ idx2 ].IndexA );
					Out.Write( BodyPose[ idx ].Spring[ idx2 ].IndexB );
					Out.Write( BodyPose[ idx ].Spring[ idx2 ].Length );
					Out.Write( BodyPose[ idx ].Spring[ idx2 ].Strength );
					Out.Write( BodyPose[ idx ].Spring[ idx2 ].Flags );
				}

				// Write Spheres //
				for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Sphere.size(); idx2++ ) {
					Out.Write( BodyPose[ idx ].Sphere[ idx2 ].Index );
					Out.Write( BodyPose[ idx ].Sphere[ idx2 ].Radius );
					Out.Write( BodyPose[ idx ].Sphere[ idx2 ].Flags );
				}
			}
		
			// Texture References //
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
