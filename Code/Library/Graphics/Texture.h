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
	unsigned int Id;  // Prob GL specific //
		
	void* Pixels;
	

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
		Id( 0 )
	{
		Load( FileName );	
	}
	

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Texture_H__ //
// - ------------------------------------------------------------------------------------------ - //
