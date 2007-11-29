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
	PairRect2D ViewArea;
	
	bool IsZoomedOut;
	Real DefaultXViewArea;
	Real DefaultYViewArea;
	
	int ZoomLevel;
	int MaxZoomLevel;

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

public:
	inline void ResetZoom() {
		ZoomLevel = 0;
	}
	
	inline void NextZoom() {
		ZoomLevel++;
		if ( ZoomLevel >= MaxZoomLevel ) {
			ZoomLevel = 0;
		}
	}
	
	inline void PreviousZoom() {
		ZoomLevel--;
		if ( ZoomLevel < 0 ) {
			ZoomLevel = MaxZoomLevel - 1;
		}
	}
	
	inline void SetZoom( const Rect2D& /*_ZoomRect*/ ) {
		// TODO: take a rectangle, and set the zoom to fit it //
	}
	
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Camera_H__ //
// - ------------------------------------------------------------------------------------------ - //
