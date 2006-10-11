// - ------------------------------------------------------------------------------------------ - //
// Camera //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Camera_H__
#define __Engine2D_Camera_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
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
public:
//	int Delay;
//	Vector2D Tracker;
//
//	Vector2D Low;
//	Vector2D High;
	
	PairRect2D CameraBounds;

public:
	cCamera() {}
	
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
		const Real _HudZoom
	 );
	 
//	Vector2D GetPos();
//	void NewTarget( cSphereObject* _NewFocus );
//	void RemoveTarget( cSphereObject* _NewFocus );
//	void RemoveTarget( cSphereObject* _NewFocus, const int _Delay );
		 
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Camera_H__ //
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
