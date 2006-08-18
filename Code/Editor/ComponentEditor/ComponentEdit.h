// - ------------------------------------------------------------------------------------------ - //
// ComponentEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_ComponentEdit_H__
#define __Editor_ComponentEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Global.h>

#include <Graphics/Camera.h>
#include "Editor/Edit.h"

#include <Physics/Body2D.h>
// - ------------------------------------------------------------------------------------------ - //
class cComponentEdit : public cEdit {
public:
	cCamera* UVCamera;
	cCamera* PreviewCamera;


public:
	// Body2D //
	std::vector< Engine2D::cBody2D > Body2D;
	size_t CurBody;
	Real NodeRadius;

	bool isDeleteNode;

public:
	cComponentEdit();
	~cComponentEdit();

public:
	// ComponentEdit.cpp //
	void Draw();
	void HudDraw();
	void PreviewDraw();
	void UVDraw();
	void Step();
	void DrawSelected();
	
	Vector2D CalcMousePos();
	Vector2D CalcUVMousePos();
	
	void Undo();
	void ActiveAction();
public:
	// ComponentEditNode.cpp //
	int SingleSelectNode();
	void SelectNode();
	void MoveNode();
	void AddNode();
	void DeleteNode();
	void ScaleNode();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_ComponentEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
