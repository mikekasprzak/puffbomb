// - ------------------------------------------------------------------------------------------ - //
// MapEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_Map_MapEdit_H__
#define __Editor_Map_MapEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Editor/Edit.h>
#include "Game.h"

#include "MapObject.h"
#include <Editor/Mesh2DEditor/Mesh2DEdit.h>
#include <Engine2D/DisplayMesh.h>
#include <Graphics/LevelData.h>

#include <vector>
#include <string>
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
#define OBJECT_MODE 1
#define ZONE_MODE 2
#define TILE_MODE 3
// - ------------------------------------------------------------------------------------------ - //
class cMapEdit : public cEdit {
public:
	// Construct, and require an associated SphereObject //
	cMapEdit( cGame& _Game, cMesh2DEdit& _Mesh2DEdit );

public:
	cGame* Game;
	cMesh2DEdit* Mesh2DEdit;
	
	std::string MapName;
	std::string DirMapName;
	//std::string MapModel;
	int CurModel;
	std::vector< cLevelData > ModelList;
	std::vector< std::string > ModelNameList;
	
	std::vector< cLevelData > Model;
	std::vector< std::string > ModelName;
	
	Real GameZoom;
	Vector2D Focus;
	
	int CurMesh;
	
	//std::vector< int > SceneryIdx;
	int SceneryIdx;
	
	size_t CurrentObject;
	std::vector<size_t> CurSelected;
	
	std::vector<cMapObject> MapObject;
	std::vector<cMapObject> CopyStorage;
		
	std::vector< cUndoObject > UndoObject;
	std::vector< cUndoObject > RedoObject;
		
	Vector2D OldMousePos;
	
	int Focus1;
	int Focus2;
	
	bool SnapToGrid;
	bool isGroupMove;
	bool isPaste;
	bool isSaved;

	unsigned int CurZone;

	int CurMode;
	
	Real CornerSize;
	int ResizeCorner;
	std::vector< std::string > ZoneDesc;
	
public:	
	// MapEdit.cpp //
	~cMapEdit();
	void Step();
	void Draw();
	void HudDraw();
	
	void Draw2D();
	void DrawMesh( int idx, Vector2D MapPos );

	void ToggleEdit();
	void ToggleGame();

	void Physics();
	
	Vector2D CalcMousePos();
	void DrawSelected();
	void DrawSelBox();
	
	void SelectObject();
	int SingleSelect( Vector2D &CurMousePos );
	void MoveObject();
	void DrawSnapToGrid( size_t idx );
	void AddObject();
	void DeleteObject();
	void SwitchMesh();
	
	void CopyObject();
	void PasteObject();
	
	void ActiveAction();
	void Undo();

	void SetFocus();
	
	void SwitchMode();
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

public:	
	// MapEditTile.cpp //
	void DrawSelModel();
	void SwitchModel();
	void SelectModel();
	void MoveModel();
	void AddModel();
	void DeleteModel();
	
public:	
	// MapEditIO.cpp //
	void LoadMap( std::string &Dir );
	void SaveMap( const char* File );
	void ListModels();
	void LoadZoneDesc();
	
public:	
	// MapEditText.cpp //
	void DisplayText();
	void DisplaySavedStatus();
	void DisplayHelp();
	void DisplayMesh2DInfo();
	void DisplayZoneInfo();
	void DisplayMapName();
	void DisplayMesh3dName();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Map_MapEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
