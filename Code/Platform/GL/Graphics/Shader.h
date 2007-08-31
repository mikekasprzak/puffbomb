// - ------------------------------------------------------------------------------------------ - //
// Shader //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_Shader_H__
#define __Util_Shader_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cShader
{
public:
	typedef unsigned int IdType;
		
	IdType Id;  // Prob GL specific //
	
	// TODO: add something here to identify Pixel or Vertex shader.
	// TODO: Or, make the shader class a complete effect.  Vertex and pixel shader.
	// TODO: Or, make another type, render effect, that identifies what pixel and vertex shaders to
	//       use //


#ifdef EDITOR
	std::string FileName;
#endif // EDITOR //
public:
	void Load( const std::string& _FileName );
public:
	cShader() :
		Id( 0 )
	{
	}
	
	cShader( const std::string& _FileName ) :
		Id( 0 )
	{
		Load( _FileName );
	}
	

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Shader_H__ //
// - ------------------------------------------------------------------------------------------ - //
