// - ------------------------------------------------------------------------------------------ - //
// ZoneInstanceInfo //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_ZoneInstanceInfo_H__
#define __Engine2D_ZoneInstanceInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Physics.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cZoneInstanceInfo {
public:
	cPhysics::BoundingRectType BoundingRect;
	int Id;
	int Arg;

public:
	cZoneInstanceInfo()
	{
		
	}
	
	cZoneInstanceInfo( const cPhysics::BoundingRectType _BoundingRect, const int _Id, const int _Arg = 0 ) :
		BoundingRect( _BoundingRect ),
		Id( _Id ),
		Arg( _Arg )
	{
		
	}

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_ZoneInstanceInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
