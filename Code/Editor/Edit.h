// - ------------------------------------------------------------------------------------------ - //
// Editor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_Edit_H__
#define __Editor_Edit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Game/Global.h>

#include <Graphics/Camera.h>

#include "Mesh2DEditor/Mesh2DInfo.h"
// - ------------------------------------------------------------------------------------------ - //
class cEdit {
public:
	// Construct, and require an associated object //
	cEdit();
	~cEdit();

public:
	cCamera* Camera;
	cCamera* HudCamera;

	bool IsHelp;
	
	bool MiddleClick;
	bool MiddleClickLast;

	bool AutoGridDepth;

	int ScrollMouseX;
	int ScrollMouseY;
	int ScrollFrame;

	Real ScrollSpeed;
	Real Scale;

	Real GridSize;
	Real GridDepth[ 13 ];
	Real GridRange[ 13 ];
	size_t CurrentGridDepth;
	
	std::vector< ABSet< Vector3D > > GridVertex;
	std::vector< unsigned int > GridIndices;
	unsigned int GridIndicesSize;

	std::vector< ABSet< Vector3D > > GridVertex2;
	std::vector< unsigned int > GridIndices2;
	unsigned int GridIndicesSize2;
	
	cCamera *LastCamera;
	
	
public:
	std::string CurrentDir;
	
	std::ostringstream TempStringStream;
	std::string TempString;
	Vector3D TempLocation;
	
public:	
	void Scroll( cCamera* MyCamera );

	void DrawGrid( cCamera* MyCamera, size_t &CurGridDepth, Real GridChange, bool DrawOrig, Real* MyGridDepth );
	void SetGridArray( size_t CurGridDepth, Real* MyGridDepth );
	void DrawOrigin();

	void Zoom( Real ScaleAmount, cCamera* MyCamera );
	bool WithinBox( Vector2D &TestPoint, Vector2D &PointA, Vector2D &PointB );
	Vector2D CalcSnapToGrid( Vector2D &TempVec2D, size_t CurGridDepth, Real* MyGridDepth );
	int ArraySize( char * array );
	bool CheckViewOne();
	bool CheckViewTwo( const Real ViewHeight );
	bool CheckViewThree( const Real ViewHeight );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Edit_H__ //
// - ------------------------------------------------------------------------------------------ - //
