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
	
	class cImage {
	public:
		SDL_Surface* Image;
		unsigned int CRC;
		std::string FileName;
	
	public:
		cImage() :
			Image( 0 ),
			CRC( 0 )
		{
		}
		
		cImage( SDL_Surface* _Image, unsigned int _CRC, std::string _FileName ) :
			Image( _Image ),
			CRC( _CRC ),
			FileName( _FileName )
		{
		}
	};

	std::vector< cImage > ImagePool;
	
	
	class cAnimation {
	public:	
		class cAnimationFrame {
		public:
			size_t ImageIndex;
			
		public:
			cAnimationFrame() :
				ImageIndex( 0 )
			{
			}
		};
		
		// How many ticks to hold a frame for //
		int FrameHold;
		std::string DirectoryName;
		
		std::vector< cAnimationFrame > Frame;
			
	public:
		cAnimation() :
			FrameHold( 3 )
		{
		}
	};
	
	std::vector< cAnimation > Animation;


public:
	cAnimationGenerator( std::string _Directory ) :
		Directory( _Directory )
	{
		Load();
	}
	
	~cAnimationGenerator() {
		for ( size_t idx = 0; idx < ImagePool.size(); idx++ ) {
			if ( ImagePool[ idx ].Image )
				SDL_FreeSurface( ImagePool[ idx ].Image );
		}
	}
		
public:
	void Load();
};
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Graphics_AnimationGenerator_H__ //
// - ------------------------------------------------------------------------------------------ - //
