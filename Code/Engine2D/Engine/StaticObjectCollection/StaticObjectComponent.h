// - ------------------------------------------------------------------------------------------ - //
// StaticObjectComponent //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObjectCollection_StaticObjectComponent_H__
#define __Engine2D_Engine_StaticObjectCollection_StaticObjectComponent_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/StaticBody2D.h>
// Update this one day.  This should replace the general purpose "Mesh3D" under library/graphics //
#include <Engine2D/Graphics/Mesh3D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectComponent {
public:
	// Collision //
	cStaticBody2D Body;
	
	// Display //
	// *Note* make display a vector, therefor supporting multiple textures (since each is only 1) //
	cMesh3D Mesh;
	
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObjectCollection_StaticObjectComponent_H__ //
// - ------------------------------------------------------------------------------------------ - //
