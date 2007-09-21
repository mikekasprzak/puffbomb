// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/String.h>
#include <FileIO/LZMA.h>

#include "Mesh3d.h"
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
void cMesh3d::Draw()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh3d::Load( const std::string& FileName )
{
	if( String::HasExtension( FileName, ".bin" ) )
	{
		Buffer = LZMA::UnPack( FileName );
			
		unsigned int ObjSize =  *( (unsigned int*)Buffer );
		Log( LOG_MESH_INFO, "ObjSize " << ObjSize );
		
		Data.push_back( cData() );

		Data[0].Vertex = (StaticArray< Vector3D >*) &Buffer[8];
		Data[0].VertexNormal = (StaticArray< Vector3D >*) &(*Data[0].Vertex)[ Data[0].Vertex->Size() ];
		Data[0].VertexColor = (StaticArray< unsigned int >*) &(*Data[0].VertexNormal)[ Data[0].VertexNormal->Size() ];
		Data[0].TextureCoord = (StaticArray< Vector2D >*) &(*Data[0].VertexColor)[ Data[0].VertexColor->Size() ];
		Data[0].Indices = (StaticArray< unsigned int >*) &(*Data[0].TextureCoord)[ Data[0].TextureCoord->Size() ];
		Data[0].TextureName = (StaticArray< char >*) &(*Data[0].Indices)[ Data[0].Indices->Size() ];

		std::string TempTextureName( &(*Data[0].TextureName)[0] );
		Data[0].TextureID = TexturePool.Load( TempTextureName );
	
		for( size_t obj = 1; obj < ObjSize; ++obj )
		{
			Data.push_back( cData() );
			
			int PadNum = Data[obj-1].TextureName->Size() % 4;
			if( PadNum != 0 )
			{
				PadNum = 4 - PadNum;
			}

			
			Data[obj].Vertex = (StaticArray< Vector3D >*) &(*Data[obj-1].TextureName)[ Data[obj-1].TextureName->Size() + PadNum ];
			Data[obj].VertexNormal = (StaticArray< Vector3D >*) &(*Data[obj].Vertex)[ Data[obj].Vertex->Size() ];
			Data[obj].VertexColor = (StaticArray< unsigned int >*) &(*Data[obj].VertexNormal)[ Data[obj].VertexNormal->Size() ];
			Data[obj].TextureCoord = (StaticArray< Vector2D >*) &(*Data[obj].VertexColor)[ Data[obj].VertexColor->Size() ];
			Data[obj].Indices = (StaticArray< unsigned int >*) &(*Data[obj].TextureCoord)[ Data[obj].TextureCoord->Size() ];
			Data[obj].TextureName = (StaticArray< char >*) &(*Data[obj].Indices)[ Data[obj].Indices->Size() ];
			
			TempTextureName = &(*Data[obj].TextureName)[0];
			Data[obj].TextureID = TexturePool.Load( TempTextureName );

		}
		
		Log( LOG_MESH_INFO, "Finished Loading Mesh3d Binary File = " << FileName );
	}
	else
	{
		Log( LOG_MESH_CREATE, FileName << " Is not a Mesh3d Binary File" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
