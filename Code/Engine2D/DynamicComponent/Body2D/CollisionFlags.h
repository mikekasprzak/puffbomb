// - ------------------------------------------------------------------------------------------ - //
// CollisionFlags //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_Constraints_CollisionFlags_H__
#define __Engine2D_Physics_Body2D_Constraints_CollisionFlags_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cCollisionFlags: public cBasicFlags {
public:
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
		
		flImpulse = bit17,	// The collision involved an impulse //		
	};
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline cCollisionFlags() :
		cBasicFlags( 0 )
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
	#define __FLAG_FUNCTION( _flag ) \
	inline cCollisionFlags& Set ## _flag() { \
		Flags |= fl ## _flag; \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( Object );
	__FLAG_FUNCTION( Sphere );
	__FLAG_FUNCTION( Cylinder );
	__FLAG_FUNCTION( Edge );
	__FLAG_FUNCTION( Corner );
	__FLAG_FUNCTION( Scenery );
	__FLAG_FUNCTION( Polygon );
	__FLAG_FUNCTION( Box );
	__FLAG_FUNCTION( Inside );
	__FLAG_FUNCTION( Impulse );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Create functions for resetting individual flags ---------------------------------------- - //
	// - -------------------------------------------------------------------------------------- - //
	#define __FLAG_FUNCTION( _flag ) \
	inline cCollisionFlags& Reset ## _flag() { \
		Flags &= ~(fl ## _flag); \
		return *this; \
	}
	// - -------------------------------------------------------------------------------------- - //
	__FLAG_FUNCTION( Object );
	__FLAG_FUNCTION( Sphere );
	__FLAG_FUNCTION( Cylinder );
	__FLAG_FUNCTION( Edge );
	__FLAG_FUNCTION( Corner );
	__FLAG_FUNCTION( Scenery );
	__FLAG_FUNCTION( Polygon );
	__FLAG_FUNCTION( Box );
	__FLAG_FUNCTION( Inside );
	__FLAG_FUNCTION( Impulse );
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
	__FLAG_FUNCTION( Object );
	__FLAG_FUNCTION( Sphere );
	__FLAG_FUNCTION( Cylinder );
	__FLAG_FUNCTION( Edge );
	__FLAG_FUNCTION( Corner );
	__FLAG_FUNCTION( Scenery );
	__FLAG_FUNCTION( Polygon );
	__FLAG_FUNCTION( Box );
	__FLAG_FUNCTION( Inside );
	__FLAG_FUNCTION( Impulse );
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
	__FLAG_FUNCTION( Object );
	__FLAG_FUNCTION( Sphere );
	__FLAG_FUNCTION( Cylinder );
	__FLAG_FUNCTION( Edge );
	__FLAG_FUNCTION( Corner );
	__FLAG_FUNCTION( Scenery );
	__FLAG_FUNCTION( Polygon );
	__FLAG_FUNCTION( Box );
	__FLAG_FUNCTION( Inside );
	__FLAG_FUNCTION( Impulse );
	// - -------------------------------------------------------------------------------------- - //
	#undef __FLAG_FUNCTION
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// If we're in any sort of collision ------------------------------------------------------ - //
	inline const bool Collision() const {
		return Flags != 0;
	}
	// - -------------------------------------------------------------------------------------- - //	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Constraints_CollisionFlags_H__ //
// - ------------------------------------------------------------------------------------------ - //
