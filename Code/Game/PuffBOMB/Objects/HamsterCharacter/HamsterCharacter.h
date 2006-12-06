// - ------------------------------------------------------------------------------------------ - //
// HamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_HamsterCharacter_H__
#define __PuffBOMB_Objects_HamsterCharacter_H__
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicCollection/DynamicCollection.h>
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cHamsterCharacter: public Engine2D::cDynamicCollection {
public:

public:
	cHamsterCharacter( const Vector2D& _Pos ) :
		cDynamicCollection( "2D/UglyHamster/UglyHamster.coll", _Pos )
	{
		
	}
	
	virtual ~cHamsterCharacter() {
	}

public:	
	virtual bool Work();


public:
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicCollection* const Sender );
	virtual int Message( int Msg, Engine2D::cPassiveObject* const Sender );

	virtual void Action( const Engine2D::cImpulse& _Vs );
	virtual void Action( const Engine2D::cZone& _Vs );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_HamsterCharacter_H__ //
// - ------------------------------------------------------------------------------------------ - //
