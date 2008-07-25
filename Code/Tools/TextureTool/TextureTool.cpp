// - ------------------------------------------------------------------------------------------ - //
// A tool that converts .png texture file to our .tx format //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <string>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include <Util/ClassDesigner/Bits.h>
#include <String/String.h>
#include <FileIO/LZMA.h>
// - ------------------------------------------------------------------------------------------ - //
#include "pngwriter.h"
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

cTex WhiteTex;

// - ------------------------------------------------------------------------------------------ - //
unsigned int Filters( const std::string PathFileName );
void ApplyFilters( unsigned int& FilterFlags, cTex& Tex );
void BlackenFilter( cTex& Tex );
void FattenFilter( cTex& Tex );
void HalfFilter( cTex& Tex );
void BlackKeyFilter( cTex& Tex );
void WhiteFilter( cTex& Tex, int SWhite );
void PowerOfTwoFilter( cTex& Tex, int RoundUp, bool isSmooth = false );
// 0 - Round Down, 1 - Round Up, 2 - Round to the closest
void FlipFilter( cTex& Tex );
void MirrorFilter( cTex& Tex );

// - ------------------------------------------------------------------------------------------ - //
//	FlagFilters
typedef const unsigned int fl;
fl flFatten 	= bit4;
fl flHalf 		= bit5;
fl flQuarter 	= bit6;
fl flEighth 	= bit7;
fl flWhite	 	= bit8;
fl flFlip	 	= bit10;
fl flMirror	 	= bit11;

