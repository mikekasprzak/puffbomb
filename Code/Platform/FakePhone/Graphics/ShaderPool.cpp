// - ------------------------------------------------------------------------------------------ - //
// ShaderPool //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/ShaderPool.h>
// - ------------------------------------------------------------------------------------------ - //
//#include <windows.h>
// - ------------------------------------------------------------------------------------------ - //
//#define GL_GLEXT_PROTOTYPES 1
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
//cShaderPool ShaderPool;

// - ------------------------------------------------------------------------------------------ - //
cShaderPool::cShaderPool()
{
	AddSearchPaths();
}
// - ------------------------------------------------------------------------------------------ - //
cShaderPool::~cShaderPool()
{
//	for( std::map<std::string,cShader>::iterator it = Pool.begin(); it != Pool.end(); ++it )
//	{
//		glDeleteShaders( 1, &it->second.Id );
//		Log( LOG_HIGHEST_LEVEL, "Deleted Shader Id ( Shader Pool ) " );
//		
//		if( it->second.WhiteId != 0 )
//		{
//			glDeleteShaders( 1, &it->second.WhiteId );
//			Log( LOG_HIGHEST_LEVEL, "Deleted Shader WhiteId ( Shader Pool ) " );
//		}
//	}
	Pool.clear();
}
// - ------------------------------------------------------------------------------------------ - //
void cShaderPool::Kill()
{
//	for( std::map<std::string,cShader>::iterator it = Pool.begin(); it != Pool.end(); ++it )
//	{
//		glDeleteShaders( 1, &it->second.Id );
//		Log( LOG_HIGHEST_LEVEL, "Deleted Shader Id ( Shader Pool ) " );
//		
//		if( it->second.WhiteId != 0 )
//		{
//			glDeleteShaders( 1, &it->second.WhiteId );
//			Log( LOG_HIGHEST_LEVEL, "Deleted Shader WhiteId ( Shader Pool ) " );
//		}
//	}
	Pool.clear();
}
// - ------------------------------------------------------------------------------------------ - //
void cShaderPool::Remove( const std::string& _FileName )
{
//	glDeleteShaders( 1, &Pool.find( _FileName )->second.Id );
//	Log( LOG_HIGHEST_LEVEL, "Deleted Shader Id ( Remove Shader Pool ) " << _FileName );
//	
//	if( Pool.find( _FileName )->second.WhiteId != 0 )
//	{
//		glDeleteShaders( 1, &Pool.find( _FileName )->second.WhiteId );
//		Log( LOG_HIGHEST_LEVEL, "Deleted Shader WhiteId ( Remove Shader Pool ) " );
//	}
	
	Pool.erase( _FileName );
}
// - ------------------------------------------------------------------------------------------ - //
