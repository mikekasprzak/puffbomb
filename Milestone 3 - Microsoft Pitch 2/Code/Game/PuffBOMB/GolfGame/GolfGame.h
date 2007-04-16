// - ------------------------------------------------------------------------------------------ - //
// GolfGame //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GolfGame_PuffBOMB_GolfGame_H__
#define __GolfGame_PuffBOMB_GolfGame_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
#include "GolfGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
class cGolfGame : public cMessageEntity { 
public:
	cGolfGameEngine* Engine;

public:
	cGolfGame( const std::string& FileName, const std::vector< cPlayerInfo >& _Players = std::vector< cPlayerInfo >(4), int _StartPlayer = 0 );
	~cGolfGame();

public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // GolfGame // 
// - ------------------------------------------------------------------------------------------ - //
