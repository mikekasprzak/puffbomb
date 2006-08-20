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

	//bool isDeleteNode;

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
	
	Vector2D CalcMousePos();
	Vector2D CalcUVMousePos();
	
	void Undo();
	void ActiveAction();
	void SwitchMode();
	
public:
	// ComponentEditBodyNode.cpp //
	int BodySingleSelectNode();
	void BodySelectNode();
	void BodyMoveNode();
	void BodyAddNode();
	void BodyDeleteNode();
	void BodyScaleNode();

public:
	// ComponentEditBodySphere.cpp //
	void BodyAddSphere();
	void BodyDeleteSphere();
	void BodyRadius( Real RadiusDiff );
	
public:
	// ComponentEditBodySpring.cpp //
	void BodySelectSpring();
	void BodyAddSpring();
	void BodyDeleteSpring();
	
public:
	// ComponentEditText.cpp //
	void DisplayText();
	void DisplayNodeInfo();
	void DisplayMode();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_ComponentEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
