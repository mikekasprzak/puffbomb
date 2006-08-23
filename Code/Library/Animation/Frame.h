// - ------------------------------------------------------------------------------------------ - //
// Frame //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_Frame_H__
#define __Rendo_Frame_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Set.h>
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
class cFrame
{
public:
	class cFace
	{
	public:
		ABCSet<int> VertexIdx;
		ABCSet<Vector2D> UV;
	public:
		cFace( const ABCSet< int >& _VertexIdx, const ABCSet< Vector2D >& _UV ) :
			VertexIdx( _VertexIdx ),
			UV( _UV )
		{
			
		}
		cFace()
		{
			
		}
	};
	
	class cVertex
	{
	public:
		Vector2D Pos;
	public:
		cVertex( const Vector2D& _Pos ) :
			Pos( _Pos )
		{
			
		}

	};

public:
	std::vector< cVertex > Vertex;
	std::vector< cFace > Face;

	unsigned int TextureId;
		
public:
	cFrame()
	{
		
	}	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_Frame_H__ //
// - ------------------------------------------------------------------------------------------ - //
