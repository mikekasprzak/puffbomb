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
class cTex
{
public:
	unsigned int PixelSize;
	unsigned int Width;
	unsigned int Height;
	unsigned char* Pixels;
};
// - ------------------------------------------------------------------------------------------ - //
unsigned int Filters( const std::string PathFileName );
void ApplyProcFilters( unsigned int& FilterFlags, cTex& Tex );
void HalfFilter( cTex& Tex );
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

	cTex Tex;

	Tex.Width = Image->w;
	Tex.Height = Image->h;

	if( Image->flags & SDL_SRCALPHA )
	{
		// RGBA Texture //
		Tex.PixelSize = 4;
	}
	else
	{
		// RGB Texture //
		Tex.PixelSize = 3;
	}

	Tex.Pixels = new unsigned char[ Tex.Width * Tex.Height * Tex.PixelSize ];
	memcpy( Tex.Pixels, Image->pixels, Tex.Width * Tex.Height * Tex.PixelSize );
	
	SDL_FreeSurface( Image );
	
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
	// Apply processing filters //
	// - -------------------------------------------------------------------------------------- - //
	ApplyProcFilters( FilterFlags, Tex );
	
	// - -------------------------------------------------------------------------------------- - //
	outfile.write( (char*)&Tex.PixelSize, sizeof( unsigned int ) );
	outfile.write( (char*)&Tex.Width, sizeof( unsigned int ) );
	outfile.write( (char*)&Tex.Height, sizeof( unsigned int ) );
	
	outfile.write( ( char* )Tex.Pixels, Tex.PixelSize * ( Tex.Width * Tex.Height ) );
	
	outfile.close();
	
	delete[] Tex.Pixels;

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
unsigned int Filters( const std::string PathFileName )
{
	unsigned int FilterFlags = 0;
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "fatten" ) )
	{
		FilterFlags |= flFatten;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "half" ) )
	{
		FilterFlags |= flHalf;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "quarter" ) )
	{
		FilterFlags |= flQuarter;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "eighth" ) )
	{
		FilterFlags |= flEighth;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "rgba" ) )
	{
		FilterFlags |= flRGBA;
	}
	else if( String::HasAnyExtension( PathFileName, "rgb" ) )
	{
		FilterFlags |= flRGB;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "bgra" ) )
	{
		FilterFlags |= flBGRA;
	}
	else if( String::HasAnyExtension( PathFileName, "bgr" ) )
	{
		FilterFlags |= flBGR;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "dxt" ) )
	{
		FilterFlags |= flDXT;
	}
	// - -------------------------------------------------------------------------------------- - //
	return FilterFlags;
}
// - ------------------------------------------------------------------------------------------ - //
// Where the Process filters are executed //
// - ------------------------------------------------------------------------------------------ - //
void ApplyProcFilters( unsigned int& FilterFlags, cTex& Tex )
{
	if( FilterFlags & flFatten )
	{
	
		FilterFlags ^= flFatten;
		cout << "Fatten filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flHalf )
	{
		HalfFilter( Tex );
		FilterFlags ^= flHalf;
		cout << "Half size filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flQuarter )
	{
		HalfFilter( Tex );
		HalfFilter( Tex );

		FilterFlags ^= flQuarter;
		cout << "Quarter size filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flEighth )
	{
		HalfFilter( Tex );
		HalfFilter( Tex );
		HalfFilter( Tex );

		FilterFlags ^= flEighth;
		cout << "Eighth size filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
}
// - ------------------------------------------------------------------------------------------ - //
void HalfFilter( cTex& Tex )
{
	size_t NewWidth = ( Tex.Width / 2 );
	size_t NewHeight = ( Tex.Height / 2 );
	
	char* HalfedImage = new char[ NewWidth * NewHeight * Tex.PixelSize ];
	
	size_t OffsetIdx = 0;
	for( size_t x = 0; x < NewWidth; ++x )
	{
		for( size_t y = 0; y < NewHeight; ++y )
		{
			for( size_t ColorIdx = 0; ColorIdx < Tex.PixelSize; ++ColorIdx )
			{
				unsigned int Color = 0;
				
				unsigned int idx = ( x * 2 * Tex.PixelSize ) + ( y * 2 * Tex.PixelSize * Tex.Width ) + ColorIdx;
				
				Color += Tex.Pixels[ idx ];
				Color += Tex.Pixels[ idx + Tex.PixelSize ];
				Color += Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) ];
				Color += Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + Tex.PixelSize ];
				
				Color /= 4;
				
				HalfedImage[ ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * NewWidth ) + ColorIdx ] = Color;

			}
		}
	}
	
	Tex.Width = NewWidth;
	Tex.Height = NewHeight;	

	delete[] Tex.Pixels;
			
	Tex.Pixels = (unsigned char*)HalfedImage;
	
}
// - ------------------------------------------------------------------------------------------ - //
