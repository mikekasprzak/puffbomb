// - ------------------------------------------------------------------------------------------ - //
// WindowManager //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_WindowManager_H__
#define __Gui_WindowManager_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Form.h"

#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cWindowManager
{
public:
	std::vector< cForm > Form;	

public:
	void Step();
	
	void Draw();
	
	void Load( const std::string &File );
	Real Anchor( const std::string &AnchorName );

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_WindowManager_H__ //
// - ------------------------------------------------------------------------------------------ - //