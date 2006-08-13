// - ------------------------------------------------------------------------------------------ - //
// AnimationEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_AnimationEdit_H__
#define __Editor_AnimationEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Geometry/Set.h>
#include <Global.h>

#include <Animation/Animation.h>
#include <Animation/Animator.h>
#include <Graphics/Camera.h>
#include "Editor/Edit.h"
// - ------------------------------------------------------------------------------------------ - //
/*#define NODE_MODE 0
#define FACE_MODE 1
#define TEXTURE_MODE 2*/
// - ------------------------------------------------------------------------------------------ - //
class cAnimationEdit : public cEdit {
public:
	cCamera* UVCamera;
	cCamera* PreviewCamera;
	
	Real UVWidth;
	Real UVHeight;
	Real UVScale;
	Real UVZoomOffsetX;
	Real UVZoomOffsetY;

	size_t UVCurGridDepth;

	bool SnapToGrid;
	bool isGroupMove;
	bool isDeleteNode;

	std::vector< cAnimation* > Animations;
	cAnimator Animator;
	cFrame* CurFrame;
	unsigned int FrameIdx;
	
	ABCDSet< Vector3D > TexVertex;
	ABCDSet< Vector2D > TexUV;
	unsigned int TexIndices[4];
	
	Vector3D SelBoxVertex[4];
	unsigned int SelBoxIndices[5];
	
	Real NodeRadius;
	
	Vector2D OldMousePos;
	Vector2D CurMousePos;
	
	std::vector<size_t> CurSelected;
	std::vector<size_t> CurSelUV;

public:
	cAnimationEdit();
	~cAnimationEdit();

public:
	// AnimationEdit.cpp //
	void Draw();
	void HudDraw();
	void PreviewDraw();
	void UVDraw();
	void Step();
	
	void Undo();
	void ActiveAction();

	void CalcUVZoomOffset();
	Vector2D CalcUVMousePos();
	Vector2D CalcMousePos();
	
	void DrawFrame();
	void DrawSelected();
	void DrawSelBox();
	
	void SwitchMode();
	void SwitchFrame();

public:
	// AnimationEditNode.cpp //
	int SingleSelectNode();
	void SelectNode();
	void MoveNode();
	void AddNode();
	void DeleteNode();
	
public:
	// AnimationEditFace.cpp //
	void AddFace();
	void DeleteFaceFromNodes();
	void Clockwise( cFrame::cFace &tempFace );
	
public:
	// AnimationEditTexture.cpp //
	void SelectFace();
	bool FaceInBox( int i, int idx );
	int SingleSelectFace();
	void DeleteFaceFromFace();
	void DrawUV();
	void DrawSelectedUV();
	void SelectUV();
	int SingleSelectUV( const Vector2D& CurPos );
	
public:
	// AnimationEditText.cpp //
	void DisplayText();
	void DisplayNodeInfo();
	void DisplayFaceInfo();
	void DisplayTextureInfo();
	void DisplayMode();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_AnimationEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
