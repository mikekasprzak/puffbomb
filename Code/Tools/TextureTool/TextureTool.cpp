// - ------------------------------------------------------------------------------------------ - //
// A tool that converts .png texture file to our .tx format //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <string>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include "../../Library/Util/ClassDesigner/Bits.h"
#include "../../Library/Util/String.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
unsigned int Filters( const std::string PathFileName );
// - ------------------------------------------------------------------------------------------ - //
//	FlagFilters
typedef const unsigned int fl;
fl flFatten 	= bit4;
fl flHalf 		= bit5;
fl flQuarter 	= bit6;
fl flEighth 	= bit7;

fl flRGB 		= bit16;
fl flRGBA 		= bit17;
fl flBGR 		= bit18;
fl flBGRA 		= bit19;
fl flDXT 		= bit20;

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	// Must have 2 or more arguments //
	if( argc < 3 )
		return -1;

	// - -------------------------------------------------------------------------------------- - //
	unsigned int FilterFlags = 0;

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
		std::string TempArg = argv[idx];
		FilterFlags |= Filters( TempArg );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Extension and Directory Name Filters //
	// - -------------------------------------------------------------------------------------- - //
	std::string PathFileName = argv[1];

	FilterFlags |= Filters( PathFileName );
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
unsigned int Filters( const std::string PathFileName )
{
	unsigned int FilterFlags = 0;
	if( String::HasAnyExtension( PathFileName, "fatten" ) )
	{
		FilterFlags |= flFatten;
	}
	if( String::HasAnyExtension( PathFileName, "half" ) )
	{
		FilterFlags |= flHalf;
	}
	if( String::HasAnyExtension( PathFileName, "quarter" ) )
	{
		FilterFlags |= flQuarter;
	}
	if( String::HasAnyExtension( PathFileName, "eighth" ) )
	{
		FilterFlags |= flEighth;
	}
	if( String::HasAnyExtension( PathFileName, "rgba" ) )
	{
		FilterFlags |= flRGBA;
	}
	else if( String::HasAnyExtension( PathFileName, "rgb" ) )
	{
		FilterFlags |= flRGB;
	}
	if( String::HasAnyExtension( PathFileName, "bgra" ) )
	{
		FilterFlags |= flBGRA;
	}
	else if( String::HasAnyExtension( PathFileName, "bgr" ) )
	{
		FilterFlags |= flBGR;
	}
	if( String::HasAnyExtension( PathFileName, "dxt" ) )
	{
		FilterFlags |= flDXT;
	}
	return FilterFlags;
}
// - ------------------------------------------------------------------------------------------ - //
