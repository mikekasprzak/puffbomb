// - ------------------------------------------------------------------------------------------ - //
// ClassicLevelEnd //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Framework_ClassicLevelEnd_ClassicLevelEnd_H__
#define __Framework_ClassicLevelEnd_ClassicLevelEnd_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Camera.h>
#include <Gui/Form.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Game/PuffBOMB/ClassicGame/ClassicGameEngine.h>
// - ------------------------------------------------------------------------------------------ - //
class cClassicLevelEnd : public cMessageEntity { 
private:
	cCamera* Camera;
public:
	cForm Form;
	
	int LastTime;
		
	cClassicGameEngine* MyEngine;

	cClassicLevelEnd( cClassicGameEngine* _MyEngine );
	~cClassicLevelEnd();
	
	void ResetMenu();
	void Draw();
	void Step();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Framework_ClassicLevelEnd_ClassicLevelEnd_H__ // 
// - ------------------------------------------------------------------------------------------ - //
