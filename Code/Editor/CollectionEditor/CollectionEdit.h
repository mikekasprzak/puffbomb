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
#include <Game/Global.h>

#include <Graphics/Camera.h>
#include "Editor/Edit.h"
// - ------------------------------------------------------------------------------------------ - //
class cCollectionEdit : public cEdit {
public:
	
public:
	cCollectionEdit();
	~cCollectionEdit();

public:
	void Draw();
	void HudDraw();
	void Step();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_CollectionEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
