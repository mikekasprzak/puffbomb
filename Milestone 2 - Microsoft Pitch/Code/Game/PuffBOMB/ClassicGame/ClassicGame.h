// - ------------------------------------------------------------------------------------------ - //
// ClassicGame //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __ClassicGame_PuffBOMB_ClassicGame_H__
#define __ClassicGame_PuffBOMB_ClassicGame_H__
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
#endif // ClassicGame // 
// - ------------------------------------------------------------------------------------------ - //
