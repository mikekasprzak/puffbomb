// - ------------------------------------------------------------------------------------------ - //
// ComponentAnimationSetPool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_ComponentAnimationSet_ComponentAnimationSetPool_H__
#define __Engine2D_ComponentAnimationSet_ComponentAnimationSetPool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Pool.h>
#include "ComponentAnimationSet.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cComponentAnimationSetPool : public cPool< cComponentAnimationSet > {
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
