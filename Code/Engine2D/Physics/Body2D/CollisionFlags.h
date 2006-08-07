// - ------------------------------------------------------------------------------------------ - //
// CollisionFlags //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_CollisionFlags_H__
#define __Engine2D_Physics_Body2D_CollisionFlags_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //
//namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cCollisionFlags {
public:
	unsigned int Flags;
	// - -------------------------------------------------------------------------------------- - //
	// Collision Flags ---------------- //
	enum {
		flObject = bit0,	// Collision with a moving object //
		flSphere = bit1,	// Collision with spheres //
		flCylinder = bit2,	// Collision with Cylinders //
		
		flEdge = bit4,		// Collision with an edge of an entity //
		flCorner = bit5,	// Collision with a corner of an entity //
		
		flScenery = bit8,	// A collision with scenery, versus a moving object //
		flPolygon = bit9,	// Collision is with a static polygon //
		//flPoint = bit10,	// Collision with a point on a polygon //
		flBox = bit11,		// Collision with an Axis Aligned Bounding Box //
		
		
		flInside = bit16,	// The centerpoint of the sphere got inside //
		
		flCollision = flObject | flScenery,		// Any Collision //
	};
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline cCollisionFlags() :
		Flags( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline void Clear() {
		Flags = 0;
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for setting individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_SET_FUNCTION( _flag ) \
	inline cCollisionFlags& Set ## _flag() { \
		Flags |= fl ## _flag; \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_SET_FUNCTION( Object );
	__FLAG_SET_FUNCTION( Sphere );
	__FLAG_SET_FUNCTION( Cylinder );
	__FLAG_SET_FUNCTION( Edge );
	__FLAG_SET_FUNCTION( Corner );
	__FLAG_SET_FUNCTION( Scenery );
	__FLAG_SET_FUNCTION( Polygon );
	__FLAG_SET_FUNCTION( Box );
	__FLAG_SET_FUNCTION( Inside );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_SET_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for resetting individual flags ---------------------------------------- - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_RESET_FUNCTION( _flag ) \
	inline cCollisionFlags& Reset ## _flag() { \
		Flags &= ~(fl ## _flag); \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_RESET_FUNCTION( Object );
	__FLAG_RESET_FUNCTION( Sphere );
	__FLAG_RESET_FUNCTION( Cylinder );
	__FLAG_RESET_FUNCTION( Edge );
	__FLAG_RESET_FUNCTION( Corner );
	__FLAG_RESET_FUNCTION( Scenery );
	__FLAG_RESET_FUNCTION( Polygon );
	__FLAG_RESET_FUNCTION( Box );
	__FLAG_RESET_FUNCTION( Inside );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_RESET_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for Testing individual flags ------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_TEST_FUNCTION( _flag ) \
	inline const bool Is ## _flag() const { \
		return Flags & (fl ## _flag); \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_TEST_FUNCTION( Object );
	__FLAG_TEST_FUNCTION( Sphere );
	__FLAG_TEST_FUNCTION( Cylinder );
	__FLAG_TEST_FUNCTION( Edge );
	__FLAG_TEST_FUNCTION( Corner );
	__FLAG_TEST_FUNCTION( Scenery );
	__FLAG_TEST_FUNCTION( Polygon );
	__FLAG_TEST_FUNCTION( Box );
	__FLAG_TEST_FUNCTION( Inside );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_TEST_FUNCTION
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Flag testing function ------------------------------------------------------------------ - //
	inline const bool Is( unsigned int _Flag ) const {
		return Flags & _Flag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If we're in any sort of collision ------------------------------------------------------ - //
	inline const bool Collision() const {
		return Flags != 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_CollisionFlags_H__ //
// - ------------------------------------------------------------------------------------------ - //
