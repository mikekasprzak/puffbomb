// - ------------------------------------------------------------------------------------------ - //
// A tool that converts .comp files to .bin.comp files, and determines what textures to convert //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <string>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include <Util/ClassDesigner.h>
#include <Util/String.h>
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicComponent/ComponentAnimationSet/ComponentAnimationSet.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
extern void QuitGame( int ReturnCode );
// ---------------------------------------------------------------------------------------------- //
void QuitGame( int ReturnCode ) {
    exit( ReturnCode );
}
// - ------------------------------------------------------------------------------------------ - //
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB;
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	// - -------------------------------------------------------------------------------------- - //

	// Must have 3 or more arguments //
	if( argc < 4 )
		return -1;

	// - -------------------------------------------------------------------------------------- - //
	
	string ComponentFile( String::SystemSlash( argv[ 1 ] ) );
	string ArtFolder = String::Directory( ComponentFile );
	
	string TargetComp( String::SystemSlash( argv[ 2 ] ) );
	string FinalFileName( String::SystemSlash( argv[ 3 ] ) );

	// - -------------------------------------------------------------------------------------- - //

	// Verify command line arguments are ok //
	cout << ".COMP: " << ComponentFile << endl;	
	cout << "ART DIR: " << ArtFolder << endl;
	cout << "BIN.COMP: " << TargetComp << endl;
	cout << "HOME: " << getenv("HOME") << endl;

//	glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)SDL_GL_GetProcAddress("glCompressedTexImage2DARB");
//
//    if( !glCompressedTexImage2DARB )
//    {
//        Log( LOG_HIGHEST_LEVEL, "One or more ARB_texture_compression functions were not found!!!!" );
//    }

	// - -------------------------------------------------------------------------------------- - //

	// Load text based component file //
	Engine2D::cComponentAnimationSet Animation;
	Animation.LoadText( ComponentFile );
	
	// Save Binary File (uhh, yeah... that easy) //
	Animation.SaveBinary( TargetComp, FinalFileName, ArtFolder );

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
