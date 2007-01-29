// - ------------------------------------------------------------------------------------------ - //
// LevelEnd //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Framework_LevelEnd_LevelEnd_H__
#define __Framework_LevelEnd_LevelEnd_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Camera.h>
#include <Gui/Form.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Game/PuffBOMB/GolfGame/GolfGameEngine.h>
// - ------------------------------------------------------------------------------------------ - //
class cLevelEnd : public cMessageEntity { 
private:
	cCamera* Camera;
public:
	cForm Form;
	
	int LastTime;

	cGolfGameEngine* MyEngine;
		
	cLevelEnd( cGolfGameEngine* _MyEngine );
	~cLevelEnd();
	
	void ResetMenu();
	void Draw();
	void Step();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Framework_LevelEnd_LevelEnd_H__ // 
// - ------------------------------------------------------------------------------------------ - //
