// - ------------------------------------------------------------------------------------------ - //
// StaticObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_StaticObject_H__
#define __Phiz_StaticObject_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>

#include "StaticNodes.h"

//#include "Constraints/Box.h"
//#include "Constraints/Triangle.h"
//#include "Constraints/Quad.h"
//#include "Constraints/Polygon.h"

#include "Constraints/StaticPolygon.h"
#include "Constraints/StaticEdge.h"
// - ------------------------------------------------------------------------------------------ - //
//#include <FileIO/ScriptParser.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cStaticObject: public cStaticNodes {
public:
//	std::vector< cBox > 		Box;
//	std::vector< cTriangle >	Triangle;
//	std::vector< cQuad >		Quad;
//	std::vector< cPolygon >		Polygon;

	std::vector< cStaticPolygon >	Polygon;
	std::vector< cStaticEdge >		Edge;

public:	
	// Bounding Rectangle of all colliding objects //
	typedef RadiusRect2D RectType;
	RectType BoundingRect;
	
	// Ammount of Friction to give to object that collide with me //
	Real Friction;
public:
	// - -------------------------------------------------------------------------------------- - //
	cStaticObject( const size_t& _NodeCount ) :
		cStaticNodes( _NodeCount ),
		Edge( _NodeCount ),
		Friction( cPhysics::SurfaceFriction )
	{
	}
	//cStaticObject( const cScriptParser& Obj, Real _x, Real _y );
	// - -------------------------------------------------------------------------------------- - //
	// Should probably take a camera or camera matrix as an argument //
	void DebugDraw( /*const Vector2D& Offset*/ );
	// - -------------------------------------------------------------------------------------- - //
	void CalcBoundingRect();
	// - -------------------------------------------------------------------------------------- - //
	void Refresh();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_StaticObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
