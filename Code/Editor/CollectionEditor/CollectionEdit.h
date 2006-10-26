// - ------------------------------------------------------------------------------------------ - //
// CollectionEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_CollectionEdit_H__
#define __Editor_CollectionEdit_H__
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
class cCollectionEdit : public cEdit {
public:
	Engine2D::cPhysics Physics;
	Engine2D::cDynamicCollection Collection;
	Engine2D::cDynamicComponent Component;
	
	std::string CollBaseDirName;
	std::string CompBaseDirName;
	
	std::vector< std::string > CollectionPath;
	std::vector< std::string > ComponentPath;
		
	size_t CurColl;
	size_t CurComp;
	
public:
	cCollectionEdit();
	~cCollectionEdit();

public:
	// CollectionEdit.cpp //
	void Draw();
	void HudDraw();
	void Step();
	
	Vector2D CalcMousePos();
	void Undo();
	void FindCollCompPaths();
	void UpdatePreviewComp();
	void SwitchComp();
	void SwitchMode();
		
public:
	// CollectionEditText.cpp //
	void DisplayText();
	void DisplayMode();
	void DisplayInfo();
	void DisplayCompInfo();

public:
	// CollectionEditStatic.cpp //
	void StaticAddComp();
	int StaticSingleSelect();
	void StaticSelect();
	void StaticMove();

public:
	// CollectionEditDyn.cpp //

public:
	// CollectionEditNode.cpp //

public:
	// CollectionEditHard.cpp //
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_CollectionEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
