// - ------------------------------------------------------------------------------------------ - //
// StaticObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObject_H__
#define __Engine2D_Engine_StaticObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include "StaticBody2D/StaticBody2D.h"
#include <Graphics/Mesh3D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObject {
public:
	// Collision //
	cStaticBody2D Body;
	
	// Display //
	std::vector< cMesh3D > Mesh;
	
	// The block of binary Mesh, as read from the file //
	char* Buffer;

	// - -------------------------------------------------------------------------------------- - //
	typedef Rect3D RectType;
	RectType BoundingRect;
	// - -------------------------------------------------------------------------------------- - //

public:
	cStaticObject() {
	}

	cStaticObject( const std::string& File ) {
		Load( File );
		Body.GenerateCollision( Mesh );
	}

public:
	void Draw( const Vector2D& Offset = Vector2D::Zero );
	
	void Load( const std::string& FileName );
		
	inline void CalcBoundingRect() {
		Vector3D P1 = (*Mesh[0].Vertex)[0];
		Vector3D P2 = (*Mesh[0].Vertex)[0];
		
		for ( size_t idx = 0; idx < Mesh.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Mesh[idx].Vertex->Size(); idx2++ ) {
				P1 = (*Mesh[idx].Vertex)[idx2].Min( P1 );
				P2 = (*Mesh[idx].Vertex)[idx2].Max( P2 );

			}
		}
		
		BoundingRect = RectType::Pair( P1, P2 );
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
