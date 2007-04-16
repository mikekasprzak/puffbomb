// - ------------------------------------------------------------------------------------------ - //
// SuperFlow //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_SuperFlow_H__
#define __Game_PuffBOMB_SuperFlow_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>

#include "GolfGame/Player/PlayerInfo.h"
#include "ClassicSaveData.h"
// - ------------------------------------------------------------------------------------------ - //
class cSuperFlow { 
public:
	int State;
	
	std::string ClassicPath;
	std::string GolfPath;	
	std::vector< std::string > ClassicMaps;
	std::vector< std::string > GolfMaps;
	
	std::vector< cPlayerInfo > Players;
	
	int CurClassicMap;
	int CurGolfMap;
	
	int CurrentStartPlayer;
	
	cClassicSaveData ClassicSaveData;
		
public:
	cSuperFlow();
	void StateFlow();
	void SetHudData();
	void FindMaps( const std::string& Path, std::vector< std::string >& Maps );
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SuperFlow_H__ // 
// - ------------------------------------------------------------------------------------------ - //
