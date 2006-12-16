// - ------------------------------------------------------------------------------------------ - //
// Font //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_Font_H__
#define __Util_Font_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "Block.h"
// - ------------------------------------------------------------------------------------------ - //
class cFont
{
public:
	std::vector< cBlock > Block;
		
	cFont()
	{
		
	}
	
	size_t TextureWidth;
	size_t TextureHeight;
		
	void Load( std::string &File );
	cCharacter& FindCharacter( int CharacterIdx );
	void Write( const std::string &Text, Vector3D Pos, const Real Size, const int Color );
	void Write( const std::string &Text, Vector2D Pos, const Real Size, const int Color );
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Font_H__ //
// - ------------------------------------------------------------------------------------------ - //
