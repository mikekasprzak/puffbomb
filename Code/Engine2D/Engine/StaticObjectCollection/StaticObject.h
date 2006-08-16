// - ------------------------------------------------------------------------------------------ - //
// StaticObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObjectCollection_StaticObject_H__
#define __Engine2D_Engine_StaticObjectCollection_StaticObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/StaticBody2D.h>
// Update this one day.  This should replace the general purpose "Mesh3D" under library/graphics //
#include <Engine2D/Graphics/Mesh3D.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObject {
public:
	cStaticBody2D Body;
	cMesh3D Mesh;
	
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObjectCollection_StaticObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
