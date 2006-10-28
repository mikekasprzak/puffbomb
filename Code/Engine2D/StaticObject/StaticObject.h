// - ------------------------------------------------------------------------------------------ - //
// StaticObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObject_H__
#define __Engine2D_Engine_StaticObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include "StaticBody2D/StaticBody2D.h"
// Update this one day.  This should replace the general purpose "Mesh3D" under library/graphics //
#include "Mesh3D/Mesh3D.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObject {
public:
	// Collision //
	cStaticBody2D Body;
	
	// Display //
	std::vector< cMesh3D > Mesh;
	
	// The block of binary data, as read from the file //
	char* Buffer;


public:
	cStaticObject() {
	}

	cStaticObject( const std::string& File ) {
	}

public:
	inline void Draw() {
	//	Mesh.Draw( Body );
	}

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