fl flBlackKey	= bit15;
fl flRGB 		= bit16;
fl flRGBA 		= bit17;
fl flBGR 		= bit18;
fl flBGRA 		= bit19;
//fl flDXT 		= bit20;
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	// Must have 2 or more arguments //
	if( argc < 3 )
		return -1;
	
	// - -------------------------------------------------------------------------------------- - //
	unsigned int FilterFlags = 0;

	std::string InputFileName = argv[1];
	std::string OutputFileName = argv[2];

	cTex Tex;

	char* Buffer;

	if( String::LastExtension( InputFileName ) == ".tx" )
	{
		Buffer = LZMA::UnPack( InputFileName );
		
		unsigned int* tempPixelSize	= (unsigned int*)&Buffer[0];
		Tex.PixelSize = *tempPixelSize;
	
		unsigned int* tempWidth	= (unsigned int*)&Buffer[4];
		Tex.Width = *tempWidth;

		unsigned int* tempHeight	= (unsigned int*)&Buffer[8];
		Tex.Height = *tempHeight;

		Tex.Pixels = (unsigned char*)&Buffer[12];
	}
	else
	{
		SDL_Surface* Image = IMG_Load( argv[1] );
		
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
	}
	
	WhiteTex.PixelSize = 0;
	
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
	//PowerOfTwoFilter( Tex, 2);
	
	ApplyFilters( FilterFlags, Tex );
	
	// - -------------------------------------------------------------------------------------- - //
	if( String::LastExtension( OutputFileName ) == ".png" )
	{
		if( Tex.PixelSize == 4 )
		{
			pngwriter image( (unsigned int)Tex.Width, (unsigned int)Tex.Height, 1.0, argv[2], 32 );

			size_t ImageY = Tex.Height;
			
			for( size_t y = 0; y < Tex.Height; ++y )
			{
				for( size_t x = 0; x < Tex.Width; ++x )
				{
					unsigned int idx = ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width );

					image.plot( x + 1, ImageY, Tex.Pixels[ idx + 0 ] * 255, Tex.Pixels[ idx + 1 ] * 255, Tex.Pixels[ idx + 2 ] * 255, Tex.Pixels[ idx + 3 ] * 255 );
				}
				--ImageY;
			}
			
			image.close();
		}
		else if( Tex.PixelSize == 3 )
		{
			pngwriter image( (unsigned int)Tex.Width, (unsigned int)Tex.Height, 1.0, argv[2], 8 );

			size_t ImageY = Tex.Height;
			
			for( size_t y = 0; y < Tex.Height; ++y )
			{
				for( size_t x = 0; x < Tex.Width; ++x )
				{
					unsigned int idx = ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width );

					image.plot( x + 1, ImageY, Tex.Pixels[ idx + 0 ] * 255, Tex.Pixels[ idx + 1 ] * 255, Tex.Pixels[ idx + 2 ] * 255 );
				}
				--ImageY;
			}
			
			image.close();
		}
	}
	else
	{
		std::ofstream outfile ( argv[2], ofstream::binary );
		
		outfile.write( (char*)&Tex.PixelSize, sizeof( unsigned int ) );
		outfile.write( (char*)&Tex.Width, sizeof( unsigned int ) );
		outfile.write( (char*)&Tex.Height, sizeof( unsigned int ) );
		
		outfile.write( ( char* )Tex.Pixels, Tex.PixelSize * ( Tex.Width * Tex.Height ) );
		
		outfile.write( (char*)&WhiteTex.PixelSize, sizeof( unsigned int ) );
		if( WhiteTex.PixelSize != 0 )
		{
			outfile.write( ( char* )WhiteTex.Pixels, WhiteTex.PixelSize * ( WhiteTex.Width * WhiteTex.Height ) );	
		}
		
		outfile.close();
	}

	if( String::LastExtension( InputFileName ) == ".tx" )
	{
		delete[] Buffer;
	}
	else
	{
		delete[] Tex.Pixels;
	}
	if( WhiteTex.Pixels != 0 )
	{
		delete[] WhiteTex.Pixels;
	}
	
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
	if( String::HasAnyExtension( PathFileName, "flip" ) )
	{
		FilterFlags |= flFlip;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "mirror" ) )
	{
		FilterFlags |= flMirror;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "blackkey" ) )
	{
		FilterFlags |= flBlackKey;
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
	/*if( String::HasAnyExtension( PathFileName, "dxt" ) )
	{
		FilterFlags |= flDXT;
	}*/
	// - -------------------------------------------------------------------------------------- - //
	if( String::HasAnyExtension( PathFileName, "white" ) )
	{
		FilterFlags |= flWhite;
	}
	// - -------------------------------------------------------------------------------------- - //

	return FilterFlags;
}
// - ------------------------------------------------------------------------------------------ - //
// Where the Process filters are executed //
// - ------------------------------------------------------------------------------------------ - //
void ApplyFilters( unsigned int& FilterFlags, cTex& Tex )
{
	if( FilterFlags & flFatten )
	{
		// Blacked the texture before we fatten it //
		BlackenFilter( Tex );
		
		// Fatten the texture //
		for ( int idx = 0; idx < 20; idx++ ) {
			FattenFilter( Tex );
			
			/*if( WhiteTex.PixelSize != 0 )
			{
				FattenFilter( WhiteTex );
			}*/
		}
			
		FilterFlags ^= flFatten;
		cout << "Fatten filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flFlip )
	{
		FlipFilter( Tex );
			
		FilterFlags ^= flFlip;
		cout << "Flip filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flMirror )
	{
		MirrorFilter( Tex );
			
		FilterFlags ^= flMirror;
		cout << "Mirror filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flBlackKey )
	{
		BlackKeyFilter( Tex );
		
		// Fatten the texture //
		for ( int idx = 0; idx < 4; idx++ )
		{
			FattenFilter( Tex );
		}
		
		FilterFlags ^= flBlackKey;
		cout << "Black Key filter applied" << endl;
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
	if( FilterFlags & flBGR )
	{
	
		FilterFlags ^= flBGR;
		cout << "BGR filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //
	/*if( FilterFlags & flDXT )
	{
	
		FilterFlags ^= flDXT;
		cout << "DXT filter applied" << endl;
	}*/
	// - -------------------------------------------------------------------------------------- - //
	if( FilterFlags & flWhite )
	{
		WhiteTex.Width = Tex.Width;
		WhiteTex.Height = Tex.Height;
		WhiteTex.PixelSize = Tex.PixelSize;
		
		WhiteTex.Pixels = new unsigned char[ WhiteTex.Width * WhiteTex.Height * WhiteTex.PixelSize ];
		
		memcpy( WhiteTex.Pixels, Tex.Pixels, WhiteTex.Width * WhiteTex.Height * WhiteTex.PixelSize );

		for( int i = 0; i < 6; ++i )
		{ 			
			WhiteFilter( WhiteTex, 0 );
			WhiteFilter( WhiteTex, 1 );
			WhiteFilter( WhiteTex, 2 );
		//	WhiteFilter( WhiteTex, 3 );
		//	WhiteFilter( WhiteTex, 4 );
		//	WhiteFilter( WhiteTex, 5 );
		//	WhiteFilter( WhiteTex, 6 );
		}
		//WhiteFilter( WhiteTex, 2 );
			
		FilterFlags ^= flWhite;
		cout << "White filter applied" << endl;
	}
	// - -------------------------------------------------------------------------------------- - //

}
// - ------------------------------------------------------------------------------------------ - //
void BlackenFilter( cTex& Tex )
{
	if( Tex.PixelSize == 4 )
	{
		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				unsigned int idx = ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width );
				if ( (Tex.Pixels[ idx + 3 ] & 0xff) == 0 ) {
					Tex.Pixels[ idx ] = 0;
					Tex.Pixels[ idx + 1] = 0;
					Tex.Pixels[ idx + 2] = 0;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FlipFilter( cTex& Tex )
{
	{
		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				unsigned int idx = ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width );
				
				unsigned int idx2 = ( x * Tex.PixelSize ) + ( (Tex.Height-1-y) * Tex.PixelSize * Tex.Width );
				
				for ( unsigned int idx3 = 0; idx3 < Tex.PixelSize; idx3++ ) {
					unsigned char Old = Tex.Pixels[ idx ];
					Tex.Pixels[ idx ] = Tex.Pixels[ idx2 ];
					Tex.Pixels[ idx2 ] = Old;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void MirrorFilter( cTex& Tex )
{
	{
		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				unsigned int idx = ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width );
				
				unsigned int idx2 = ( (Tex.Width-1-x) * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width );
				
				for ( unsigned int idx3 = 0; idx3 < Tex.PixelSize; idx3++ ) {
					unsigned char Old = Tex.Pixels[ idx + idx3 ];
					Tex.Pixels[ idx + idx3 ] = Tex.Pixels[ idx2 + idx3 ];
					Tex.Pixels[ idx2 + idx3 ] = Old;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FattenFilter( cTex& Tex )
{
	if( Tex.PixelSize == 4 )
	{
		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				for( size_t ColorIdx = 0; ColorIdx < Tex.PixelSize; ++ColorIdx )
				{
					unsigned int Color = 0;
					
					unsigned int idx = ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width ) + ColorIdx;
					
					Color = Tex.Pixels[ idx ] + ( Tex.Pixels[ idx + 1 ] << 8 ) + ( Tex.Pixels[ idx + 2 ] << 16 ) + ( Tex.Pixels[ idx + 3 ] << 24 );
					
					if( Color == 0 && ColorIdx == 0 )
					{
						unsigned int Left = 0;
						unsigned int Right = 0;
						unsigned int Up = 0;
						unsigned int Down = 0;
						
						int ColorCount = 0;
						
//						int RedCount = 0;
//						int GreenCount = 0;
//						int BlueCount = 0;
						
						if( x != 0 )
						{
							Left = Tex.Pixels[ idx - 4 ] 
								 + ( Tex.Pixels[ idx - 3 ] << 8 ) 
								 + ( Tex.Pixels[ idx - 2 ] << 16 ) 
								 + ( Tex.Pixels[ idx - 1 ] << 24 );

							if ( Left != 0 )
								ColorCount++;
								
//							if( Tex.Pixels[ idx - 4 ] != 0 )
//								RedCount++;
//							if( Tex.Pixels[ idx - 3 ] != 0 )
//								GreenCount++;
//							if( Tex.Pixels[ idx - 2 ] != 0 )
//								BlueCount++;
						}
						if( x != Tex.Width - 2 )
						{
							Right = Tex.Pixels[ idx + 4 ] 
								  + ( Tex.Pixels[ idx + 5 ] << 8 ) 
								  + ( Tex.Pixels[ idx + 6 ] << 16 ) 
								  + ( Tex.Pixels[ idx + 7 ] << 24 );

							if ( Right != 0 )
								ColorCount++;
								  
//							if( Tex.Pixels[ idx + 4 ] != 0 )
//								RedCount++;
//							if( Tex.Pixels[ idx + 5 ] != 0 )
//								GreenCount++;
//							if( Tex.Pixels[ idx + 6 ] != 0 )
//								BlueCount++;

						}
						if( y != 0 )
						{
							Up = Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) ]
							   + ( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 1 ] << 8 )
							   + ( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 2 ] << 16 )
							   + ( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 3 ] << 24 );

							if ( Up != 0 )
								ColorCount++;
							   
//							if( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) ] != 0 )
//								RedCount++;
//							if( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 1 ] != 0 )
//								GreenCount++;
//							if( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 2 ] != 0 )
//								BlueCount++;
						}
						if( y < Tex.Height - 2 )
						{
							Down = Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) ]
							   	 + ( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 1 ] << 8 )
							  	 + ( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 2 ] << 16 )
							  	 + ( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 3 ] << 24 );

							if ( Down != 0 )
								ColorCount++;
							  	 
//							if( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) ] != 0 )
//								RedCount++;
//							if( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 1 ] != 0 )
//								GreenCount++;
//							if( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 2 ] != 0 )
//								BlueCount++;

						}
						
						
						
						unsigned int TempColor = (Left & 0xff) + (Right & 0xff) + (Up & 0xff) + (Down & 0xff);
						
						if( ColorCount != 0 )
						{
							TempColor /= ColorCount;
						}
						
						Tex.Pixels[ idx ] = TempColor;

						TempColor = (( Left >> 8 ) & 0xff) + (( Right >> 8 ) & 0xff) + (( Up >> 8 ) & 0xff) + (( Down >> 8 ) & 0xff);
						
						if( ColorCount != 0 )
						{
							TempColor /= ColorCount;
						}
						
						Tex.Pixels[ idx + 1 ] = TempColor;
												
						TempColor = (( Left >> 16 ) & 0xff) + (( Right >> 16 ) & 0xff) + (( Up >> 16 ) & 0xff) + (( Down >> 16 ) & 0xff);

						if( ColorCount != 0 )
						{
							TempColor /= ColorCount;
						}
						
						Tex.Pixels[ idx + 2 ] = TempColor;

					}
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void HalfFilter( cTex& Tex )
{
	size_t NewWidth = ( Tex.Width / 2 );
	size_t NewHeight = ( Tex.Height / 2 );
	
	char* HalfedImage = new char[ NewWidth * NewHeight * Tex.PixelSize ];
	
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
void BlackKeyFilter( cTex& Tex )
{
	if( Tex.PixelSize == 4 )
	{
		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				unsigned int idx = ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width );
				if( Tex.Pixels[ idx ] == 0 &&
					Tex.Pixels[ idx + 1 ] == 0 &&
					Tex.Pixels[ idx + 2 ] == 0 )
				{
					Tex.Pixels[ idx + 3 ] = 0;
				}
				else
				{
					Tex.Pixels[ idx + 3 ] = 255;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void WhiteFilter( cTex& Tex, int SWhite )
{
	if( Tex.PixelSize == 4 )
	{
		int MaxColor = 255;

		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				unsigned int idx = ( ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width ) );
					
				if( ( Tex.Pixels[ idx + 3 ] & 0xff ) == 0 )
				{
					Tex.Pixels[ idx ] = MaxColor;
					Tex.Pixels[ idx + 1 ] = MaxColor;
					Tex.Pixels[ idx + 2 ] = MaxColor;
										
				}
				else
				{
					Tex.Pixels[ idx ] = MaxColor;
					Tex.Pixels[ idx + 1 ] = MaxColor;
					Tex.Pixels[ idx + 2 ] = MaxColor;
					Tex.Pixels[ idx + 3 ] = MaxColor;
				}
			}
		}

		MaxColor = 128;

		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				unsigned int idx = ( ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width ) );

				if( SWhite == 0 || SWhite >= 2 )
				{
					bool IsUp = false;
					bool IsDown = false;

					if( y != 0 ) // Add white below and check the upper pixel //
					{
						if( ( ( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 3 ] ) == 255 ) )
						{
							if( Tex.Pixels[ idx+3 ] == 0 )
							{
								if( SWhite <= 2 )
								{
									Tex.Pixels[ idx ] = MaxColor;
									Tex.Pixels[ idx + 1 ] = MaxColor;
									Tex.Pixels[ idx + 2 ] = MaxColor;
									Tex.Pixels[ idx + 3 ] = MaxColor;
								}
							}
							else
							{
								IsUp = true;
							}
						}  
					} 
					if( y < Tex.Height - 2 ) // Add white above and check the lower pixel //
					{
						if( ( ( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 3 ] ) == 255 ) )
						{
							if( Tex.Pixels[ idx+3 ] == 0 )
							{
								if( SWhite <= 2 )
								{
									Tex.Pixels[ idx ] = MaxColor;
									Tex.Pixels[ idx + 1 ] = MaxColor;
									Tex.Pixels[ idx + 2 ] = MaxColor;
									Tex.Pixels[ idx + 3 ] = MaxColor;
								}
							}
							else
							{							
								IsDown = true;
							}
						}  
					}
					if( IsUp && IsDown && Tex.Pixels[ idx + 3 ] == 255 )
					{
						if( x != 0 && SWhite == 5 )
						{
							Tex.Pixels[ idx - 4 + 0 ] = MaxColor;
							Tex.Pixels[ idx - 4 + 1 ] = MaxColor;
							Tex.Pixels[ idx - 4 + 2 ] = MaxColor;
							Tex.Pixels[ idx - 4 + 3 ] = MaxColor;
						}
						if( x != Tex.Width - 2 && SWhite == 6 )
						{
							Tex.Pixels[ idx + 4 + 0 ] = MaxColor;
							Tex.Pixels[ idx + 4 + 1 ] = MaxColor;
							Tex.Pixels[ idx + 4 + 2 ] = MaxColor;
							Tex.Pixels[ idx + 4 + 3 ] = MaxColor;
						}
					}
				}
				if( SWhite == 1 || SWhite >= 2 )
				{
					bool IsLeft = false;
					bool IsRight = false;
									
					if( x != 0 ) // Add white to the right and check the left pixel //
					{
						if( ( ( Tex.Pixels[ idx - 4 + 3 ] ) == 255 ) )
						{
							if( Tex.Pixels[ idx+3 ] == 0 )
							{
								if( SWhite <= 2 )
								{
									Tex.Pixels[ idx ] = MaxColor;
									Tex.Pixels[ idx + 1 ] = MaxColor;
									Tex.Pixels[ idx + 2 ] = MaxColor;
									Tex.Pixels[ idx + 3 ] = MaxColor;
								}
							}
							else
							{
								IsLeft = true;
							}
						}
					}
					if( x != Tex.Width - 2 ) // Add white to the left and check the right pixel //
					{
						if( ( ( Tex.Pixels[ idx + 4 + 3 ] ) == 255 ) )
						{
							if( Tex.Pixels[ idx+3 ] == 0 )
							{
								if( SWhite <= 2 )
								{
									Tex.Pixels[ idx ] = MaxColor;
									Tex.Pixels[ idx + 1 ] = MaxColor;
									Tex.Pixels[ idx + 2 ] = MaxColor;
									Tex.Pixels[ idx + 3 ] = MaxColor;
								}
							}
							else
							{
								IsRight = true;
							}
						}
					}
					if( IsLeft && IsRight && Tex.Pixels[ idx + 3 ] == 255 )
					{
						if( y != 0 && SWhite == 3 )
						{
							Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 0 ] = MaxColor;
							Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 1 ] = MaxColor;
							Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 2 ] = MaxColor;
							Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 3 ] = MaxColor;
						} 
						if( y < Tex.Height - 2  && SWhite == 4 )
						{
							Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 0 ] = MaxColor;
							Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 1 ] = MaxColor;
							Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 2 ] = MaxColor;
							Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 3 ] = MaxColor;
						}
					}
					
				}						
			/*	else
				{
					// Angle ones //
					if( y < Tex.Height - 2 && x != Tex.Width - 2 ) // upper left //
					{
						if( ( ( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) - 4 + 3 ] ) == 255 ) && Tex.Pixels[ idx + 3 ] == 0 )
						{
							Tex.Pixels[ idx ] = MaxColor;
							Tex.Pixels[ idx + 1 ] = MaxColor;
							Tex.Pixels[ idx + 2 ] = MaxColor;
							Tex.Pixels[ idx + 3 ] = MaxColor;
						}  
					}
					if( y < Tex.Height - 2 && x != Tex.Width - 2 ) // upper right //
					{
						if( ( ( Tex.Pixels[ idx + ( Tex.Width * Tex.PixelSize ) + 4 + 3 ] ) == 255 ) && Tex.Pixels[ idx + 3 ] == 0 )
						{
							Tex.Pixels[ idx ] = MaxColor;
							Tex.Pixels[ idx + 1 ] = MaxColor;
							Tex.Pixels[ idx + 2 ] = MaxColor;
							Tex.Pixels[ idx + 3 ] = MaxColor;
						}  
					}
					
					if( y != 0 && x != 0 ) // lower left //
					{
						if( ( ( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) - 4 + 3 ] ) == 255 ) && Tex.Pixels[ idx + 3 ] == 0 )
						{
							Tex.Pixels[ idx ] = MaxColor;
							Tex.Pixels[ idx + 1 ] = MaxColor;
							Tex.Pixels[ idx + 2 ] = MaxColor;
							Tex.Pixels[ idx + 3 ] = MaxColor;
						}  
					} 
					if( y != 0 && x != 0 ) // lower right //
					{
						if( ( ( Tex.Pixels[ idx - ( Tex.Width * Tex.PixelSize ) + 4 + 3 ] ) == 255 ) && Tex.Pixels[ idx + 3 ] == 0 )
						{
							Tex.Pixels[ idx ] = MaxColor;
							Tex.Pixels[ idx + 1 ] = MaxColor;
							Tex.Pixels[ idx + 2 ] = MaxColor;
							Tex.Pixels[ idx + 3 ] = MaxColor;
						}  
					}
				}*/
			}
		}
		
		for( size_t y = 0; y < Tex.Height; ++y )
		{
			for( size_t x = 0; x < Tex.Width; ++x )
			{
				unsigned int idx = ( ( x * Tex.PixelSize ) + ( y * Tex.PixelSize * Tex.Width ) );
					
				if( ( Tex.Pixels[ idx + 3 ] & 0xff ) == MaxColor )
				{
					Tex.Pixels[ idx ] = 255;
					Tex.Pixels[ idx + 1 ] = 255;
					Tex.Pixels[ idx + 2 ] = 255;
					Tex.Pixels[ idx + 3 ] = 255;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void PowerOfTwoFilter( cTex& Tex, int RoundUp, bool isSmooth )
{
	cTex NewTex;
	
	NewTex.PixelSize = Tex.PixelSize;
	
	unsigned int NewWidth = 1;
	unsigned int NewHeight = 1;
	while( NewWidth < Tex.Width )
	{
		NewWidth *= 2;
	}
	while( NewHeight < Tex.Height )
	{
		NewHeight *= 2;
	}
	
	if( RoundUp == 0 )
	{
		// Will round the texture height down to the nearest power of two
		NewTex.Height = NewHeight / 2;
	}
	else if( RoundUp == 1 )
	{
		// Will round the texture height up to the nearest power of two
		NewTex.Height = NewHeight;
	}
	else if( RoundUp == 2 )
	{
		if( NewHeight - Tex.Height <= Tex.Height - (NewHeight / 2) )
		{
			// Will round the texture height to the nearest power of two
			NewTex.Height = NewHeight;
		}
		else
		{
			// Will round the texture height to the nearest power of two
			NewTex.Height = NewHeight / 2;
		}
	}

	NewTex.Width = Tex.Width;
	
	NewTex.Pixels = new unsigned char[ NewWidth * NewHeight * NewTex.PixelSize ];

	float TexHeightOffset = (float)Tex.Height / (float)NewTex.Height;

	if( NewTex.PixelSize == 4 )
	{
		if( isSmooth )
		{
			int IdxTracker = 0;
			for( size_t y = 0; y < NewTex.Height; ++y )
			{
				for( size_t x = 0; x < NewTex.Width; ++x )
				{
					for( size_t ColorIdx = 0; ColorIdx < NewTex.PixelSize; ++ColorIdx )
					{
						unsigned int TempColor = 0;
						unsigned int Color = 0;
												
						unsigned int NewIdx = ( ( x * NewTex.PixelSize ) + ( y * NewTex.PixelSize * NewTex.Width ) + ColorIdx );
						unsigned int idx = ( ( x * NewTex.PixelSize ) + ( ( int( (float)y * TexHeightOffset ) * NewTex.PixelSize * NewTex.Width ) ) + ColorIdx );
						unsigned int TempIdx = idx;
						if( y > 0 )
						{
							TempIdx -= ( Tex.Width * NewTex.PixelSize + 4 );
						}
						
						//TempColor = Tex.Pixels[ TempIdx ] + ( Tex.Pixels[ TempIdx + 1 ] << 8 ) + ( Tex.Pixels[ TempIdx + 2 ] << 16 ) + ( Tex.Pixels[ TempIdx + 3 ] << 24 );
						//Color = Tex.Pixels[ idx ] + ( Tex.Pixels[ idx + 1 ] << 8 ) + ( Tex.Pixels[ idx + 2 ] << 16 ) + ( Tex.Pixels[ idx + 3 ] << 24 );
						
						//TempColor = Tex.Pixels[ TempIdx ] + ( Tex.Pixels[ TempIdx + 1 ] << 8 ) + ( Tex.Pixels[ TempIdx + 2 ] << 16 ) + ( Tex.Pixels[ TempIdx + 3 ] << 24 );
						
						if( IdxTracker == idx )
						{
							Color = Tex.Pixels[ idx ] + ( Tex.Pixels[ idx + 1 ] << 8 ) + ( Tex.Pixels[ idx + 2 ] << 16 ) + ( Tex.Pixels[ idx + 3 ] << 24 );
						}
						else
						{
							IdxTracker = idx;
							
							int Red = ( ( int( Tex.Pixels[ idx ] ) + int( Tex.Pixels[ TempIdx ] ) ) / 2 );
							int Green = ( ( int( Tex.Pixels[ idx + 1 ] ) + int( Tex.Pixels[ TempIdx + 1 ] ) ) / 2 );
							int Blue = ( ( int( Tex.Pixels[ idx + 2 ] ) + int( Tex.Pixels[ TempIdx + 2 ] ) ) / 2 );
							int Alpha = ( ( int( Tex.Pixels[ idx + 3 ] ) + int( Tex.Pixels[ TempIdx + 3 ] ) ) / 2 );
							if( int( Tex.Pixels[ idx + 3 ] ) == 0 )
							{
							//	Alpha = int( Tex.Pixels[ TempIdx + 3 ] );
							}
							else if( int( Tex.Pixels[ TempIdx + 3 ] ) == 0 )
							{
							//	Alpha = int( Tex.Pixels[ idx + 3 ] );
							}
							
							Color = Red + ( Green << 8 ) + ( Blue << 16 ) + ( Alpha << 24 );
						}
						IdxTracker += 1;
								
						NewTex.Pixels[NewIdx] = Color;
						
					}
				}
			}			
		}
		else
		{
			for( size_t y = 0; y < NewTex.Height; ++y )
			{
				for( size_t x = 0; x < NewTex.Width; ++x )
				{
					for( size_t ColorIdx = 0; ColorIdx < NewTex.PixelSize; ++ColorIdx )
					{
						unsigned int Color = 0;
						
						unsigned int NewIdx = ( ( x * NewTex.PixelSize ) + ( y * NewTex.PixelSize * NewTex.Width ) + ColorIdx );
						unsigned int idx = ( ( x * NewTex.PixelSize ) + ( ( int( (float)y * TexHeightOffset ) * NewTex.PixelSize * NewTex.Width )  ) + ColorIdx );

						Color = Tex.Pixels[ idx ] + ( Tex.Pixels[ idx + 1 ] << 8 ) + ( Tex.Pixels[ idx + 2 ] << 16 ) + ( Tex.Pixels[ idx + 3 ] << 24 );

						NewTex.Pixels[NewIdx] = Color;
						
					}
				}
			}
		}

		if( RoundUp == 0 )
		{
			// Will round the texture width down to the nearest power of two
			NewTex.Width = NewWidth / 2;
		}
		else if( RoundUp == 1 )
		{
			// Will round the texture width up to the nearest power of two
			NewTex.Width = NewWidth;
		}
		else if( RoundUp == 2 )
		{
			if( NewWidth - Tex.Width <= Tex.Width - (NewWidth / 2) )
			{
				// Will round the texture width to the nearest power of two
				NewTex.Width = NewWidth;
			}
			else
			{
				// Will round the texture width to the nearest power of two
				NewTex.Width = NewWidth / 2;
			}
		}
		
		
		if( isSmooth )
		{
			cTex TempTex;
			TempTex.Pixels = new unsigned char[ NewWidth * NewHeight * NewTex.PixelSize ];
			memcpy( TempTex.Pixels, NewTex.Pixels, NewWidth * NewHeight * NewTex.PixelSize );

			float TexWidthOffset = (float)Tex.Width / (float)NewTex.Width;
			
			int IdxTracker = 0;
			
			for( size_t y = 0; y < NewTex.Height; ++y )
			{
				for( size_t x = 0; x < NewTex.Width; ++x )
				{
					for( size_t ColorIdx = 0; ColorIdx < NewTex.PixelSize; ++ColorIdx )
					{
						unsigned int Color = 0;
						
						unsigned int NewIdx = ( ( x * NewTex.PixelSize ) + ( y * NewTex.PixelSize * NewTex.Width ) + ColorIdx );
						unsigned int idx = ( ( int( float( x * TexWidthOffset ) ) * NewTex.PixelSize ) + ( ( y * NewTex.PixelSize * Tex.Width ) ) + ColorIdx );
						unsigned int TempIdx = idx;
						if( x > 0 )
						{
							TempIdx -= 1 * NewTex.PixelSize;
						}

						if( IdxTracker == idx )
						{
							Color = TempTex.Pixels[ idx ] + ( TempTex.Pixels[ idx + 1 ] << 8 ) + ( TempTex.Pixels[ idx + 2 ] << 16 ) + ( TempTex.Pixels[ idx + 3 ] << 24 );
						}
						else
						{
							IdxTracker = idx;
								
							int Red = ( ( int( TempTex.Pixels[ idx ] ) + int( TempTex.Pixels[ TempIdx ] ) ) / 2 );
							int Green = ( ( int( TempTex.Pixels[ idx + 1 ] ) + int( TempTex.Pixels[ TempIdx + 1 ] ) ) / 2 );
							int Blue = ( ( int( TempTex.Pixels[ idx + 2 ] ) + int( TempTex.Pixels[ TempIdx + 2 ] ) ) / 2 );
							int Alpha = ( ( int( TempTex.Pixels[ idx + 3 ] ) + int( TempTex.Pixels[ TempIdx + 3 ] ) ) / 2 );
							if( int( TempTex.Pixels[ idx + 3 ] ) == 0 )
							{
							//	Alpha = int( TempTex.Pixels[ TempIdx + 3 ] );
							}
							else if( int( TempTex.Pixels[ TempIdx + 3 ] ) == 0 )
							{
							//	Alpha = int( TempTex.Pixels[ idx + 3 ] );
							}
							
							Color = Red + ( Green << 8 ) + ( Blue << 16 ) + ( Alpha << 24 );
						}
						IdxTracker += 1;

						NewTex.Pixels[NewIdx] = Color;
						
					}
				}
			}
		}
		else
		{
			cTex TempTex;
			TempTex.Pixels = new unsigned char[ NewWidth * NewHeight * NewTex.PixelSize ];
			memcpy( TempTex.Pixels, NewTex.Pixels, NewWidth * NewHeight * NewTex.PixelSize );

			float TexWidthOffset = (float)Tex.Width / (float)NewTex.Width;
			
			for( size_t y = 0; y < NewTex.Height; ++y )
			{
				for( size_t x = 0; x < NewTex.Width; ++x )
				{
					for( size_t ColorIdx = 0; ColorIdx < NewTex.PixelSize; ++ColorIdx )
					{

						unsigned int Color = 0;
						
						unsigned int NewIdx = ( ( x * NewTex.PixelSize ) + ( y * NewTex.PixelSize * NewTex.Width ) + ColorIdx );
						unsigned int idx = ( ( int( float( x * TexWidthOffset ) ) * NewTex.PixelSize ) + ( ( y * NewTex.PixelSize * Tex.Width ) ) + ColorIdx );
					
						Color = TempTex.Pixels[ idx ] + ( TempTex.Pixels[ idx + 1 ] << 8 ) + ( TempTex.Pixels[ idx + 2 ] << 16 ) + ( TempTex.Pixels[ idx + 3 ] << 24 );
						NewTex.Pixels[NewIdx] = Color;
						
					}
				}
			}
		}
	}

	Tex = NewTex;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
