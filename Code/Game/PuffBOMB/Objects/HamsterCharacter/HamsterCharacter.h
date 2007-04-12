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
	// Constants for referencing the indices of the collision spheres in the character //
	static const int MiddleIndex = 0;
	
	static const int TopLeftIndex = 1;
	static const int TopRightIndex = 2;
	static const int BottomLeftIndex = 3;
	static const int BottomRightIndex = 4;

public:
	cHamsterCharacter( const Vector2D& _Pos ) :
		cDynamicCollection( "2D/NewHamster/NewHamster.coll", _Pos )
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

	virtual void Message( const Engine2D::cImpulse& Sender );
	virtual void Message( const Engine2D::cZone& Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_HamsterCharacter_H__ //
// - ------------------------------------------------------------------------------------------ - //
