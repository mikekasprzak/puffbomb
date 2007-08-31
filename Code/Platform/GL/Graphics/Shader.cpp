// - ------------------------------------------------------------------------------------------ - //
// Shader //
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Shader.h>

#include <Util/Debug.h>
#include <Util/String.h>
#include <Util/LZMA.h>
// - ------------------------------------------------------------------------------------------ - //
//#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
//#define GL_GLEXT_PROTOTYPES
// - ------------------------------------------------------------------------------------------ - //
void cShader::Load( const std::string& _FileName )
{
#ifdef EDITOR
	FileName = _FileName;
#endif // EDITOR //

	Log( 10, "Attempting to load Shader" );

	// Validate it's a texture by checking end extension //
	if( String::LastExtension( _FileName ) == ".shader" )
	{
		// Decompress the loaded data //
		char* Buffer = LZMA::UnPack( _FileName );
			
		//Shader = glCreateShaderObjectARB( GL_VERTEX_SHADER_ARB );
		//Shader = glCreateShaderObjectARB( GL_FRAGMENT_SHADER_ARB );
		
		//glCompileShaderARB( Shader );
		
		


		
		delete[] Buffer;
	}
	
	Log( 10, "Shader Loaded" );

}
// - ------------------------------------------------------------------------------------------ - //
