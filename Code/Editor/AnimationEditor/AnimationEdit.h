// - ------------------------------------------------------------------------------------------ - //
// AnimationEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_AnimationEdit_H__
#define __Editor_AnimationEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Game/Global.h>

#include <Animation/Animation.h>
#include <Graphics/Camera.h>
#include "Editor/Edit.h"

// - ------------------------------------------------------------------------------------------ - //
class cAnimationEdit : public cEdit {
public:
	cCamera* UVCamera;
	cCamera* PreviewCamera;
	
	Real UVWidth;
	Real UVHeight;

public:
	cAnimationEdit();
	~cAnimationEdit();

public:
	void Draw();
	void HudDraw();
	void PreviewDraw();
	void UVDraw();
	void Step();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_AnimationEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
