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
//	void* Pixels;
	char* Pixels;
};
// - ------------------------------------------------------------------------------------------ - //
unsigned int Filters( const std::string PathFileName );
void ApplyProcFilters( unsigned int& FilterFlags, cTex& Tex );
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

	Tex.PixelSize = 0;
	Tex.Width = Image->w;
	Tex.Height = Image->h;
	Tex.Pixels = (char*)Image->pixels;
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

	outfile.write( (char*)&Tex.PixelSize, sizeof( unsigned int ) );
	outfile.write( (char*)&Tex.Width, sizeof( unsigned int ) );
	outfile.write( (char*)&Tex.Height, sizeof( unsigned int ) );
	
	outfile.write( (char*)Tex.Pixels, Tex.PixelSize * ( Tex.Width * Tex.Height ) );
	
	outfile.close();
	
	if( Tex.Pixels != Image->pixels )
	{
		delete[] Tex.Pixels;
	}

	SDL_FreeSurface( Image );

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
//		size_t NewSize = ( Tex.Width * Tex.Height ) / 2;
//		unsigned int* HalfedImage = new unsigned int[ NewSize ];
		
//		size_t AvgIdx = 0;
/*
		for( size_t idx = 0; idx < NewSize; ++idx )
		{
			unsigned int Red = 0;
			unsigned int Green = 0;
			unsigned int Blue = 0;
			unsigned int Alpha = 0;
			
			unsigned int TempColor = Tex.Pixels[ AvgIdx ];

			Red += TempColor & 0xff;
			TempColor = Tex.Pixels[ AvgIdx ];
			AvgIdx++;
			Green += (TempColor>>8) & 0xff;
			TempColor = Tex.Pixels[ AvgIdx ];
			AvgIdx++;
			Blue += (TempColor>>16) & 0xff;
			TempColor = Tex.Pixels[ AvgIdx ];
			AvgIdx++;
			Alpha += (TempColor>>24) & 0xff;
		
			TempColor = Tex.Pixels[ AvgIdx ];
			AvgIdx++;
			Red += TempColor & 0xff;
			TempColor = Tex.Pixels[ AvgIdx ];
			AvgIdx++;
			Green += (TempColor>>8) & 0xff;
			TempColor = Tex.Pixels[ AvgIdx ];
			AvgIdx++;
			Blue += (TempColor>>16) & 0xff;
			TempColor = Tex.Pixels[ AvgIdx ];
			AvgIdx++;
			Alpha += (TempColor>>24) & 0xff;

			TempColor = Tex.Pixels[ AvgIdx + ( Tex.Width * 4 ) ];
			AvgIdx++
			TempColor = Tex.Pixels[ AvgIdx + ( Tex.Width * 4 ) ];
			Red += TempColor & 0xff;
			Green += (TempColor>>8) & 0xff;
			Blue += (TempColor>>16) & 0xff;
			Alpha += (TempColor>>24) & 0xff;

			TempColor = Tex.Pixels[ AvgIdx + 4 + ( Tex.Width * 4 ) ];
			Red += TempColor & 0xff;
			Green += (TempColor>>8) & 0xff;
			Blue += (TempColor>>16) & 0xff;
			Alpha += (TempColor>>24) & 0xff;
			
			Red /= 2;
			Green /= 2;
			Blue /= 2;
			Alpha /= 2;
*/
//			cout << "Red " << Red << endl;
//			cout << "Green " << Green << endl;
//			cout << "Blue " << Blue << endl;
//			cout << "Alpha " << Alpha << endl;
			
//			HalfedImage[ idx ] = Red;
			
//			HalfedImage[ idx ] = Blue;
//			HalfedImage[ idx ] = Red + (Green<<8) + (Blue<<16) + (Alpha<<24);
//			HalfedImage[ idx ] = Red & 0xff + (Green<<8) & 0xff + (Blue<<16) & 0xff + (Alpha<<24) & 0xff;
						
//			AvgIdx += 8;
			
		/*	if( AvgIdx % Tex.Width == 0 )
			{
				AvgIdx += Tex.Width;
			}
		}*/
		
//		Tex.Width /= 2;
//		Tex.Height /= 2;		

//		Tex.Pixels = (char*)HalfedImage;
		
		FilterFlags ^= flHalf;
		cout << "Half size filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flQuarter )
	{
		

		FilterFlags ^= flQuarter;
		cout << "Quarter size filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flEighth )
	{
		

		FilterFlags ^= flEighth;
		cout << "Eighth size filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
}
// - ------------------------------------------------------------------------------------------ - //
