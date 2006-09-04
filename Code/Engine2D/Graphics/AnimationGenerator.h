// - ------------------------------------------------------------------------------------------ - //
// AnimationGenerator //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Graphics_AnimationGenerator_H__
#define __Engine2D_Graphics_AnimationGenerator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cAnimationGenerator {
public:
	std::string Directory;
	std::vector< SDL_Surface* > ImagePool;
		
	std::vector< std::string > Folder;

public:
	cAnimationGenerator( std::string _Directory ) :
		Directory( _Directory )
	{
		Load();
	}
	
public:
	void Load();
};
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Graphics_AnimationGenerator_H__ //
// - ------------------------------------------------------------------------------------------ - //
