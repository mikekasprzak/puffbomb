// - ------------------------------------------------------------------------------------------ - //
// CollectionEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_CollectionEdit_H__
#define __Editor_CollectionEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Global.h>

#include <Graphics/Camera.h>
#include "Editor/Edit.h"
// - ------------------------------------------------------------------------------------------ - //
class cCollectionEdit : public cEdit {
public:
	
public:
	cCollectionEdit();
	~cCollectionEdit();

public:
	// CollectionEdit.cpp //
	void Draw();
	void HudDraw();
	void Step();
	
	Vector2D CalcMousePos();
	
public:
	// CollectionEditText.cpp //
	void DisplayText();
	void DisplayMode();
	void DisplayComponentInfo();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_CollectionEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
