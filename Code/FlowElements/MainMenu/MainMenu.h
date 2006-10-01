// - ------------------------------------------------------------------------------------------ - //
// MainMenu //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __FlowElements_MainMenu_MainMenu_H__
#define __FlowElements_MainMenu_MainMenu_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Camera.h>
#include <Gui/Form.h>
// - ------------------------------------------------------------------------------------------ - //
class cMainMenu : public cMessageEntity { 
private:
	cCamera* Camera;
public:
	cForm Form;

	cMainMenu();
	~cMainMenu();
	
	void ResetMenu();
	void Draw();
	void Step();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __FlowElements_MainMenu_MainMenu_H__ // 
// - ------------------------------------------------------------------------------------------ - //
