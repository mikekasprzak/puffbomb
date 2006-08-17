// - ------------------------------------------------------------------------------------------ - //
// LinkageFlags //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_LinkageFlags_H__
#define __Engine2D_Physics_Body2D_LinkageFlags_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cLinkageFlags: public cBasicFlags {
public:
	// - -------------------------------------------------------------------------------------- - //
	// Linkage Flags ---------------- //
	enum {
		flActive = bit0,			// If the Link is active //

		flIgnoreMinimum = bit4,		// Don't solve if the distance is less than my length //
		flIgnoreMaximum = bit5,		// Don't solve if the distance is greater than my length //
	};
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline cLinkageFlags() :
		cBasicFlags( flActive )
	{
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for setting individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_SET_FUNCTION( _flag ) \
	inline cLinkageFlags& Set ## _flag() { \
		Flags |= fl ## _flag; \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_SET_FUNCTION( IgnoreMinimum );
	__FLAG_SET_FUNCTION( IgnoreMaximum );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_SET_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for resetting individual flags ---------------------------------------- - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_RESET_FUNCTION( _flag ) \
	inline cLinkageFlags& Reset ## _flag() { \
		Flags &= ~(fl ## _flag); \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_RESET_FUNCTION( IgnoreMinimum );
	__FLAG_RESET_FUNCTION( IgnoreMaximum );
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
	__FLAG_TEST_FUNCTION( IgnoreMinimum );
	__FLAG_TEST_FUNCTION( IgnoreMaximum );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_TEST_FUNCTION
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_LinkageFlags_H__ //
// - ------------------------------------------------------------------------------------------ - //
