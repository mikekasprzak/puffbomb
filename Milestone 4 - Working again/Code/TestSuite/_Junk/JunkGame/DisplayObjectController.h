// - ------------------------------------------------------------------------------------------ - //
// DisplayObjectController //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_DisplayObjectController_H__
#define __Game_DisplayObjectController_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Matrix.h>

#include "ObjectController.h"
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cDisplayObjectController: public cObjectController {
public:
	// - -------------------------------------------------------------------------------------- - //	
	class cVertex: public Vector2D {
	public:
		cVertex( const Vector2D& _Vector, int _Orientation ) :
			Vector2D( _Vector ),
			Orientation( _Orientation )
		{
		}
				
		int Orientation;
	};
	// - -------------------------------------------------------------------------------------- - //	
	class cFace {
	public:
		ABCSet<int>	Index;
		ABCSet<Vector2D> UV;
		Real z;
		
		cFace( const ABCSet<int>& _Index, const ABCSet<Vector2D>& _UV, const Real& _z ) :
			Index( _Index ),
			UV( _UV ),
			z( _z )
		{
		}
	};
	// - -------------------------------------------------------------------------------------- - //	
	class cOrientation {
	public:
		Matrix2x2 HomeMatrix;
		Matrix2x2 Matrix;
		int Pivot;
		int Handle;
		
		cOrientation( const int& _Pivot, const int& _Handle ) :
			Pivot( _Pivot ),
			Handle( _Handle )
		{
		}

		void CalculateHomeMatrix( cDynamicNodes& Node ) {
			Vector2D Line = Node.Pos( Handle ) - Node.Pos( Pivot );
			Line.Normalize();
			
			HomeMatrix[ 0 ] = Line.x;
			HomeMatrix[ 1 ] = Line.y;
			HomeMatrix[ 2 ] = Line.Tangent().x;
			HomeMatrix[ 3 ] = Line.Tangent().y;
			
			HomeMatrix = HomeMatrix.Inverse();
		}
		
		void CalculateMatrix( cDynamicNodes& Node ) {
			Vector2D Line = Node.Pos( Handle ) - Node.Pos( Pivot );
			Line.Normalize();
			
			Matrix[ 0 ] = Line.x;
			Matrix[ 1 ] = Line.y;
			Matrix[ 2 ] = Line.Tangent().x;
			Matrix[ 3 ] = Line.Tangent().y;
		}
	};
	// - -------------------------------------------------------------------------------------- - //	
public:	
	// - -------------------------------------------------------------------------------------- - //	
	std::vector< cVertex >		Vertex;
	std::vector< cFace >		Face;

	std::vector< cOrientation >	Orientation;
		
	unsigned int TextureId;
	// - -------------------------------------------------------------------------------------- - //	
public:	
	cDisplayObjectController( cSphereObject* _Object, const std::string& File );
	virtual ~cDisplayObjectController();
	virtual void Draw();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_DisplayObjectController_H__ //
// - ------------------------------------------------------------------------------------------ - //
