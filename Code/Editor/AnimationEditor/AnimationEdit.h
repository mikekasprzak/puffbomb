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
class cAnimationEdit : public cEdit {
public:
	cCamera* UVCamera;
	cCamera* PreviewCamera;
	
	Real UVWidth;
	Real UVHeight;
	Real UVScale;
	Real UVZoomOffsetX;
	Real UVZoomOffsetY;
	
	std::vector< cAnimation* > Animations;
	cAnimator Animator;
	cFrame* CurFrame;
	unsigned int FrameIdx;
	
	ABCDSet< Vector3D > TexVertex;
	ABCDSet< Vector2D > TexUV;
	unsigned int TexIndices[4];
	
	Real NodeRadius;
	
	Vector2D OldMousePos;

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
	
	void ScrollUV();
	void CalcUVZoomOffset();
	Vector2D CalcUVMousePos();
	Vector2D CalcMousePos();
	
	void DrawFrame();
	
	// AnimationEditNode.cpp //
	void SelectNode();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_AnimationEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
