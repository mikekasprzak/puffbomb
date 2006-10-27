// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/String.h>

#include "ComponentAnimationSet.h"

#include <Graphics/TexturePool.h>

#include <DynamicComponent/Mesh2D/Pose/Mesh2DPose.h>
#include <DynamicComponent/Body2D/Body2D.h>
#include <DynamicComponent/AnimationGenerator/AnimationGenerator.h>

// - ------------------------------------------------------------------------------------------ - //
#include <Util/InputOutput.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
/*class cEndianReader {
public:
	ifstream File;
	bool LittleEndian;

public:
	cEndianReader() :
		LittleEndian( true )
	{
	}
	
	cEndianReader( const std::string& _FileName, bool _LittleEndian = true ) :
		File( _FileName.c_str(), ios::binary | ios::in ),
		LittleEndian( _LittleEndian )	
	{
	}

public:
	template< class T >
	void Read( const T& Data ) {
		if ( LittleEndian )
			File.read( (char*)&Data, sizeof(Data) );
		else {
			
		}
	}

	int Read() {
		if ( LittleEndian ) {
			int Data;
			File.read( (char*)&Data, sizeof(Data) );
			
			return Data;
		}
		else {
			
		}
		return 0;
	}

};*/
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::LoadBinary( const std::string& FileName ) {
	// Read Data //
	cEndianReader In( FileName );

	// 8 byte File Header //
	{
		//char MagicNumber[4];
		int MagicNumber;
		unsigned int FileVersion;
		
		In.Read( MagicNumber );
		In.Read( FileVersion );
		
		Log( LOG_HIGHEST_LEVEL, "Magic: " << MagicNumber );
		Log( LOG_HIGHEST_LEVEL, "Version: " << FileVersion );
	}
	
	// Animations part //
	{
		Animation.resize( In.Read() );
		Log( LOG_HIGHEST_LEVEL, "Animation Count: " << Animation.size() );

		// For every animation //
		for ( size_t idx = 0; idx < Animation.size(); idx++ ) {
			// Frame count //
			Animation[ idx ].Frame.resize( In.Read() );
			Log( LOG_HIGHEST_LEVEL, "Frame Count " << Animation[ idx ].Frame.size() );
			
			// Loop point //
			In.Read( Animation[ idx ].LoopPoint );
			
			// Frames //
			for ( size_t idx2 = 0; idx2 < Animation[ idx ].Frame.size(); idx2++ ) {
				// Data //
				In.Read( Animation[ idx ].Frame[ idx2 ].Time );
				In.Read( Animation[ idx ].Frame[ idx2 ].Flags );
				In.Read( Animation[ idx ].Frame[ idx2 ].BodyPoseIndex );
				In.Read( Animation[ idx ].Frame[ idx2 ].TextureIndex );
				
				// Mesh //
				{
					// Vertices //
					Animation[ idx ].Frame[ idx2 ].Mesh.Vertex.resize( In.Read() );
					for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.Vertex.size(); idx3++ ) {
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Vertex[ idx3 ].x );
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Vertex[ idx3 ].y );
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Vertex[ idx3 ].OrientationIndex );
					}
				
					// UV //
					Animation[ idx ].Frame[ idx2 ].Mesh.UV.resize( In.Read() );
					for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.UV.size(); idx3++ ) {
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.UV[ idx3 ].x );
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.UV[ idx3 ].y );
					}

					// Faces //
					Animation[ idx ].Frame[ idx2 ].Mesh.Face.resize( In.Read() );
					for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.Face.size(); idx3++ ) {
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Face[ idx3 ].a );
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Face[ idx3 ].b );
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Face[ idx3 ].c );
					}

					// Orientation //
					Animation[ idx ].Frame[ idx2 ].Mesh.Orientation.resize( In.Read() );
					for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.Orientation.size(); idx3++ ) {
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Orientation[ idx3 ].PivotIndex );
						In.Read( Animation[ idx ].Frame[ idx2 ].Mesh.Orientation[ idx3 ].HandleIndex );
					}
				}
			}
		}

		// Body Poses //
		BodyPose.resize( In.Read() );
		// For every body //
		for ( size_t idx = 0; idx < BodyPose.size(); idx++ ) {
			// Write nodes //
			BodyPose[ idx ].Node.resize( In.Read() );
			for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Node.size(); idx2++ ) {
				In.Read( BodyPose[ idx ].Node[ idx2 ].Pos.x );
				In.Read( BodyPose[ idx ].Node[ idx2 ].Pos.y );
				In.Read( BodyPose[ idx ].Node[ idx2 ].Mass );
				
				//Log( 10, "Mo " << BodyPose[ idx ].Node[ idx2 ].Mass );
			}

			// Write Springs //
			BodyPose[ idx ].Spring.resize( In.Read() );
			for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Spring.size(); idx2++ ) {
				// Write //
				In.Read( BodyPose[ idx ].Spring[ idx2 ].IndexA );
				In.Read( BodyPose[ idx ].Spring[ idx2 ].IndexB );
				In.Read( BodyPose[ idx ].Spring[ idx2 ].Length );
				In.Read( BodyPose[ idx ].Spring[ idx2 ].Strength );
				In.Read( BodyPose[ idx ].Spring[ idx2 ].Flags );
			}

			// Write Spheres //
			BodyPose[ idx ].Sphere.resize( In.Read() );
			for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Sphere.size(); idx2++ ) {
				In.Read( BodyPose[ idx ].Sphere[ idx2 ].Index );
				In.Read( BodyPose[ idx ].Sphere[ idx2 ].Radius );
				In.Read( BodyPose[ idx ].Sphere[ idx2 ].Flags );
			}
		}
	
		// Texture References //
		{
			Texture.resize( In.Read() );
			for ( size_t idx = 0; idx < Texture.size(); idx++ ) {
				// Read the File Name //
				int StrLen = In.Read();
				char MyString[ StrLen + 1 ];
				
				In.File.read( MyString, StrLen );
				
				MyString[ StrLen ] = 0;
				
				// Load the texture //
				Texture[ idx ] = TexturePool.Load( string( MyString ) );
			}
			
			// Convert local Id's to texture Id's //
			for ( size_t idx = 0; idx < Animation.size(); idx++ ) {
				for ( size_t idx2 = 0; idx2 < Animation[ idx ].Frame.size(); idx2++ ) {
					Animation[ idx ].Frame[ idx2 ].TextureIndex =
						Texture[ Animation[ idx ].Frame[ idx2 ].TextureIndex ];
				}
			}
		}
		
		// Calculate Mesh Orientation Home Matrix //
		for ( size_t idx = 0; idx < Animation.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Animation[ idx ].Frame.size(); idx2++ ) {
				for ( size_t idx3 = 0; idx3 < Animation[ idx ].Frame[ idx2 ].Mesh.Orientation.size(); idx3++ ) {
					Animation[ idx ].Frame[ idx2 ].Mesh.Orientation[ idx3 ].CalculateHomeMatrix(
						BodyPose[ Animation[ idx ].Frame[ idx2 ].BodyPoseIndex ].Node
						);
				}
			}
		}

	}
}
// - ------------------------------------------------------------------------------------------ - //
/*class cEndianWriter {
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
};*/
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::SaveBinary( const std::string& CompFileName, const std::string& FinalFileName, const std::string& ArtDirectory, bool LittleEndian ) {
	// Extract the base name from the output file, to know what we're going to call what we write to //
	string WorkingBaseName = String::DirectorySlash( CompFileName ) + String::BaseName( CompFileName );
	string FinalBaseName = String::DirectorySlash( FinalFileName ) + String::BaseName( FinalFileName );
	
	// Acquire art assets, and description of animation timings //
	cAnimationGenerator Art( ArtDirectory );
	
	// Write Image Conversion Shell Script //
	{
		ofstream OutScript( (WorkingBaseName + ".sh").c_str() );
		
		OutScript << "# Generated Shell Script for Image conversion" << endl;
		
		for ( size_t idx = 0; idx < Art.ImagePool.size(); idx++ ) {
			// PNG to TX //
			OutScript << getenv("TextureTool") << " " <<
				Art.Directory << "/" << Art.ImagePool[ idx ].FileName << " " << 
				WorkingBaseName << idx << ".tx " <<
				getenv("TextureToolArgs") << endl;
			
			// Compress //
			OutScript << getenv("Compress") << " " <<
				WorkingBaseName << idx << ".tx " <<
				FinalBaseName << idx << ".pack.tx" <<
				endl;
		}
		
		OutScript.close();
	}


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
	
	
	// Write Data (Comp File) //
	{
		cEndianWriter Out( CompFileName, LittleEndian );
				
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
					
					// Write the index from the AnimationGenerator instead //
					Out.Write( Art.Animation[ idx ].Frame[ idx2 ].ImageIndex );
					//Out.Write( Animation[ idx ].Frame[ idx2 ].TextureIndex );
					
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
		}
		
						
		// Body Poses //
		{
			Out.Write( BodyPose.size() );
			// For every body //
			for ( size_t idx = 0; idx < BodyPose.size(); idx++ ) {
				// Calculate Mass Distribution //
				Real MassDistribution = 0;
				for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Node.size(); idx2++ ) {
					MassDistribution += BodyPose[ idx ].Node[ idx2 ].Mass;
				}
			
				// Write nodes //
				Out.Write( BodyPose[ idx ].Node.size() );
				for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Node.size(); idx2++ ) {
					Out.Write( BodyPose[ idx ].Node[ idx2 ].Pos.x );
					Out.Write( BodyPose[ idx ].Node[ idx2 ].Pos.y );
					Out.Write( Real::One / ((BodyPose[ idx ].Node[ idx2 ].Mass / MassDistribution) * BodyPose[ idx ].TotalMass) );
				}

				// Write Springs //
				Out.Write( BodyPose[ idx ].Spring.size() );
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
				Out.Write( BodyPose[ idx ].Sphere.size() );
				for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Sphere.size(); idx2++ ) {
					Out.Write( BodyPose[ idx ].Sphere[ idx2 ].Index );
					Out.Write( BodyPose[ idx ].Sphere[ idx2 ].Radius );
					Out.Write( BodyPose[ idx ].Sphere[ idx2 ].Flags );
				}
			}
		}
		
		// Texture Names //
		{
			string PreFolder = String::BaseName( Art.Directory );
			string PrePreFolder = String::BaseName( String::Directory( Art.Directory ) ); 
			
			Out.Write( Art.ImagePool.size() );
			for ( size_t idx = 0; idx < Art.ImagePool.size(); idx++ ) {
				// Write original filename //
				//Out.File.write( Art.ImagePool[ idx ].FileName.c_str(), Art.ImagePool[ idx ].FileName.size() + 1 );
				
				// Write new filename //
				string FileString = PrePreFolder + "/" + PreFolder + "/" + String::BaseName( CompFileName );
				
				stringstream ImageIndex;
				ImageIndex << idx;
				
				FileString += ImageIndex.str() + ".pack.tx";
				
				Out.Write( FileString.size() );
				Out.File.write( FileString.c_str(), FileString.size() );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
