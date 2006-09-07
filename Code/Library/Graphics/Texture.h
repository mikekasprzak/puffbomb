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
	typedef unsigned int IdType;
	
	unsigned int PixelSize;
	unsigned int Width;
	unsigned int Height;
	
	IdType Id;  // Prob GL specific //
		
	void* Pixels;

#ifdef EDITOR
	std::string FileName;
#endif // EDITOR //
public:
	void Load( const std::string& _FileName );

public:
	cTexture()
	{
		
	}
	
	cTexture( const std::string& _FileName ) :
		PixelSize( 0 ),
		Width( 0 ),
		Height( 0 ),
		Id( 0 )
	{
		Load( _FileName );
	}
	

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Texture_H__ //
// - ------------------------------------------------------------------------------------------ - //
