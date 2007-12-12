// - ------------------------------------------------------------------------------------------ - //
// MapData //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_MapData_H__
#define __Game_PuffBOMB_MapData_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cMapData
{
public:
	std::string MapName;
	bool NormalCompleted;
	bool AlternateCompleted;
	bool Locked;
	
public:
	// Best Time Replay
	// Alternate Replay
	// Prefered Replay
	
	Real BestTime;
	Real AlternateTime;

public:
	cMapData( const std::string& _MapName ) :
		MapName( _MapName ), 
		NormalCompleted( false ),
		AlternateCompleted( false ),
		Locked( true ),
		BestTime( Real::Zero ),
		AlternateTime( Real::Zero )
	{
		
	}
			
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __MapData_H__ // 
// - ------------------------------------------------------------------------------------------ - //
