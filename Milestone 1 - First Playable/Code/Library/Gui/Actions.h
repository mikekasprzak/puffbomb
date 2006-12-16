// - ------------------------------------------------------------------------------------------ - //
// Actions //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_Actions_H__
#define __Gui_Actions_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cActions
{
public:


public:
	static void Quit();
	static int StartClassic();
	static int StartGolf();
#ifdef EDITOR
	static int StartEditor();
#endif // EDITOR //
	static int SplashScreen();
	static int ExecuteAction( int _ActionID );
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_Actions_H__ //
// - ------------------------------------------------------------------------------------------ - //
