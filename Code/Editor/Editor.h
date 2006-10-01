// - ------------------------------------------------------------------------------------------ - //
// Editor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_Editor_H__
#define __Editor_Editor_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//#include "Game.h"
#include <Geometry/Vector.h>

#include "MapEditor/MapEdit.h"
#include "CollectionEditor/CollectionEdit.h"
#include "ComponentEditor/ComponentEdit.h"
#include "AnimationEditor/AnimationEdit.h"
//#include "Mesh2DEditor/Mesh2DEdit.h"
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
class cEditor : public cMessageEntity {
public:
	// Construct, and require an associated object //
	cEditor();
//	cEditor( cGame& _Game );
	~cEditor();

public:
//	cGame* Game;

//	cMapEdit* MapEdit;
	cCollectionEdit* CollectionEdit;
	cComponentEdit* ComponentEdit;
//	cAnimationEdit* AnimationEdit;

public:	
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_Editor_H__ //
// - ------------------------------------------------------------------------------------------ - //
