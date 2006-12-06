// - ------------------------------------------------------------------------------------------ - //
// SuperFlow //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_SuperFlow_H__
#define __Game_PuffBOMB_SuperFlow_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
class cSuperFlow { 
public:
	int State;
	
	std::string ClassicPath;
	std::string GolfPath;	
	std::vector< std::string > ClassicMaps;
	std::vector< std::string > GolfMaps;
		
	int CurClassicMap;
	int CurGolfMap;
		
public:
	cSuperFlow();
	void StateFlow();
	void SetHudData();
	void FindMaps( const std::string& Path, std::vector< std::string >& Maps );
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SuperFlow_H__ // 
// - ------------------------------------------------------------------------------------------ - //
