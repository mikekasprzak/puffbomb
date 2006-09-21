// - ------------------------------------------------------------------------------------------ - //
// Mesh2DInfo //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_Mesh_Mesh2DInfo_H__
#define __Editor_Mesh_Mesh2DInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glu.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Set.h>
#include <Phiz/SphereObject.h>
#include <Engine2D/DisplayMesh.h>
// - ------------------------------------------------------------------------------------------ - //
class cStoreMesh {
public:
	Real Radius;
	Real Mass;
	
	Vector2D Pos;
};
// - ------------------------------------------------------------------------------------------ - //
class cCompleteMesh
{
public:
	cSphereObject SphereObject;
	cDisplayMesh DisplayMesh;
	
	cCompleteMesh( const cSphereObject& _SphereObject, const cDisplayMesh& _DisplayMesh )
	{
		SphereObject = _SphereObject;
		DisplayMesh = _DisplayMesh;
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cMesh2DInfo {
public:
	bool isSaved;
	std::string MeshName;
	
	std::vector< cCompleteMesh > UndoObject;
	std::vector< cCompleteMesh > RedoObject;
		
public:
	cMesh2DInfo() :
		isSaved( true )
	{
		
	}	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Mesh_Mesh2DInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
