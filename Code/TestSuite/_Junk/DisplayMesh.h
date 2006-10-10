// - ------------------------------------------------------------------------------------------ - //
// DisplayMesh //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_DisplayMesh_H__
#define __Engine2D_DisplayMesh_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glu.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Set.h>
// - ------------------------------------------------------------------------------------------ - //
class cDisplayMesh
{
public:
	class cDisplayNode
	{
	public:
		Vector2D Pos;
		int Handle;
		int Pivot;
	
		cDisplayNode( Vector2D _Pos, int _Handle, int _Pivot )
		{
			Pos = _Pos;
			Handle = _Handle;
			Pivot = _Pivot;
		}	
		cDisplayNode()
		{
			
		}	
	};
	class cFace
	{
	public:
		ABCSet<int> Vertex;
		ABCSet<Vector2D> UV;
		int Layer;
		
		cFace() :
		Layer( 0 )
		{
			
		}
	};
	
	cDisplayMesh() :
		TextureIdx( -1 )
	{

	}

	cDisplayMesh( const std::string& File ) :
		TextureIdx( -1 )
	{
		Load( File );
	}

	~cDisplayMesh()
	{

	}
	
	std::vector< cDisplayNode > DisplayNode;
	std::vector< cFace > Face;
	
	int TextureIdx;
	std::string TextureName;
	
	inline size_t size()
	{
		return DisplayNode.size();
	}
	inline Vector2D& Pos( int Node )
	{
		return DisplayNode[ Node ].Pos;
	}
	inline int& Handle( int Node )
	{
		return DisplayNode[ Node ].Handle;
	}
	inline int& Pivot( int Node )
	{
		return DisplayNode[ Node ].Pivot;
	}
	inline void clear()
	{
		DisplayNode.clear();
		Face.clear();
	}
	
	bool Load( const std::string& FileName );
	void Save( const std::string& FileName, std::vector< int > &DrawLayers );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_DisplayMesh_H__ //
// - ------------------------------------------------------------------------------------------ - //
