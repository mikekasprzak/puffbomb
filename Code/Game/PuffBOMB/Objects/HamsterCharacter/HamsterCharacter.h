// - ------------------------------------------------------------------------------------------ - //
// HamsterCharacter //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_HamsterCharacter_H__
#define __PuffBOMB_Objects_HamsterCharacter_H__
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicCollection/DynamicCollection.h>
// - ------------------------------------------------------------------------------------------ - //
class cHamsterCharacter: public Engine2D::cDynamicCollection {
public:

public:
	cHamsterCharacter( const Vector2D& _Pos ) :
		cDynamicCollection( "2D/UglyHamster/UglyHamster.coll", _Pos )
	{
		
	}

public:	
	virtual bool Work();

public:
	// Messanging //
	//virtual void Action( class cDynamicComponent& _Vs ) const;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_HamsterCharacter_H__ //
// - ------------------------------------------------------------------------------------------ - //
