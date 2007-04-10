// - ------------------------------------------------------------------------------------------ - //
// MultiplayerHamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_MultiplayerHamsterCharacter_H__
#define __PuffBOMB_Objects_MultiplayerHamsterCharacter_H__
// - ------------------------------------------------------------------------------------------ - //
#include "HamsterCharacter.h"
// - ------------------------------------------------------------------------------------------ - //
class cMultiplayerHamsterCharacter: public cHamsterCharacter {
public:
	cMultiplayerHamsterCharacter( const Vector2D& _Pos ) :
		cHamsterCharacter( _Pos )
	{
		
	}
	
	virtual ~cMultiplayerHamsterCharacter() {
	}

public:
	// Messanging //
	virtual int Message( int Msg, Engine2D::cPassiveObject* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_MultiplayerHamsterCharacter_H__ //
// - ------------------------------------------------------------------------------------------ - //
