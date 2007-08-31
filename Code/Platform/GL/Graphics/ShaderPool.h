// - ------------------------------------------------------------------------------------------ - //
// ShaderPool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Graphics_ShaderPool_H__
#define __Library_Graphics_ShaderPool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/Pool.h>
#include "Shader.h"
// - ------------------------------------------------------------------------------------------ - //
class cShaderPool : public cPool< cShader > {
public:
	cShaderPool();
	~cShaderPool();
	
	void AddSearchPaths()
	{
		SearchPath.Add( "Shaders" );
		//SearchPath.Add( "2D" );
		//SearchPath.Add( "Maps" );
	}
	
public:
//	inline unsigned int Load( const std::string _FileName ) {
//		return (cPool< cShader >::Load( _FileName )).Id;
//	}

public:
	// ******************* Explicit kill function for broken destructor ********************** //
	void Kill();
	
	// - -------------------------------------------------------------------------------------- - //
	// Remove Shader from the pool //
	void Remove( const std::string& _FileName );
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
//extern cShaderPool ShaderPool;
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Graphics_ShaderPool_H__ //
// - ------------------------------------------------------------------------------------------ - //
