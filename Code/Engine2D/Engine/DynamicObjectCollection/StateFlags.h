// - ------------------------------------------------------------------------------------------ - //
// StateFlags //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicObject_StateFlags_H__
#define __Engine2D_Engine_DynamicObject_StateFlags_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStateFlags {
public:
	unsigned int Flags;
	// - -------------------------------------------------------------------------------------- - //
	// State Flags ---------------- //
	enum {
		flActive = bit0,		// Object component exists and acts with world //
		
		flIgnoreFamily = bit1,	// Ignore interactions with other components part of same object //
		flIgnoreObjects = bit2,	// Ignore interactions with other components //
		flIgnoreScenery = bit3,	// Ignore interactions with scenery //
		flIgnoreZones = bit4,	// Ignore interactions with zones //
		flIgnorePassives = bit5,// Ignore interactions with passive objects //
		flIgnoreImpulses = bit6,// Ignore interactions with impulses //
	};
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline cStateFlags() :
		Flags( flActive )
	{
	}
	// - -------------------------------------------------------------------------------------- - //	

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for setting individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_SET_FUNCTION( _flag ) \
	inline cStateFlags& Set ## _flag() { \
		Flags |= fl ## _flag; \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_SET_FUNCTION( Active );
	__FLAG_SET_FUNCTION( IgnoreFamily );
	__FLAG_SET_FUNCTION( IgnoreObjects );
	__FLAG_SET_FUNCTION( IgnoreScenery );
	__FLAG_SET_FUNCTION( IgnoreZones );
	__FLAG_SET_FUNCTION( IgnorePassives );
	__FLAG_SET_FUNCTION( IgnoreImpulses );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_SET_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for resetting individual flags ---------------------------------------- - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_RESET_FUNCTION( _flag ) \
	inline cStateFlags& Reset ## _flag() { \
		Flags &= ~(fl ## _flag); \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_RESET_FUNCTION( Active );
	__FLAG_RESET_FUNCTION( IgnoreFamily );
	__FLAG_RESET_FUNCTION( IgnoreObjects );
	__FLAG_RESET_FUNCTION( IgnoreScenery );
	__FLAG_RESET_FUNCTION( IgnoreZones );
	__FLAG_RESET_FUNCTION( IgnorePassives );
	__FLAG_RESET_FUNCTION( IgnoreImpulses );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_RESET_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for Testing individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_TEST_FUNCTION( _flag ) \
	inline const bool _flag() const { \
		return Flags & (fl ## _flag); \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_TEST_FUNCTION( Active );
	__FLAG_TEST_FUNCTION( IgnoreFamily );
	__FLAG_TEST_FUNCTION( IgnoreObjects );
	__FLAG_TEST_FUNCTION( IgnoreScenery );
	__FLAG_TEST_FUNCTION( IgnoreZones );
	__FLAG_TEST_FUNCTION( IgnorePassives );
	__FLAG_TEST_FUNCTION( IgnoreImpulses );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_TEST_FUNCTION
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Flag testing function ------------------------------------------------------------------ - //
	inline const bool Is( unsigned int _Flag ) const {
		return Flags & _Flag;
	}
	// - -------------------------------------------------------------------------------------- - //	
	// Return true if you are only Active, so not to do othe work //
	inline const bool OnlyActive() const {
		return (Flags == flActive);
	}
	// - -------------------------------------------------------------------------------------- - //	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicObject_StateFlags_H__ //
// - ------------------------------------------------------------------------------------------ - //
