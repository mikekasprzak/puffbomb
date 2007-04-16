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
// Alignments //
#define LEFT_ALIGN		0
#define RIGHT_ALIGN		1
#define CENTER_ALIGN	2
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
		
	void Load( const std::string &File );
	cCharacter& FindCharacter( int CharacterIdx );
	void Write( const std::string &Text, Vector3D Pos, const Real Size, const int Color, const int Alignment = LEFT_ALIGN );
	void Write( const std::string &Text, const Vector2D Pos, const Real Size, const int Color, const int Alignment = LEFT_ALIGN );
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Font_H__ //
// - ------------------------------------------------------------------------------------------ - //
