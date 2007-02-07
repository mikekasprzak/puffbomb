// - ------------------------------------------------------------------------------------------ - //
// PlayerSelect //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Framework_PlayerSelect_PlayerSelect_H__
#define __Framework_PlayerSelect_PlayerSelect_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Camera.h>
#include <Gui/WindowManager.h>
// - ------------------------------------------------------------------------------------------ - //
class cPlayerSelect : public cMessageEntity { 
private:
	cCamera* Camera;
public:
	cWindowManager Window;
	
	int LastTime;

	cPlayerSelect();
	~cPlayerSelect();
	
	void Draw();
	void Step();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Framework_PlayerSelect_PlayerSelect_H__ // 
// - ------------------------------------------------------------------------------------------ - //
