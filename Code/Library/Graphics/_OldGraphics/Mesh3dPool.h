// - ------------------------------------------------------------------------------------------ - //
// Mesh3dPool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Graphics_Mesh3dPool_H__
#define __Library_Graphics_Mesh3dPool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/Pool.h>
#include "Mesh3d.h"
// - ------------------------------------------------------------------------------------------ - //
class cMesh3dPool : public cPool< cMesh3d > {
public:
	cMesh3dPool()
	{
		SearchPath.Add( "3D" );
	}
	~cMesh3dPool()
	{
		for( std::map<std::string,cMesh3d>::iterator it = Pool.begin(); it != Pool.end(); ++it )
		{
			delete[] it->second.Buffer;
			Log( LOG_HIGHEST_LEVEL, "Deleted Mesh3d (Mesh3dPool) " );
		}
		
	}
};

extern cMesh3dPool Mesh3dPool;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Graphics_Mesh3dPool_H__ //
// - ------------------------------------------------------------------------------------------ - //
