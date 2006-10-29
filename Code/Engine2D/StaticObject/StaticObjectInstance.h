// - ------------------------------------------------------------------------------------------ - //
// StaticObjectInstance //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_StaticObjectInstance_H__
#define __Engine2D_Engine_StaticObjectInstance_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>

#include "StaticObject.h"
#include "StaticObjectPool.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectInstance {
public:
	// Index of the contents of the instance inside the StaticObject pool //
	cStaticObject* Object;

	// Position of this instance //
	Vector2D Pos;

public:
	cStaticObjectInstance() {
	}
	
	cStaticObjectInstance( const std::string& FileName, const Vector2D& _Pos = Vector2D::Zero ) :
		Object( StaticObjectPool.Load( FileName ) ),
		Pos( _Pos )
	{
	}

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
