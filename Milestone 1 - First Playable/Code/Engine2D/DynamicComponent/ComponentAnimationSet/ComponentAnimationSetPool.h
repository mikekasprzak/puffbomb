// - ------------------------------------------------------------------------------------------ - //
// ComponentAnimationSetPool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_ComponentAnimationSet_ComponentAnimationSetPool_H__
#define __Engine2D_ComponentAnimationSet_ComponentAnimationSetPool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/PointerPool.h>
#include "ComponentAnimationSet.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cComponentAnimationSetPool : public cPointerPool< cComponentAnimationSet > {
public:
	cComponentAnimationSetPool() {
		SearchPath.Add( "2D" );
	}
};
// - ------------------------------------------------------------------------------------------ - //
extern cComponentAnimationSetPool ComponentAnimationSetPool;
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_ComponentAnimationSetPool_H__ //
// - ------------------------------------------------------------------------------------------ - //
