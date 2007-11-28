// - ------------------------------------------------------------------------------------------ - //
// StaticObjectInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObjectInstance_H__
#define __Engine2D_Engine_StaticObjectInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>

#include "StaticObject.h"
#include "StaticObjectPool.h"

#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectInstance {
public:
	// Index of the contents of the instance inside the StaticObject pool //
	cStaticObject* Object;

	// Position of this instance //
	Vector2D Pos;
	
	// Edge Testing Flags //
	std::vector< bool > UsedEdge;
		
		
	// * NEW * //
	
	// Orientation -- As the name says, it's an orientation matrix.  This allows us to reorient //
	// a generally static object, at per instance level (since the matrix is inside the instance).//
	// Both the collision and the display need to be transformed by the matrix.  You can rotate, //
	// Scale, and Skew with this matrix.  Position, well, move the damn thing! //
	Matrix2x2 Orientation;
	
	// IsInverted -- A flag identifying that such a tranformation is occuring in the orientation //
	// matrix, that we need to interpret our various winding orders (polygon drawing, and //
	// collision) to be the opposite of what it is.  Without this, we can't correctly mirror //
	// an object, without it dissapearing, and collision acting wrong. //
	// This is due to the way both are implemented, and cannot be solved due to transformation //
	// magic.  You'd have to change how "Tangent()" works on the fly, and how graphics hardware //
	// works.  Though technically, if backface drawing is on, you can make it work. //
	bool IsInverted;
	
	// Default matrix should be //
	// [ 1 0 ] //
	// [ 0 1 ] //
	
	// Flips and Mirrors should be implemented by toggling the IsInverted flag, and multiplying //
	// one of the following respected matricies by the current orientation matrix //
	// [-1 0 ]  [ 1 0 ] //
	// [ 0 1 ]  [ 0 -1] //
	
	// * NEW * //

public:
	cStaticObjectInstance() {
	}
	
	cStaticObjectInstance( const std::string& FileName, const Vector2D& _Pos = Vector2D::Zero ) :
		Object( StaticObjectPool.Load( FileName ) ),
		Pos( _Pos ),
		UsedEdge( Object->Body.Edge.size(), true )
	{
	}

public:
	inline void Draw() {
		Object->Draw( Pos );
	}

	inline void DrawBody() {
		std::vector< size_t > Selection;
			
		Object->Body.DrawBoundingRect( false, Pos );
		
		Object->Body.DrawPolygonRects( Selection, Pos );
		Object->Body.DrawEdgeRects( Selection, Pos );
		Object->Body.DrawPolygons( Selection, Pos );
		Object->Body.DrawEdges( Selection, Pos );
		Object->Body.DrawNodes( Selection, Pos );
	}

	inline void DrawThickEdges( ) const {
		Gfx::SetLineWidth( 4 );
			
		Vector3D Offset( Pos.x, Pos.y, GetFrontPolygonZ() );
		
		// For every edge //
		for ( size_t idx = 0; idx < UsedEdge.size(); idx++ ) {
			if ( UsedEdge[ idx ] )
				Object->Body.DrawThickEdge( idx, Offset );
		}
		
		Gfx::SetLineWidth( 1 );
	}

	inline const Real GetFrontPolygonZ() const {
		// Get the front Z of the bounding rectangle.  Adding zero, 'cause Z offset would be 0. //
		return Object->BoundingRect.P2().z + Real::Zero;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObjectInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
