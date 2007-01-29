// - ------------------------------------------------------------------------------------------ - //
// BodyFlags //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_BodyFlags_H__
#define __Engine2D_Engine_DynamicComponent_BodyFlags_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cBodyFlags: public cBasicFlags {
public:
	// - -------------------------------------------------------------------------------------- - //
	// State Flags ---------------- //
	enum {		
		flObjectSensor = bit1,		// For interactions with components, treat like a sensor //
		flScenerySensor = bit2,		// For interactions with scenery, treat like a sensor //
		flImpulseSensor = bit3,		// For interactions with impulses, treat like a sensor //
	};
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline cBodyFlags()
	{
	}
	// - -------------------------------------------------------------------------------------- - //	

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for setting individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_FUNCTION( _flag ) \
	inline cBodyFlags& Set ## _flag() { \
		Flags |= fl ## _flag; \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
	__FLAG_FUNCTION( ImpulseSensor );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for resetting individual flags ---------------------------------------- - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_FUNCTION( _flag ) \
	inline cBodyFlags& Reset ## _flag() { \
		Flags &= ~(fl ## _flag); \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
	__FLAG_FUNCTION( ImpulseSensor );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for Testing individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_FUNCTION( _flag ) \
	inline const bool _flag() const { \
		return Flags & (fl ## _flag); \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
	__FLAG_FUNCTION( ImpulseSensor );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for Testing individual flags only ------------------------------------- - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_FUNCTION( _flag ) \
	inline const bool Only ## _flag() const { \
		return Flags == (fl ## _flag); \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
	__FLAG_FUNCTION( ImpulseSensor );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_BodyFlags_H__ //
// - ------------------------------------------------------------------------------------------ - //
