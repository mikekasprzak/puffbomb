// - ------------------------------------------------------------------------------------------ - //
// ComponentEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_ComponentEdit_H__
#define __Editor_ComponentEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Global.h>

#include <Graphics/Camera.h>
#include "Editor/Edit.h"

// - ------------------------------------------------------------------------------------------ - //
class cComponentEdit : public cEdit {
public:
	cCamera* PreviewCamera;
	
	Real PreviewWidth;
	Real PreviewHeight;

public:
	cComponentEdit();
	~cComponentEdit();

public:
	void Draw();
	void HudDraw();
	void PreviewDraw();
	void Step();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_ComponentEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
