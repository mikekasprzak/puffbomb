// - ------------------------------------------------------------------------------------------ - //
// ScriptParser //
// The "Phiz Script" is a container for a script file, which is a list of instructions. //
//
// The instruction list is then interpreted by the appropriate object. //
// Unfortunately, there is a bit of a hack from the ObjectTemplate in here. //
// Essentially, for every "Node" command, it increments an internal counter.  No harm done. //
//
// "//"'s comment out a block, and the script reader ignores everything following until the end //
//   of line. //
//
// Formerly known as the ObjectTemplate, but more uses were found and it was extended for use as //
//  in map loading. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_PhizScript_H__
#define __Phiz_PhizScript_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>

#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cScriptParser {
public:
	// Name to use for map hash //
	std::string Name;

public:
	class cInstruction {
	public:
		std::string Command;
		std::string Arg[4];
	};

public:
	std::vector< cInstruction > Instruction;
	int NodeCount;
	
	cScriptParser() :
		NodeCount( 0 )
	{
	}
	
	cScriptParser( const std::string& File ) :
		Name( File )
	{
		LoadFile( );
	}
	
	inline void Append(
		std::string _Command,
		std::string _Arg0 = "",
		std::string _Arg1 = "",
		std::string _Arg2 = "",
		std::string _Arg3 = ""
		)
	{
		if ( _Command == "Node" )
			NodeCount++;
		
		Instruction.push_back( cInstruction() );
		Instruction.back().Command = _Command;
		Instruction.back().Arg[0] = _Arg0;
		Instruction.back().Arg[1] = _Arg1;
		Instruction.back().Arg[2] = _Arg2;
		Instruction.back().Arg[3] = _Arg3;
	}

	void Append(
		std::string _Command,
		double _Arg0
		);

	void Append(
		std::string _Command,
		double _Arg0,
		double _Arg1
		);
	
	void Append(
		std::string _Command,
		double _Arg0,
		double _Arg1,
		double _Arg2
		);
			
	void Append(
		std::string _Command,
		double _Arg0,
		double _Arg1,
		double _Arg2,
		double _Arg3
		);

	void Append(
		std::string _Command,
		std::string _Arg0,
		double _Arg1
		);
	
	inline void LoadFile( ) {
		LoadFile( Name.c_str() );	
	}
	
	void LoadFile( const std::string& File );
	
	void SaveFile( const std::string& File ) const;
	
	void Write() {
		for ( size_t idx = 0; idx < Instruction.size(); idx++ ) {
			Log( LOG_HIGHEST_LEVEL, 
				Instruction[ idx ].Command << " " <<
				Instruction[ idx ].Arg[ 0 ] << " " <<
				Instruction[ idx ].Arg[ 1 ] << " " <<
				Instruction[ idx ].Arg[ 2 ] << " " <<
				Instruction[ idx ].Arg[ 3 ]
				);
		}
	}
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_PhizScript_H__ //
// - ------------------------------------------------------------------------------------------ - //
