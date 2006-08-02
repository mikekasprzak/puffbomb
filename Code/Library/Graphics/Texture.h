// - ------------------------------------------------------------------------------------------ - //
// Texture //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_Texture_H__
#define __Util_Texture_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cTexture
{
public:
	unsigned int PixelSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int ID;  // Prob GL specific //
	
	void* Pixels;
	
	char* Buffer;

public:
	void Load( const std::string& FileName );

public:
	cTexture()
	{
		
	}
	
	cTexture( const std::string& FileName ) :
		PixelSize( 0 ),
		Width( 0 ),
		Height( 0 ),
		ID( 0 )
	{
		Load( FileName );	
	}
	

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Texture_H__ //
// - ------------------------------------------------------------------------------------------ - //
