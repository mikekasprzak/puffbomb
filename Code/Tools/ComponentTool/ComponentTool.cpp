// - ------------------------------------------------------------------------------------------ - //
// A tool that converts .comp files to .bin.comp files, and determines what textures to convert //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <string>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include <Util/ClassDesigner.h>
#include <Util/String.h>
// - ------------------------------------------------------------------------------------------ - //
#include <DynamicComponent/ComponentAnimationSet/ComponentAnimationSet.h>

// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	// Must have 2 or more arguments //
	if( argc < 3 )
		return -1;

	// - -------------------------------------------------------------------------------------- - //
	
	string ComponentFile( argv[ 1 ] );
	string ArtFolder = String::Directory( ComponentFile );
	
	string TargetComp( argv[ 2 ] );
	string OutputBaseName = String::DirectorySlash( TargetComp ) + String::BaseName( TargetComp );

	// - -------------------------------------------------------------------------------------- - //

	// Verify command line arguments are ok //
	cout << ComponentFile << endl;	
	cout << ArtFolder << endl;
	cout << TargetComp << endl;
	cout << OutputBaseName << endl;

	// - -------------------------------------------------------------------------------------- - //

	Engine2D::cComponentAnimationSet Animation;
	Animation.LoadText( ComponentFile );
	
	

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
