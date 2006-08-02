// - ------------------------------------------------------------------------------------------ - //
// A tool that converts .png texture file to our .tx format //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <string>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include "../../Library/Util/String.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
void CmdFilters( char* argv );
void ExtFilters( char* argv );
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	// Must have 2 or more arguments //
	if( argc < 3 )
		return -1;

	// - -------------------------------------------------------------------------------------- - //

	SDL_Surface* Image = IMG_Load( argv[1] );
	std::ofstream outfile ( argv[2], ofstream::binary );

	unsigned int PixelSize = 0;
	unsigned int Width = Image->w;
	unsigned int Height = Image->h;
	
	// - -------------------------------------------------------------------------------------- - //
	// Command Line Filters //
	// - -------------------------------------------------------------------------------------- - //
	for( int idx = 3; idx < argc; ++idx )
	{
		CmdFilters( argv[idx] );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Extension Filters //
	// - -------------------------------------------------------------------------------------- - //
	std::string PathFileName = argv[0];
	
	ExtFilters( argv[0] );
	
	// - -------------------------------------------------------------------------------------- - //
	// Directory Name Filters //
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	if( Image->flags & SDL_SRCALPHA )
	{
		// RGBA Texture //
		PixelSize = 4;
	}
	else
	{
		// RGB Texture //
		PixelSize = 3;
	}

	outfile.write( (char*)&PixelSize, sizeof( unsigned int ) );
	outfile.write( (char*)&Width, sizeof( unsigned int ) );
	outfile.write( (char*)&Height, sizeof( unsigned int ) );
	
	outfile.write( (char*)Image->pixels, PixelSize * ( Width * Height ) );
	
	outfile.close();
	SDL_FreeSurface( Image );

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
void CmdFilters( char* argv )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void ExtFilters( char* argv )
{
//	HasAnyExtension( const std::string& _FileName, const std::string& _Pattern )
}
// - ------------------------------------------------------------------------------------------ - //
