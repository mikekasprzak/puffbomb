// - ------------------------------------------------------------------------------------------ - //
// Editor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_Editor_H__
#define __Editor_Editor_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include <Geometry/Vector.h>

#include "MapEditor/MapEdit.h"
#include "CollectionEditor/CollectionEdit.h"
#include "Body2DEditor/Body2DEdit.h"
#include "AnimationEditor/AnimationEdit.h"
#include "Mesh2DEditor/Mesh2DEdit.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cEditor {
public:
	// Construct, and require an associated object //
	cEditor( cGame& _Game );
	~cEditor();

public:
	cGame* Game;

	cMapEdit* MapEdit;
	cCollectionEdit* CollectionEdit;
	cBody2DEdit* Body2DEdit;
	cAnimationEdit* AnimationEdit;
	cMesh2DEdit* Mesh2DEdit;

public:	
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Editor_H__ //
// - ------------------------------------------------------------------------------------------ - //
