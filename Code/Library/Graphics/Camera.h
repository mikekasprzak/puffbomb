// - ------------------------------------------------------------------------------------------ - //
// Camera //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_Camera_H__
#define __Util_Camera_H__
// - ------------------------------------------------------------------------------------------ - //
#include <list>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Rect.h>
//#include <Phiz/SphereObject.h>
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
class cCamera
{
public:
	Vector3D Pos;
	Vector3D View;
	Vector3D Up;
	
	Real FovY; // Field Of View Y
	Real Aspect;
	Real NearClip;
	Real FarClip;
	
	Real MinZoom;
	Real MaxZoom;
	
	// A pixel perfect zoom for the highest resolution of each aspect ratio
	Real HudZoom;
	
	// break up the screen into a segment //
	
	Real XPos;
	Real YPos;
	
	Real Width;
	Real Height;
public:
//	std::list< cSphereObject* > Focus;
	Vector2D Focus;
		
//	cSphereObject* RemoveFocus;
	int Delay;
	Vector2D Tracker;

	Vector2D Low;
	Vector2D High;
	
	PairRect2D CameraBounds;

public:
	cCamera(
		const Vector3D _Pos,
		const Vector3D _View,
		const Vector3D _Up,
		const Real _FovY,
		const Real _Aspect,
		const Real _NearClip,
		const Real _FarClip,
		const Real _MinZoom,
		const Real _MaxZoom,
		const Real _HudZoom,
		const Real _XPos,
		const Real _YPos,
		const Real _Width,
		const Real _Height
	 );
	 
	Vector2D GetPos();
	void UpdateTarget( const Vector2D& _Focus );
	void Update();
//	void RemoveTarget( cSphereObject* _NewFocus );
//	void RemoveTarget( cSphereObject* _NewFocus, const int _Delay );

/*

	Vector2D GetPos();
	void NewTarget( cSphereObject* _NewFocus );
	void RemoveTarget( cSphereObject* _NewFocus );
	void RemoveTarget( cSphereObject* _NewFocus, const int _Delay );
*/		 
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Camera_H__ //
// - ------------------------------------------------------------------------------------------ - //
