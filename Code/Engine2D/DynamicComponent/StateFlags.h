// - ------------------------------------------------------------------------------------------ - //
// StateFlags //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_StateFlags_H__
#define __Engine2D_Engine_DynamicComponent_StateFlags_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStateFlags: public cBasicFlags {
public:
	// - -------------------------------------------------------------------------------------- - //
	// State Flags ---------------- //
	enum {
		flActive = bit0,			// Object component exists and acts with world //
		
		flIgnoreFamily = bit1,		// Ignore interactions with other components part of same object //
		flIgnoreObjects = bit2,		// Ignore interactions with other components //
		flIgnoreScenery = bit3,		// Ignore interactions with scenery //
		flIgnoreZones = bit4,		// Ignore interactions with zones //
		flIgnorePassives = bit5,	// Ignore interactions with passive objects //
		flIgnoreImpulses = bit6,	// Ignore interactions with impulses //
		
		flObjectSensor = bit8,		// For interactions with components, treat like a sensor //
		flScenerySensor = bit9,		// For interactions with scenery, treat like a sensor //
	};
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline cStateFlags() :
		cBasicFlags( flActive )
	{
	}
	// - -------------------------------------------------------------------------------------- - //	

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for setting individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_FUNCTION( _flag ) \
	inline cStateFlags& Set ## _flag() { \
		Flags |= fl ## _flag; \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( Active );
	__FLAG_FUNCTION( IgnoreFamily );
	__FLAG_FUNCTION( IgnoreObjects );
	__FLAG_FUNCTION( IgnoreScenery );
	__FLAG_FUNCTION( IgnoreZones );
	__FLAG_FUNCTION( IgnorePassives );
	__FLAG_FUNCTION( IgnoreImpulses );
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for resetting individual flags ---------------------------------------- - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_FUNCTION( _flag ) \
	inline cStateFlags& Reset ## _flag() { \
		Flags &= ~(fl ## _flag); \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( Active );
	__FLAG_FUNCTION( IgnoreFamily );
	__FLAG_FUNCTION( IgnoreObjects );
	__FLAG_FUNCTION( IgnoreScenery );
	__FLAG_FUNCTION( IgnoreZones );
	__FLAG_FUNCTION( IgnorePassives );
	__FLAG_FUNCTION( IgnoreImpulses );
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
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
	__FLAG_FUNCTION( Active );
	__FLAG_FUNCTION( IgnoreFamily );
	__FLAG_FUNCTION( IgnoreObjects );
	__FLAG_FUNCTION( IgnoreScenery );
	__FLAG_FUNCTION( IgnoreZones );
	__FLAG_FUNCTION( IgnorePassives );
	__FLAG_FUNCTION( IgnoreImpulses );
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
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
	__FLAG_FUNCTION( Active );
	__FLAG_FUNCTION( IgnoreFamily );
	__FLAG_FUNCTION( IgnoreObjects );
	__FLAG_FUNCTION( IgnoreScenery );
	__FLAG_FUNCTION( IgnoreZones );
	__FLAG_FUNCTION( IgnorePassives );
	__FLAG_FUNCTION( IgnoreImpulses );
	__FLAG_FUNCTION( ObjectSensor );
	__FLAG_FUNCTION( ScenerySensor );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_StateFlags_H__ //
// - ------------------------------------------------------------------------------------------ - //
