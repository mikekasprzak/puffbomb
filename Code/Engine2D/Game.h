// - ------------------------------------------------------------------------------------------ - //
// Game //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_H__
#define __Game_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <GL/glu.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Camera.h>
#include <Graphics/LevelData.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
#include <Geometry/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Game/Global.h>
#include <Phiz/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/SphereObject.h>
//#include <Phiz/PolyObject.h>
#include <Phiz/StaticObject.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/NodeLink.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Phiz/Impulse.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Game/ObjectController.h>
#include <Game/Zone.h>
#include <Game/Element.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Animation/Animator.h>
#include <Particle2D/ParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //

//#include "Phiz/DenseParticleSystem.h"

#include <Gui/Form.h>

// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	static cGame* Current;
public:
	// SphereObject that are collections of initial static members //
	cGlobal Global;
	cPhysics Physics;

	cCamera* Camera;
	cCamera* HudCamera;
	
	cForm Form;
	
public:
	// Cheesy camera focus.  Should become invalid once we have a real camera //
	// These are now used so the camera has somthing to follow. //
	// Without some sort of sphere object it would be motionless //
	cSphereObject* Focus1;
	cSphereObject* Focus2;
	
	// Texture ID's and Texture Coords for 2d Objects
	//std::vector< GLuint > TextureID;
	//std::vector< Real > TextureCoord;

	// Our in game Entities //
	std::vector< cSphereObject* > SphereObject;
//	std::vector< cPolyObject* > PolyObject;
	std::vector< cStaticObject* > StaticObject;
	
	// A system of spring that connects objects or polyobjects together //
	std::vector< cNodeLink* > NodeLink;
	// A means for controlling objects, by association //
	std::vector< cObjectController* > ObjectController;
	
	std::vector< cImpulse > Impulse;

	// Regions that do things //
	std::vector< cZone > Zone;
		
	// Create Things //
	std::vector< cElement > Element;
	
	
	// Model Files
	std::vector< cLevelData > Mesh3d;
	
	// Dense Particle System //
	//cDenseParticleSystem DenseParticleSystem;
	
public:
	class cCollisionLine {
	public:
		Vector2D a, b;
		Vector2D Normal;
		bool Used;
		
		cCollisionLine() :
			Used( false )
		{
		}
	};

	//std::vector< cCollisionLine > CollisionLine;
	std::vector< std::vector< cCollisionLine > > Polygon;

public:
	cGame( int _ScreenW, int _ScreenH );
	~cGame();
	
	// Populate the above game structures //
	void LoadMap( char* _FileName );
	// Generate collision from the current map model //
	void GenerateCollision();
	
	// A frontend function that recieves ID's, and creates controllers and hooks them to objects //
	void AddController( int _ControllerId, cSphereObject* _Object, const std::string& FileName );
	
	// Get normal gameloop control //
	void Input();
	// Do a frame of action //
	void Step();
	// Draw //
	void Draw();
	// For drawing anything stationary, such as gui //
	void HudDraw();
	
	// Reset all Objects back to home point //
	void Reset();
	// Reallocate all objects at home positions specified by map //
	void Reload();
	
	// For setting the boundaries of the screen and setting the hud camera z pos //
	Real SetHudData();

public:
	static bool BackgroundOn;		
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_H__ //
// - ------------------------------------------------------------------------------------------ - //
