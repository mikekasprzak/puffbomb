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
