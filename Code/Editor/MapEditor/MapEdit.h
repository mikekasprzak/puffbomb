// - ------------------------------------------------------------------------------------------ - //
// MapEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_MapEdit_H__
#define __Editor_MapEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Global.h>

#include <Physics/Physics.h>
#include <DynamicCollection/DynamicCollection.h>

#include <Graphics/Camera.h>
#include "Editor/Edit.h"
// - ------------------------------------------------------------------------------------------ - //
#define TILE_MODE 1
#define ZONE_MODE 2
#define OBJECT_MODE 3
#define FREE_OBJECT_MODE 4
#define PASSIVE_OBJECT_MODE 5
// - ------------------------------------------------------------------------------------------ - //
class cMapEdit : public cEdit {
public:
/*	Engine2D::cPhysics Physics;
	Engine2D::cDynamicCollection Collection;
	Engine2D::cDynamicComponent Component;
	
	std::string CollBaseDirName;
	std::string CompBaseDirName;
		
	size_t CurColl;
	size_t CurComp;
	size_t CurSelComp;
	
	std::vector< Vector2D > MouseOffset;*/
	
public:
	cMapEdit();
	~cMapEdit();

public:
	// MapEdit.cpp //
	void Draw();
	void HudDraw();
	void Step();
	
	Vector2D CalcMousePos();
	void SwitchColl();
	void SwitchComp();
	void SwitchMode();
	void ActiveAction();
	void Save();
		
public:
	// MapEditText.cpp //
	void DisplayText();
	void DisplayMode();
	void DisplayInfo();
	void DisplayMapInfo();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_CollectionEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
