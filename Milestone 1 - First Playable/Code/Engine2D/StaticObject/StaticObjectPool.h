// - ------------------------------------------------------------------------------------------ - //
// StaticObjectPool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_StaticObject_StaticObjectPool_H__
#define __Engine2D_StaticObject_StaticObjectPool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/PointerPool.h>
#include "StaticObject.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cStaticObjectPool : public cPointerPool< cStaticObject > {
public:
	cStaticObjectPool() {
		SearchPath.Add( "3D" );
	}
	
	~cStaticObjectPool() {
		for ( MapType::iterator it = Pool.begin(); it != Pool.end(); ++it )
		{
			delete [] it->second->Buffer;
			Log( LOG_HIGHEST_LEVEL, "Deleted Mesh3D (Mesh3dPool) " );
		}		
	}
};
// - ------------------------------------------------------------------------------------------ - //
extern cStaticObjectPool StaticObjectPool;
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_StaticObjectPool_H__ //
// - ------------------------------------------------------------------------------------------ - //
