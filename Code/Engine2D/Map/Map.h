// - ------------------------------------------------------------------------------------------ - //
// Map //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Map_H__
#define __Engine2D_Map_H__
// - ------------------------------------------------------------------------------------------ - //
#include "StaticObjectInstanceInfo.h"
#include "DynamicObjectInstanceInfo.h"
#include "PassiveObjectInstanceInfo.h"
#include "ZoneInstanceInfo.h"
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cMap {
public:
	std::vector< cStaticObjectInstanceInfo > StaticObjectInstanceInfo;
	std::vector< cDynamicObjectInstanceInfo > DynamicObjectInstanceInfo;
	std::vector< cPassiveObjectInstanceInfo > PassiveObjectInstanceInfo;
	std::vector< cZoneInstanceInfo > ZoneInstanceInfo;
	
public:
	cMap()
	{
		
	}

public:
	void LoadBinary( const std::string FileName );
	void SaveBinary( const std::string FileName );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Map_H__ //
// - ------------------------------------------------------------------------------------------ - //
