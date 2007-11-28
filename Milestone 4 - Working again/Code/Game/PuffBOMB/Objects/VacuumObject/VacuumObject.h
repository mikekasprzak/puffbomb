// - ------------------------------------------------------------------------------------------ - //
// VacuumObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_VacuumObject_H__
#define __PuffBOMB_Objects_VacuumObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicCollection/DynamicCollection.h>
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cVacuumObject: public Engine2D::cDynamicCollection {
public:


public:
	cVacuumObject( const Vector2D& _Pos ) :
		cDynamicCollection( "2D/ForegroundElementsOne/ForegroundRockThree.coll", _Pos )
	{
		Component[ 0 ].Body.Flags.SetImpulseSensor();
	}
	
	virtual ~cVacuumObject() {
	}

public:	
	virtual bool Work();


public:
	// Messanging //
	virtual int Message( int Msg, Engine2D::cDynamicCollection* const Sender );
	//virtual int Message( int Msg, Engine2D::cPassiveObject* const Sender );

	//virtual void Message( const Engine2D::cImpulse& Sender );
	//virtual void Message( const Engine2D::cZone& Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_VacuumObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
