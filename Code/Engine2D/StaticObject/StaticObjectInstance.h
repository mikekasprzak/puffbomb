// - ------------------------------------------------------------------------------------------ - //
// StaticObjectInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObjectInstance_H__
#define __Engine2D_Engine_StaticObjectInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>

#include "StaticObject.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectInstance {
public:
	// Position of this instance //
	Vector2D Pos;

	// Index of the contents of the instance inside the StaticObject pool //
	cStaticObject* Object;
	
public:
	inline void Draw() {
		Object->Draw( Pos );
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObjectInstance_H__ //
// - ------------------------------------------------------------------------------------------ - //
