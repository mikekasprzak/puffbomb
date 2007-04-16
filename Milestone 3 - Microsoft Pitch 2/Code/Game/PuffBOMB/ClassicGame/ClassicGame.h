// - ------------------------------------------------------------------------------------------ - //
// ClassicGame //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_PuffBOMB_Classic_ClassicGame_H__
#define __Game_PuffBOMB_Classic_ClassicGame_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>

#include <MessageEntity.h>
#include "ClassicGameEngine.h"
// - ------------------------------------------------------------------------------------------ - //
class cClassicGame : public cMessageEntity { 
public:
	cClassicGameEngine* Engine;

public:
	cClassicGame( const std::string& FileName );
	~cClassicGame();

public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_PuffBOMB_Classic_ClassicGame_H__ // 
// - ------------------------------------------------------------------------------------------ - //
