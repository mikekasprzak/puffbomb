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
#include <Global.h>
#include <Geometry/Vector.h>
#include <Graphics/Camera.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicCollection/DynamicCollection.h>
#include <StaticObject/StaticObjectInstance.h>
#include <PassiveObject/PassiveObject.h>
#include <Zone/Zone.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Map/Map.h>
// - ------------------------------------------------------------------------------------------ - //
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
	Engine2D::cMap Map;

	// Our in game entities //
	std::vector< Engine2D::cDynamicCollection* > DynamicCollection;
	std::vector< Engine2D::cStaticObjectInstance > StaticObjectInstance;
	std::vector< Engine2D::cPassiveObject* > PassiveObject;
	std::vector< Engine2D::cZone* > Zone;

	std::string MapBaseDirName;
		
	std::vector< std::string > MapPath;
		
	size_t CurMap;
		
public:
	cMapEdit();
	~cMapEdit();

public:
	// MapEdit.cpp //
	void Draw();
	void HudDraw();
	void Step();
	
	Vector2D CalcMousePos();
	void SwitchMap();
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
