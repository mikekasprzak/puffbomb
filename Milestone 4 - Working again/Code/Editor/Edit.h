// - ------------------------------------------------------------------------------------------ - //
// Editor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_Edit_H__
#define __Editor_Edit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Set.h>
#include <Global.h>

#include <Util/ClassDesigner.h>
#include <Graphics/Camera.h>
// - ------------------------------------------------------------------------------------------ - //
#define MAP_EDITOR 			4
#define COLLECTION_EDITOR 	5
#define COMPONENT_EDITOR 	6
#define ANIMATION_EDITOR 	7
#define MESH2D_EDITOR 		8
// - ------------------------------------------------------------------------------------------ - //
//#include "Mesh2DEditor/Mesh2DInfo.h"
// - ------------------------------------------------------------------------------------------ - //
#define NODE_MODE 				0
#define SPHERE_MODE 			1
#define SPRING_MODE 			2
#define DISPLAY_NODE_MODE		3
#define MESH_NODE_MODE			4
#define PIVOT_HANDLE_MODE 		5
#define FACE_MODE	 			6
#define TEXTURE_MODE 			7
#define DRAWING_ORDER_MODE		8
#define SUPER_MODE 				9
#define COMP_BODY_MODE			10
#define COMP_MESH_MODE			11
#define COLL_STATIC_COMP		12
#define COLL_DYNAMIC_COMP		13
#define COLL_NODE_LINK			14
#define COLL_HARD_NODE			15
#define ANGLE_CONSTRAINTS_MODE 	16
// - ------------------------------------------------------------------------------------------ - //
typedef const unsigned int fl;
// - ------------------------------------------------------------------------------------------ - //
class cEdit {
public:
	// Construct, and require an associated object // 
	cEdit();
	~cEdit();

public:
	cCamera* Camera;
	cCamera* HudCamera;

	//	EventFlags
	// - -------------------------------------------------------------------------------------- - //
	static const fl flDelete;
	static const fl flMove;
	static const fl flScale;
	static const fl flHelp;
	static const fl flMiddleClick;
	static const fl flAutoGridDepth;
	static const fl flSnapToGrid;
	static const fl flisGroupMove;
	static const fl flGlobalIncrease;
	static const fl flGlobalDecrease;
		
	unsigned int EditEventFlags;
	// - -------------------------------------------------------------------------------------- - //

	bool IsHelp;
	
	int ScrollMouseX;
	int ScrollMouseY;

	int ScrollFrame;

	int CurView;
	int LastView;

	Real ScrollSpeed;
	Real Scale;

	Real GridSize;
	Real GridDepth[ 13 ];
	Real GridRange[ 13 ];
	size_t CurrentGridDepth;
	
	Real UVWidth;
	Real UVHeight;
	Real UVScale;
	Real UVZoomOffsetX;
	Real UVZoomOffsetY;
	//size_t CurUVGridDepth;
	bool SnapToGrid;
	bool isGroupMove;
	Vector2D OldMousePos;
	Vector2D CurMousePos;
	
	std::vector< ABSet< Vector3D > > GridVertex;
	std::vector< unsigned int > GridIndices;
	unsigned int GridIndicesSize;

	std::vector< ABSet< Vector3D > > GridVertex2;
	std::vector< unsigned int > GridIndices2;
	unsigned int GridIndicesSize2;
	
	Vector3D TexVertex[4];
	Vector2D TexUV[4];
	unsigned int TexIndices[4];
	
	unsigned int CurMode;
		
	cCamera *LastCamera;
	
	std::vector< unsigned int > TextureID;
	std::vector< std::string > TextureName;

	std::vector<size_t> CurSelected;

	Vector3D SelBoxVertex[4];
	unsigned int SelBoxIndices[5];

public:
	std::string CurrentDir;
	
	std::ostringstream TempStringStream;
	std::string TempString;
	Vector3D TempLocation;

	bool IsSaved;

public:	
	void Scroll( cCamera* MyCamera );
	void Scroll( cCamera* MyCamera, const Real PercentW, const Real PercentH, const Vector2D ZoomInfo );

	void DrawGrid( cCamera* MyCamera, size_t &CurGridDepth, Real GridChange, bool DrawOrig, Real* MyGridDepth );
	void SetGridDepth( cCamera* MyCamera, size_t &CurGridDepth, Real GridChange );
	void SetGridArray( size_t CurGridDepth, Real* MyGridDepth );
	void DrawOrigin();

	void Zoom( Real ScaleAmount, cCamera* MyCamera );
	bool WithinBox( Vector2D &TestPoint, Vector2D &PointA, Vector2D &PointB );
	Vector2D CalcSnapToGrid( Vector2D &TempVec2D, size_t CurGridDepth, Real* MyGridDepth );
	int ArraySize( char * array );
	bool CheckViewOne();
	bool CheckViewTwo( const Real ViewHeight );
	bool CheckViewThree( const Real ViewHeight );
	void LoadTextures();
	int FindTexture( const unsigned int& TempTextureID );
	void DrawSelBox();
	void CalcUVZoomOffset();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Edit_H__ //
// - ------------------------------------------------------------------------------------------ - //
