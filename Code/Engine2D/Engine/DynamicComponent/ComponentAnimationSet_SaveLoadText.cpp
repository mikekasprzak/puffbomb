// - ------------------------------------------------------------------------------------------ - //
#include "ComponentAnimationSet.h"

#include <Util/ScriptParser.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::LoadText( const std::string& FileName ) {
	// Load the File //
	cScriptParser Obj( FileName );
	
	// For every instruction //
	for ( size_t idx = 0; idx < Obj.Instruction.size(); idx++ ) {
		cScriptParser::cInstruction& Instr = Obj.Instruction[ idx ];
		
		if ( Instr.Command == "TotalMass" ) {
			Log( LOG_PHIZOBJECT_INFO, "- Found Total Mass" );
		}
		
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::SaveText( const std::string& FileName ) {
	cScriptParser Obj;
	
	
	

	// Save the File //	
	Obj.SaveFile( FileName );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
