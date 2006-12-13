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
			#include <Animation/Animator.h>
			
#define TILE_MODE 1
#define ZONE_MODE 2
#define OBJECT_MODE 3
#define FREE_OBJECT_MODE 4
#define PASSIVE_OBJECT_MODE 5
// - ------------------------------------------------------------------------------------------ - //
class cMapEdit : public cEdit {
public:
	Engine2D::cMap Map;
	Engine2D::cPhysics Physics;

	// Our in game entities //
	std::vector< Engine2D::cDynamicCollection* > DynamicCollection;
	std::vector< Engine2D::cStaticObjectInstance > StaticObjectInstance;
	std::vector< Engine2D::cPassiveObject* > PassiveObject;
	std::vector< Engine2D::cZone > Zone;

	std::string MapBaseDirName;
	std::vector< std::string > MapPath;
	size_t CurMap;

	// Tile //
	// - -------------------------------------------------------------------------------------- - //
	std::string Mesh3DBaseDirName;
	std::vector< std::string > Mesh3DName;

	Engine2D::cStaticObjectInstance Mesh3DPreview;
	
	size_t CurMesh3D;
	
	int CurLayer;

	// Dynamic //
	// - -------------------------------------------------------------------------------------- - //
	std::vector< int > ActiveDyns;
	
	Engine2D::cDynamicCollection* DynPreview;
	
	size_t CurDyn;
	
	size_t CurSelColl;
	size_t CurSelComp;
	
	std::vector< Vector2D > MouseOffset;
	
	// Passive //
	// - -------------------------------------------------------------------------------------- - //
	std::vector< int > ActivePass;
	
	size_t CurPass;
		
	
	// Zone //
	// - -------------------------------------------------------------------------------------- - //
	size_t CurZone;

	Real CornerSize;
	int ResizeCorner;
	std::vector< std::string > ZoneDesc;

		
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
	void LoadMap();
	void SaveMap();
	void FindMapMesh3DPaths();
	void Reset();
		
public:
	// MapEditText.cpp //
	void DisplayText();
	void DisplayMode();
	void DisplayInfo();
	void DisplayMapInfo();
	void DisplayZoneInfo();

public:
	// MapEditTile.cpp //
	void SelectMesh3D();
	void MoveMesh3D();
	void AddMesh3D();
	void DeleteMesh3D();
	void UpdateMesh3DPreview();
	void SwitchMesh3D();
	void SwitchLayer();

public:
	// MapEditDyn.cpp //
	int SingleSelectDyn();
	void SelectDyn();
	void MoveDyn();
	void AddDyn();
	void DeleteDyn();
	void UpdateDynPreview();
	void SwitchDyn();
	
	int SingleSelectDynFree();
	void SelectDynFree();
	void MoveDynFree();

public:
	// MapEditPass.cpp //
	void SelectPass();
	void MovePass();
	void AddPass();
	void DeletePass();
	void SwitchPass();

public:
	// MapEditZone.cpp //
	void DrawZones();
	void DrawSelZone();
	void SwitchZone();
	void SelectZone();
	void MoveZone();
	void ResizeZone();
	void AddZone();
	void DeleteZone();
	void ChangeID();
	void ChangeArg();
	void LoadZoneDesc();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_CollectionEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
