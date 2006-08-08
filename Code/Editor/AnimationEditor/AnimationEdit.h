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
	
	void ScrollUV();
	void CalcUVZoomOffset();
	Vector2D CalcUVMousePos();
	Vector2D CalcMousePos();
	
	void DrawFrame();
	void DrawSelected();
	void DrawSelBox();
		
	// AnimationEditNode.cpp //
	int SingleSelect();
	void SelectNode();
	void MoveNode();
	void AddNode();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_AnimationEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
