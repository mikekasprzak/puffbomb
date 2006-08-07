// - ------------------------------------------------------------------------------------------ - //
// Mesh2DEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_Mesh_Mesh2DEdit_H__
#define __Editor_Mesh_Mesh2DEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/SphereObject.h>
#include <Util/ScriptParser.h>

#include <vector>
#include <string>
#include <sstream>

#include <Engine2D/DisplayMesh.h>

#include "Editor/Edit.h"
#include "Mesh2DInfo.h"
// - ------------------------------------------------------------------------------------------ - //
#define NODE_MODE 				0
#define SPHERE_MODE 			1
#define SPRING_MODE 			2
#define DISPLAY_NODE_MODE		3
#define PIVOT_HANDLE_MODE 		4
#define FACE_MODE	 			5
#define TEXTURE_MODE 			6
#define DRAWING_ORDER_MODE		7
#define SUPER_MODE 				8
// - ------------------------------------------------------------------------------------------ - //
class cMesh2DEdit : public cEdit {
public:
	// Construct, and require an associated object //
	cMesh2DEdit();
	~cMesh2DEdit();
	
public:
	
	cCamera* UVCamera;
	cCamera* PreviewCamera;
	
	std::vector< cSphereObject > Object;
	std::vector< cDisplayMesh > DisplayMesh;
	std::vector< GLuint > TextureID;
	
	// Undo Mesh //		
	std::vector< cMesh2DInfo > Mesh2DInfo;

	std::vector< cStoreMesh > StoreMesh;

	std::vector< std::string > TextureName;

	Real ScrollSpeed;
	size_t CurrentObject;
	size_t CurrentNode;
	size_t CurrentSpring;
	size_t CurrentFace;
		
	bool SnapToGrid;
	bool LeftClicked;
	bool SpringPlacement;
	bool isPaste;
	bool isDelete;
	int EditMode;
	
	int CurLayer;
//	int LowLayer;
//	int HighLayer;
	int LastView;
	int CurView;
	
	Real UVGridDepth[ 13 ];
	
	std::vector< int > DrawLayers;
			
	std::vector<bool> HasSphere;
		
	Vector2D OldMousePos;
	std::vector<size_t> CurSelected;
	bool isGroupMove;
	
public:	
	std::vector<size_t> CurSelUV;

	Vector3D TEXa;
	Vector3D TEXb;
	Vector3D TEXc;
	Vector3D TEXd;
	Vector2D UVa;
	Vector2D UVb;
	Vector2D UVc;
	Vector2D UVd;
	Real UVScale;
//	Real UVZoom;
//	Vector2D UVOrigin;
	size_t CurUVGridDepth;
	Real UVWidth;
	Real UVHeight;
	Real UVZoomOffsetX;
	Real UVZoomOffsetY;
	Real UVScrollMouseX;
	Real UVScrollMouseY;
	bool UVMiddleClick;
	bool UVMiddleClickLast;
	bool isUVGroupMove;
	bool SnapToUVGrid;
	
public:	
	// Mesh2DEdit.cpp //
	void Step();
	void Draw();
	void DrawPreview();
	void HudDraw();
	void DrawTextureCoord();
	void DrawPreviewBox();
	void SwitchMesh();
	void DrawMesh();
	void SwitchMode();
	void DrawSelected();
	Vector2D CalcMousePos();
	void ActiveAction();
	void Undo();
	void DrawGroupAction();
	void ToggleColToDis( int Mode );
	void KeepWithinBox();

public:
	// Mesh2DEditColNode.cpp // 
	void DrawNode( int Color, int Node );
	void DrawColSnapToGrid( size_t Node );
	void SwitchNode();
	void ColAddNode();
	void SetMass( Real MassDiff, int Node );
	void ColSelectNode();
	int ColSingleSelect( Vector2D &CurMousePos );
	void ColMoveNode();
	void ColCopy();
	void ColPaste();
	void ColDeleteNode();
	void ColMass( Real MassDiff );
	void DrawColSelect();
	void ColLockNode();
	bool ColIsLocked( size_t Idx );
	
public:
	// Mesh2DEditColSphere.cpp //
	void DrawSphere( int Color, int SphereNumber );
	void SetRadius( Real RadiusDiff, int Node );
	void AddSphere();
	void DelSphere( int Node );
	void SphereCheck();
	void ColDeleteSphere();
	void ColRadius( Real RadiusDiff );
	void ColAddSphere();

public:
	// Mesh2DEditColSpring.cpp // 
	void DrawSpring( int Color, size_t Spring );
	void SelectSpring();
	void DrawSpringPlacement();
	void ColAddSpring();
	void ColDeleteSpring();
	void SwitchSpring();

public:
	// Mesh2DEditDisNode.cpp // 
	void DisAddNode();
	void DisSelectNode();
	void DrawDisSelect();
	int DisSingleSelect( Vector2D &CurMousePos );
	void DisMoveNode();
	void DrawDisSnapToGrid( size_t Node );
	void DisDeleteNode();
	void DisSetPivot();
	void DisSetHandle();

public:
	// Mesh2DEditText.cpp //
	void DisplayText();
	void DisplayNodeInfo();
	void DisplaySphereInfo();
	void DisplaySpringInfo();
	void DisplayDisNodeInfo();
	void DisplayDisFaceInfo();
	void DisplayTextureInfo();
	void DisplaySuperInfo();
	void DisplayMode();
	void DisplaySavedStatus();
	void DisplayHelp();

public:
	// Mesh2DEditIO.cpp //	
	void OpenCMesh( const std::string &Dir );
	void OpenDMesh( std::string &Dir );
	void LoadTextures();
	void SaveCurrentMesh();
	void SaveDMesh( const char* File );
	
public:
	// Mesh2DEditDisTexture.cpp // 
	void DisChangeTexture();
	void DisAddTexture();
	void DisDeleteTexture();
	void DisDrawUV();
	void DisSelectUV();
	void ZoomUV();
	void ScrollUV();
	Vector2D CalcUVMousePos();
	void DrawDisSelectUV();
	int DisSingleSelectUV( Vector2D &CurMousePos );
	void DisMoveUV();
	void DisRotateUV();
	void DisRotateUVRGB();
	void DisInvertUV();
	void DisChangeLayer();
	void LayerCheck();
	int CheckLow( int ObjectIdx );
	int CheckHigh( int ObjectIdx );
	void CalcUVZoomOffset();
	
public:
	// Mesh2DEditDisFace.cpp // 
	void DrawDisSelectFace();
	void DisAddFace();
	void DisDeleteFace();
	void DisClockwise( cDisplayMesh::cFace &tempFace );
	void SwitchFace();
	void DisSelectFace();
	bool DisFaceInBox( int i, int idx );
	int DisSingleSelectFace( Vector2D &CurMousePos );
};

// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Mesh_Mesh2DEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
