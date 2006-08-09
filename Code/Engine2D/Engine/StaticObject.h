// - ------------------------------------------------------------------------------------------ - //
// StaticObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObject_H__
#define __Engine2D_Engine_StaticObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include "StaticObject/StaticObjectComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObject {
public:
	// Components in this object //
	std::vector< cStaticObjectComponent > Component;	

public:

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_StaticObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
