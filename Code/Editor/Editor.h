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
#include "Mesh2DEditor/Mesh2DEdit.h"
#include "AnimationEditor/AnimationEdit.h"
// - ------------------------------------------------------------------------------------------ - //
#define MAP_EDITOR 			4
#define COLLECTION_EDITOR 	5
#define BODY_EDITOR 		6
#define ANIMATION_EDITOR 	7
#define MESH2D_EDITOR 		8

// - ------------------------------------------------------------------------------------------ - //
class cEditor {
public:
	// Construct, and require an associated object //
	cEditor( cGame& _Game );
	~cEditor();

public:
	int CurEditor;

	cGame* Game;

	cMapEdit* MapEdit;
	cMesh2DEdit* Mesh2DEdit;
	cAnimationEdit* AnimationEdit;

public:	
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Editor_H__ //
// - ------------------------------------------------------------------------------------------ - //
