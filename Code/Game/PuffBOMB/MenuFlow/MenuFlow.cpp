// - ------------------------------------------------------------------------------------------ - //
#include "MenuFlow.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cMenuFlow::cMenuFlow( const std::string& FileName ) {
	// Creating Engine //
	Log( LOG_HIGHEST_LEVEL, "Creating Engine..." );
	Engine = new cMenuFlowEngine( FileName );
	
	Work();
}
// - ------------------------------------------------------------------------------------------ - //
cMenuFlow::~cMenuFlow() {
	delete Engine;
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuFlow::Draw() {
	Engine->Draw();
}
// - ------------------------------------------------------------------------------------------ - //
void cMenuFlow::Step() {
	Engine->Step();
	
	// Temp hack to make the menus work like before //
/*	if( Engine->MenuManager.Form[ Engine->MenuManager.CurForm ].SuperFlowState != 1 )
	{
		BreakLoop = true;	
	}*/
	
	if( Engine->MenuManager.BreakLoop )
	{
		BreakLoop = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
