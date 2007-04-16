// - ------------------------------------------------------------------------------------------ - //
// DynamicVortexCollection //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PuffBOMB_Objects_DynamicVortexCollection_H__
#define __PuffBOMB_Objects_DynamicVortexCollection_H__
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicCollection/DynamicCollection.h>
#include <PassiveObject/PassiveObject.h>
// - ------------------------------------------------------------------------------------------ - //
class cDynamicVortexCollection: public Engine2D::cDynamicCollection {
public:
	cDynamicVortexCollection( ) {
	}
	
	cDynamicVortexCollection( const std::string& FileName, const Vector2D& Offset = Vector2D::Zero ) :
		cDynamicCollection( FileName, Offset )
	{
	}

		
	virtual ~cDynamicVortexCollection() {
	}

public:	


public:
	// Messanging //
	virtual int Message( int Msg, Engine2D::cPassiveObject* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PuffBOMB_Objects_DynamicVortexCollection_H__ //
// - ------------------------------------------------------------------------------------------ - //
