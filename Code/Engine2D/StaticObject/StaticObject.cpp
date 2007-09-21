// - ------------------------------------------------------------------------------------------ - //
// StaticObject //
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Util/String.h>
#include <FileIO/LZMA.h>

#include <Graphics/Gfx.h>
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
#include "StaticObject.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cStaticObject::Draw( const Vector2D& Offset ) {
	Gfx::DrawMesh3D( Mesh, Offset.ToVector3D() + Vector3D( 0, 0, -20 ) );
}	
// - ------------------------------------------------------------------------------------------ - //
void cStaticObject::Load( const std::string& FileName )
{
	Buffer = LZMA::UnPack( FileName );
		
	unsigned int ObjSize =  *( (unsigned int*)Buffer );
	Log( LOG_MESH_INFO, "ObjSize " << ObjSize );
	
	Mesh.push_back( cMesh3D() );

	Mesh[0].Vertex = (StaticArray< Vector3D >*) &Buffer[8];
	Mesh[0].VertexNormal = (StaticArray< Vector3D >*) &(*Mesh[0].Vertex)[ Mesh[0].Vertex->Size() ];
	Mesh[0].VertexColor = (StaticArray< unsigned int >*) &(*Mesh[0].VertexNormal)[ Mesh[0].VertexNormal->Size() ];
	Mesh[0].TextureCoord = (StaticArray< Vector2D >*) &(*Mesh[0].VertexColor)[ Mesh[0].VertexColor->Size() ];
	Mesh[0].Indices = (StaticArray< unsigned int >*) &(*Mesh[0].TextureCoord)[ Mesh[0].TextureCoord->Size() ];
	Mesh[0].TextureName = (StaticArray< char >*) &(*Mesh[0].Indices)[ Mesh[0].Indices->Size() ];

	std::string TempTextureName( &(*Mesh[0].TextureName)[0] );
	Mesh[0].TextureID = TexturePool.Load( TempTextureName ).Id;

	for( size_t obj = 1; obj < ObjSize; ++obj )
	{
		Mesh.push_back( cMesh3D() );
		
		int PadNum = Mesh[obj-1].TextureName->Size() % 4;
		if( PadNum != 0 )
		{
			PadNum = 4 - PadNum;
		}

		
		Mesh[obj].Vertex = (StaticArray< Vector3D >*) &(*Mesh[obj-1].TextureName)[ Mesh[obj-1].TextureName->Size() + PadNum ];
		Mesh[obj].VertexNormal = (StaticArray< Vector3D >*) &(*Mesh[obj].Vertex)[ Mesh[obj].Vertex->Size() ];
		Mesh[obj].VertexColor = (StaticArray< unsigned int >*) &(*Mesh[obj].VertexNormal)[ Mesh[obj].VertexNormal->Size() ];
		Mesh[obj].TextureCoord = (StaticArray< Vector2D >*) &(*Mesh[obj].VertexColor)[ Mesh[obj].VertexColor->Size() ];
		Mesh[obj].Indices = (StaticArray< unsigned int >*) &(*Mesh[obj].TextureCoord)[ Mesh[obj].TextureCoord->Size() ];
		Mesh[obj].TextureName = (StaticArray< char >*) &(*Mesh[obj].Indices)[ Mesh[obj].Indices->Size() ];
		
		TempTextureName = &(*Mesh[obj].TextureName)[0];
		Mesh[obj].TextureID = TexturePool.Load( TempTextureName ).Id;

	}
	
	Log( LOG_MESH_INFO, "Finished Loading Mesh3d Binary File = " << FileName );
	
	CalcBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
