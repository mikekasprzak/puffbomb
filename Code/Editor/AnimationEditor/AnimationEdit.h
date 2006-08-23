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
	
	bool isDeleteNode;

	bool isScaleNode;
	bool isRotateNode;

	std::vector< cAnimation* > Animations;
	cAnimator Animator;
	cFrame* CurFrame;
	unsigned int FrameIdx;
	
	Real NodeRadius;
	
//	std::vector<size_t> CurSelected;
	std::vector<size_t> CurSelUV;
		
	int CurTexIdx;

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
	
	void SwitchMode();
	void SwitchFrame();
	void AddFrame();

public:
	// AnimationEditNode.cpp //
	int SingleSelectNode();
	void SelectNode();
	void MoveNode();
	void AddNode();
	void DeleteNode();
	void ScaleNode();
	void RotateNode();
	
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
	void MoveUV();
	void RotateUV();
	void RotateUVRGB();
	void InvertUV();
	void SwitchTexture();
	
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
